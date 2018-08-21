// #include <signal.h>
// #include <config.h>
// #include <socket.h>
// #include <json.h>

// SELF* self;
// short chk_exit = 0; // bcz thread m
// void intHandler() {
//     if (!chk_exit) {
//         printf("free\n");
//         free_json(self);
//         printf("free json\n");
//         free_socket();
//         printf("free socket\n");
//         free(self);
//         printf("free self\n");
//         chk_exit = 1;
//     }
// }

#include <gateway.h>

int main(int argc, char *argv[]) {
    int status = 0;
    status = cmd_arg_gateway(argc, argv);
    
    init_gateway(status, argc, argv);

    // self = (SELF*) malloc (sizeof(SELF));
    // signal(SIGINT, intHandler);
    
    // init_sensor_list(self);
    // init_config(self);
    // init_socket(self);

    // run();

    // intHandler();
    
    return 0;
}
// ps -ef|grep "gateway" | grep -v grep |awk '{print "ps -p " $2 " -o vsz,rss"}' | sh


// 상시 가동
// init을 할 필요가 있음
//
