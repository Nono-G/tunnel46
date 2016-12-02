#include "extremite.h"
#include "iftun.h"

int main(int argc, char *argv[])
{
	if(argc < 3){
		printf("USAGE : ./tunServ [Tun dev name] [16 / 36]\n");
		return -1;
	}
	char commande[100] = "./";
	strcat(commande, argv[2]);
	strcat(commande, "configure-routes-tun.sh");

	ext_out(argv[1], commande);
	return 0;
}