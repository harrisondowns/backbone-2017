/*  
 *  SpriteMaker.ino - responsible for the sprite maker, aka the paint
 *  program that allows a person to draw sprites to use later.
*/

// Save button coordinates
#define saveX 70
#define saveY 60
#define saveW 30

// ui vars
#define sbX 110
#define sbY 40
#define sbS 24
#define sbMX (sbX + (8 * sbS))
#define sbMY (sbY + (8 * sbS))

int oldcolor, currentcolor;
int colorInd = 0;

void drawSpriteMaker(void){
  tft.fillScreen(BLACK);
  for (int x = 0; x < 2; x++){
    for (int y = 0; y < 8; y++){
      tft.fillRect(1 + x * BOXSIZE, BOXSIZE*y + 1, BOXSIZE, BOXSIZE, colors[x * 8 + y]);
    }
  }

  // color box horizontal lines
  for (int y = 0; y < 9; y++){
    tft.drawLine(0, y * BOXSIZE, BOXSIZE * 2, y * BOXSIZE, WHITE);
  }

  // color pallet box frame
  tft.drawLine(0, 239, BOXSIZE * 2, 239, WHITE);
  tft.drawLine(0, 0, 0, 239, WHITE);
  tft.drawLine(BOXSIZE, 0, BOXSIZE, 240, WHITE);
  tft.drawLine(BOXSIZE * 2, 0, BOXSIZE * 2, 240, WHITE);

  unsigned long start = micros();
  
 

 // top line
  tft.drawLine(sbX, sbY, sbX, sbMY, WHITE);

  // bottom line of grid
  tft.drawLine(sbX, sbMY, sbMX, sbMY, WHITE);

  // vertical grid lines
  for (int x = 0; x < 9; x++){
    int u = x * sbS;
    tft.drawLine(sbX + u, sbY, sbX + u, sbMY, WHITE);
  }

  // horizontal grid lines
  for (int y = 0; y < 9; y++){
    int v = y * 12 * 2;
    tft.drawLine(sbX, sbY + v, sbMX, sbY + v, WHITE);
  }
  osState = 1;

  for (int y = 0; y < 8; y++){
    for (int x = 0; x < 8; x++){
      tft.fillRect(sbX + x * sbS + 1, sbY + y * sbS + 1, sbS - 1, sbS - 1, colors[sprites[currentSprite][x][y]]);
      makeButton(sbX + x * sbS + 1, sbY + y * sbS + 1, sbS - 1, sbS - 1, 
                              colors[sprites[currentSprite][x][y]], WHITE, BLACK, "", placeTile, y * 8 + x) ;

    }
  }
  Button *back = makeButton(saveX, saveY, saveW, saveW, BLUE, WHITE, WHITE, "Exit", popState, 0);
  drawButton(back);
  tft.setCursor(100, 10);
  tft.setTextColor(WHITE);  
  tft.setTextSize(3);
  tft.println("Sprite Maker");
}

/* placeTile() - function responsible for coloring in a specific tile of the sprite maker. */
void placeTile(int i){
  Button *b = buttons->at(i); 
  Serial.println("i: ");
  Serial.println(i);
  tft.fillRect(b->x, b->y, sbS - 1, sbS - 1, currentcolor);
  int x = i % 8;
  int y = i / 8;
  sprites[currentSprite][x][y] = colorInd;
     
}

void runSpriteMaker(void){
  TSPoint p = getTouchPoint(); //ts.getPoint();
  if (p.z == 500){
    if (p.x < BOXSIZE) {
         oldcolor = currentcolor;
         currentcolor = colors[p.y / 30];
         colorInd = (p.y / 30);
         
     }
     else if (p.x < BOXSIZE * 2){
        oldcolor = currentcolor;
        colorInd = (p.y / 30) + 8;
        currentcolor = colors[(p.y / 30) + 8];
     }
  
  // if selecting a square on board
    for (int i = 0; i < buttons->size(); i++){
      Button *b = buttons->at(i);
      if (p.x >= b->x && p.x < b->x + b->w && p.y >= b->y && p.y < b->y + b->h){
        b->callFunc(b->p);
        break;
      }
  
      
    }
  }
    
  
}

