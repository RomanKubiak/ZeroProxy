#include "config.h"


in_port_t get_in_port(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return (((struct sockaddr_in*)sa)->sin_port);
    }

    return (((struct sockaddr_in6*)sa)->sin6_port);
}

char *get_ip_str(const struct sockaddr *sa)
{
	char *buf = (char *)malloc(128);
    switch(sa->sa_family) {
        case AF_INET:
            inet_ntop(AF_INET, &(((struct sockaddr_in *)sa)->sin_addr),
                    buf, 128);
            break;

        case AF_INET6:
            inet_ntop(AF_INET6, &(((struct sockaddr_in6 *)sa)->sin6_addr),
                    buf, 128);
            break;

        default:
            strncpy(buf, "Unknown AF", 128);
            return NULL;
    }

    return buf;
}

void util_timer_callback(int fd, short event, void *arg)
{
}

int utils_register(struct event_base *evbase)
{
    struct event *ev;
    struct timeval tv;
    tv.tv_sec   = 0;
    tv.tv_usec  = 950000;

    ev = event_new(evbase, -1, EV_PERSIST, util_timer_callback, NULL);
    event_add(ev, &tv);

    return 0;
}