#include "extremite.h"


#define TAILLE_MAX 1000

int main(int argc, char* argv[])
{
	if(argc < 2){
		printf("USAGE :  ./tunnel {nom du fichier config}\n");
		return -1;
	}

	char tun[124];
	char inip[124];
	char inport[124];
	char options[124];
	char outip[124];
  	char outport[124];

	FILE *fic;
	fic = fopen(argv[1],"r");

	char ignore[TAILLE_MAX] = "";

	fgets(ignore, TAILLE_MAX, fic);
	fscanf(fic, "tun=%s ",&tun);
	fgets(ignore, TAILLE_MAX, fic);
	fscanf(fic, "inip=%s ",&inip);
	fscanf(fic, "inport=%s ",&inport);
	fscanf(fic, "options=%s ",&options);
	
	fgets(ignore, TAILLE_MAX, fic); //  # adresse distante
	
	fscanf(fic, "outip=%s ",&outip);
	fscanf(fic, "outport=%s ",&outport);
	
	fclose(fic);

	printf("tun : %s\n",tun);
	printf("inip : %s\n",inip);
	printf("inport : %s\n",inport);
	printf("options : %s\n",options);
	printf("outip : %s\n",outip);
  	printf("outport : %s\n",outport);

	int descrTun = createTun(tun, inip, options);
	
	if (descrTun < 0 ){
		printf("Tun Error, try SUDO\n");
		return -1;
	}
	int pid = fork();
	if(pid == 0){
		ext_in(descrTun,outip,outport);
		return 0;
	}else{
		int status;
		ext_out(descrTun,inport);
		wait(&status);

	}
	return 0;
}