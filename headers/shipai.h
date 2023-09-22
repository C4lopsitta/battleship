#ifndef __SHIP_AI_H__
#define __SHIP_AI_H__

#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "utils.h"
#include "defines.h"
#include "printers.h"
#include "textutils.h"

Player* setupAI();
void generateRandomField(Player*);
void aiTurn(Player*ai, Player*pl);

#endif //endif __SHIP_AI_H__
