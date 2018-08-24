/*
 * gateway/model.h
 *
 * Copyright (c) 2018.
 * YongJun Kim <StaySharp0@gmail.com>
 *
 */

#ifndef GATEWAY_MODEL_H
#define GATEWAY_MODEL_H

#define DEFAULT_STORAGE_DURATION 7
#define DEFAULT_STORAGE_ROOT_PATH "~/ls_storage/"

#include <unistd.h>         // access
#include <stdio.h>          // sprintf
#include <stdlib.h>         // system
#include <string.h>         //
#include <time.h>           // time, strftime

#include "type.h"


// return TRUE FALSE
int init_storage (SELF*);

#endif
