#include "extremite.h"

int main(int argc, char* argv[])
{
	if(argc < 3){
		printf("USAGE :  [tun device name] [other end host] [routes script] \n");
		return -1;
	}

	int descrTun = createTun(argv[1], argv[3]);
	if (descrTun < 0 ){
		printf("Tun Error, try SUDO\n");
		return -1;
	}
	int pid = fork();
	if(pid == 0){
		ext_in(descrTun, argv[2]);
		return 0;
	}else{
		int status;
		ext_out(descrTun);
		wait(&status);

	}
	return 0;
}