#include "headers/utils.h"

void sigint_handler(int sig_num){
  clearScreen();
  setCursor(1, 1);
  printf("Exiting game\n");
  exit(0);
}

void error(byte errOp, String fmt, ...){
  va_list args;
  setCursor(MESG_X+5, MESG_Y);
  if(errOp) clearScreen();
  va_start(args, fmt);
  clearLine();
  vprintf(fmt, args);
  va_end(args);
  fflush(stdout);
  if(errOp) exit(errOp);
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
    printPlayerFieldHidden(pl2);
    printTooltip(pl->boats, "---[ Your boats ]---");
    setCursorWithOffset(xcur, ycur);
  }
}

void awaitUserConfirm(){
  printHintbar("Continue", 0);
  while(getUserInput() != '\n');
}

void singlePlayer(){
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
}

String readline(FILE*fp){
  char buf[128];
  unsigned char i = 0;
  for(; buf[i]=fgetc(fp) , buf[i] != EOF , buf[i] != '\n'; i++){};
  buf[i] = '\0';
  if(!i) return NULL;
  return strdup(buf);
}

String* split(String s, String d){
  String tmparr[256];
  char i = 0;
  String tok = strtok(s, d);
  if(!tok) return NULL;
  tmparr[i] = strdup(tok);
  for(i = 1; (tok = strtok(NULL, d)) && i<255; i++){
    tmparr[i] = strdup(tok);
  }
  tmparr[i+1] = NULL;
  String* ret = (String*)malloc(sizeof(String) * i + 1);
  memcpy(ret, tmparr, (i+1));
  return ret;
}

void initConfig(){
  FILE* fp = fopen(CONFIG_FILE, "w");
  fprintf(fp, 
          "{\n\t\"ai_difficulty\" : \"0\",\n\t\"max_tries\" : \"100\",\n\t\"tooltip\" : \"true\",\n\t\"hintbar\" : \"true\",\n\t\"net_iface\" : \"wlan0\"\n}\n"
          );
  fclose(fp);
}

String getJSONKey(String line){
  char* begin = strchr(line, '"');
  if(!begin) error(254, 
                   "[ERROR] JSON isn't correctly formatted!\n[INFO] A line is missing the first \'\"\' character\n"
                   );
  begin++;
  char* end = strchr(begin, '"');
  if(!end) error(254, 
                 "[ERROR] JSON isn't correctly formatted!\n[INFO] A line is missing the second \'\"\' character\n"
                 );
  char buf[32], i = 0;
  for(; buf[i] = *begin, begin<end; i++, begin++){};
  buf[i] = '\0';
  return strdup(buf);
}

String getJSONValue(String line){
  char* begin = strchr(line, ':');
  if(!begin) error(253, "[ERROR] Missing \':\' in value!");
  begin = strchr(begin, '"');
  if(!begin) error(253, "[ERROR] Missing \'\"\' in value!"); begin++; 
  char* end = strchr(begin, '"');
  if(!end) error(253, "[ERROR] Missing ending \'\"\' in value!");
  char buf[32], i = 0;
  for(; buf[i] = *begin, begin<end; i++, begin++){};
  buf[i] = '\0';
  return strdup(buf);
}

Config* loadConfig(){
  FILE* fp = fopen(CONFIG_FILE, "r");
  if(!fp){
    initConfig();
    return loadConfig();
  }
  String line = readline(fp);
  if(!line) error(255, "[ERROR] JSON is empty!\n[INFO] Delete the %s file and retry!\n", CONFIG_FILE);
  if(!strchr(line, '{')) error(255, "[ERROR] JSON is not correctly formatted!\n[INFO] Either delete the %s file or fix the formatting!\n", CONFIG_FILE);
  Config* config = (Config*)malloc(sizeof(Config));
  free(line);
  while((line = readline(fp))){
    if(strchr(line, '}')) break;
    String key = getJSONKey(line), value = getJSONValue(line);
    free(line);
    if(!strcmp(key, "ai_difficulty")) config->aiDifficulty = atoi(value);
    else if(!strcmp(key, "max_tries")) config->maxTries = atoi(value);
    else if(!strcmp(key, "tooltip")) config->tooltip = !strcmp(value, "true");
    else if(!strcmp(key, "hintbar")) config->hintbar = !strcmp(value, "true");
    else if(!strcmp(key, "net_iface")) config->netIface = strdup(value);
    else error(255, "[ERROR] Unknown key in %s file!\n[INFO] Key: %s\n", CONFIG_FILE, key);
    free(key);
    free(value);
  }
  fclose(fp);
  return config;
}

void updateConfig(){
  return;
}

void hideAndAwait(char awaitChar, String mesgs){
  clearScreen();
  setCursor(5, 5);
  printf("%s\n", mesgs);
  while(getUserInput() != awaitChar){};
}



