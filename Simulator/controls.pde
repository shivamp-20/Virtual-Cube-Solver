 
 
int i=0;
String[] scramble;
String[] moves;
  
 
   void keyPressed() {
  
    if (key == 'D') {
    currentmove=allMoves[0];
    currentmove.start();
  }
   else if (key == 'd') {
    currentmove=allMoves[1];
    currentmove.start();
  }
   else if (key == 'u') {
    currentmove=allMoves[2];
    currentmove.start();
  }
   else if (key == 'U') {
    currentmove=allMoves[3];
    currentmove.start();
  }
   else if (key == 'r') {
    currentmove=allMoves[4];
    currentmove.start();
  }
   else if (key == 'R') {
    currentmove=allMoves[5];
    currentmove.start();
  }
  else if (key == 'L') {
    currentmove=allMoves[6];
    currentmove.start();
  }
  else if (key == 'l') {
    currentmove=allMoves[7];
    currentmove.start();
  }
   else if (key == 'f') {
    currentmove=allMoves[8];
    currentmove.start();
  }
   else if (key == 'F') {
    currentmove=allMoves[9];
    currentmove.start();
  }
   else if (key == 'B') {
    currentmove=allMoves[10];
    currentmove.start();
  }
   else if (key == 'b') {
    currentmove=allMoves[11];
    currentmove.start();
  }
  else if(key == ' '){   
     
      scramble = loadStrings("scramble.txt");  
      moves = scramble;
     control(i,moves); 
       i++;  
  }
  else if(key == 'a'){
    
      i=0;
    
  }
  else if(key == 's'){
    
    scramble = loadStrings("solve.txt");
    moves = scramble;
    control(i,moves); 
       i++; 
  }
   }
  
  
  
    
   
  /* void keyPressed(){     
     if(key == ' '){
     flag=true;
     
     control(i);
     i++;
     }
     }   */
   
void control(int i,String[] scramble){ 
  
  char move;
  
//char[] scramble = { 'f', 'b', 'b' }; 

      print(scramble[0].charAt(i));
      
      if(scramble[0].charAt(i)=='2'){
         move = scramble[0].charAt(i-1);         
      }
      else{
        move = scramble[0].charAt(i);        
      }
      
        if (move == 'D') {
    currentmove=allMoves[0];
    currentmove.start();
  }
   else if (move == 'd') {
    currentmove=allMoves[1];
    currentmove.start();
  }
   else if (move == 'u') {
    currentmove=allMoves[2];
    currentmove.start();
  }
   else if (move == 'U') {
    currentmove=allMoves[3];
    currentmove.start();
  }
   else if (move == 'r') {
    currentmove=allMoves[4];
    currentmove.start();
  }
   else if (move == 'R') {
    currentmove=allMoves[5];
    currentmove.start();
  }
  else if (move == 'L') {
    currentmove=allMoves[6];
    currentmove.start();
  }
  else if (move == 'l') {
    currentmove=allMoves[7];
    currentmove.start();
  }
   else if (move == 'f') {
    currentmove=allMoves[8];
    currentmove.start();
  }
   else if (move == 'F') {
    currentmove=allMoves[9];
    currentmove.start();
  }
   else if (move == 'B') {
    currentmove=allMoves[10];
    currentmove.start();
  }
   else if (move == 'b') {
    currentmove=allMoves[11];
    currentmove.start();       
  } 
     }


   
     
   
