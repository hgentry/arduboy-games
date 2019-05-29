#include <Arduboy2.h>
Arduboy2 arduboy;

enum GameState {MAIN_MENU, GAME_PLAYING, GAME_OVER};
GameState gamestate;

String projectName = "CodeTemplate";

void setup() {
  // put your setup code here, to run once:
  
  arduboy.begin();
  arduboy.clear();

  gamestate = MAIN_MENU;
}

void loop() {
  arduboy.clear();
  arduboy.pollButtons();
  
  if(gamestate == MAIN_MENU) {
    displayMainMenu();

    if(arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
      gamestate = GAME_PLAYING;
    }
  }
  else if(gamestate == GAME_PLAYING) {
    if(arduboy.justPressed(LEFT_BUTTON)) {
      
    }

    if(arduboy.justPressed(DOWN_BUTTON)) {

    }

    if(arduboy.justPressed(UP_BUTTON)) {

    }

    if(arduboy.justPressed(RIGHT_BUTTON)) {

    }

  }

  arduboy.display();
}

void displayMainMenu() {
    int len = projectName.length();
    len = 3*len+1;
    arduboy.setCursor(64-len,27);
    arduboy.write(projectName.c_str());
}
