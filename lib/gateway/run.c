#include "run.h"

int set_daemon(SELF* self) {
    int pid;
    int ret;
    char buf[100];
    pipe(self->fd);

    if ((pid = fork()) < 0) {
        fprintf(stderr, "Main Fork Error\n");
        return PROC_MAIN;
    } else if(pid > 0) {
        self->procType = PROC_MAIN;
        return PROC_MAIN; // exit main process
    }

    setsid();
    self->procType = PROC_MANAGER;
    sprintf(buf, "pid %d\n", getpid());
    debugMsg(self, buf);
    config_set_pid(self->procType, getpid());

    while (1) {
        if ((pid = fork()) < 0) { // exit manager process
            fprintf(stderr, "Manager Fork Error\n");
            return PROC_MANAGER; 
        } else if (pid == 0) { // worker process entrance
            self->procType = PROC_WORKER;
            sprintf(buf, "pid %d\n", getpid());
            debugMsg(self, buf);
            
            config_set_pid(self->procType, getpid());
            break;
        } else if(pid > 0) { // wait manager process until the worker dies
            wait(&ret);
            read(self->fd[0], self->pipe_buf, PIPE_BUF_SZIE);
            
            if(!strcmp(self->pipe_buf, pipe_msg[WORKER_API_REQUIRE])){
                printf("\n%s\n\n",self->pipe_buf);
                return PROC_MANAGER;
            }
        }
    }
    
    return PROC_WORKER;
}

void fn_run(SELF* self) {
    int init_status = TRUE;
    self->config = (CONFIG*) malloc (sizeof(CONFIG));

    // OR opration bcz TRUE(1), FALSE(-1) 
    init_status = init_config_sensor_list(self->config);
    init_status |= init_config_server(self->config);
    init_status |= init_storage(self);

    if(init_status == TRUE) {
        write(self->fd[1], pipe_msg[WORKER_RUN], BUFSIZ);

        while(TRUE){
            _run_init_sf(self);
            sleep(2); // wait loading sf module
            _run_sf_connection_handler(self);
        }
    } else {
        write(self->fd[1], pipe_msg[WORKER_API_REQUIRE], BUFSIZ);
    }
}

/*
    sf: 
    {
        sfid(auto increment or bsid packet):
        {
            tty: '/dev/ttyUSB[] (device)',
            port: 9000,
            borderate: 115200,
        },
        ...
    },
*/

void _run_init_sf(SELF* self) {
    json_object *ptr_sf, *ptr;
    char sf_command[100];
    char *tty, *port, *borderate;
    
    // initialize variable
    json_object_object_get_ex(self->config->server, "sf", &ptr_sf);

    json_object_object_foreach(ptr_sf, key, val) {
        // printf("%s\n", json_object_to_json_string(val));
        
        ptr         = find_object_by_key(val, "tty");
        tty         = (char *) json_object_get_string(ptr);
        ptr         = find_object_by_key(val, "port");
        port        = (char *) json_object_get_string(ptr);
        ptr         = find_object_by_key(val, "borderate");
        borderate   = (char *) json_object_get_string(ptr);

        // sf 9000 /dev/ttyS1 115200 &
        sprintf(sf_command, "%s %s %s %s &", SF_PATH, port, tty, borderate);

        // printf("%s\n", sf_command);
        // system(sf_command);
    }
}

void _run_sf_connection_handler(SELF* self) {
    // json
    json_object *ptr_sf = NULL;
    json_object *ptr = NULL;
    int port = 0;

    // iterator
    int i = 0;

    // select
    int state = 0;
    int nfds = 0;
    int sockfd = 0;
    struct timeval tv;
    fd_set readfds;
    char buf[SF_MSG_SIZE];

    // initialize sf_socket
    json_object_object_get_ex(self->config->server, "sf", &ptr_sf);
    json_object_object_foreach(ptr_sf, key, val) {
        ptr     = find_object_by_key(val, "port");
        port    = atoi((char *) json_object_get_string(ptr));

        self->socks[self->idx_socks] = _run_init_socket(self, port);
        self->socks_port[self->idx_socks] = port;
        self->idx_socks++;
    }
    debugMsg(self, "init socket... OK\n");
    
    for (nfds = 0;;) {
        debugMsg(self, "loop select\n");
        tv.tv_sec = 3;
        tv.tv_usec = 0;

        FD_ZERO(&readfds); 
        for (i = 0; i < self->idx_socks; i++) {
            sockfd = self->socks[i];

            if (nfds  < sockfd) nfds = sockfd;
            if (sockfd > 0) FD_SET(sockfd, &readfds);
        }
        debugMsg(self, "FD SET\n");

        printf("%d\n",nfds);

        state = select(nfds + 1, &readfds, 0, 0, &tv);
        debugMsg(self, "select\n");

        for (i = 0; i < self->idx_socks; i++) {
            sockfd = self->socks[i];
            port = self->socks_port[i];

            if (sockfd == FALSE) {
                continue;
            }
            else if (sockfd == SOCKET_CLOSE) {
                self->socks[i] = _run_init_socket(self, port);
            }
            else if (FD_ISSET(sockfd, &readfds)) {
                printf("fd_isset(%d)\n",i);
                memset(buf, 0, SF_MSG_SIZE);

                if (read(sockfd, buf, SF_MSG_SIZE) <= 0) {
                    debugMsg(self, "Close socket\n");
                    close(sockfd);
                    FD_CLR(sockfd, &readfds);
                    self->socks[i] = SOCKET_CLOSE;
                } 
                
                printf("[%d]RECV %s\n", sockfd, buf); 

                // packet logging
                // write(sockfd, buf, 255);
                
                // if (state-- < 0) break;
            } 
        }
        
    }
}

int _run_init_socket(SELF* self, int port){
    int sock;
    struct sockaddr_in server_addr;
    const char* server_name = "127.0.0.1";

    if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0)
    {
        debugMsg(self, "can't create socket\n");
        raise(2);
    }

    // Initialize server_addr -> NULL & Set header 
    bzero((char *)&server_addr, sizeof(server_addr));
    inet_pton(AF_INET, server_name, &server_addr.sin_addr);
    server_addr.sin_port = htons(port);


    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0) {
		debugMsg(self, "could not connect to server\n");
        close(sock);
        return SOCKET_CLOSE;
	}

    return sock;
}
