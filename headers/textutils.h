#ifndef __TEXTUTILS_H__
#define __TEXTUTILS_H__

#include <sys/ioctl.h>

void clearScreen();
void getTerminalSize(int*, int*);
void clearText();
void boldText();
void underText();
void rgbText(int, int, int);
void negativeText();
void crossedText();
void drawSelbox(byte, byte);
void drawCursor(byte, byte, int, BoatType);

void setCursor(int x, int y){
  printf("\033[%d;%dH", x, y);
}

void clearScreen(){
  printf("\033[2J\033[1;1H");
}

void clearLine(){
  printf("\33[2K\r");
}

void getTerminalSize(int* x, int* y){
  struct winsize win;
  ioctl(0, TIOCGWINSZ, &win);
  *x = win.ws_col;
  *y = win.ws_row;
}

void clearText(){
  printf("\033[0;0m");
}

void boldText(){
  printf("\033[0;1m");
}

void redText(){
  rgbText(255, 0, 0);
}

void rgbText(int r, int g, int b){
  printf("\033[38;2;%d;%d;%dm", r, g, b);
}

void underText(){
  printf("\033[0;4m");
}

void negativeText(){
  printf("\033[47;30m");
}

void crossedText(){
  printf("\033[9m");
}

void drawSelbox(byte x, byte y){
  setCursor(x, y-1); putchar('[');
  setCursor(x, y+1); putchar(']');
}

void drawCursor(byte y, byte x, int r, BoatType type){
  int actX = 3, actY = 6;
  for(; x; x--) actX += 1;
  for(; y; y--) actY += 3;
  for(int i=0; i<getBoatLengthFromType(type); i++){
    if(r == 0 || r == 180 || r == -180){
      if(!r) drawSelbox(actX, actY+(i*3));
      else drawSelbox(actX, actY-(i*3));
    }else{
      if(r==90 || r==-270) drawSelbox(actX-i, actY);
      else drawSelbox(actX+i, actY);
    }
  }
  setCursorWithOffset(y, x);
}

#endif //endif __TEXTUTILS_H__
