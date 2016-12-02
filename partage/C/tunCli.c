#include "extremite.h"

int main(int argc, char *argv[])
{
	
	char sripName[350];
	if (argc < 4){
		printf("USAGE : tunCli [Tun device name] [Host] [\"16\" or \"36\"] \n");
		return 666;
	}
	char commande[100] = "./";
	strcat(commande, argv[3]);
	strcat(commande, "configure-routes-tun.sh");
	ext_in(argv[1],argv[2],commande);
	return 0;
}