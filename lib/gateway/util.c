#include "util.h"

void debugMsg(SELF* self, const char* msg) {
    if(debug == TRUE) {
        fprintf(stdout, "%s: %s", process_name[self->procType] ,msg);
    }
}

json_object* find_object_by_key(json_object* rootObj, const char* key) {
    json_object* returnObj;

    if (json_object_object_get_ex(rootObj, key, &returnObj)){
        return returnObj;
    }

    return NULL;
}