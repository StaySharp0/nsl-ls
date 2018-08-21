/*
 * gateway/util.h
 *
 * Copyright (c) 2018.
 * YongJun Kim <StaySharp0@gmail.com>
 *
 */

#ifndef gateway_util_h
#define gateway_util_h

#include <stdio.h>
#include <json.h>
#include "type.h"

#define SAFE_FREE(a) if(a){free(a); a=NULL;}
#define MAX(a, b) (a >= b) ? a : b

static int debug = TRUE;

void debugMsg(SELF* self, const char* msg);
json_object* find_object_by_key(json_object*, const char*);

#endif