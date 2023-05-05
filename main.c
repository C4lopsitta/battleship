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
    printHintbar("Continue", 0);
    while(getUserInput() != '\n');
    if(!boatsLeft(ai)) break;
    //ai turn
    aiTurn(ai, pl);
  }
  //   
  //   //ai turn
  //   mesg("AI player turn!                           ");
  //   int res = SHOT_DOUBLE;
  //   while(res == SHOT_DOUBLE){
  //     int aiX = rand() % FIELD_X, aiY = rand() % FIELD_Y;
  //     res = hitBoat(pl, aiX, aiY);
  //     if(res == SHOT_HIT) mesgWarn("AI Hit your boat!                           ");
  //     else mesg("AI Missed your boats!                            ");
  //   }
  //   ai->tries++;
  //   setCursor(1, 1);
  //   printPlayerField(pl);
  //   printHintbar("Continue", 0);
  //   while(getUserInput() != '\n'){}
  // }
  clearScreen();
  setCursor(1, 1);
  if(!boatsLeft(ai)) printf("Player won in %d shots!\n", pl->tries);
  else printf("AI won in %d shots!\n", ai->tries);
  return 0;
}

