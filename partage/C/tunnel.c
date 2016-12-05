#include "extremite.h"


#define TAILLE_MAX 1000

int main(int argc, char* argv[])
{
	if(argc < 2){
		printf("USAGE :  16 pour VM16 ou 32 pour VM36 \n");
		return -1;
	}

	char tun[124];
	char inip[124];
	char inport[124];
	char options[124];
	char outip[124];
  	char outport[124];

	FILE *fic;
	if(argv[1] == "16"){
		fic = fopen("configVM1-6","r");
	}else 
		fic = fopen("configVM3-6","r");

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

	int descrTun = createTun(&tun, inip);
	
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