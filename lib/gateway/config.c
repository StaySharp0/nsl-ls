
#include "config.h"

int init_config_sensor_list(CONFIG* self) {
    char path[] = { SNLIST_JPATH };
	
	int nResult = access(path, 0);

	if( nResult == 0 )
	{ // exist
		self->sensor_list = json_object_from_file(path);

        return TRUE;
	}
	else if( nResult == -1 )
	{ // no exist
    
        // create new json ojbect
		self->sensor_list               = json_object_new_object();

        json_object *sensor_count       = json_object_new_int(0);
        json_object *sensor_list        = json_object_new_object();
        json_object *sid_mapping_list   = json_object_new_object();

        json_object_object_add(self->sensor_list, "sensor_count",        sensor_count);
        json_object_object_add(self->sensor_list, "sensor_list",         sensor_list);
        json_object_object_add(self->sensor_list, "sid_mapping_list",    sid_mapping_list);
        
        // write file
        json_object_to_file(path, self->sensor_list);
    }
    printf("init: sensor_list.json\n");

    return FALSE;
}

int init_config_server(CONFIG* self) {
    char path[] = { SERVER_JPATH };
	
	int nResult = access(path, 0);

	if( nResult == 0 )
	{ // exist
		self->server = json_object_from_file(path);

        return TRUE;
	}
	else if( nResult == -1 )
	{ // no exist
    
        // create new json ojbect
		self->server= json_object_new_object();

        json_object *server               = json_object_new_array();
        json_object *default_API          = json_object_new_object();
        json_object *default_BaseURL      = json_object_new_string("http://api.test.com");
        json_object *default_AuthKey      = json_object_new_string("nslnslnslnsl");
        
        json_object_array_add(server, default_API);
        json_object_object_add(default_API,  "baseURL",     default_BaseURL);
        json_object_object_add(default_API,  "authKey",     default_AuthKey);
        json_object_object_add(self->server,    "server",   server);

        json_object *sf                   = json_object_new_object();
        json_object *default_sf           = json_object_new_object();
        json_object *default_sf_tty       = json_object_new_string("/dev/ttyUSB[]");
        json_object *default_sf_port      = json_object_new_string("9000");
        json_object *default_sf_borderate = json_object_new_string("115200");

        json_object_object_add(default_sf,      "tty",          default_sf_tty);
        json_object_object_add(default_sf,      "port",         default_sf_port);
        json_object_object_add(default_sf,      "borderate",    default_sf_borderate);
        json_object_object_add(sf,              "0",            default_sf);
        json_object_object_add(self->server,    "sf",           sf);
        
        // write file
        json_object_to_file(path, self->server);
    }
    printf("init: server.json\n");

    return FALSE;
}



void config_set_pid (int proc_type, int pid) {
    FILE * pFile;
    char buf[10];

    if (proc_type == PROC_MANAGER) 
    {
        pFile = fopen ( MANAGER_PATH , "w" );
    } 
    else if (proc_type == PROC_WORKER)
    {
        pFile = fopen ( WORKER_PATH , "w" );
    }

    sprintf(buf, "%d", pid);

    fwrite (buf , 1 , sizeof(buf) , pFile );
    fclose (pFile);
}

int config_get_pid (int proc_type) {
    FILE * pFile;
    int pid;

    if (proc_type == PROC_MANAGER) 
    {
        pFile = fopen ( MANAGER_PATH , "r" );
    } 
    else if (proc_type == PROC_WORKER)
    {
        pFile = fopen ( WORKER_PATH , "r" );
    }

    if (pFile == NULL) {
        return FALSE;
    } else {
        fscanf (pFile, "%d", &pid);
    }

    fclose (pFile);

    return pid;
}

void free_json(CONFIG* self) {
    json_object_put(self->sensor_list);
    json_object_put(self->server);
}
