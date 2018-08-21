#include "socket.h"

void set_thread_exit() { exitRequested = 1; }

void init_socket_config(SELF *_self) {
    self = _self;
    json_object *sf_jobj, *server_jobj;

    json_object_object_get_ex(self->config, "sf", &sf_jobj);            //json-object
    // json_object_object_get_ex(self->config, "server", &server_jobj);    //json-array
    
    _init_sf(sf_jobj);
    //_init_server(server_jobj);
}

void _init_sf(json_object *sf_list) {
    int i = 0;
    int err;
    int thread_num = 0;
    char *sf_command = (char*) malloc (SF_COMMAND_SIZE * sizeof(char));
    char *tty, *port, *borderate;
    json_object* pointer;
    SF_THREAD_ARGS args;

    json_object_object_length(sf_list, thread_num);
    sf_threads = (pthread_t*) malloc (thread_num * sizeof(pthread_t));
    sf_sockets = (int *) malloc (thread_num * sizeof(int));
    sf_count = thread_num;

    json_object_object_foreach(sf_list, key, val) {
        printf("%s\n", json_object_to_json_string(val));
        pointer     = find_object_by_key(val, "tty");
        tty         = (char *) json_object_get_string(pointer);
        pointer     = find_object_by_key(val, "port");
        port        = (char *) json_object_get_string(pointer);
        pointer     = find_object_by_key(val, "borderate");
        borderate   = (char *) json_object_get_string(pointer);

        // sf 9000 /dev/ttyS1 115200 &
        sprintf(sf_command, "%s %s %s %s &", SF_PATH, port, tty, borderate);

        printf("%s\n", sf_command);
        // system(sf_command);
        sleep(2); // wait loading sf module

        // create sf module socket threads
        args.thread_id = i;
        args.port = atoi(port);
        err = pthread_create(sf_threads + i, NULL, &sf_connection_handler, (void*) &args);
		if(err != 0){
			printf("Error creating sf thread %d: %s\n", i + 1, strerror(err));
		}else{
			printf("Successfully created sf thread %d\n", i + 1);
		}
        sleep(2);
        i++;
    }

    free(sf_command);
}

