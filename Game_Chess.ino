#include "structure.h"
#include "math.h"
#define RED_JU 'C'
#define RED_MA 'H'
#define RED_XIANG 'L'
#define RED_SHI 'Q'
#define RED_JIANG 'W'
#define RED_PAO 'Y'
#define RED_BIN 'D'

#define BLACK_JU 'J'
#define BLACK_MA 'M'
#define BLACK_XIANG 'X'
#define BLACK_SHI 'S'
#define BLACK_JIANG 'K'
#define BLACK_PAO 'P'
#define BLACK_BIN 'B'


static enum GameChessPages
{
  WelcomeChess         = 0,
  ChessInstructions    = 1,
  ChessDisplayBoard    = 2,
  ChessGameResult      = 3,
} gameChessUiPage = WelcomeChess;

void gameChessInit()
{
  gameChessUiPage = WelcomeChess;
  CountChessInstruction = 0;
  CountBlackChessBoardScrollClick = 0;
  CountBlackChessSelectBlock = 0;
  CountRedChessBoardScrollClick = 0;
  CountRedChessSelectBlock = 0;
  BlackChessOldMove = 0;
  BlackChessNewMove = 0;
  RedChessOldMove = 0;
  RedChessNewMove = 0;
  BlackChessIndex = 0;
  RedChessIndex = 0;
  ChessWinner = 0; // 0 for Tie, 1 for Black, -1 for Red
  isBlackToMove = true;
  isBlackOldChoice = true;
  isRedOldChoice = true;
  for(int i = 0; i < 10; i++)
    for(int j = 0; j < 9; j++)
      {
        chessBoardPiece[i][j] = ' ';
      }
  chessBoardPiece[0][0] = 'J';
  chessBoardPiece[0][1] = 'M';
  chessBoardPiece[0][2] = 'X';
  chessBoardPiece[0][3] = 'S';
  chessBoardPiece[0][4] = 'K';
  chessBoardPiece[0][5] = 'S';
  chessBoardPiece[0][6] = 'X';
  chessBoardPiece[0][7] = 'M';
  chessBoardPiece[0][8] = 'J';
  chessBoardPiece[2][1] = 'P';
  chessBoardPiece[2][7] = 'P';
  for(int k = 0; k < 9; k += 2)
  {
    chessBoardPiece[3][k] = 'B';
    chessBoardPiece[6][k] = 'D';
  }
  chessBoardPiece[7][1] = 'Y';
  chessBoardPiece[7][7] = 'Y';
  chessBoardPiece[9][0] = 'C';
  chessBoardPiece[9][1] = 'H';
  chessBoardPiece[9][2] = 'L';
  chessBoardPiece[9][3] = 'Q';
  chessBoardPiece[9][4] = 'W';
  chessBoardPiece[9][5] = 'Q';
  chessBoardPiece[9][6] = 'L';
  chessBoardPiece[9][7] = 'H';
  chessBoardPiece[9][8] = 'C';
}

void handlePageWelcomeChess()
{
  // Welcome Message
  OrbitOledMoveTo(0, 0);
  OrbitOledDrawString("Welcome to Chess");
  OrbitOledMoveTo(17, 12);
  OrbitOledDrawString("BTN1 For INS");
  OrbitOledMoveTo(17, 24);
  OrbitOledDrawString("BTN2 For GAME");

  // Initiat the game
  gameChessInit();
  
  // If press BTN1
  if(gameInputState.buttons[0].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    gameChessUiPage = ChessInstructions;
  } 
  
  // If press BTN2
  if(gameInputState.buttons[1].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    gameChessUiPage = ChessDisplayBoard; 
  }
}

void handlePageChessInstructions()
{
  // Always Show the "INSTRUCTION" message on the first row
  OrbitOledMoveTo(17, 0);
  OrbitOledDrawString("INSTRUCTION");

  // Press BTN1 to display and scroll the instruction
  if(gameInputState.buttons[0].isRising)
  {
    // print the instruction and update the count
    printInstruction(ChessInstruction, CountChessInstruction);
    CountChessInstruction += 32;
  }

  // Press BTN2 to go to the ChooseRoll page
  if(gameInputState.buttons[1].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    gameChessUiPage = ChessDisplayBoard; 
  }
}

