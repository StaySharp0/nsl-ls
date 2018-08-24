#include "model.h"

// Private Variables
static char _today_dir[100];

// Private Function

// Fn: Make node dir 
// Fn: Today check
// Fn: write

// public
int init_storage (SELF* self)
{
	char cmd[100], buf[12];
	int nResult = access(DEFAULT_STORAGE_ROOT_PATH, 0);
	time_t timer;
	struct tm* tm_info;


	if ( nResult == -1 ) // Make root dir
	{ 	
		sprintf(cmd, "mkdir %s", DEFAULT_STORAGE_ROOT_PATH);
		system(cmd);
    }

	// Check today dir
	time(&timer);
	tm_info = localtime(&timer);
	strftime(buf, 12, "%Y-%m-%d", tm_info);
	sprintf(cmd, "%s/%s", DEFAULT_STORAGE_ROOT_PATH, buf);
	strcmp(_today_dir, cmd);
	nResult = access(cmd, 0);

	if ( nResult == -1 ) // Make today dir
	{ 	
		sprintf(cmd, "mkdir %s/%s", DEFAULT_STORAGE_ROOT_PATH, buf);
		system(cmd);
	}

    return TRUE;

}
