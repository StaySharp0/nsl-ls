/*
 * gatway/config.h
 *
 * Copyright (c) 2018.
 * YongJun Kim <StaySharp0@gmail.com>
 *
 */

#ifndef gateway_config_h
#define gateway_config_h

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <json.h>
#include <sqlite3.h>

#include "type.h"

#define SNLIST_JPATH "config/sensor_list.json"
#define SERVER_JPATH "config/server.json"

#define DB_PATH "config/localStorage.db"

#define MANAGER_PATH "config/manager.txt"
#define WORKER_PATH  "config/worker.txt"

/*
sensor_list.json
./
{
    struct route/NODE { ptr },
    int { child_no },
    int { total_no },
    child : {
        struct route/NODE { ptr } 
        int child_no,
        int total_no,
        child : { ... },
    }
}
*/
int init_config_sensor_list(CONFIG*);

/*
server.json
{
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
    server:
    {
        baseURL: 'http://api.test.com',
        authKey: 'nslnslnslnsl'
    }   
}
*/
int init_config_server(CONFIG*);

int config_get_pid (int); 
void config_set_pid(int, int);

void free_json(CONFIG*);

#endif
