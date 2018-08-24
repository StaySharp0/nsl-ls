/*
 * gateway/run.h
 *
 * Copyright (c) 2018.
 * YongJun Kim <StaySharp0@gmail.com>
 *
 */

#ifndef gateway_run_h
#define gateway_run_h

#include<stdlib.h>  // sprintf
#include<stdio.h>   // fprintf
#include<unistd.h>  // fork, chdir, setsid, pipe
#include <signal.h> // raise

// socket
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include "type.h"
#include "util.h"
#include "config.h"
#include "model.h"

#define SF_PATH "../sf"

// publice
int set_daemon(SELF*);
void fn_run(SELF*);

// private
void _run_init_sf(SELF*);
void _run_sf_connection_handler(SELF*);
int _run_init_socket(SELF*, int);
int _run_reconnect_socket(SELF* self, int idx);
#endif