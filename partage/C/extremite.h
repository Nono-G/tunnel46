#ifndef __ETREMITE_H__
#define __ETREMITE_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/select.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define PORT_TUNNEL "1450"
#define MAX_TENTATIVES_CONNECT 30

int recopie(int src, int dst);
int initServeur(char* port);
int initClient(char* hote, char* port);
int ext_in(int tun, char* hote,char* portTunnel);
int ext_out(int tun, char* portTunnel);
int createTun(char* tun, char* ip, char* tunRoutesScript);

#endif
