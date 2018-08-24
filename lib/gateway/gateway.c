#include "gateway.h"

// Global variable
SELF* self = NULL;

void intHandler() {
    free_gateway();

    exit(0);
}

void init_self(){
    signal(SIGINT, intHandler);

    self = (SELF*) malloc (sizeof(SELF));
    self->config = NULL;

    memset(self->socks, FALSE, sizeof(self->socks));
    memset(self->socks_port, FALSE, sizeof(self->socks));
    self->idx_socks = 0;

    debugMsg(self, "init\n");
}

void free_gateway() {
    int i = 0;
    if(self != NULL){
        // Free config
        if (self->config != NULL){
            debugMsg(self, "free config\n");

            free_json(self->config);
            SAFE_FREE(self->config);
        }

        // Close Socekt
        for (i = 0; i < SELF_SOCKS_SIZE; i ++) {
            if(self->socks[i] != FALSE) close(self->socks[i]);
        }
        debugMsg(self, "free\n");

        SAFE_FREE(self);
    }
}


/*
 * cmd_arg_gateway
 *  - run(0): 24hour running daemon (sf connect & sesnsor data logging)
 *  - console(1): sensor data, sensor network
 *  - update(2): update all sensor data to server(default every time)
 *  - config(3):
 *  - exit(4): exit manager & worker process
 *  - help(...):
 *  - test(...):
 */

const char* cmd_arg[] = {
    "run",
    "console",
    "update",
    "config",
    "exit",
    "help",
};
int cmd_arg_gateway(int argc, char *argv[]){
    int i;
    int idx_cmd_arg = sizeof(cmd_arg) / sizeof(char*);

    if (argc < 2) return -1;

    for (i = 0; i < idx_cmd_arg; i++){
        if(!strcmp(argv[1], cmd_arg[i]))
        {
            return i;
        }
    }

    return -1;
}

void init_gateway(int cmd_status, int argc, char *argv[]){
    int status;
    init_self();
    debugMsg(self, "init_gateway\n");
    
    switch (cmd_status)
    {
        case 0:
            debugMsg(self, "Fn: run\n");
            if ((status = set_daemon(self)) == PROC_WORKER) { 
                fn_run(self);
            }

            break;
        case 1:
            debugMsg(self, "Fn: console\n");

            break;
        case 2:
            debugMsg(self, "Fn: update\n");

            break;
        case 3:
            debugMsg(self, "Fn: config\n");
            break;
        
        case 4:
            fn_exit();
            break;
        case 5:
            debugMsg(self, "Fn: help\n");
            fn_help();
			break;
        default:
            debugMsg(self, "Fn: test\n");

            
            break;
    }

    free_gateway();
}

void fn_help() {
    printf("usage: gatewaye <command> [<args>]\n\n");
    printf("These are common Gateway commands used in various situations:\n\n");
    printf("  run       24hour running daemon (sf connect & sesnsor data logging)\n");
    printf("  console   Ask sensor data, sensor network\n");
    printf("  update    Update all sensor data to server(default every time)\n");
    printf("  config    Setting update period etc...\n");
    printf("  exit      Exit manager & worker process\n\n");
    
}

void fn_exit() {
    int pid;
    int rtn;
    char cmd[100];

    if( (pid = config_get_pid(PROC_MANAGER)) != FALSE ){
        sprintf(cmd, "kill -2 %d", pid);
        rtn = system(cmd);
        if (rtn == 0) {
            sprintf(cmd, "rm %s", MANAGER_PATH);
            system(cmd);
        } else {
            system("ps -ef | grep gate");
            printf("cmd: kill -2 [pid] plz\n");
        }
    } 
    
    if ( (pid = config_get_pid(PROC_WORKER)) != FALSE )
    {
        sprintf(cmd, "kill -2 %d", pid);
        rtn = system(cmd);
        if (rtn == 0) {
            sprintf(cmd, "rm %s", WORKER_PATH);
            system(cmd);
        } else {
            system("ps -ef | grep gate");
            printf("cmd: kill -2 [pid] plz\n");
        }
    }
    
}