void* sf_connection_handler(void *_args){
    SF_THREAD_ARGS *args = (SF_THREAD_ARGS*) _args;

    int thread_id = args->thread_id;
    int sock_desc;
    struct sockaddr_in serv_addr;
    char sbuff[BUF_MAX_SIZE],rbuff[BUF_MAX_SIZE];

    // init socket setting
    bzero((char *) &serv_addr, sizeof (serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(args->port);

    // create socket 
    if((sock_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Failed creating socket\n");
    }
    sf_sockets[thread_id] = sock_desc;

    // connection socket
    if (connect(sock_desc, (struct sockaddr *) &serv_addr, sizeof (serv_addr)) < 0) {
        printf("Failed to connect to server\n");
        // return 0;
    }
    
    printf("Connected successfully Sf socket: %d\n", thread_id);
    while(!exitRequested) {
        if(recv(sock_desc, rbuff, BUF_MAX_SIZE, 0) == 0){
            //printf("Error");
        }
        else{
            fputs(rbuff, stdout);
            //PKG pkg = get_sf_packekt(rbuff);
            /*
            
            */
            bzero(rbuff, BUF_MAX_SIZE);
        }
    }

    close(sock_desc);

    return 0;


	// while(1) {
	// 	int p = produce(pthread_self());
	// 	sem_wait(&empty_count);
	// 	sem_wait(&buf_mutex);
	// 	++buf_pos;			// critical section
	// 	*(buf + buf_pos) = p; 
	// 	sem_post(&buf_mutex);
	// 	sem_post(&fill_count);
	// 	sleep(1 + rand()%3);
	// }
}

// int produce(pthread_t self){
// 	int i = 0;
// 	int p = 1 + rand()%40;
// 	while(!pthread_equal(*(producers+i),self) && i < prod_count){
// 		i++;
// 	}
// 	printf("Producer %d produced %d \n",i+1,p);
// 	return p;
// }


void _init_server(json_object *server_list) {
    // int i;
    // int thread_num = json_object_array_length(server_list);
    // char *name, *ip, *port;
    // json_object *jobj, *pointer;
    // SERVER_THREAD_ARGS args;

    // server_threads = (pthread_t*) malloc(thread_num * sizeof(pthread_t));
    // server_sockets = (int *) malloc (thread_num * sizeof(int));
    // server_count = thread_num;

    // for (i = 0; i < thread_num; i++) {
    //     jobj = json_object_array_get_idx(server_list, i);
    //     printf("%s\n",json_object_to_json_string(jobj));
		
    //     pointer     = find_object_by_key(jobj, "name");
    //     name        = (char *) json_object_get_string(pointer);
    //     pointer     = find_object_by_key(val, "ip");
    //     ip          = (char *) json_object_get_string(pointer);
    //     pointer     = find_object_by_key(val, "port");
    //     port        = (char *) json_object_get_string(pointer);
        
    //     args.thread_id = i;
    //     args.name = name;
    //     args.ip = ip
    //     args.port = atoi(port);

    //     err = pthread_create(server_threads + i, NULL, &server_connection_handler, (void*) &args);
	// 	if(err != 0){
	// 		printf("Error creating server thread %d: %s\n", i + 1, strerror(err));
	// 	}else{
	// 		printf("Successfully created server thread %d\n", i + 1);
	// 	}
    //     sleep(2);
    //     i++;
	// }
}

void* sever_connection_handler(void *_args){
    // SERVER_THREAD_ARGS *args = (SERVER_THREAD_ARGS*) _args;
    // int i;
    // int thread_id = args->thread_id;
    // int sock_desc;
    // struct sockaddr_in serv_addr;
    // char sbuff[BUF_MAX_SIZE],rbuff[BUF_MAX_SIZE];
    // fd_set active_fd_set, read_fd_set;

    // // init socket setting
    // bzero((char *) &serv_addr, sizeof (serv_addr));
    // serv_addr.sin_family = AF_INET;
    // serv_addr.sin_addr.s_addr = inet_addr(args->ip);
    // serv_addr.sin_port = htons(args->port);

    // // create socket 
    // if((sock_desc = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    //     printf("Failed creating socket\n");
    //     return 1;
    // }
    // server_sockets[thread_id] = sock_desc;

    // // listen socket
	// if (listen(sock_desc, 1) < 0) {
	// 	printf("could not open socket for listening\n");
	// 	return 1;
	// }

    // // Initialize the set of active sockets
    // FD_ZERO (&active_fd_set);
    // FD_SET (sock_desc, &active_fd_set);

    // // Select loop
    // while(!exitRequested) {
    //     read_fd_set = active_fd_set;
        
    //     if (select (FD_SETSIZE, &read_fd_set, NULL, NULL, NULL) < 0) {
    //         printf("could not run select\n");
	// 	    return 1;
    //     }

    //     /* Service all the sockets with input pending. */
    //     for (i = 0; i < FD_SETSIZE; ++i)
    //     {
    //         if (FD_ISSET (i, &read_fd_set)) {
    //             if (i == sock_desc) {
    //                 int new;
    //                 size = sizeof (clientname);
    //                 new = accept (sock,
    //                             (struct sockaddr *) &clientname,
    //                             &size);
    //                 if (new < 0)
    //                 {
    //                     perror ("accept");
    //                     exit (EXIT_FAILURE);
    //                 }
    //                 fprintf (stderr,
    //                         "Server: connect from host %s, port %hd.\n",
    //                         inet_ntoa (clientname.sin_addr),
    //                         ntohs (clientname.sin_port));
    //                 FD_SET (new, &active_fd_set);
    //             }
    //             else {
    //                 if (read_from_client (i) < 0)
    //               {
    //                 close (i);
    //                 FD_CLR (i, &active_fd_set);
    //               }

    //             }
    //         }
    //     }
    // }

    // close(sock_desc);
    // return 0;
}

void run() {
    int i;

    for(i = 0; i < sf_count; i++){
		pthread_join( *(sf_threads + i), NULL);
	}
	for(i = 0; i < server_count; i++){
		pthread_join( *(server_threads+i), NULL);
	}
}

void free_socket() {
    int i;
    set_thread_exit();

    for(i = 0; i < sf_count; i++){
		pthread_join( *(sf_threads + i), NULL);
	}
	for(i = 0; i < server_count; i++){
		pthread_join( *(server_threads+i), NULL);
	}

    free(sf_threads);
    free(sf_sockets);

    free(server_threads);
    free(server_sockets);
}







/*
use the pthread flag with gcc to compile this code
~$ gcc -pthread producer_consumer.c -o producer_consumer
*/




// sem_t buf_mutex,empty_count,fill_count;

// int *buf,buf_pos=-1,prod_count,con_count,buf_len;





// void consume(int p,pthread_t self){
// 	int i = 0;
// 	while(!pthread_equal(*(consumers+i),self) && i < con_count){
// 		i++;
// 	}

// 	printf("Buffer:");
// 	for(i=0;i<=buf_pos;++i)
// 		printf("%d ",*(buf+i));
// 	printf("\nConsumer %d consumed %d \nCurrent buffer len: %d\n",i+1,p,buf_pos);
	
// }




// void* consumer(void *args){
// 	int c;
// 	while(1){
// 		sem_wait(&fill_count);
// 		sem_wait(&buf_mutex);
// 		c = *(buf+buf_pos);
// 		consume(c,pthread_self());
// 		--buf_pos;
// 		sem_post(&buf_mutex);
// 		sem_post(&empty_count);
// 		sleep(1+rand()%5);
// 	}

// 	return NULL;
// }

// int main(void){
	
// 	int i,err;

// 	srand(time(NULL));

// 	sem_init(&buf_mutex,0,1);
// 	sem_init(&fill_count,0,0);

// 	printf("Enter the number of Producers:");
// 	scanf("%d",&prod_count);
// 	producers = (pthread_t*) malloc(prod_count*sizeof(pthread_t));

// 	printf("Enter the number of Consumers:");
// 	scanf("%d",&con_count);
// 	consumers = (pthread_t*) malloc(con_count*sizeof(pthread_t));

// 	printf("Enter buffer capacity:");
// 	scanf("%d",&buf_len);
// 	buf = (int*) malloc(buf_len*sizeof(int));

// 	sem_init(&empty_count,0,buf_len);
