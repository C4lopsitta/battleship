#ifndef __LIBUTILS_H__
#define __LIBUTILS_H__

#include <signal.h>
#include <termios.h>
#include "libdefines.h"

void setCursorWithOffset(int, int);
void mesgDebug(String, ...);
char getUserInput();

#include "libboats.h"
#include "textutils.h"
#include "libprinters.h"

void sigint_handler(int);
void fillField(Player*);
void setBoats(Player*);
Player* setupPlayer(int);
int handleWASDInput(char, byte*, byte*);
void setCursorWithOffset(int, int);
void setupPlayerBoats(Player*);

void sigint_handler(int sig_num){
  clearScreen();
  setCursor(1, 1);
  printf("Exiting game\n");
  exit(0);
}

void fillField(Player*p){
  for(int i=0; i<FIELD_Y; i++)
    for(int j=0; j<FIELD_X; j++)
      p->field[i][j] = WATER;
}

void setBoats(Player*p){
  p->boats[0] = CARRIERS;
  p->boats[1] = BATTLESHIPS;
  p->boats[2] = CRUISERS;
  p->boats[3] = DESTROYERS;
  p->boats[4] = SUBMARINES;
  p->boatsHealth[0] = 5;
  p->boatsHealth[1] = 4;
  p->boatsHealth[2] = 3;
  p->boatsHealth[3] = 2;
  p->boatsHealth[4] = 2;
}

Player* setupPlayer(int playerno){
  Player* player = (Player*)malloc(sizeof(Player));
  setBoats(player);
  player -> type = (playerno==1)?'1':'2';
  player -> tries = 0;
  fillField(player);
  return player;
}

int handleWASDInput(char input, byte* x, byte* y){
  switch(input){
      case 'w':
        if(*y) (*y)--;
        return -1;
      case 'a':
        if(*x) (*x)--;
        return -1;
      case 's':
        if((*y) < FIELD_Y-1) (*y)++;
        return -1;
      case 'd':
        if((*x) < (FIELD_X-1)) (*x)++;
        return -1;
      default:
        return 0;
    }
}

void setCursorWithOffset(int y, int x){
  int actX = 3, actY = 6;
  for(; x; x--) actX += 1;
  for(; y; y--) actY += 3;
  setCursor(actX, actY);
}


char getUserInput(){
  static struct termios oldt, newt;
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  char userInput = fgetc(stdin);
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  return userInput;
}

void setupPlayerBoats(Player*p){
  clearScreen();
  printHintbar("Place Boat", 1);
  byte xcur = 0, ycur = 0;
  int rot = 0;
  setCursor(1, 1);
  printPlayerField(p);
  printTooltip(p->boats, "-[Boats left to place]-");
  setCursorWithOffset(xcur, ycur);
  drawCursor(xcur, ycur, rot, (BoatType)0);
  for(int i=0; i<5; i++){
    while(p->boats[i]){
      char userInput = getUserInput();
      if(!handleWASDInput(userInput, &xcur, &ycur)){
        switch(userInput){
          case '\n':
            int res = putBoat(p, ycur, xcur, (BoatType)i, rot, p->boats[i]-1);
            if(res==PLACE_CONFIRM) p->boats[i]--;
            else{
              mesgWarn("Cannot place boat in this position");
              putchar('\a');
            }
            break;
          case 'r':
            rot -= 90;
            rot %= 360;
            break;
          case 'R':
            rot += 90;
            rot %= 360;
            break;
        }
      }
      setCursor(1, 1);
      printPlayerField(p);
      printTooltip(p->boats, "-[Boats left to place]-");
      drawCursor(xcur, ycur, rot, (BoatType)i);
    }
  }
  setBoats(p);
  mesg("Do you want to confirm these positions? (y/n)\n");
  if(getUserInput()=='n'){
    fillField(p);
    setupPlayerBoats(p);
  }
  return;
}

void playerTurn(Player*pl, Player*pl2){
  printHintbar("ATTACK!", 0);
  byte xcur = 0, ycur = 0;
  setCursor(1, 1);
  printPlayerFieldHidden(pl2);
  printTooltip(pl->boats, "---[ Your boats ]---");
  mesg("Your turn!                     ");
  setCursorWithOffset(xcur, ycur);
  char userInput = '1';
  while(userInput){
    userInput = getUserInput();
    if(!handleWASDInput(userInput, &xcur, &ycur)){
      if(userInput == '\n'){ //player attacked
        int res = hitBoat(pl2, xcur, ycur);
        switch(res){
          case SHOT_MISS:
            mesg("No enemy boat hit                   ");
            userInput = '\0';
            break;
          case SHOT_HIT:
            mesg("HIT ENEMY BOAT!                     ");
            userInput = '\0';
            break;
          case SHOT_DOUBLE:
            mesgWarn("You already hit this coordinate!   ");
            break;
        }
        pl->tries++;
      }
    }
    setCursor(1, 1);
    printPlayerField(pl2);
    printTooltip(pl2->boats, "---[ Your boats ]---");
    setCursorWithOffset(xcur, ycur);
  }
}

void awaitUserConfirm(){
  printHintbar("Continue", 0);
  while(getUserInput() != '\n');
}

void updateConfig(){};

#endif //endif __LIBUTILS_H__
