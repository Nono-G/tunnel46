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

#define MAXLENMSG 100

int boucle_princ = 1;



int recopie(int src, int dst){
  int nbLus = 0;
  int maxSize = 8192;
  char buffer[maxSize];
  nbLus = read(src, buffer, maxSize);
  while(nbLus > 0){
      write(dst, buffer, nbLus);
      nbLus = read(src, buffer, maxSize);
  }
}

int unEcho (int descrSock){
		char req[MAXLENMSG+1];
		int lu = recv(descrSock, req, MAXLENMSG, 0);
		if(lu != 0){
			req[lu] = '\0';
			send(descrSock, req, MAXLENMSG, 0);
		}

		return(lu != 0);
}

int initServeur (char* port){
	
	struct addrinfo* addrResult;
	struct addrinfo filtre = {AI_PASSIVE,PF_INET,SOCK_STREAM,0,0,NULL,NULL,NULL};

	int err;
	int descrSock;
	int descrSockNew;
	
	err = getaddrinfo(NULL, port,&filtre, &addrResult);										if(err !=  0){fprintf(stderr,"Erreur 2\n");return -2;}

	err = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);	if(err == -1){fprintf(stderr,"Erreur 3\n");return -3;}
	descrSock = err;
	err = bind(descrSock, addrResult->ai_addr, sizeof(struct sockaddr_in));					if(err == -1){fprintf(stderr,"Erreur 4\n");return -4;}
	freeaddrinfo(addrResult);
	
	err = listen(descrSock, SOMAXCONN);if(err == -1){printf("Erreur 5\n");exit(5);}
	 
	return descrSock;
}

int initClient(char* hote, char* port){
	struct addrinfo *resol;
	int err;
	int descrSock
	err = getaddrinfo(hote,port,NULL, &resol); 												if(err !=0){fprintf(stderr, "Erreur 2\n");return -2;}
	err = socket(resol->ai_family,resol->ai_socktype, resol->ai_protocol);					if(err == -1){fprintf(stderr, "Erreur 3\n");return -3;}
	descrSock = err;
	err = connect(descrSock,resol->ai_addr,sizeof(struct sockaddr_in);						if(err == -1){fprintf(stderr, "Erreur 4\n");return -4;}
	freeaddrinfo(resol);
	return descrSock;
}
int ext_in(){
	getaddrinfo(hote,port,NULL, &resol);

}

int ext_out(){
	int descrSock = initServeur("1230");
	if (descrSock < 0){
		fprintf(stderr, "Serveur Init Fail\n");
		return (descrSock);
	}
	
	printf("Attente connection \n");
	int descrClient = accept(descrSock,NULL,NULL);
	printf("Connection établie \n");

	recopie(descrClient,1);

	// shutdown(descrClient, SHUT_RDRW);
	close(descrClient);
	// shutdown(descrSock, SHUT_RDRW);
	close(descrSock);
	return 0;
}

int main(int argc, char const *argv[])
{
	ext_out();
	
	return 0;
}


