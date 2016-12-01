all: clean tunServ tunCli

iftun.o:
	gcc -c iftun.c

extremite.o: iftun.o
	gcc -c extremite.c iftun.o

tunServ: extremite.o iftun.o
	gcc -o tunServ extremite.o iftun.o tunServ.c

tunCli: extremite.o iftun.o
	gcc -o tunCli tunCli.c extremite.o iftun.o

clean:
	rm *.o
	rm tunCli
	rm tunServ