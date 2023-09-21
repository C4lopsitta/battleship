#ifndef __LIB_BOATS_H__
#define __LIB_BOATS_H__

#include <stdlib.h>
#include <string.h>

#include "defines.h"

char getBoatCharByType(BoatType, int);
int getBoatLengthFromType(BoatType);
int putBoat(Player*, byte, byte, BoatType, int, int);
void removeBoat(Player*, byte, byte);
int boatsLeft(Player*);
int isBoatFullyHit(Player*, int, int);
BoatType getBoatTypeByChar(char);
int hitBoat(Player*, byte, byte);

/*  BOATS                                       ROTATION DIRECTION
 *        C is the centre of rotation           
 *  Aircraft Carrier  Destroyer     Submarine   0   ->
 *                                              
 *  C X X X X (5)     C X (2x2)     C (1x2)     90  /\
 *                                              
 *  Battleship        Cruiser                   180 <-
 *                                              
 *  C X X X (4)       C X X (3)                 270 \/
 *                                              
 */



#endif //endif __LIB_BOATS_H__
