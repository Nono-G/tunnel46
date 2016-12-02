#include "extremite.h"
#include "iftun.h"

#define MAXLENMSG 100
#define PORT_TUNNEL "1450"

int initServeur (char* port){
	
	struct addrinfo* addrResult;
	struct addrinfo filtre = {AI_PASSIVE,PF_INET6,SOCK_STREAM,0,0,NULL,NULL,NULL};

	int err;
	int descrSock;
	int descrSockNew;
	
	err = getaddrinfo(NULL, port,&filtre, &addrResult);										if(err !=  0){fprintf(stderr,"Erreur 2\n");return -2;}

	err = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);	if(err == -1){fprintf(stderr,"Erreur 3\n");return -3;}
	descrSock = err;
	err = bind(descrSock, addrResult->ai_addr, sizeof(struct sockaddr_in6));					if(err == -1){fprintf(stderr,"Erreur 4\n");return -4;}
	freeaddrinfo(addrResult);
	
	err = listen(descrSock, SOMAXCONN);if(err == -1){printf("Erreur 5\n");exit(5);}
	 
	return descrSock;
}

int initClient(char* hote, char* port){
	struct addrinfo *resol;
	int err;
	int descrSock;
	err = getaddrinfo(hote,port,NULL, &resol); 												if(err != 0){fprintf(stderr, "Erreur 2\n");return -2;}
	err = socket(resol->ai_family,resol->ai_socktype, resol->ai_protocol);					if(err == -1){fprintf(stderr, "Erreur 3\n");return -3;}
	descrSock = err;
	err = connect(descrSock,resol->ai_addr,sizeof(struct sockaddr_in6));						if(err == -1){fprintf(stderr, "Erreur 4\n");return -4;}
	freeaddrinfo(resol);
	return descrSock;
}

int ext_in(char* tun, char* hote, char* commandeRoutes){
	int descrSock = initClient(hote, PORT_TUNNEL);
	if(descrSock < 0){
		fprintf(stderr, "Connection Fail\n");
		return (descrSock);
	}
	printf("Connection établie\n");
	int tunDescr = tun_alloc(tun);
	printf("Tunnel établi\n");
	system("./configure-tun.sh");
	system(commandeRoutes);
	recopie(tunDescr,descrSock);

}

int ext_out(char* tun, char* commandeRoutes){
	int descrSock = initServeur(PORT_TUNNEL);
	if (descrSock < 0){
		fprintf(stderr, "Serveur Init Fail\n");
		return (descrSock);
	}
	int descrTun = tun_alloc(tun);
	if(descrTun < 0){
		fprintf(stderr, "Erreur tunnel\n");
		exit(666);
	}
	printf("Tunnel établi\n");
	system("./configure-tun.sh");
	system(commandeRoutes);
	printf("Attente connection \n");
	int descrClient = accept(descrSock,NULL,NULL);
	printf("Connection établie \n");

	recopie(descrClient,descrTun);

	// shutdown(descrClient, SHUT_RDRW);
	close(descrClient);
	// shutdown(descrSock, SHUT_RDRW);
	close(descrSock);
	return 0;
}