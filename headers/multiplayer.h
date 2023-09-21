#ifndef __LIBMULTIPLAYER_H__
#define __LIBMULTIPLAYER_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <ifaddrs.h>

void multiPlayer(){
  Player* pl1 = setupPlayer(1);
  Player* pl2 = setupPlayer(2);
  clearScreen();
  setupPlayerBoats(pl1);
  clearScreen();
  hideAndAwait('\n', "Player 2, press [ENTER] to start setting up your boats");
  while(getUserInput() != '\n'){};
  setupPlayerBoats(pl2);
  clearScreen();
  printHintbar("Confirm action", 0);
  //main game cycle
  while(boatsLeft(pl1) && boatsLeft(pl2)){
    hideAndAwait('\n', "Player 1, press [ENTER] to start your turn");
    playerTurn(pl1, pl2);

    if(!boatsLeft(pl2)) break;
    hideAndAwait('\n', "Player 2m press [ENTER] to start your turn");
    playerTurn(pl2, pl1);
  }
}



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

String getUserInputString(byte x, byte y, String placeHolder, byte inY, byte maxchar){
  va_list args;
  setCursor(x, y);
  printf("%s", placeHolder);
  fflush(stdout);
  setCursor(x, inY);
  char buf[128], i = 0;
  for(; (buf[i] = getUserInput()) && (buf[i] != '\n') && (i<maxchar); i++){};
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

// String normaliseIP(String addr){
//   String ipRet = (String)malloc(sizeof(char) * 16);
//   printf("%s\n", addr);
//   String* ipUnits = split(addr, ".");
//   char dots = 0, zeroes = 0, delta;
//   for(int i=0, unit = 0; i<15, unit<4; i++){
//     if(i == 3 || i == 7 | i == 11){
//       ipRet[i] = '.';
//       dots++;
//       zeroes = 3 - strlen(*(ipUnits + unit));
//       delta = 0;
//     }else{
//       if(zeroes){
//         ipRet[i] = '0';
//         zeroes--;
//         delta++;
//       }else{
//         putchar(*(ipUnits + unit)[(i-dots)%3 - delta]);
//         fflush(stdout);
//         ipRet[i] = *(ipUnits + unit)[(i-dots)%3 - delta];
//       }
//     }
//     if((i - dots)%4 == 3){
//       unit++;
//     }
//   }
//   *(ipRet+15) = '\0';
//   printf("%s\n", ipRet);
//   free(ipUnits);
//   return ipRet;
// }

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
      *addr = getUserInputString(13, 5, "---[ HOST IP ]---[               ]---", 13+10, 14);
      break;
    case 'h': //act as host
      clearScreen();
      printHeader();
      setCursor(13, 5);
      *addr = getIfaceIP(config->netIface);
      printf("---[ INTERFACE %s IP ADDRESS ]---", config->netIface);
      setCursor(14, 5);
      fflush(stdout);
      printf("---[ %s ]---", *addr);
      free(*addr);
      break;
  }
}

void initNetworkMultiplayer(){
  clearScreen();
  String addr;
  char userInput = printNetMenu(&addr);
}


#endif //__LIBMULTIPLAYER_H__
