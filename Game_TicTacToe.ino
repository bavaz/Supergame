#include"structure.h"

int cell_i, cell_j, cell;    //cell_i is x co-ord of cell and cell_j is y co-ord of cell
int sqav[9];    //sqav is square available

static enum GameTicTacPages
 {
   WelcomeTT            = 0,
   TicTacToeInstruction = 1,
   GridTT               = 2,
 
 } gameTicTacUiPage = WelcomeTT;


static void gameTicTacToeInit( )
 {
   cell_i = 0;
   cell_j = 0;
   cell = 0;
   for(int i = 0; i < 9; i++)
    {
      sqav[i] = i + 1;
    }
   
   gameTicTacUiPage=WelcomeTT;
 }
 
static void handlePageWelcomeTT( ) 
 {
   // Welcome Message
   OrbitOledMoveTo(0, 0);
   OrbitOledDrawString("Welcome to TTT");
   OrbitOledMoveTo(17, 12);
   OrbitOledDrawString("BTN1 For INS");
   OrbitOledMoveTo(17, 24);
   OrbitOledDrawString("BTN2 For GAME");
   
   gameTicTacToeInit( );
   
   if(gameInputState.buttons[0].isRising)
    {
      OrbitOledClearBuffer( );
      OrbitOledClear( );
      gameTicTacUiPage = TicTacToeInstruction;    //sets Game page to TicTacToe Instructions
    } 
    
   if(gameInputState.buttons[1].isRising)
    {
      OrbitOledClearBuffer( );
      OrbitOledClear( );
      gameTicTacUiPage=GridTT;    //sets Game page to the page having function that draws grid
    }
 } 
 
static void handlePageTicTacToe()
 {
   // Always Show the "INSTRUCTION" message on the first row
   OrbitOledMoveTo(17, 0);
   OrbitOledDrawString("INSTRUCTION");
   
   // Press BTN1 to display and scroll the instruction
   if(gameInputState.buttons[0].isRising)
    {
      // print the instruction and update the count
      printInstruction(TicTacToeInstructions, CountTicTacToeInstruction);
      CountTicTacToeInstruction += 32;
    }  
    
   // Press BTN2 to go to the ChooseRoll page
   if(gameInputState.buttons[1].isRising)
    {
      OrbitOledClearBuffer();
      OrbitOledClear( );
      gameTicTacUiPage=GridTT;    //sets game page to the page having function that draws grid
    }  
 }


int isBlockFree(int cell_x)    //checks if a cell is free
 {
   if(sqav[cell_x] == 10 || sqav[cell_x] == 11)
    {
      return 0;
    }
   
   return 1;
 }


void oboxselection( )
 {
   int i;
   for(i = 0; i < 9; i++)
    {
      if(isBlockFree(i))
       {
         sqav[i] = 10;
         break;
       }
    } 
   
 }


void xselection( )
 {
   if(isBlockFree(cell))
    {
      if(cell_i == 0)
       {
         if(cell_j == 0)
          {
            sqav[0] = 11;
          }
        else
         if(cell_j == 10)
          {
            sqav[3] = 11;
          }
        else
          {
            sqav[6] = 11;
          }
       }
      
      if(cell_i == 25)
       {
         if(cell_j == 0)
          {
            sqav[1] = 11;
          }
        else
         if(cell_j == 10)
          {
            sqav[4] = 11;
          }
        else
          {
            sqav[7] = 11;
          }
       }
   
      if(cell_i == 50)
       {
         if(cell_j == 0)
          {
            sqav[2] = 11;
          }
        else
         if(cell_j == 10)
          {
            sqav[5] = 11;
          }
        else
          {
            sqav[8] = 11;
          }
       }
      
    oboxselection( );
    }
   
 }


void Move( )
 {
   if(cell_j >= 0 && cell_j < 21)
    {
      if(cell_i >= 0 && cell_i < 51)
       {
         cell_i += 25;
         cell++;
       }
       
      
      if(cell_i >= 51)
       {
         cell_i = 0;
         cell_j += 10;
        
       }
       
      if(cell_j >= 21)
       {
         cell_j = 0;
         cell_i = 0;
         cell = 0;
       }

    }
 }
   

