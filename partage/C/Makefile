all: tunnel

iftun.o:
	gcc -c iftun.c

extremite.o: iftun.o
	gcc -c extremite.c iftun.o

tunServ: extremite.o iftun.o
	gcc -o tunServ extremite.o iftun.o tunServ.c

tunCli: extremite.o iftun.o
	gcc -o tunCli tunCli.c extremite.o iftun.o

tunnel: extremite.o iftun.o
	gcc -o tunnel tunnel.c extremite.o iftun.o

clean:
	rm *.o
	rm tunnel
