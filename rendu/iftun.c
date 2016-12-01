#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#include <unistd.h>
#include <fcntl.h>
#include <linux/if.h>
#include <linux/if_tun.h>

int tun_alloc(char *dev)
{
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
  if( *dev )
    strncpy(ifr.ifr_name, dev, IFNAMSIZ);

  if( (err = ioctl(fd, TUNSETIFF, (void *) &ifr)) < 0 ){
    close(fd);
    return err;
  }
  strcpy(dev, ifr.ifr_name);
  return fd;
}

int recopie(int src, int dst){
  int nbLus;
  int maxSize = 8096;
  char buffer[maxSize];
  while(1){
      nbLus = read(src, buffer, maxSize);
      write(dst, buffer, nbLus);
  }
}

int main (int argc, char** argv){
  if (argc != 2) {return 1;}
  int tunDescr = tun_alloc(argv[1]);
  char* rien = malloc(50*sizeof(char));
  //scanf("AAA:%s\n", &rien);
  recopie(tunDescr, 1);
  close(tunDescr);
  free(rien);
  return 0;
}
