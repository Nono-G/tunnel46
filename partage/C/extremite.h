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

int recopie(int src, int dst);
int initServeur(char* port);
int initClient(char* hote, char* port);
int ext_in(char* tun, char* hote, char* commandeRoutes);
int ext_out(char* tun, char* commandesRoutes);

#endif