//How to display the whole screen
// CountChessBoardScrollClick 0 0-1 LineStyle1  \/
// CountChessBoardScrollClick 1 1-2 LineStyle2  /\
// CountChessBoardScrollClick 2 2-3 LineStyle3  Normal
// CountChessBoardScrollClick 3 3-4 LineStyle3  Normal
// CountChessBoardScrollClick 4 4-5 LineStyle4  SPACE
// CountChessBoardScrollClick 5 5-6 LineStyle3  Normal
// CountChessBoardScrollClick 6 6-7 LineStyle3  Normal
// CountChessBoardScrollClick 7 7-8 LineStyle1  \/
// CountChessBoardScrollClick 8 8-9 LineStyle2  /\

// CountChessSelectBlock = 0 - 89
// in displaySelect, index = CountChessSelectBlock % 18
void displaySelect(int index)
{
  if(index <= 8 && index >= 0)
  {
    OrbitOledMoveTo(0 + index * 15, 6);
    OrbitOledDrawRect(7 + index * 15, 14);
  }
  else if(index <= 17 && index >= 9)
  {
    int i = index - 9;
    OrbitOledMoveTo(0 + 15 * i, 21);
    OrbitOledDrawRect(7 + 15 * i, 29);
  }
}

void handlePageChessDisplayBoard()
{
  // Display the board page depending on how many times user press the button
  switch((isBlackToMove ? CountBlackChessBoardScrollClick : CountRedChessBoardScrollClick) % 9)
  {
    case 0:
      drawChessBoardLineStyle1();
      drawChessBoardPiece(0);
      break;
      
    case 1:
      drawChessBoardLineStyle2();
      drawChessBoardPiece(1);
      break;
      
    case 2:
      drawChessBoardLineStyle3();
      drawChessBoardPiece(2);
      break;
      
    case 3:
      drawChessBoardLineStyle3();
      drawChessBoardPiece(3);
      break;
      
    case 4:
      drawChessBoardLineStyle4();
      drawChessBoardPiece(4);
      break;
      
    case 5:
      drawChessBoardLineStyle3();
      drawChessBoardPiece(5);
      break;
      
    case 6:
      drawChessBoardLineStyle3();
      drawChessBoardPiece(6);
      break;  
      
    case 7:
      drawChessBoardLineStyle1();
      drawChessBoardPiece(7);
      break;
      
    case 8:
      drawChessBoardLineStyle2();
      drawChessBoardPiece(8);
      break;  

    default:
      drawChessBoardLineStyle1();
      drawChessBoardPiece(0);
      break;
  }

  displaySelect((isBlackToMove ? CountBlackChessSelectBlock : CountRedChessSelectBlock) % 18);
  // If press BTN1, then scroll the screen
  if(gameInputState.buttons[0].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    if(isBlackToMove)
    {
      BlackChessIndex += 9;
      CountBlackChessBoardScrollClick++;
      CountBlackChessSelectBlock += 18;
      if(CountBlackChessBoardScrollClick % 9 == 0)
      {
        BlackChessIndex += 9;
      }
    }
    else
    {
      RedChessIndex += 9;
      CountRedChessBoardScrollClick++;
      CountRedChessSelectBlock += 18;
      if(CountRedChessBoardScrollClick % 9 == 0)
      {
        RedChessIndex += 9;
      }
    }
  }

  // If press BTN2, then move to the next block
  if(gameInputState.buttons[1].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    if(isBlackToMove)
    {
      BlackChessIndex++;
      CountBlackChessSelectBlock++;
      if(CountBlackChessSelectBlock % 18 == 0)
      {
        CountBlackChessBoardScrollClick++;
        BlackChessIndex -= 9;
        if(CountBlackChessBoardScrollClick % 9 == 0)
        {
          BlackChessIndex += 9;
        }
      }
    }
    else
    {
      RedChessIndex ++;
      CountRedChessSelectBlock++;
      if(CountRedChessSelectBlock % 18 == 0)
      {
        CountRedChessBoardScrollClick++;
        RedChessIndex -= 9;
        if(CountRedChessBoardScrollClick % 9 == 0)
        {
          RedChessIndex += 9;
        }
      }
    }
  }

  // if switch SW1 down and up, then playerBlack seclect this piece
  if(gameInputState.switches[0].isRising)
  {
    if(isBlackOldChoice)
    {
      if(checkIsValidChoice((BlackChessIndex % 90), 0))
      {
        digitalWrite(GLED,HIGH);
        delay(1000);
        digitalWrite(GLED,LOW);
        BlackChessOldMove = BlackChessIndex % 90 ;
        isBlackOldChoice = false;
        CountBlackChessSelectBlock = 0;
        CountBlackChessBoardScrollClick = 0;
        BlackChessIndex = 0;
        OrbitOledClearBuffer();
        OrbitOledUpdate();
      }
      else 
      {
        digitalWrite(RLED,HIGH);
        delay(1000);
        digitalWrite(RLED,LOW);
      }
    }
    else
    {
      if(checkIsValidMove(BlackChessIndex % 90, BlackChessOldMove))
      {
        digitalWrite(GLED,HIGH);
        delay(1000);
        digitalWrite(GLED,LOW);
        BlackChessNewMove = BlackChessIndex % 90;
        isBlackOldChoice = true;
        isBlackToMove = false;
        updateChessPiece(BlackChessOldMove, BlackChessNewMove);
        CountBlackChessSelectBlock = 0;
        CountBlackChessBoardScrollClick = 0;
        BlackChessIndex = 0;
        OrbitOledClearBuffer();
        OrbitOledUpdate();
        if(checkIfAnybodyWin()) gameChessUiPage = ChessGameResult;
      }
      else 
      {
        digitalWrite(RLED,HIGH);
        delay(1000);
        digitalWrite(RLED,LOW);
      }
    }
  }

  // if switch SW2 down and up, then playerRed seclect this piece
  if(gameInputState.switches[1].isRising)
  {
    if(isRedOldChoice)
    {
      if(checkIsValidChoice((RedChessIndex % 90), 1))
      {
        digitalWrite(GLED,HIGH);
        delay(1000);
        digitalWrite(GLED,LOW);
        RedChessOldMove = RedChessIndex % 90 ;
        isRedOldChoice = false;
        CountRedChessSelectBlock = 0;
        CountRedChessBoardScrollClick = 0;
        RedChessIndex = 0;
        OrbitOledClearBuffer();
        OrbitOledUpdate();
      }
      else 
      {
        digitalWrite(RLED,HIGH);
        delay(1000);
        digitalWrite(RLED,LOW);
      }
    }
    else
    {
      if(checkIsValidMove(RedChessIndex % 90, RedChessOldMove))
      {
        digitalWrite(GLED,HIGH);
        delay(1000);
        digitalWrite(GLED,LOW);
        RedChessNewMove = RedChessIndex % 90;
        isRedOldChoice = true;
        isBlackToMove = true;
        updateChessPiece(RedChessOldMove, RedChessNewMove);
        CountRedChessSelectBlock = 0;
        CountRedChessBoardScrollClick = 0;
        RedChessIndex = 0;
        OrbitOledClearBuffer();
        OrbitOledUpdate();
        if(checkIfAnybodyWin()) gameChessUiPage = ChessGameResult;
      }
      else 
      {
        digitalWrite(RLED,HIGH);
        delay(1000);
        digitalWrite(RLED,LOW);
      }
    }
  }
  
  //playerRedSelectPiece();
  //playerRedSelectMove();
  //checkIfWin();
  //playerBlackSelectPiece();
  //playerBlackSelectMove();
  //checkIfWin();
}

