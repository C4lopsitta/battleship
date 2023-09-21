#ifndef __LIBMULTIPLAYER_H__
#define __LIBMULTIPLAYER_H__

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <net/if.h>
#include <ifaddrs.h>

#include "defines.h"

void multiPlayer();
String getIfaceIP(String iface);
String getUserInputString(byte x, byte y, String placeHolder, byte inY, byte maxchar);
void printHeader();
char printNetMenu(String* addr);
void initNetworkMultiplayer();

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

#endif //__LIBMULTIPLAYER_H__
