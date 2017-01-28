#ifndef _STRUCTURE_H_
#define _STRUCTURE_H_

/* structure.h 
 * This is a file where we store all the variables we will use in almost every file
 * Includes: gameMainUiPage, GameState, InputState, ButtonState
 * @author: Root
 */
static enum GameMainPages
{
  Welcome                 = 0,
  SelectGamesInstructions = 1,
  SelectGames             = 2,
  GameRPSLS               = 3,
  GameGuessTheNumber      = 4,
  GameTicTacToe           = 5,
  GameChess               = 6,
  MainPageProgress        = 7,
  NumberOfMainPages       = 8,
} gameMainUiPage = Welcome;


// We can reduce it to an int, but I just use a structure in case we want to add something
// This structure will be used when switching and selecting games
struct GameState
{
  int gameIndex;
} gameMenu;



const uint32_t GLED = GREEN_LED;
const uint32_t RLED = RED_LED;
const uint32_t SwitchCount = 2;
const uint32_t ButtonCount = 2;
const uint32_t Switches[SwitchCount] = { PA_7, PA_6 }; // PA_7 for SW1, PA_6 for SW2
const uint32_t Buttons[ButtonCount] = { PD_2, PE_0 }; // PD_2 for BTN1, PE_0 for BTN2
const uint32_t Potentiometer = PE_3;
const uint32_t GameCount = 4;
const uint32_t MAXLENGTH = 50;
char Games[GameCount][MAXLENGTH] = {"RPSLS",
                                    "NumWhat",
                                    "TicTacToe",
                                    "Chess"};

const uint32_t RpslsRollCount = 5;
char RpslsRoll[RpslsRollCount][MAXLENGTH] = {"rock", 
                                             "Spock",
                                             "paper",
                                             "lizard",
                                             "scissors"}; 

uint32_t RpslsIndex = 0;
uint32_t RpslsPlayerRoll = 0;
uint32_t RpslsComputerRoll = 0;
uint32_t RpslsResultFlag = 0;
uint32_t RpslsResult = 0; // 0 for Tie, 1 for PlayerWin, -1 for ComputerWin
uint32_t CountRpslsResult = 0;
String RpslsResultMessage;                                          


char chessBoardPiece[10][9] = {{'J','M','X','S','K','S','X','M','J'},
                               {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                               {' ','P',' ',' ',' ',' ',' ','P',' '},
                               {'B',' ','B',' ','B',' ','B',' ','B'},
                               {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                               {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                               {'D',' ','D',' ','D',' ','D',' ','D'},
                               {' ','Y',' ',' ',' ',' ',' ','Y',' '},
                               {' ',' ',' ',' ',' ',' ',' ',' ',' '},
                               {'C','H','L','Q','W','Q','L','H','C'}};
uint32_t CountBlackChessBoardScrollClick = 0;
uint32_t CountBlackChessSelectBlock = 0;
uint32_t CountRedChessBoardScrollClick = 0;
uint32_t CountRedChessSelectBlock = 0;
uint32_t BlackChessOldMove = 0;
uint32_t BlackChessNewMove = 0;
uint32_t RedChessOldMove = 0;
uint32_t RedChessNewMove = 0;
uint32_t BlackChessIndex = 0;
uint32_t RedChessIndex = 0;
uint32_t ChessWinner = 0; // 0 for Tie, 1 for Black, -1 for Red
bool isBlackToMove = true;
bool isBlackOldChoice = true;
bool isRedOldChoice = true;


struct ButtonState
{
  bool state;
  bool isRising;
};

struct SwitchState
{
  bool state;
  bool isRising;
};

struct InputState
{
  struct SwitchState switches[2];
  struct ButtonState buttons[2];
  float              potentiometer;
} gameInputState;



/************************ INSTRUCTIONS MESSAGES FOR EACH GAME ************************/
String RpslsInstruction = "This is a pretty interesting game.\
 Scissors cuts paper.\
 Paper covers rock.\
 Rock crushes lizard.\
 Lizard poisons Spock.\
 Spock smashes scissors.\
 Scissors decapitates lizard.\
 Lizard eats paper.\
 Paper disproves Spock.\
 Spock vaporizes rock.\
 Rock crushes scissors.\
 In the game, use BTN1 to change roll,\
 use BTN2 to choose roll\
 Now Press BTN2!";

String GuessTheNumInstructions = "How good is your guessing ability?\
 The computer selects a number between 1 to 20.\
 This number won't be disclosed to you.\
 You have to guess the number.\
 Scroll through the numbers in the grid with BTN1.\
 Select the number by pressing BTN2.\
 If your number is greater than the computer number,\
 the green LED will light up.\
 If it's lower than the computer number,\
 the red LED will light up.\
 If it's right a message will be displayed.\
 Now Press BTN2!.";

String TicTacToeInstructions="You are shown a 3x3 grid.\
 Navigate by pressing BTN1.\
 Select a cell by pressing BTN2.\
 To win one must get all x's in a row,column or diagonal.\
 Good Luck!.";

String ChessInstruction="This is Chinese Chess.\
 Press BTN1 to scroll the page.\
 Press BTN2 to change the single block.\
 Switch SW1 up AND down to choose black MOVE.\
 Switch SW2 up AND down to choose red MOVE.\
 Everytime you TRY to MOVE, you choose the piece AND then choose the destination.\
 Now Press BTN2!";

uint32_t CountRpslsInstruction = 0;
uint32_t CountGuessTheNumInstruction = 0;
uint32_t CountTicTacToeInstruction = 0;
uint32_t CountChessInstruction = 0;
#endif