void updateChessPiece(int oldMove, int newMove)
{
  int oldRow = oldMove / 9;
  int oldCol = oldMove - oldRow * 9;
  int newRow = newMove / 9;
  int newCol = newMove - newRow * 9;
  chessBoardPiece[newRow][newCol] = chessBoardPiece[oldRow][oldCol];
  chessBoardPiece[oldRow][oldCol] = ' ';
}

bool checkIsValidChoice(int block, int player)
{
  int blockRow = block / 9;
  int blockCol = block - blockRow * 9;
  if(player == 0) // if is Black, then it can only select its chess
  {
    switch(chessBoardPiece[blockRow][blockCol])
    {
      case BLACK_JU:
        return true;
        break;

      case BLACK_MA:
        return true;
        break;

      case BLACK_XIANG:
        return true;
        break;

      case BLACK_SHI:
        return true;
        break;

      case BLACK_JIANG:
        return true;
        break;

      case BLACK_PAO:
        return true;
        break;

      case BLACK_BIN:
        return true;
        break;
        
      default:
        return false;
        break;
    }
  }
  else if (player == 1)
  {
    switch(chessBoardPiece[blockRow][blockCol])
    {
      case RED_JU:
        return true;
        break;

      case RED_MA:
        return true;
        break;

      case RED_XIANG:
        return true;
        break;

      case RED_SHI:
        return true;
        break;

      case RED_JIANG:
        return true;
        break;

      case RED_PAO:
        return true;
        break;

      case RED_BIN:
        return true;
        break;

      default:
        return false;
        break;
    }
  }
}

