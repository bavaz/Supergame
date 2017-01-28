#include <stdbool.h>
#include <string.h>
#include "structure.h"

/* #####Notes on coordinates consistency#####
 * Looks good on the OLED when the difference
 * of y coordinate is the multiple of 12.
 * Use 17 for x coordinate when you want to dis-
 * play the string in the middle.
 * Only 16 characters can be shown on the same row
 * Feel free to change this setting if necessary.
 * The coordinates should always stay consistent.
 * @author: Root
 */



/* ------------------------------------------------------------ */
/***  GameUIInit()
**   
**    Description:
**      Initiate the Oled Screen display, gameInput, gameMenu
**      Set the switches and buttons to be INPUT
*/
void GameUIInit()
{
  OrbitOledInit();
  OrbitOledClear();
  OrbitOledClearBuffer();
  OrbitOledSetFillPattern(OrbitOledGetStdPattern(iptnSolid));
  OrbitOledSetDrawMode(modOledSet);

  gameInputState = { 0 };
  gameMenu = { 0 };

  for(int i = 0; i < SwitchCount; ++i )
    pinMode(Switches[i], INPUT);
  for(int i = 0; i < ButtonCount; ++i )
    pinMode(Buttons[i], INPUT);

  pinMode(RLED,OUTPUT);
  pinMode(GLED,OUTPUT);
}

/* ------------------------------------------------------------ */
/***  handleMainPageWelcome()
**   
**    Description:
**      Display "Welcome to SUPERGAME, Press BTN1"
**      If press the BTN1, then go to SelectGamesInstructions page
*/

static void handleMainPageWelcome()
{
  OrbitOledMoveTo(17, 0);
  OrbitOledDrawString("Welcome to");

  OrbitOledMoveTo(20, 12);
  OrbitOledDrawString("SUPERGAME");

  OrbitOledMoveTo(17, 24);
  OrbitOledDrawString("Press BTN1");

  if(gameInputState.buttons[0].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    gameMainUiPage = SelectGamesInstructions;
  } 
}

/* ------------------------------------------------------------ */
/***  handleMainPageSelectGamesInstructions()
**   
**    Description:
**      Display "Instruction, BTN2 to switch, BTN1 to select"
**      If press the BTN1, then go to SelectGames page
*/
static void handleMainPageSelectGamesInstructions()
{
  OrbitOledMoveTo(17, 0);
  OrbitOledDrawString("Instruction");
  
  OrbitOledMoveTo(0, 12);
  OrbitOledDrawString("BTN2 to switch");

  OrbitOledMoveTo(0, 24);
  OrbitOledDrawString("BTN1 to select");

  if(gameInputState.buttons[0].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    gameMainUiPage = SelectGames;
  } 
}

/* ------------------------------------------------------------ */
/***  handleMainPageSelectGames()
**   
**    Description:
**      Display "Games" with each game
**      If press the BTN2, then the game switches
**      If press the BTN1, then go to this game's page
*/
static void handleMainPageSelectGames()
{
  OrbitOledMoveTo(28, 0);
  OrbitOledDrawString("GAMES");

  OrbitOledMoveTo(5, 12);
  OrbitOledDrawBracket(0,20);
  OrbitOledMoveTo(7, 12);
  OrbitOledDrawBracket(2,20);
  OrbitOledMoveTo(9, 12);
  OrbitOledDrawBracket(4,20);

  // Display the game, SEE Games[] in structure.h
  OrbitOledMoveTo(20,16);
  OrbitOledDrawString(Games[gameMenu.gameIndex]);

  OrbitOledMoveTo(100, 12);
  OrbitOledDrawBracket(95,20);
  OrbitOledMoveTo(102, 12);
  OrbitOledDrawBracket(97,20);
  OrbitOledMoveTo(104, 12);
  OrbitOledDrawBracket(99,20);

  // If the user press BTN2, the menu switches to the next game
  // (gameMenu.gameIndex + 1) % 4 makes sure the index are just 0, 1, 2, 3
  if(gameInputState.buttons[1].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    gameMenu.gameIndex = (gameMenu.gameIndex + 1) % 4;
  } 

  // If the user press BTN1, the game is selected
  // we look at the gameIndex at this moment, and go to that game page
  if(gameInputState.buttons[0].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    switch(gameMenu.gameIndex)
    {
      case 0: // RPSLS
        gameMainUiPage = GameRPSLS;
        break;
      
      case 1: // Guess The Numer
        gameMainUiPage = GameGuessTheNumber;
        break;

      case 2: // Tic Tac Toe
        gameMainUiPage = GameTicTacToe;
        break;

      case 3: // Chess
        gameMainUiPage = GameChess;
        break;

      default:
        gameMainUiPage = Welcome;
        break;
    }
  } 
}

// Not sure sure if we need this, just keep it now
static void handleMainPageProgressBar()
{
  ;
}


/* ------------------------------------------------------------ */
/***  uiInputTick()
**   
**    Description:
**      uodate the input state in every loop
**      For Buttons, Switches, Potentiometer 
*/
static void uiInputTick()
{
  for(int i = 0; i < SwitchCount; ++i )
  {
    bool previousState = gameInputState.switches[i].state;
    gameInputState.switches[i].state = digitalRead(Switches[i]);
    gameInputState.switches[i].isRising = (!previousState && gameInputState.switches[i].state);
  }

  for(int i = 0; i < ButtonCount; ++i )
  {
    // Only look for Rising Edge Signals.
    bool previousState = gameInputState.buttons[i].state;
    gameInputState.buttons[i].state = digitalRead(Buttons[i]);
    gameInputState.buttons[i].isRising = (!previousState && gameInputState.buttons[i].state);
  }
  
  gameInputState.potentiometer = analogRead(Potentiometer);
}


/* ------------------------------------------------------------ */
/***  GameUITick()
**   
**    Description:
**     read the input state at the beginning 
**     and switch from the page     
*/
void GameUITick()
{
  uiInputTick();
  switch(gameMainUiPage)
  {
    case Welcome:
      handleMainPageWelcome();
      break;

    case SelectGamesInstructions:
      handleMainPageSelectGamesInstructions();
      break;
      
    case SelectGames:
      handleMainPageSelectGames();
      break;

    case GameRPSLS:
      gameRpslsTick();
      break;

    case GameGuessTheNumber:
      gameGuessTheNumberTick();
      break;

    case GameTicTacToe:
      gameTicTacToeTick();
      break;

    case GameChess:
      gameChessTick();
      break;
      
    default:
      handleMainPageProgressBar();
      break;
  }
  OrbitOledUpdate();
}

