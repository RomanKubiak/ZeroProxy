#include "config.h"
#include <time.h>

void heartbeat_led_local(int fd, short event, void *arg)
{
	live_data.local_time = time(NULL);
}

int heartbeat_led_register(struct event_base *evbase)
{
	struct event *ev;
	struct timeval tv;
	tv.tv_sec 	= 0;
	tv.tv_usec 	= 150000;
	
	live_data.start_time = time(NULL);
	
	ev = event_new(evbase, -1, EV_PERSIST, heartbeat_led_local, NULL);
	event_add(ev, &tv);

	return 0;
}