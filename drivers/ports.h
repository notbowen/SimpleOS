#ifndef PORTS_H
#define PORTS_H

/* Communicates with ports to get info */
void outb(unsigned short port, unsigned char data);
unsigned char inb(unsigned short port);

#endif