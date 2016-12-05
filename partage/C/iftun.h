#ifndef __IFTUN_H__

#define __IFTUN_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

int recopie(int src, int dst);
int tun_alloc(char* dev);

#endif
