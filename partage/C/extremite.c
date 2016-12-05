#include "extremite.h"
#include "iftun.h"

int initServeur (char* port){
	
	struct addrinfo* addrResult;
	struct addrinfo filtre = {AI_PASSIVE,PF_INET6,SOCK_STREAM,0,0,NULL,NULL,NULL};

	int err;
	int descrSock;
	int descrSockNew;
	
	err = getaddrinfo(NULL, port,&filtre, &addrResult);										if(err !=  0){fprintf(stderr,"Erreur 2\n");return -2;}

	err = socket(addrResult->ai_family, addrResult->ai_socktype, addrResult->ai_protocol);	if(err == -1){fprintf(stderr,"Erreur 3\n");return -3;}
	descrSock = err;
	err = bind(descrSock, addrResult->ai_addr, sizeof(struct sockaddr_in6));				if(err == -1){fprintf(stderr,"Erreur 4\n");return -4;}
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
	int tentatives = 0;
	do{
		sleep(1);
		printf("Tentative connection au serveur n°%d\n", tentatives);
		err = connect(descrSock,resol->ai_addr,sizeof(struct sockaddr_in6));
		tentatives++;
	}while(err < 0 && tentatives < MAX_TENTATIVES_CONNECT);
	freeaddrinfo(resol);
	if(tentatives >= MAX_TENTATIVES_CONNECT){
		//ABANDON
		return -1;
	}
	return descrSock;
}

int ext_in(int descrTun, char* hote){
	int descrSock = initClient(hote, PORT_TUNNEL);
	if(descrSock < 0){
		fprintf(stderr, "Connection Fail\n");
		return (descrSock);
	}
	printf("Connection établie\n");
	recopie(descrTun,descrSock);

}

int createTun(char* tun, char* commandeRoutes){
	int descrTun = tun_alloc(tun);
	if(descrTun < 0){
		fprintf(stderr, "Erreur tunnel\n");
		return descrTun;
	}
	printf("Tunnel établi\n");
	system("./configure-tun.sh");
	system(commandeRoutes);
	printf("Attente connection \n");
	return descrTun;
}

int ext_out(int descrTun){
	int descrSock = initServeur(PORT_TUNNEL);
	if (descrSock < 0){
		fprintf(stderr, "Serveur Init Fail\n");
		return (descrSock);
	}
	int descrClient = accept(descrSock,NULL,NULL);
	printf("Connection établie \n");

	recopie(descrClient,descrTun);

	// shutdown(descrClient, SHUT_RDRW);
	close(descrClient);
	// shutdown(descrSock, SHUT_RDRW);
	close(descrSock);
	return 0;
}
