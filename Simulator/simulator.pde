//  *** THIS PROGRAM HAS BEEN DEVELOPED BY SPEED CUBING CLUB IIT KANPUR  ***  

import peasy.*;

PeasyCam cam;

float speed = 0.1;
int dim = 3;
Cubie[] cube = new Cubie[dim*dim*dim];

   Move[] allMoves = new Move[] {
  new Move(0, 1, 0, 1),    // D
  new Move(0, 1, 0, -1),     //D
  new Move(0, -1, 0, 1),    //U
  new Move(0, -1, 0, -1),   //U
  new Move(1, 0, 0, 1),      //R
  new Move(1, 0, 0, -1),     //R
  new Move(-1, 0, 0, 1),    //L
  new Move(-1, 0, 0, -1),   //L
  new Move(0, 0, 1, 1),   //F
  new Move(0, 0, 1, -1),   //F
  new Move(0, 0, -1, 1),   //B
  new Move(0, 0, -1, -1)   //B
};   

 Move currentmove = new Move(0, 1, 0, 1) ;

//boolean started = false;



void setup() {
  size(600, 600, P3D);
  
  cam = new PeasyCam(this, 400);
  int index = 0;
  for (int x = -1; x <= 1; x++) {
    for (int y = -1; y <= 1; y++) {
      for (int z = -1; z <= 1; z++) {
        PMatrix3D matrix = new PMatrix3D();
        matrix.translate(x, y, z);
        cube[index] = new Cubie(matrix, x, y, z);
        index++;
      }
    }
  }
}

boolean flag = false;



void draw(){
  
   background(51); 
  rotateX(-0.5);
  rotateY(0.4);
  rotateZ(0.1);
  
  currentmove.update();
  
  scale(50);
  for (int i = 0; i < cube.length; i++) {
    push();
    if (abs(cube[i].z) > 0 && cube[i].z == currentmove.z) {
      rotateZ(currentmove.angle);
    } else if (abs(cube[i].x) > 0 && cube[i].x == currentmove.x) {
      rotateX(currentmove.angle);
    } else if (abs(cube[i].y) > 0 && cube[i].y ==currentmove.y) {
      rotateY(-currentmove.angle);
    }   
    cube[i].show();
    pop();
  }  
}

 