bool checkIsValidMove(int block, int old)
{
  int oldRow = old / 9;
  int oldCol = old - oldRow * 9;
  char oldPiece = chessBoardPiece[oldRow][oldCol];
  int blockRow = block / 9;
  int blockCol = block - blockRow * 9;
  switch(oldPiece)
  {
    // If cross the border, then can move UDLR
      case BLACK_JU:
        if(blockRow == oldRow)
        {
          int largerY = (blockCol > oldCol ? blockCol : oldCol);
          int smallerY = (blockCol < oldCol ? blockCol : oldCol);
          for(int i = smallerY + 1; i < largerY; i++)
          {
            if(chessBoardPiece[oldRow][i] != ' ') return false;
          }
          return true;
        }
        else if(blockCol == oldCol)
        {
          int largerX = (blockRow > oldRow ? blockRow : oldRow);
          int smallerX = (blockRow < oldRow ? blockRow : oldRow);
          for(int i = smallerX + 1; i < largerX; i++)
          {
            if(chessBoardPiece[i][oldCol] != ' ') return false;
          }
          return true;
        }
        return false;
        break;

      case RED_JU:
        if(blockRow == oldRow)
        {
          int largerY = (blockCol > oldCol ? blockCol : oldCol);
          int smallerY = (blockCol < oldCol ? blockCol : oldCol);
          for(int i = smallerY + 1; i < largerY; i++)
          {
            if(chessBoardPiece[oldRow][i] != ' ') return false;
          }
          return true;
        }
        else if(blockCol == oldCol)
        {
          int largerX = (blockRow > oldRow ? blockRow : oldRow);
          int smallerX = (blockRow < oldRow ? blockRow : oldRow);
          for(int i = smallerX + 1; i < largerX; i++)
          {
            if(chessBoardPiece[i][oldCol] != ' ') return false;
          }
          return true;
        }
        return false;
        break;

      case BLACK_MA:
        if(((blockRow - oldRow) == 2) && ((blockCol - oldCol) == 1)) return true;
        else if(((blockRow - oldRow) == 2) && ((blockCol - oldCol) == -1)) return true;
        else if(((blockRow - oldRow) == -2) && ((blockCol - oldCol) == 1)) return true;
        else if(((blockRow - oldRow) == -2) && ((blockCol - oldCol) == -1)) return true;
        else if(((blockRow - oldRow) == 1) && ((blockCol - oldCol) == 2)) return true;
        else if(((blockRow - oldRow) == -1) && ((blockCol - oldCol) == 2)) return true;
        else if(((blockRow - oldRow) == 1) && ((blockCol - oldCol) == -2)) return true;
        else if(((blockRow - oldRow) == -1) && ((blockCol - oldCol) == -2)) return true;
        return false;
        break;

      case RED_MA:
        if(((blockRow - oldRow) == 2) && ((blockCol - oldCol) == 1)) return true;
        else if(((blockRow - oldRow) == 2) && ((blockCol - oldCol) == -1)) return true;
        else if(((blockRow - oldRow) == -2) && ((blockCol - oldCol) == 1)) return true;
        else if(((blockRow - oldRow) == -2) && ((blockCol - oldCol) == -1)) return true;
        else if(((blockRow - oldRow) == 1) && ((blockCol - oldCol) == 2)) return true;
        else if(((blockRow - oldRow) == -1) && ((blockCol - oldCol) == 2)) return true;
        else if(((blockRow - oldRow) == 1) && ((blockCol - oldCol) == -2)) return true;
        else if(((blockRow - oldRow) == -1) && ((blockCol - oldCol) == -2)) return true;
        return false;
        break;

      case BLACK_XIANG:
        if(blockRow <= 4 && blockRow >= 0)
        {
          if(((blockRow - oldRow) == 2) && ((blockCol - oldCol) == 2)) return true;
          else if(((blockRow - oldRow) == -2) && ((blockCol - oldCol) == 2)) return true;
          else if(((blockRow - oldRow) == 2) && ((blockCol - oldCol) == -2)) return true;
          else if(((blockRow - oldRow) == -2) && ((blockCol - oldCol) == -2)) return true;
        }
        return false;
        break;

      case RED_XIANG:
        if(blockRow <= 9 && blockRow >= 5)
        {
          if(((blockRow - oldRow) == 2) && ((blockCol - oldCol) == 2)) return true;
          else if(((blockRow - oldRow) == -2) && ((blockCol - oldCol) == 2)) return true;
          else if(((blockRow - oldRow) == 2) && ((blockCol - oldCol) == -2)) return true;
          else if(((blockRow - oldRow) == -2) && ((blockCol - oldCol) == -2)) return true;
        }
        return false;
        break;

      case BLACK_SHI:
        if(blockRow <= 2 && blockRow >= 0 && blockCol >= 3 && blockCol <= 5)
        {
          if(((blockRow - oldRow) == 1) && ((blockCol - oldCol) == 1)) return true;
          else if(((blockRow - oldRow) == -1) && ((blockCol - oldCol) == 1)) return true;
          else if(((blockRow - oldRow) == -1) && ((blockCol - oldCol) == -1)) return true;
          else if(((blockRow - oldRow) == 1) && ((blockCol - oldCol) == -1)) return true;
        }
        return false;
        break;

      case RED_SHI:
        if(blockRow <= 9 && blockRow >= 7 && blockCol >= 3 && blockCol <= 5)
        {
          if(((blockRow - oldRow) == 1) && ((blockCol - oldCol) == 1)) return true;
          else if(((blockRow - oldRow) == -1) && ((blockCol - oldCol) == 1)) return true;
          else if(((blockRow - oldRow) == -1) && ((blockCol - oldCol) == -1)) return true;
          else if(((blockRow - oldRow) == 1) && ((blockCol - oldCol) == -1)) return true;
        }
        return false;
        break;

      case BLACK_JIANG:
        if(blockRow <= 2 && blockRow >= 0 && blockCol >= 3 && blockCol <= 5)
        {
          if(((blockRow - oldRow) == 1) && ((blockCol - oldCol) == 0)) return true;
          else if(((blockRow - oldRow) == -1) && ((blockCol - oldCol) == 0)) return true;
          else if(((blockRow - oldRow) == 0) && ((blockCol - oldCol) == 1)) return true;
          else if(((blockRow - oldRow) == 0) && ((blockCol - oldCol) == -1)) return true;
        }
        return false;
        break;

      case RED_JIANG:
        if(blockRow <= 9 && blockRow >= 7 && blockCol >= 3 && blockCol <= 5)
        {
          if(((blockRow - oldRow) == 1) && ((blockCol - oldCol) == 0)) return true;
          else if(((blockRow - oldRow) == -1) && ((blockCol - oldCol) == 0)) return true;
          else if(((blockRow - oldRow) == 0) && ((blockCol - oldCol) == 1)) return true;
          else if(((blockRow - oldRow) == 0) && ((blockCol - oldCol) == -1)) return true;
        }
        return false;
        break;

      case BLACK_PAO:
        if(blockRow == oldRow)
        {
          int countCrossBarrier = 0;
          int largerY = (blockCol > oldCol ? blockCol : oldCol);
          int smallerY = (blockCol < oldCol ? blockCol : oldCol);
          for(int i = smallerY + 1; i < largerY; i++)
          {
            if(chessBoardPiece[oldRow][i] != ' ')
            {
              countCrossBarrier++;
            }
          }
          if(countCrossBarrier == 1)  return true;
        }
        else if(blockCol == oldCol)
        {
          int countCrossBarrier = 0;
          int largerX = (blockRow > oldRow ? blockRow : oldRow);
          int smallerX = (blockRow < oldRow ? blockRow : oldRow);
          for(int i = smallerX + 1; i < largerX; i++)
          {
            if(chessBoardPiece[i][oldCol] != ' ') countCrossBarrier++;
          }
          if(countCrossBarrier == 1)  return true;
        }
        return false;
        break;

      case RED_PAO:
        if(blockRow == oldRow)
        {
          int countCrossBarrier = 0;
          int largerY = (blockCol > oldCol ? blockCol : oldCol);
          int smallerY = (blockCol < oldCol ? blockCol : oldCol);
          for(int i = smallerY + 1; i < largerY; i++)
          {
            if(chessBoardPiece[oldRow][i] != ' ')
            {
              countCrossBarrier++;
            }
          }
          if(countCrossBarrier == 1)  return true;
        }
        else if(blockCol == oldCol)
        {
          int countCrossBarrier = 0;
          int largerX = (blockRow > oldRow ? blockRow : oldRow);
          int smallerX = (blockRow < oldRow ? blockRow : oldRow);
          for(int i = smallerX + 1; i < largerX; i++)
          {
            if(chessBoardPiece[i][oldCol] != ' ') countCrossBarrier++;
          }
          if(countCrossBarrier == 1)  return true;
        }
        return false;
        break;

      case BLACK_BIN:
        if(oldRow >= 0 && oldRow <= 4)
        {
          if(((blockRow - oldRow) == 1) && (blockCol == oldCol))
          {
            return true;
          }
        }
        else if(oldRow >= 5 && oldRow <= 9)
        {
          if(((blockRow - oldRow) == 1) && (blockCol == oldCol)) return true;
          else if(((oldRow - blockRow) == 1) && (blockCol == oldCol)) return true;
          else if(((blockCol - oldCol) == 1) && (blockRow == oldRow)) return true;
          else if(((oldCol - blockCol) == 1) && (blockRow == oldRow)) return true;
        }
        return false;
        break;

      case RED_BIN:
        if(oldRow >= 5 && oldRow <= 9)
        {
          if(((blockRow - oldRow) == -1) && (blockCol == oldCol))
          {
            return true;
          }
        }
        else if(oldRow >= 0 && oldRow <= 4)
        {
          if(((blockRow - oldRow) == 1) && (blockCol == oldCol)) return true;
          else if(((oldRow - blockRow) == 1) && (blockCol == oldCol)) return true;
          else if(((blockCol - oldCol) == 1) && (blockRow == oldRow)) return true;
          else if(((oldCol - blockCol) == 1) && (blockRow == oldRow)) return true;
        }
        return false;
        break;
        
      default:
        return false;
        break;
  }
}

