#include "structure.h"
#include "math.h"

static enum GameRpslsPages
{
  WelcomeRpsls       = 0,
  RpslsInstructions  = 1,
  RpslsChooseRoll    = 2,
  RpslsGameResult    = 3,
  RpslsProgress      = 4,
  RpslsNumberOfPages = 5,
} gameRpslsUiPage = WelcomeRpsls;

static void handlePageWelcomeRpsls() 
{
  // Welcome Message
  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Welcome to RPSLS");
  OrbitOledMoveTo(17, 12);
  OrbitOledDrawString("BTN1 For INS");
  OrbitOledMoveTo(17, 24);
  OrbitOledDrawString("BTN2 For GAME");

  // Initiat the game
  gameRpslsInit();
  
  // If press BTN1
  if(gameInputState.buttons[0].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    gameRpslsUiPage = RpslsInstructions;
  } 
  
  // If press BTN2
  if(gameInputState.buttons[1].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    gameRpslsUiPage = RpslsChooseRoll; 
  }
}

static void handlePageRpslsInstruction()
{
  // Always Show the "INSTRUCTION" message on the first row
  OrbitOledMoveTo(17, 0);
  OrbitOledDrawString("INSTRUCTION");

  // Press BTN1 to display and scroll the instruction
  if(gameInputState.buttons[0].isRising)
  {
    // print the instruction and update the count
    printInstruction(RpslsInstruction, CountRpslsInstruction);
    CountRpslsInstruction += 32;
  }

  // Press BTN2 to go to the ChooseRoll page
  if(gameInputState.buttons[1].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    gameRpslsUiPage = RpslsChooseRoll;
  }
}

static void handlePageRpslsChooseRoll()
{
  OrbitOledMoveTo(28, 0);
  OrbitOledDrawString("ROLLS");

  OrbitOledMoveTo(5, 12);
  OrbitOledDrawBracket(0, 20);
  OrbitOledMoveTo(7, 12);
  OrbitOledDrawBracket(2, 20);
  OrbitOledMoveTo(9, 12);
  OrbitOledDrawBracket(4, 20);

  // Display the game, SEE Games[] in structure.h
  OrbitOledMoveTo(20, 16);
  OrbitOledDrawString(RpslsRoll[RpslsIndex]);

  OrbitOledMoveTo(100, 12);
  OrbitOledDrawBracket(95, 20);
  OrbitOledMoveTo(102, 12);
  OrbitOledDrawBracket(97, 20);
  OrbitOledMoveTo(104, 12);
  OrbitOledDrawBracket(99, 20);

  // If the user press BTN1, change the roll
  // (RpslsIndex + 1) % 4 makes sure the index are just 0, 1, 2, 3, 4
  if(gameInputState.buttons[0].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    RpslsIndex = (RpslsIndex + 1) % 5;
  } 

  // If the user press BTN2, the roll is selected
  if(gameInputState.buttons[1].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    RpslsPlayerRoll = RpslsIndex;
    gameRpslsUiPage = RpslsGameResult;
  } 
}

void RpslsResultCalculate()
{
  // Computer generates random roll and Calculate the result
  RpslsComputerRoll = (uint32_t)floor(random(5));
  RpslsResultFlag = RpslsComputerRoll - RpslsPlayerRoll;
  if(RpslsResultFlag == 1 || RpslsResultFlag == 2 || RpslsResultFlag == -3 || RpslsResultFlag == -4)
  {
    RpslsResult = -1;
    RpslsResultMessage = "Computer Wins";
  }
  else if(RpslsResultFlag == 3 || RpslsResultFlag == 4 || RpslsResultFlag == -1 || RpslsResultFlag == -2)
  {
    RpslsResult = 1;
    RpslsResultMessage = "Player Wins";
  }
  else
  {
    RpslsResult = 0;
    RpslsResultMessage = "Tie"; 
  }
}

static void handlePageRpslsGameResult()
{
  OrbitOledMoveTo(17, 0);
  OrbitOledDrawString("GAME RESULT");
  if(gameInputState.buttons[0].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    if(CountRpslsResult == 0) 
    {
      OrbitOledMoveTo(0, 12);
      OrbitOledDrawString("PLAYER CHOICE:");
      OrbitOledMoveTo(0, 24);
      OrbitOledDrawString(RpslsRoll[RpslsPlayerRoll]);
    }
    else if(CountRpslsResult == 1) 
    {
      RpslsResultCalculate();
      OrbitOledMoveTo(0, 12);
      OrbitOledDrawString("COMPUTER CHOICE:");
      OrbitOledMoveTo(0, 24);
      OrbitOledDrawString(RpslsRoll[RpslsComputerRoll]);
    }
    else if(CountRpslsResult == 2) 
    {
      char charBuf[50]; 
      RpslsResultMessage.toCharArray(charBuf, 50);
      OrbitOledMoveTo(0, 12);
      OrbitOledDrawString(charBuf);
      OrbitOledMoveTo(0, 24);
      OrbitOledDrawString("PRESS BTN2");
    }
    else 
    {
      goto RpslsResultTarget;
    }
    
    CountRpslsResult++;
  } 

  RpslsResultTarget:
  // Press BTN2 to go back to Main Menu
  if(gameInputState.buttons[1].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    gameRpslsInit();
    gameMainUiPage = Welcome;
  } 
}

static void handleRpslsPageProgressBar()
{
  ;
}

static void  gameRpslsInit()
{
  CountRpslsInstruction = 0;
  RpslsResultMessage = "TIE";
  CountRpslsResult = 0;
  RpslsResult = 0;
  RpslsResultFlag = 0;
  RpslsComputerRoll = 0;
  RpslsPlayerRoll = 0;
  RpslsIndex = 0;
  gameRpslsUiPage = WelcomeRpsls;
}

void gameRpslsTick()
{
  switch(gameRpslsUiPage)
  {
    case WelcomeRpsls:
      handlePageWelcomeRpsls();
      break;

    case RpslsInstructions:
      handlePageRpslsInstruction();
      break;

    case RpslsChooseRoll:
      handlePageRpslsChooseRoll();
      break;

    case RpslsGameResult:
      handlePageRpslsGameResult();
      break;

    default:
      handleRpslsPageProgressBar();
      break;
  }
}

