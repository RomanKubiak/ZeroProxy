#include "config.h"
#include <wiringSerial.h>
#include <cwpack.h>

void serial_event(int serial_fd, short event, void *arg)
{
    char readbuf[128];
    int read_data_size = 0;
    uint8_t cmd_type = 0;
    unsigned long remote_millis = 0, battery_millis = 0;
    if ( (read_data_size = read(serial_fd, readbuf, sizeof(readbuf))) == -1)
    {
        ERROR("error reading from serial port \"%s\"\n", strerror(errno));
        return;
    }
    
    cw_unpack_context uc;
    cw_unpack_context_init(&uc, readbuf, read_data_size, 0);
    cw_unpack_next(&uc);
    cw_unpack_next(&uc);
    cmd_type = uc.item.as.u64;
    cw_unpack_next(&uc);     
    remote_millis = uc.item.as.u64;   
    cw_unpack_next(&uc);
    battery_millis = uc.item.as.u64;
    if (cmd_type == 0x01)
        DEBUG("body remote millis: %lu battery %lu mV\n", remote_millis, battery_millis);
}

int serial_register(struct event_base *evbase)
{
    int serial_fd;
    struct event *ev;
    if ((serial_fd = serialOpen(CONFIG_SERIAL, CONFIG_SERIAL_SPEED)) < 0)
    {
        ERROR("can't open serial device %s@%d\n", CONFIG_SERIAL, CONFIG_SERIAL_SPEED);
        return -1;
    }
    
    ev = event_new(evbase, serial_fd, EV_READ|EV_PERSIST, serial_event, NULL);
    
    if (ev == NULL)
    {
        ERROR("can't create new event\n");
        return -1;
    }
    
    event_add(ev, NULL);
    return 0;
}