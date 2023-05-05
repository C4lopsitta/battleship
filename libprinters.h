#ifndef __LIB_PRINTERS_H__
#define __LIB_PRINTERS_H__

void printHintbar();
void mesg(String);
void mesgWarn(String);void printFieldItem(char);
void printFieldItemHidden(char);
void printPlayerField(Player*);
void printPlayerFieldHidden(Player*);


void printHintbar(String returnMesg, int showRotate){
  negativeText();
  setCursor(HINT_X, HINT_Y);
  printf("[W] Move up   [A] Move left  [S] Move down   [D] Move right\n[return] %s   %-s[ctrl-c] Quit game               \n"
      , returnMesg, (showRotate)?"[r] Rotate 90deg   [s-r] Rotate -90deg\n":"");
  clearText();
}

void mesg(String mesgs){
  setCursor(MESG_X, MESG_Y);
  printf("%s\n", mesgs);
}

void mesgWarn(String mesgs){
  redText();
  mesg(mesgs);
  clearText();
}

void printFieldItem(char item){
  String items[] = {" . ", " C ", " B ", "~C~", " D ", " D ", " S ", " S "};
  if(item > SUBMARINEB) crossedText();
  printf("%s", items[(item-'a'>DELTA)?item-'a'-DELTA:item-'a']);
  clearText();
}

void printFieldItemHidden(char item){
  String items[] = {" . ", " C ", " B ", "~C~", " D ", " D ", " S ", " S "};
  if(item > SUBMARINEB) crossedText();
  printf("%s", (item-'a'>DELTA)?items[item-'a'-DELTA]:" . ");
  clearText();
}

void printPlayerField(Player*p){
  boldText();
  if(p->type == 'a'){
    printf("-------[ ai ]----------------------\n");
  }else{
    printf("-------[ p%c ]----------------------\n", p->type);
  }
  rgbText(127, 127, 127);
  printf("     1  2  3  4  5  6  7  8  9  10\n");
  for(int i=0; i<FIELD_Y; i++){
    boldText();
    rgbText(127, 127, 127);
    printf(" %2d ", i+1);
    clearText();
    for(int j=0; j<FIELD_X; j++)
      printFieldItem(p->field[j][i]);
    putchar('\n'); 
  }
}

void printPlayerFieldHidden(Player*p){
    if(p->type == 'a'){
    printf("-------[ ai ]----------------------\n     1  2  3  4  5  6  7  8  9  10\n");
  }else{
    printf("-------[ p%c ]----------------------\n     1  2  3  4  5  6  7  8  9  10\n", p->type);
  }
  for(int i=0; i<FIELD_Y; i++){
    printf(" %2d ", i+1);
    for(int j=0; j<FIELD_X; j++)
      printFieldItemHidden(p->field[j][i]);
    putchar('\n');
  }
}

void printTooltip(int*p, String extramsg){
  setCursor(TOOLTIP_X, TOOLTIP_Y);
  String items[] = {" C ", " B ", "~C~", " D ", " S "};
  printf("---[ TOOLTIP ]----------");
  int i;
  for( i=0; i < 5; i++){
    setCursor(TOOLTIP_X+i+1, TOOLTIP_Y);
    String str = getBoatStringByType((BoatType)i);
    printf(" [%3s] %s : %d      ", items[i], str, p[i]);
    free(str);
  }
  setCursor(TOOLTIP_X+i+1, TOOLTIP_Y);
  printf("%s", extramsg);
  fflush(stdout);
}

char printSplashscreen(){
  setCursor(4, 12);
  printf("---[ BATTLESHIPS ]---");
  setCursor(9, 5);
  rgbText(127, 127, 127);
  printf("---[h]   [  HUMAN VS COMPUTER  ]---");
  setCursor(10, 5);
  printf("---[m]   [   HUAMN VS HUMAN    ]---");
  setCursor(11, 5);
  printf("---[s]   [ SERIAL  MULTIPLAYER ]---");
  setCursor(13, 5);
  clearText();
  printf("---[ PRESS ANY KEY TO CONTINUE ]---");
  return getUserInput();
}

#endif //endif __LIB_PRINTERS_H__