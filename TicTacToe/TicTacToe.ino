#include <Arduboy2.h>
Arduboy2 arduboy;

enum GameState {MAIN_MENU, GAME_PLAYING, GAME_OVER};
enum BoardPiece {N,X,O};
int draw_row[] = {1, 23, 45};
int draw_column[] = {1, 23, 45};
int o_wins;
int x_wins;
int ties;
BoardPiece turn;
GameState gamestate;
int highlightCounter;
int highlight;
int winstyle;

BoardPiece board[] = {N,N,N,N,N,N,N,N,N};



void setup() {
  // put your setup code here, to run once:
  
  arduboy.begin();
  arduboy.clear();

  gamestate = MAIN_MENU;
  x_wins = 0;
  o_wins = 0;
  ties = 0;
}

void gameplay_setup() {
    gamestate = GAME_PLAYING;
    turn = X;
    highlight = 0;
    highlightCounter = 90;
    winstyle = 0;
}

void loop() {
  arduboy.clear();
  arduboy.pollButtons();
  
  if(gamestate == MAIN_MENU) {
    arduboy.setCursor(37,27);
    arduboy.write("TicTacToe");

    if(arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
      gameplay_setup();
    }
  }
  else if(gamestate == GAME_PLAYING) {
    arduboy.setCursor(0,0);
    drawBoard();
    drawUI();
    drawHighlight();

    if(arduboy.justPressed(LEFT_BUTTON)) {
      do {
        highlight += 8;
        highlight = highlight % 9;
      } while(board[highlight] != N);
    }

    if(arduboy.justPressed(DOWN_BUTTON)) {
      if(board[(highlight+3)%9] == N) {
        highlight = (highlight+3)%9;
      } else if(board[(highlight+6)%9] == N) {
        highlight = (highlight+6)%9;
      }
    }

    if(arduboy.justPressed(UP_BUTTON)) {
      if(board[(highlight+6)%9] == N) {
        highlight = (highlight+6)%9;
      } else if(board[(highlight+3)%9] == N) {
        highlight = (highlight+3)%9;
      }
    }

    if(arduboy.justPressed(RIGHT_BUTTON)) {
      do {
        highlight += 1;
        highlight = highlight % 9;
      } while(board[highlight] != N);
    }
    if(arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
      mark();
      checkWin();
      if(turn == X) {
        turn = O;
      }
      else if(turn == O) {
        turn = X;
      }
      
    }
  } else if(gamestate == GAME_OVER) {
    arduboy.setCursor(0,0);
    drawBoard();
    drawUI();

    if(arduboy.justPressed(A_BUTTON) || arduboy.justPressed(B_BUTTON)) {
      for(int i = 0; i < 9; i++) {
          board[i] = N;
      }
      gamestate = MAIN_MENU;
    }
  }

  arduboy.display();
}

void drawBoard() {
  arduboy.drawLine(21,1,21,62);
  arduboy.drawLine(43,1,43,62);
  arduboy.drawLine(1,21,62,21);
  arduboy.drawLine(1,43,62,43);

  for(int i = 0; i < 9; i++) {
    if(board[i] == X || board[i] == O) {
        int rowpos = i % 3;
        int colpos = i / 3;
      
        int draw_x = draw_row[rowpos] + 1;
        int draw_y = draw_column[colpos] + 1;

        if(board[i] == X) {
            arduboy.drawLine(draw_x, draw_y, draw_x + 17, draw_y + 17);
            arduboy.drawLine(draw_x + 17, draw_y, draw_x, draw_y + 17);
        }
        if(board[i] == O) {
          arduboy.drawCircle(draw_x + 8, draw_y + 8, 8);
        }
    }
  }

   switch(winstyle) {
    case 1: arduboy.drawLine(0,10,62,10); break;
    case 6: arduboy.drawLine(0,32,62,32); break;
    case 7: arduboy.drawLine(0,54,62,54); break;
    case 2: arduboy.drawLine(10,0,10,62); break;
    case 4: arduboy.drawLine(32,0,32,62); break;
    case 5: arduboy.drawLine(54,0,54,62); break;
    case 3: arduboy.drawLine(3,0, 61, 62); break;
    case 8: arduboy.drawLine(5,62,64,0); break;
    default: break;
  }
}

void drawUI() {
  arduboy.setCursor(64,0);
  arduboy.write("TicTacToe");
  String turnStr;
  if(gamestate == GAME_OVER) {
    turnStr = "Game Over";
  }
  else if(turn == O) {
        turnStr = "O's Turn";
  } else {
        turnStr = "X's Turn";
  }

  arduboy.setCursor(64,12);
  arduboy.write(turnStr.c_str());

  arduboy.setCursor(64,24);
  arduboy.print("X: ");
  arduboy.print(x_wins);

  arduboy.setCursor(64,36);
  arduboy.print("O: ");
  arduboy.print(o_wins);

  arduboy.setCursor(64,48);
  arduboy.print("T: ");
  arduboy.print(ties);
}

void drawHighlight() {
  if(highlight == 9) return;
  int rowpos = highlight % 3;
  int colpos = highlight / 3;

  int draw_x = draw_row[rowpos] + 1;
  int draw_y = draw_column[colpos] + 1;
  
  arduboy.drawRect(draw_x, draw_y, 17, 17);

}

void mark() {
  board[highlight] = turn;
  highlight = 0;
  while(board[highlight] != N) {
    highlight += 1;
    if(highlight == 9) {
      break;
    }
  }
}

void checkWin(){
  if(board[0] == board[1] && board[0] == board[2] && board[0] != N) {
    winstyle = 1;
  }
  if(board[0] == board[3] && board[0] == board[6] && board[0] != N) {
    winstyle = 2;
  }
  if(board[0] == board[4] && board[0] == board[8] && board[0] != N) {
    winstyle = 3;
  }
  if(board[1] == board[4] && board[1] == board[7] && board[1] != N) {
    winstyle =4;
  }
  if(board[2] == board[5] && board[2] == board[8] && board[2] != N) {
    winstyle = 5;
  }
  if(board[3] == board[4] && board[3] == board[5] && board[3] != N) {
    winstyle = 6;
  }
  if(board[6] == board[7] && board[6] == board[8] && board[6] != N) {
    winstyle = 7;
  }
  if(board[6] == board[4] && board[6] == board[2] && board[6] != N) {
    winstyle = 8;
  }
    if(winstyle > 0) {
        gamestate = GAME_OVER;
        if(turn == X) {
          x_wins += 1;
        } else {
          o_wins += 1;
        }
      } else {
        int i;
        for(i = 0; i < 9; i++) {
          if(board[i] == N) {
            break;
          }
        }
        if(i == 9) {
          gamestate = GAME_OVER;
          ties += 1;
          winstyle = 9;
        }
      }
}
