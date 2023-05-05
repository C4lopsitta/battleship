#ifndef __SHIP_AI_H__
#define __SHIP_AI_H__

Player* setupAI();
void generateRandomField(Player*);

Player* setupAI(){
  Player* player = (Player*)malloc(sizeof(Player));
  setBoats(player);
  player -> type = 'a';
  player -> tries = 0;
  generateRandomField(player);
  return player;
}

void generateRandomField(Player*p){
  srand(time(NULL) * getpid());
  fillField(p);
  // first three single boats
  for(int i=0; i<5; i++) while(p->boats[i]){
      int x = rand()%10, y = rand()%10, r = ((rand()%32)*90)%360;
      if((putBoat(p, x, y, (BoatType)i, r, p->boats[i]-1)) == PLACE_CONFIRM)
        p->boats[i]--;
  }
  setBoats(p);
}

void aiTurn(Player*ai, Player*pl){

}

#endif //endif __SHIP_AI_H__
