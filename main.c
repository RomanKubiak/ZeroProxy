#include "config.h"

int main (int argc, char *argv[])
{
	struct event_base *evbase = NULL;
    evbase = event_base_new();
    if (evbase == NULL)
    {
        printf("error: failed to initialize libevent\n");
        return -1;
    }

    INFO("starting http server\n");
    if (http_server_register(evbase) == -1)
    {
    	printf("http_server_register failed\n");
    	return -1;
    }

    INFO("starting UDP server\n");
    if (udp_server_register(evbase) == -1)
    {
    	printf("udp_server_register failed\n");
    	return -1;
    }

    if (heartbeat_led_register(evbase) == -1)
    	return -1;

    if (utils_register(evbase) == -1)
    	return -1;
    INFO("starting main program loop\n");
    event_base_dispatch(evbase);
    return 0;
}
