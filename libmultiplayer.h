#ifndef __LIBMULTIPLAYER_H__
#define __LIBMULTIPLAYER_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <ifaddrs.h>

String getIfaceIP(String iface){
  int fd;
  struct ifreq ifr;
  fd = socket(AF_INET, SOCK_DGRAM, 0);
  ifr.ifr_addr.sa_family = AF_INET;
  strncpy(ifr.ifr_name, iface, IFNAMSIZ-1);
  ioctl(fd, SIOCGIFADDR, &ifr);
  close(fd);
  return strdup(inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr));
  //gotten from https://stackoverflow.com/questions/2283494/get-ip-address-of-an-interface-on-linux
}

String getUserInputString(byte x, byte y, String placeHolder, byte inY){
  va_list args;
  setCursor(x, y);
  printf("%s", placeHolder);
  fflush(stdout);
  setCursor(x, inY);
  char buf[128], i = 0;
  for(; buf[i] = getUserInput(), buf[i] != '\n', i<127; i++){};
  buf[i] = '\0';
  if(!i) return NULL;
  return strdup(buf);
}

void printHeader(){
  setCursor(4, 12);
  printf("---[ BATTLESHIPS ]---");
  setCursor(5, 5);
  printf("---[ LOCAL NETWORK MULTIPLAYER ]---");
}

char printNetMenu(String* addr){
  printHeader();
  fflush(stdout);
  setCursor(12, 5);
  printf("---[c]   [   CONNECT TO HOST   ]---");
  setCursor(13, 5);
  printf("---[h]   [   CREATE NEW GAME   ]---");
  char userInput = getUserInput();
  switch(userInput){
    case 'c': //connect to host
      clearScreen();
      printHeader();
      getUserInputString(13, 5, "---[ HOST IP ]---[               ]---", 13+10);
      break;
    case 'h': //act as host
      
      break;
  }
}

void initNetworkMultiplayer(){
  clearScreen();
  String addr;
  char userInput = printNetMenu(&addr);
}


#endif //__LIBMULTIPLAYER_H__
