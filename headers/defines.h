#ifndef __LIB_DEFINES_H__
#define __LIB_DEFINES_H__

#define FIELD_X 10
#define FIELD_Y 10
#define PLAYER_1 '1'
#define PLAYER_2 '2'
#define SHOT_HIT 1
#define SHOT_MISS 0
#define SHOT_DOUBLE -1
#define PLACE_CONFIRM 1
#define PLACE_REMOVED 0
#define PLACE_NOSPACE -1

#define HINT_X 15
#define HINT_Y 1
#define MESG_X 14
#define MESG_Y 1
#define TOOLTIP_X 4
#define TOOLTIP_Y 42

#define WATER 'a'
#define CARRIER 'b'
#define BATTLESHIP 'c'
#define CRUISER 'd'
#define DESTROYERA 'e'
#define DESTROYERB 'f'
#define SUBMARINEA 'g'
#define SUBMARINEB 'h'
#define HIT_WATER 'i'
#define HIT_CARRIER 'j'
#define HIT_BATTLESHIP 'k'
#define HIT_CRUISER 'l'
#define HIT_DESTROYERA 'm'
#define HIT_DESTROYERB 'n'
#define HIT_SUBMARINEA 'o'
#define HIT_SUBMARINEB 'p'

#define DELTA 8

#define CARRIERS 1
#define BATTLESHIPS 1
#define CRUISERS 1
#define DESTROYERS 2
#define SUBMARINES 2

#define CONFIG_FILE "config.json"

typedef char* String;
typedef char byte;

typedef enum{
  BOAT_CARRIER,
  BOAT_BATTLESHIP,
  BOAT_CRUISER,
  BOAT_DESTROYER,
  BOAT_SUBMARINE,
}BoatType;

// typedef struct{
//   byte carrier;
//   byte battleship;
//   byte cruiser;
//   byte destroyer;
//   byte submarine;
// }Boats;

typedef struct{
  byte field[FIELD_Y][FIELD_X];
  int boats[5];
  byte boatsHealth[5];
  char type;
  byte tries;
}Player;

typedef struct{
  char aiDifficulty;
  char maxTries;
  char tooltip;
  char hintbar;
  String netIface;
}Config;

Config* config;

#endif //endif __LIB_DEFINES_H__
