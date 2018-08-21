JSON_C_DIR = /usr/local
JSON_CFLAGS = -I$(JSON_C_DIR)/include/json-c
JSON_LIBADD = -L$(JSON_C_DIR)/lib -ljson-c

bin_PROGRAMS = gateway
gateway_SOURCES = gateway.c
gateway_CFLAGS = $(JSON_CFLAGS) \
                -I$(srcdir)/../lib/gateway 
gateway_LDADD = $(JSON_LIBADD) \
                -L$(srcdir)/../lib/gateway/ -lGateway 