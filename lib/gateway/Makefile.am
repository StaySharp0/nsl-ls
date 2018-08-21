JSON_C_DIR = /usr/local
#JSON_CFLAGS = -I$(JSON_C_DIR)/include/json-c
#JSON_LIBADD = -L$(JSON_C_DIR)/lib -ljson-c

lib_LTLIBRARIES = libGateway.la
libGateway_la_SOURCES = gateway.h gateway.c \
                        config.h config.c \
                        run.h run.c \
                        model.h model.c \
                        type.h \
                        util.h util.c
libGateway_la_CFLAGS = -I$(JSON_C_DIR)/include/json-c 
libGateway_la_LIBADD = -L$(JSON_C_DIR)/lib -ljson-c -lsqlite3