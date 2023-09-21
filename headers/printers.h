#ifndef __LIB_PRINTERS_H__
#define __LIB_PRINTERS_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

#include "textutils.h"
#include "defines.h"

void printHintbar();
void mesg(String);
void mesgWarn(String);
void printFieldItem(char);
void mesgDebug(String fmt, ...){}
void printFieldItemHidden(char);
void printPlayerField(Player*);
void printPlayerFieldHidden(Player*);
void printTooltip(int*p, String extramsg);
char printSplashscreen();

#endif //endif __LIB_PRINTERS_H__
