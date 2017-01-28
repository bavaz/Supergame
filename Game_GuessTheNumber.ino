#include "structure.h"

int stringdecide, numi,numj,num;  //numi and numj are for the cursor to move to the x,y co-ords of a num and num is the number


static enum GameGuessTheNumPages
 {
   WelcomeGuessTheNum = 0,
   GuessTheNumInstruction = 1,
   DrawBox = 2,
   getNum = 3,
   
 } gameGuessTheNumUiPage = WelcomeGuessTheNum;


static void handlePageWelcomeGuessTheNum( ) 
 {
   // Welcome Message
   OrbitOledMoveTo(0, 0);
   OrbitOledDrawString("Welcome to Guess The Number");
   OrbitOledMoveTo(17, 12);
   OrbitOledDrawString("BTN1 For INS");
   OrbitOledMoveTo(17, 24);
   OrbitOledDrawString("BTN2 For GAME");
   
   gameGuessTheNumInit( );
    
   if(gameInputState.buttons[0].isRising)
    {
      OrbitOledClearBuffer( );
      OrbitOledClear( );
      gameGuessTheNumUiPage = GuessTheNumInstruction;    //sets the game page to Guess The Num Instructions
    } 
    
   if(gameInputState.buttons[1].isRising)
    {
      OrbitOledClearBuffer( );
      OrbitOledClear( );
      gameGuessTheNumUiPage=DrawBox;    //sets the game page to the page that has the Draw box function
    }
 }


static void handlePageGuessTheNumInstruction()
 {
   // Always Show the "INSTRUCTION" message on the first row
   OrbitOledMoveTo(17, 0);
   OrbitOledDrawString("INSTRUCTION");
   
   // Press BTN1 to display and scroll the instruction
   if(gameInputState.buttons[0].isRising)
    {
      // print the instruction and update the count
      printInstruction(GuessTheNumInstructions, CountGuessTheNumInstruction);
      CountGuessTheNumInstruction += 32;
    }
    
   // Press BTN2 to go to the ChooseRoll page
   if(gameInputState.buttons[1].isRising)
    {
      OrbitOledClearBuffer( );
      OrbitOledClear( );
      gameGuessTheNumUiPage=DrawBox;    //sets the game page to the page that has the Draw box function(after Instructions)
    }
 }


static void  gameGuessTheNumInit( )
 {
   stringdecide=0,numi=5,numj=5,num=1;
   gameGuessTheNumUiPage = WelcomeGuessTheNum;
 }


int comprand=rand( )%21;    //computer generated random number 

  
void MoveNum( )
 {
   OrbitOledMoveTo(numi,numj);
   OrbitOledDrawRect(numi+25,numj+20);
   if(gameInputState.buttons[0].isRising) 
    {
      if(numi>=5 && numi<131)
       {
         num++;
         numi+=25;
       }
    }
  
   if(gameInputState.buttons[1].isRising)
    {
      gameGuessTheNumUiPage=getNum;    //sets the game page to the page that gets user number and shows result 
    }
    
   if(numi>=111)
    {
      numi=5;
      stringdecide++;
    }
 }


void printing(String ins, uint32_t count)
 {
   ins.toUpperCase( );
   String toShow; 
   char charBuf[50]; // toShow will be converted into charBuf[]

   // Only when the message is not completely printed, we print it.
   if(count <= ins.length( )) 
    {
      // OrbitOledClear( );
      //OrbitOledClearBuffer( );
        
      // If there is enough chars to be printed on the second row, we print them.
      if(ins.length() >= count + 16) 
       {
         toShow = ins.substring(count, count + 16);
         toShow.toCharArray(charBuf, 50);
         OrbitOledMoveTo(0, 12);
         OrbitOledDrawString(charBuf);
       }
     else 
       {
         int remain = ins.length( ) - count;
         toShow = ins.substring(count, count + remain);
         toShow.toCharArray(charBuf, 50);
         OrbitOledMoveTo(0, 12);
         OrbitOledDrawString(charBuf);
         return;
       }

      // If there is enough chars to be printed on the third row, we print them.
      if(ins.length( ) >= count + 32) 
       {
         toShow = ins.substring(count + 16, count + 32);
         toShow.toCharArray(charBuf, 50);
         OrbitOledMoveTo(0, 24);
         OrbitOledDrawString(charBuf); 
       }
       
      // If there is not enough chars to be printed on the third row, it means we are almost at the end of the string.
      // We print the rest of the string.
     else 
       {
         int remain = ins.length( ) - count;
         toShow = ins.substring(count + 16, count + remain);
         toShow.toCharArray(charBuf, 50);
         OrbitOledMoveTo(0, 24);
         OrbitOledDrawString(charBuf);
         return;
       }      
    }
 }


void Draws( )
 {
   OrbitOledClearBuffer( );
   //OrbitOledClear( );
   OrbitOledMoveTo(0,0);
   OrbitOledDrawRect(200,100);
   
   if(stringdecide==4)
    {
      stringdecide=0;
      num=1;
    }
   
   Printstr( );
 }


void Printstr( )
 {
   int notimp=0;    //notimp is always 0, so not imp
   String NumberDisplay1=" 01 02 03 04 05";
   String NumberDisplay2=" 06 07 08 09 10 ";
   String NumberDisplay3=" 11 12 13 14 15";
   String NumberDisplay4= " 16 17 18 19 20";
   
   if(stringdecide==0)
    {
      printing(NumberDisplay1,notimp);
    }
    
   if(stringdecide==1)
    {
      printing(NumberDisplay2,notimp);
    }
    
   if(stringdecide==2)
    {
      printing(NumberDisplay3,notimp);
    }
    
   if(stringdecide==3)
    {
      printing(NumberDisplay4,notimp);
    }
    
   MoveNum( );
 }


void getNumUser( )
 {
   if(num==comprand)
    {
      OrbitOledClearBuffer( );
      OrbitOledClear( );
      OrbitOledMoveTo(0,0);
      OrbitOledDrawString("CORRECT ANSWER!");
    }
  else
   if(num<comprand)
    {
      digitalWrite(RLED,HIGH);
      delay(1000);
      digitalWrite(RLED,LOW);
    } 
  else
    {
      digitalWrite(GLED,HIGH);
      delay(1000);
      digitalWrite(GLED,LOW);
    }
    
   delay(1000);
   OrbitOledClearBuffer( );
   OrbitOledClear( );
   gameGuessTheNumInit( );
   gameMainUiPage = Welcome;
 }
    

void gameGuessTheNumberTick( )
 { 
   switch(gameGuessTheNumUiPage)
    {
      case WelcomeGuessTheNum:
        handlePageWelcomeGuessTheNum( );
        break;
      
      case GuessTheNumInstruction:
        handlePageGuessTheNumInstruction( );
        break;
      
      case DrawBox:
        Draws( );
        break;

      case getNum:
        getNumUser( );       
        break;
      
      default:
        handlePageWelcomeGuessTheNum( );
        break;
    }
 }

  
