#include "iftun.h"

int tun_alloc(char* dev){
  struct ifreq ifr;
  int fd, err;
  //*TRACE*/printf("A\n");
  if( (fd = open("/dev/net/tun", O_RDWR)) < 0 ){
    perror("alloc tun");
    exit(1);
  }
  //*TRACE*/printf("P\n");
  memset(&ifr, 0, sizeof(ifr));
  //*TRACE*/printf("R\n");
  /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
   *        IFF_TAP   - TAP device
   *
   *        IFF_NO_PI - Do not provide packet information
   */
  ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
  if( *dev ){
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);
  }
  //*TRACE*/printf("E\n");
  if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
    close(fd);
    return err;
  }
  //*TRACE*/printf("S\n");
  strcpy(dev, ifr.ifr_name);
  //*TRACE*/printf("L\n");
  return fd;
}

int recopie(int src, int dst){
  int nbLus;
  int maxSize = 8192;
  char buffer[maxSize];
  while(1){
      nbLus = read(src, buffer, maxSize);
      write(dst, buffer, nbLus);
  }
}

// int main (int argc, char** argv){
//   if (argc != 2) {return 1;}
//   int tunDescr = tun_alloc(argv[1]);
//   char* rien = malloc(50*sizeof(char));
//   //scanf("AAA:%s\n", &rien);
//   recopie(tunDescr, 1);
//   close(tunDescr);
//   free(rien);
//   return 0;
// }
