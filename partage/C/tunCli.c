#include "extremite.h"

int main(int argc, char *argv[])
{
	if (argc < 3){
		printf("USAGE : tunCli [Tun device name] [Host]\n");
		return 666;
	}
	ext_in(argv[1],argv[2]);
	return 0;
}