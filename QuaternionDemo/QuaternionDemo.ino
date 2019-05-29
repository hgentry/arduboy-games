#include <Arduboy2.h>
Arduboy2 arduboy;

String projectName = "QuaternionDemo";

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

  

  double rot[4] = {0,0,1,0};
  double Qy[4] = {cos(PI/360.0),0,sin(PI/360.0),0};
  double Qx[4] = {cos(PI/360.0),sin(PI/360.0),0,0};
  double Qyn[4] = {cos(-PI/360.0),0,sin(-PI/360.0),0};
  double Qxn[4] = {cos(-PI/360.0),sin(-PI/360.0),0,0};
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
      applyToRot(Qyn);
    }

    if(arduboy.pressed(DOWN_BUTTON)) {
      applyToRot(Qxn);
    }

    if(arduboy.pressed(UP_BUTTON)) {
      applyToRot(Qx);
    }

    if(arduboy.pressed(RIGHT_BUTTON)) {
      applyToRot(Qy);
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
      (int)round(display_cube[a][0]) + 32,
      (int)round(display_cube[a][1]) + 32,
      (int)round(display_cube[b][0]) + 32,
      (int)round(display_cube[b][1]) + 32
    );
}

void calcPos(int vertex) {

  double x = (double)cube[vertex][0];
  double y = (double)cube[vertex][1];
  double z = (double)cube[vertex][2];
  double p[3] = {x,y,z};
    double* pos_2 = rotatePoint(p,rot);
    

    display_cube[vertex][0] = pos_2[0];
    display_cube[vertex][1] = pos_2[1];
    display_cube[vertex][2] = pos_2[2];
    free(pos_2);
  
}

double* cross(double* q, double* r) {
  double* ret = (double*)malloc(4 * sizeof(double));
  ret[0] = r[0]*q[0] - r[1]*q[1] - r[2]*q[2] - r[3]*q[3];
  ret[1] = r[0]*q[1] + r[1]*q[0] - r[2]*q[3] + r[3]*q[2];
  ret[2] = r[0]*q[2] + r[1]*q[3] + r[2]*q[0] - r[3]*q[1];
  ret[3] = r[0]*q[3] - r[1]*q[2] + r[2]*q[1] + r[3]*q[0];
  normalize(ret);
  return ret;
}

double* conjugate(double* q) {
  double* ret = (double*)malloc(4 * sizeof(double));
  ret[0] = q[0];
  ret[1] = -q[1];
  ret[2] = -q[2];
  ret[3] = -q[3];
  return ret;
}

double* rotatePoint(double* p, double* q) {
  double x = p[0];
  double y = p[1];
  double z = p[2];
  double qr = q[0];
  double qi = q[1];
  double qj = q[2];
  double qk = q[3];
  double* ret = (double*)malloc(3 * sizeof(double));

  ret[0] = (1- 2*(qj*qj+qk*qk))*x + 2*(qi*qj-qk*qr)*y + 2*(qi*qk + qj*qr)*z;
  ret[1] = 2*(qi*qj+qk*qr)*x + (1 - 2*(qi*qi+qk*qk))*y + 2*(qj*qk-qi*qr)*z;
  ret[2] = 2*(qi*qk - qj*qr)*x + 2*(qj*qk+qi*qr)*y + (1-2*(qi*qi+qj*qj))*z;

  return ret;
}

void applyToRot(double* r) {
  double* rotated = cross(r, rot);
  for(int i = 0; i < 4; i++) {
    rot[i] = rotated[i];
  }
  free(rotated);
}

void normalize(double* v) {
  double s = sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2] + v[3]*v[3]);
  v[0] /= s;
  v[1] /= s;
  v[2] /= s;
  v[3] /= s;
}

void drawUI() {
  
  arduboy.setCursor(64, 0);
  arduboy.print("Qr=");
  arduboy.print(rot[0]);
  arduboy.setCursor(64, 16);
  arduboy.print("Qi=");
  arduboy.print(rot[1]);
  arduboy.setCursor(64, 32);
  arduboy.print("Qj=");
  arduboy.print(rot[2]);
  arduboy.setCursor(64, 46);
  arduboy.print("Qk=");
  arduboy.print(rot[3]);
}

void displayMainMenu() {
    int len = projectName.length();
    len = 3*len+1;
    arduboy.setCursor(64-len,27);
    arduboy.write(projectName.c_str());
}
