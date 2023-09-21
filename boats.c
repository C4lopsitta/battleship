#include "headers/boats.h"

char getBoatCharByType(BoatType type, int isSecond){
  char chars[] = {CARRIER, BATTLESHIP, CRUISER, DESTROYERA, DESTROYERB,
    SUBMARINEA, SUBMARINEB};
  return chars[(type<=BOAT_CRUISER)?type:(type==BOAT_DESTROYER)?type+isSecond:type+isSecond+1];
}

String getBoatStringByType(BoatType type){
  String strs[] = {"Carrier", "Battleship", "Cruiser", "Destroyer", "Submarine"};
  return strdup(strs[type]);
}

int getBoatLengthFromType(BoatType type){
  int sizes[] = {5, 4, 3, 2, 1};
  return sizes[type];
}

int isPlaceFree(Player*p, byte x, byte y, BoatType type, int rotation){
  int boatLenght = getBoatLengthFromType(type), flag = boatLenght;
  if(rotation == 0){ // ->
    for(int i=0; i<boatLenght && x+i<FIELD_Y; i++){
      if(p->field[y+i][x]==WATER) flag--;
      else break;
    }
  }else if(rotation == 90 || rotation == -270){ // /
    for(int i=0; i<boatLenght && x-i>=0; i++){
      if(p->field[y][x-i]==WATER) flag--;
      else break;
    }
  }else if(rotation == 180 || rotation == -180){ // <-
    for(int i=0; i<boatLenght && y-i>=0; i++){
      if(p->field[y-i][x]==WATER) flag--;
      else break;
    }
  }else{ // 360
    for(int i=0; i<boatLenght && x+i<FIELD_X; i++){
      if(p->field[y][x+i]==WATER) flag--;
      else break;
    }
  }
  return (flag)?0:-1;
}

int putBoat(Player*p, byte x, byte y, BoatType type, int rotation, int isSecond){
  //check if positions are free
  if(isPlaceFree(p, x, y, type, rotation)){
    int boatLenght = getBoatLengthFromType(type);
    if(rotation == 0){
      for(int i=0; i<boatLenght && y+i<FIELD_Y; i++)
        p->field[y+i][x] = getBoatCharByType(type, isSecond);
    }
    else if(rotation == 90 || rotation == -270){
      for(int i=0; i<boatLenght && x-i>=0; i++)
        p->field[y][x-i] = getBoatCharByType(type, isSecond);
    }
    else if(rotation == 180 || rotation == -180)
      for(int i=0; i<boatLenght && y-i>=0; i++){
        p->field[y-i][x] = getBoatCharByType(type, isSecond);
    }
    else{
      for(int i=0; i<boatLenght && x+i<FIELD_X; i++)
        p->field[y][x+i] = getBoatCharByType(type, isSecond);         
    }
    return PLACE_CONFIRM;
  }
  return PLACE_NOSPACE;
}


int boatsLeft(Player*p){
  int b = 0;
  for(int i=0; i<5; i++) b += p->boats[i];
  return b;
}

int getBoatLengthFromChar(char c){
  c -= 'a'+DELTA;
  int lenghts[] = {-1, 5, 4, 3, 2, 2, 1, 1};
  return lenghts[c];
}

int isBoatFullyHit(Player*p, int x, int y){
  BoatType type = getBoatTypeByChar(p->field[y][x]);
  if(type == BOAT_SUBMARINE) return -1;
  if(type == BOAT_DESTROYER && p->field[y][x] == HIT_DESTROYERB) type++;
  p->boatsHealth[type]--;
  return (p->boatsHealth[type])?0:-1;
}

BoatType getBoatTypeByChar(char c){
  c -= 'a';
  if(c >= DELTA) c -= DELTA;
  if(c == 0) return -1;
  c--;
  BoatType types[] = {BOAT_CARRIER, BOAT_BATTLESHIP, BOAT_CRUISER, BOAT_DESTROYER,BOAT_DESTROYER, BOAT_SUBMARINE, BOAT_SUBMARINE};
  return types[c];
}

int hitBoat(Player*p, byte y, byte x){
  char fieldPos = p->field[y][x];
  if(fieldPos >= HIT_WATER) return SHOT_DOUBLE;
  p->field[y][x] += DELTA;
  if(fieldPos == WATER) return SHOT_MISS;
  if(isBoatFullyHit(p, x, y)){
    p->boats[getBoatTypeByChar(p->field[y][x])]--;
  }
  return SHOT_HIT;
}

