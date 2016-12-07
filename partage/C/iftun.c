#include "iftun.h"

int tun_alloc(char* dev){
  struct ifreq ifr;
  int fd, err;
  if( (fd = open("/dev/net/tun", O_RDWR)) < 0 ){
    perror("alloc tun");
    exit(1);
  }
  memset(&ifr, 0, sizeof(ifr));
  /* Flags: IFF_TUN   - TUN device (no Ethernet headers)
   *        IFF_TAP   - TAP device
   *
   *        IFF_NO_PI - Do not provide packet information
   */
  ifr.ifr_flags = IFF_TUN | IFF_NO_PI;
  if( *dev ){
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);
  }
  if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
    close(fd);
    return err;
  }
  strcpy(dev, ifr.ifr_name);
  return fd;
}

int boucle_princ = 1; 

void handlerChild() {
   boucle_princ = 0;

}

int recopie(int src, int dst){
  int nbLus;
  int maxSize = 8192;
  char buffer[maxSize];
  signal(SIGINT, handlerChild);
  /*int mode;
  mode = fcntl(src, F_GETFL, 0);
  mode |= O_NONBLOCK;
  fcntl(src, F_SETFL, mode);*/
  
  while(boucle_princ == 1){
      nbLus = read(src, buffer, maxSize);
      if(nbLus <= 0){
        continue;
      }
      write(dst, buffer, nbLus);
  }}
