/*
 * Name: gateway.h
 *
 * Description: bin 파일을 위한 헤더
 * 초기화 및 명령 인자 처리 관련 함수 처리
 *
 * Copyright (c) 2018.
 * YongJun Kim <StaySharp0@gmail.com>
 *
 */
#ifndef gateway_h
#define gateway_h

#include <stdio.h>      // prinft,
#include <string.h>     // strcmp,
#include <unistd.h>     // fork, chdir, setsid
#include <sys/wait.h>   // wait
#include <signal.h>     // signal

#include "type.h"
#include "util.h"
#include "config.h"
#include "run.h"


int cmd_arg_gateway(int argc, char *argv[]);
void init_gateway(int cmd_status, int argc, char *argv[]);
void free_gateway();

void fn_exit();
void fn_help();

#endif