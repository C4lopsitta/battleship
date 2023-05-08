
#define DEBUG

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#include "libutils.h"
#include "shipai.h"

int main (int argc, char **argv){
  //setup functions and ctrl-c handler
  signal(SIGINT, sigint_handler);
  clearScreen();

  char menuSelect = printSplashscreen();
  switch (menuSelect) {
    case 'h':
      break;
    case 'c':
      updateConfig();
    case 'q':
      exit(0);
  }

  //setup AI player
  Player* ai = setupAI();
  //setup player
  Player* pl = setupPlayer(1);
  //reset seed for ai
  srand(time(NULL) / getpid());
  //query player for boat postions
  setupPlayerBoats(pl);
  clearScreen();
  printHintbar("Confirm action", 0);
  
  //main game cycle
  while(boatsLeft(ai) && boatsLeft(pl)){
    //player turn
    playerTurn(pl, ai);
    //check mid turn if player already won
    awaitUserConfirm();
    if(!boatsLeft(ai)) break;
    //ai turn
    aiTurn(ai, pl);
    awaitUserConfirm();
  }
  clearScreen();
  setCursor(1, 1);
  if(!boatsLeft(ai)) printf("Player won in %d shots!\n", pl->tries);
  else printf("AI won in %d shots!\n", ai->tries);
  return 0;
}