int TicTacResultCalc( )
 {
   //Checks if a row has same sign
   if(sqav[0]==11 &&sqav[1]==11 && sqav[2]==11)
     return 1;
   
   if(sqav[0]==10 &&  sqav[1]==10 && sqav[2]==10)
     return 0;
     
   
   if(sqav[3]==11 && sqav[4]==11 && sqav[4]==11)
     return 1;
     
   if(sqav[3]==10 && sqav[4]==10 && sqav[5]==10)
     return 0;
   
   
   if(sqav[6]==11 && sqav[7]==11 && sqav[8]==11)
     return 1;
     
   if(sqav[6]==10 && sqav[7]==10 && sqav[8]==10)
     return 0;
   

   //Checks if a column has same sign
   if(sqav[0]==11 && sqav[3]==11 && sqav[6]==11)
     return 1;
     
   if(sqav[0]==10 && sqav[3]==10 && sqav[6]==10)
     return 0;
   
   
   if(sqav[1]==11 && sqav[4]==11 && sqav[7]==11)
     return 1;
   
   if(sqav[1]==10 && sqav[4]==10 && sqav[7]==10)
     return 0;
   
   
   if(sqav[2]==11 && sqav[5]==11 && sqav[8]==11)
     return 1;
   
   if(sqav[2]==10 && sqav[5]==10 && sqav[8]==10)
     return 0;


   //Checks if diagonls have same sign
   if(sqav[0]==11 && sqav[4]==11 && sqav[8]==11)
     return 1;
   
   if(sqav[0]==10 && sqav[4]==10 && sqav[8]==10)
     return 0;

    
   if(sqav[2]==11 && sqav[4]==11 && sqav[6]==11)
     return 1;
     
   if(sqav[2]==10 && sqav[4]==10 && sqav[6]==10)
     return 0;

   
   //if above conditions not satisfied and grid still empty, returns 3
   for(int i = 0; i < 9; i++)
    {
      if(sqav[i] != 11 && sqav[i] != 10)
       return 3;
    }

   //if above conditions not satisfied and grid full, returns 2
   return 2;
 } 


void GridTicTac( )
 {
   OrbitOledClearBuffer( );
   //OrbitOledClear();

   //Draws a small rectangle that scrolls
   OrbitOledMoveTo(cell_i, cell_j);
   OrbitOledDrawRect(cell_i + 23, cell_j + 9);
  
   int i, j, z, xi = 5;
  
   //Draws the big grid
   for(j = 0;j < 21;j = j + 10) 
    {
      for(i = 0; i < 51; i = i + 25)
       {
         OrbitOledMoveTo(i, j);
         OrbitOledDrawRect(i+25,j+10);
       }
    }

   //Following functions are to draw the x's and o's 
   for(z = 0; z < 3; z++)   
    {
      if(sqav[z] == 11)
       {
         OrbitOledMoveTo(xi, 2);
         OrbitOledDrawString("x");
       }
       
      if(sqav[z] == 10)
       {
         OrbitOledMoveTo(xi, 2);
         OrbitOledDrawString("o");
       }
      
      xi += 25;
    }
   
   xi = 5;
   
   for(z = 3;z < 6; z++)
    {
      if(sqav[z] == 11)
       {
         OrbitOledMoveTo(xi, 12);
         OrbitOledDrawString("x");
       }
       
      if(sqav[z] == 10)
       {
         OrbitOledMoveTo(xi, 12);
         OrbitOledDrawString("o");
       }
      
      xi += 25;
    }

   xi = 5;

   for(z = 6; z < 9; z++)
    {
      if(sqav[z] == 11)
       {
         OrbitOledMoveTo(xi, 22);
         OrbitOledDrawString("x");
       }
       
      if(sqav[z] == 10)
       {
         OrbitOledMoveTo(xi, 22);
         OrbitOledDrawString("o");
       }
      xi += 25;
    }
   
   reachresult( );
   scrolling( );
 }


void scrolling( )
 {
   if(gameInputState.buttons[0].isRising)
    {
      Move( );    
    }

   if(gameInputState.buttons[1].isRising)
    {
      xselection( );
    }
   
  
 } 


void reachresult( )
 {
   int result = TicTacResultCalc( );
   if(result == 1)
    {
      OrbitOledClearBuffer( );
      OrbitOledClear( );
      OrbitOledMoveTo(20, 10);
      OrbitOledDrawString("Player wins");
      OrbitOledUpdate( );
      gameMainUiPage = Welcome;
    }
   else
    if(result == 0)
     {
       OrbitOledClearBuffer( );
       OrbitOledClear( );
       OrbitOledMoveTo(20, 10);
       OrbitOledDrawString("Computer wins");
       OrbitOledUpdate( );
       gameMainUiPage = Welcome;
     }
   else
    if(result == 2)
     {
       OrbitOledClearBuffer( );
       OrbitOledClear( );
       OrbitOledMoveTo(20, 10);
       OrbitOledDrawString("TIE");
       OrbitOledUpdate( );
       gameMainUiPage = Welcome;
     }

   if(result == 3)
      return;
     
   if(result == 1 || result == 0 || result == 2)
    {
      delay(1000);
      OrbitOledClearBuffer( );
      gameTicTacToeInit( );
    } 
 }


void gameTicTacToeTick()
 {
   switch(gameTicTacUiPage)
    {
      case WelcomeTT:
        handlePageWelcomeTT( );             
        break;
    
      case TicTacToeInstruction:
        handlePageTicTacToe( );                        
        break;
    
      case GridTT:
        GridTicTac( );
        break;
    
      default:
        handlePageWelcomeTT( );
        break;
    }
 }

 
   
   
