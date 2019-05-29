#include <Arduboy2.h>
Arduboy2 arduboy;

String projectName = "RotatingCubeDemo";

enum GameState {MAIN_MENU, GAME_PLAYING, GAME_OVER};
GameState gamestate;

int cube[][3] = {
    {-15,-15,-15},
    {15, -15, -15},
    {15, 15, -15},
    {-15, 15, -15},
    {-15,-15,15},
    {15, -15, 15},
    {15, 15, 15},
    {-15, 15, 15}
  };

double display_cube[][3] = {
    {-15,-15,-15},
    {15, -15, -15},
    {15, 15, -15},
    {-15, 15, -15},
    {-15,-15,15},
    {15, -15, 15},
    {15, 15, 15},
    {-15, 15, 15}
  };

  int vDegree = 0;
  int hDegree = 0;
  
  bool showUI = false;
  bool correct = false;

void setup() {
  // put your setup code here, to run once:
  
  arduboy.begin();
  arduboy.setFrameRate(15);
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
    if(arduboy.pressed(LEFT_BUTTON)) {
      vDegree += 359;
      vDegree %= 360;
    }

    if(arduboy.pressed(DOWN_BUTTON)) {
      hDegree += 359;
      hDegree %= 360;
    }

    if(arduboy.pressed(UP_BUTTON)) {
      hDegree += 361;
      hDegree %= 360;
    }

    if(arduboy.pressed(RIGHT_BUTTON)) {
      vDegree += 361;
      vDegree %= 360;
    }

    if(arduboy.justPressed(B_BUTTON) || arduboy.justPressed(A_BUTTON)) {
      showUI = !showUI;
    }
    
    drawCube();
    if(showUI) {
      drawUI();
    }
  }

  arduboy.display();
}

void drawCube() {
  for(byte i = 0; i < 8; i++) {
      calcPos(i);
    }

  for(byte i = 0; i < 8; i++) {
      int newpos[2] = {(int)round(display_cube[i][0])+ 64, (int)round(display_cube[i][1]) + 32};
      arduboy.drawPixel(newpos[0], newpos[1]);
  }

  drawCubeEdge(0, 1);
  drawCubeEdge(0, 3);
  drawCubeEdge(0, 4);
  drawCubeEdge(1, 2);
  drawCubeEdge(1, 5);
  drawCubeEdge(2, 3);
  drawCubeEdge(2, 6);
  drawCubeEdge(3, 7);
  drawCubeEdge(4, 5);
  drawCubeEdge(4, 7);
  drawCubeEdge(5, 6);
  drawCubeEdge(6, 7);
}

void drawCubeEdge(int a, int b) {
  arduboy.drawLine(
      (int)round(display_cube[a][0]) + 64,
      (int)round(display_cube[a][1]) + 32,
      (int)round(display_cube[b][0]) + 64,
      (int)round(display_cube[b][1]) + 32
    );
}

void calcPos(int vertex) {

  double x = (double)cube[vertex][0];
  double y = (double)cube[vertex][1];
  double z = (double)cube[vertex][2];

    double* pos_1 = rotateY(x, y, z, vDegree*PI/180.0);
    double* pos_2 = rotateX(pos_1[0], pos_1[1], pos_1[2], hDegree*PI/180.0);
    display_cube[vertex][0] = pos_2[0];
    display_cube[vertex][1] = pos_2[1];
    display_cube[vertex][2] = pos_2[2];
    free(pos_1);
    free(pos_2);
}

double* cross(double* a, double* b) {
  double* ret = (double*)malloc(3* sizeof(double));
  ret[0] = a[1]*b[2]-a[2]*b[1];
  ret[1] = a[2]*b[0] - a[0]*b[2];
  ret[2] = a[0]*b[1] - a[1]*b[0];
  return ret;
}

void normalize(double* v) {
  double s = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
  v[0] /= s;
  v[1] /= s;
  v[2] /= s;
}

double* rotateX(double x, double y, double z, double d) {
  double cos_d = cos(d);
  double sin_d = sin(d);
  double* pos = (double*)malloc(sizeof(double)*3);

  pos[0] = x;
  pos[1] = cos_d*y + sin_d*z;
  pos[2] = -sin_d*y + cos_d*z;
  return pos;
}

double* rotateY(double x, double y, double z, double d) {
  double cos_d = cos(d);
  double sin_d = sin(d);
  double* pos = (double*)malloc(sizeof(double)*3);

  pos[0] = cos_d*x - sin_d*z;
  pos[1] = y;
  pos[2] = sin_d*x + cos_d*z;
  return pos;
}

void drawUI() {
  arduboy.drawLine(0, 32, 127, 32);
  arduboy.drawLine(64, 0, 64, 63);
  arduboy.setCursor(66, 0);
  arduboy.print(vDegree);
  arduboy.setCursor(0, 34);
  arduboy.print(hDegree);
}

void displayMainMenu() {
    int len = projectName.length();
    len = 3*len+1;
    arduboy.setCursor(64-len,27);
    arduboy.write(projectName.c_str());
}