// return false if nobody wins
// return true if anybody wins
bool checkIfAnybodyWin()
{
  bool isBlackJiangExist = false;
  bool isRedJiangExist = false;
  for(int i = 0; i <= 2; i++)
    for(int j = 3; j <= 5; j++)
      {
        if(chessBoardPiece[i][j] == BLACK_JIANG)
          isBlackJiangExist = true;
      }
      
  for(int i = 7; i <= 9; i++)
    for(int j = 3; j <= 5; j++)
      {
        if(chessBoardPiece[i][j] == RED_JIANG)
          isRedJiangExist = true;
      }
   if(isRedJiangExist && isBlackJiangExist) return false;
   else if(!isRedJiangExist && isBlackJiangExist) ChessWinner = 1;
   else if(isRedJiangExist && !isBlackJiangExist) ChessWinner = -1;
   return true;
}

void handlePageChessGameResult()
{
  OrbitOledMoveTo(17, 0);
  OrbitOledDrawString("GAME RESULT");
  if(ChessWinner == 1)
  {
    OrbitOledMoveTo(0, 12);
    OrbitOledDrawString("Black Wins");
  }
  else if(ChessWinner == -1)
  {
    OrbitOledMoveTo(0, 12);
    OrbitOledDrawString("Red Wins");
  }
  else if(ChessWinner == 0)
  {
    OrbitOledMoveTo(0, 12);
    OrbitOledDrawString("Ties");
  }
  OrbitOledMoveTo(0, 24);
  OrbitOledDrawString("Press BTN1");

  // If press BTN1, go back to main page
  if(gameInputState.buttons[0].isRising)
  {
    OrbitOledClearBuffer();
    OrbitOledClear();
    gameChessInit();
    gameMainUiPage = Welcome;
  }  
}


void gameChessTick()
{
  switch(gameChessUiPage)
  {
    case WelcomeChess:
      handlePageWelcomeChess();
      break;

    case ChessInstructions:
      handlePageChessInstructions();
      break;

    case ChessDisplayBoard:
      handlePageChessDisplayBoard();
      break;

    case ChessGameResult:
      handlePageChessGameResult();
      break;

    default:
      break;
  }
}


