/*
 * gateway/socket.h
 *
 * Copyright (c) 2018.
 * YongJun Kim <StaySharp0@gmail.com>
 *
 */
#ifndef gateway_socket_h
#define gateway_socket_h

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "config.h"
#include "json-util.h"

#define SF_COMMAND_SIZE 100
#define BUF_MAX_SIZE 512
#define SF_PATH "../sf"

SELF *self;
int sf_count, server_count;
pthread_t *sf_threads, *server_threads;
int *sf_sockets, *server_sockets;
volatile sig_atomic_t exitRequested = 0;

typedef struct _SF_THREAD_ARGS{
    int thread_id;
    int port;
} SF_THREAD_ARGS;

typedef struct _SERVER_THREAD_ARGS{
    int thread_id;
    char *name;
    char *ip;
    int port;
} SERVER_THREAD_ARGS;


void init_socket(SELF*);

void run();

void _init_sf(json_object*);
void* sf_connection_handler(void *args);

void _init_server();
void* sever_connection_handler(void *args);

void free_socket();

#endif