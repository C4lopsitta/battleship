#ifndef __LIBUTILS_H__
#define __LIBUTILS_H__

#include <signal.h>
#include <termios.h>

#include "boats.h"
#include "textutils.h"
#include "printers.h"
#include "shipai.h"

void sigint_handler(int sig_num);

void error(byte, String, ...);
void mesgDebug(String, ...);

void fillField(Player*);
void setBoats(Player*);

Player* setupPlayer(int);
void setupPlayerBoats(Player*);
int handleWASDInput(char, byte*, byte*);
void setCursorWithOffset(int, int);
char getUserInput();

void playerTurn(Player*pl, Player*pl2);
void awaitUserConfirm();
void singlePlayer();

String readline(FILE*fp);
String* split(String s, String d);
void initConfig();
String getJSONKey(String line);
String getJSONValue(String line);
Config* loadConfig();
void updateConfig();
void hideAndAwait(char awaitChar, String mesgs);

void ptrArrCopy(String* o, String* d){
  for(; *d = *o; d++, o++){};
}


#endif //endif __LIBUTILS_H__
