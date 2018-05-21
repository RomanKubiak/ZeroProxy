CC=gcc
CFLAGS=-c -Wall -std=c99 -I.
LDFLAGS=-levent
SOURCES=main.c utils.c udp_server.c http_server.c heartbeat_local_led.c cwpack.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=zero

all: $(SOURCES) $(EXECUTABLE)
    
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o
	rm -f zero
