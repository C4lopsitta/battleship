#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "libdefines.h"

Config* config;
#include "libutils.h"
#include "libmultiplayer.h"


int main (int argc, char **argv){
  //setup functions and ctrl-c handler
  signal(SIGINT, sigint_handler);
  clearScreen();
  config = loadConfig();

  char menuSelect = printSplashscreen();
  switch (menuSelect) {
    case 'h': // singleplayer
      singlePlayer();
      break;
    case 'c': //config setup
      updateConfig();
      break;
    case 'm': //local pc multiplayer
      break;
    case 'n': //LOCAL network multiplayer
      initNetworkMultiplayer();
      break;
    case 'q': //quit
      exit(0);
  }

  
  return 0;
}

