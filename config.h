#ifndef CONFIG_H__
#define CONFIG_H__

#include <evhttp.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdbool.h>
#include "ipc.h"


#define CONFIG_FILE 		"./zero.json"
#define CONFIG_PORT		12345
#define CONFIG_DEBUG	1

struct ipc_live_data
{
	time_t local_time;
	time_t start_time;
} live_data;

#define ERROR(...) \
    fprintf(stderr, "\033[31mERROR:\033[0m %s:%d: ", __FUNCTION__, __LINE__); \
    fprintf(stderr, __VA_ARGS__);

#if (CONFIG_DEBUG == 1)
#define DEBUG(...) \
    fprintf(stderr, "\033[32;1mDEBUG:\033[0m %s:%d: ", __FUNCTION__, __LINE__); \
    fprintf(stderr, __VA_ARGS__);
#else
    #define DEBUG(...)
#endif

#define INFO(...) \
    fprintf(stderr, "\033[34mINF:\033[0m %s:%d: ", __FUNCTION__, __LINE__); \
    fprintf(stderr, __VA_ARGS__);

int udp_server_register(struct event_base *evbase);
int http_server_register(struct event_base *evbase);
int heartbeat_led_register(struct event_base *evbase);
int utils_register(struct event_base *evbase);

char *get_ip_str(const struct sockaddr *sa);
in_port_t get_in_port(struct sockaddr *sa);

#endif