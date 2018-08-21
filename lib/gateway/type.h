/*
 * gateway/type.h
 *
 * Copyright (c) 2018.
 * YongJun Kim <StaySharp0@gmail.com>
 *
 */

#ifndef gateway_type_h
#define gateway_type_h

#include <json.h>

#define TRUE 1
#define FALSE -1

#define WORKER_API_REQUIRE 0
#define WORKER_RUN 1
static const char* pipe_msg[] = {
    "Please Modify config/server.json!",
    "Running"
};

#define PROC_MAIN 0
#define PROC_MANAGER 1
#define PROC_WORKER 2
static const char* process_name[] = {
    "Main",
    "Manager",
    "Woker"
};

typedef struct _CONFIG{
    json_object* server;
    json_object* sensor_list;
} CONFIG;

#define SELF_SOCKS_SIZE 4
#define SOCKET_CLOSE -2
#define PIPE_BUF_SZIE 30
typedef struct _SELF{
    CONFIG* config;
    int procType; // 0:parent 1:sub-parent 2:child
    char pipe_buf[PIPE_BUF_SZIE];
    int fd[2];
    
    // socket;
    int socks[SELF_SOCKS_SIZE];
    int socks_port[SELF_SOCKS_SIZE];
    int idx_socks; // avail idx
} SELF;


#define SENSOR_LOG_TABLE_NAME "SensorLog"
#define SENSOR_LOG_TABLE_CREATE "(Id INT, Value TEXT, Time TEXT)"
typedef struct _PACKET{
    int id;
    char* value;
    char* cur_time;
} PACKET;

#define SF_MSG_SIZE 255
// typedef struct _SF_MSG{
//     char pkg[SF_MSG_SIZE];
// } SF_MSG;

#endif