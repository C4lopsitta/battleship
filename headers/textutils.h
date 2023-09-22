#ifndef __TEXTUTILS_H__
#define __TEXTUTILS_H__

#include <sys/ioctl.h>
#include <stdio.h>
#include <stdlib.h>

#include "defines.h"

void setCursor(int x, int y);
void setCursorWithOffset();
void clearScreen();
void clearLine();
void getTerminalSize(int*, int*);
void clearText();
void boldText();
void underText();
void redText();
void rgbText(int, int, int);
void negativeText();
void crossedText();
void drawSelbox(byte, byte);
void drawCursor(byte, byte, int, BoatType);

#endif //endif __TEXTUTILS_H__
