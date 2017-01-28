#include <FillPat.h>
#include <LaunchPad.h>
#include <OrbitBoosterPackDefs.h>
#include <OrbitOled.h>
#include <OrbitOledChar.h>
#include <OrbitOledGrph.h>
#include <stdlib.h>

// A strange fact is the following should have been 
// in our orbitOled library. But it appears to be not.
// So I just copy these things here
// COPY STARTS
extern int    xcoOledCur;
extern int    ycoOledCur;
extern char * pbOledCur;
extern char   rgbOledBmp[];
extern char   rgbFillPat[];
extern int    bnOledCur;
extern char   clrOledCur;
extern char * pbOledPatCur;
extern char * pbOledFontUser;
extern char * pbOledFontCur;
extern int    dxcoOledFontCur;
extern int    dycoOledFontCur;  



/* ------------------------------------------------------------ */
/***  OrbitOledClampXco
**
**  Parameters:
**    xco   - x value to clamp
**
**  Return Value:
**    Returns clamped x value
**
**  Errors:
**    none
**
**  Description:
**    This routine forces the x value to be on the display.
*/

int
OrbitOledClampXco(int xco)
  {
  if (xco < 0) {
    xco = 0;
  }
  if (xco >= ccolOledMax) {
    xco = ccolOledMax-1;
  }

  return xco;

}

/* ------------------------------------------------------------ */
/***  OrbitOledClampYco
**
**  Parameters:
**    yco   - y value to clamp
**
**  Return Value:
**    Returns clamped y value
**
**  Errors:
**    none
**
**  Description:
**    This routine forces the y value to be on the display.
*/

int
OrbitOledClampYco(int yco)
  {
  if (yco < 0) {
    yco = 0;
  }
  if (yco >= crowOledMax) {
    yco = crowOledMax-1;
  }

  return yco;

}



// COPY ENDS


/* ------------------------------------------------------------ */
/***  OrbitOledDrawBracket
**
**  Parameters:
**    xco   - x coordinate of other corner
**    yco   - y coordinate of other corner
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Draw a bracket bounded by the current location and
**    the specified location.
*/

void OrbitOledDrawBracket(int xco, int yco)
{
  int xco1;
  int yco1;

  // Clamp the point to be on the display.
  xco = OrbitOledClampXco(xco);
  yco = OrbitOledClampYco(yco);
  
  xco1 = xcoOledCur;
  yco1 = ycoOledCur + (yco - ycoOledCur) * 2;

  // Clamp the point to be on the display.
  xco1 = OrbitOledClampXco(xco1);
  yco1 = OrbitOledClampYco(yco1);
  
  OrbitOledLineTo(xco, yco);
  OrbitOledLineTo(xco1, yco1);
}

/* ------------------------------------------------------------ */
/***  printInstruction
**
**  Parameters:
**    ins   - the instruction that will be printed
**    count - use count to control which part of the instruction will be displayed
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Print the given part of the instruction
**    Remember to update the count after using this function
**    Use count += 16; to update
*/
void printInstruction(String ins, uint32_t count) {
    ins.toUpperCase();
    String toShow; 
    char charBuf[50]; // toShow will be converted into charBuf[]

    // Only when the message is not completely printed, we print it.
    if(count <= ins.length()) {
        OrbitOledClear();
        OrbitOledClearBuffer();
        
        // If there is enough chars to be printed on the second row, we print them.
        if(ins.length() >= count + 16) {
          toShow = ins.substring(count, count + 16);
          toShow.toCharArray(charBuf, 50);
          OrbitOledMoveTo(0, 12);
          OrbitOledDrawString(charBuf);
        }
        // If there is not enough chars to be printed on the second row, it means we are almost at the end of the string.
        // We print the rest of the string.
        else {
          int remain = ins.length() - count;
          toShow = ins.substring(count, count + remain);
          toShow.toCharArray(charBuf, 50);
          OrbitOledMoveTo(0, 12);
          OrbitOledDrawString(charBuf);
          return;
        }

        // If there is enough chars to be printed on the third row, we print them.
        if(ins.length() >= count + 32) {
          toShow = ins.substring(count + 16, count + 32);
          toShow.toCharArray(charBuf, 50);
          OrbitOledMoveTo(0, 24);
          OrbitOledDrawString(charBuf); 
        }
        // If there is not enough chars to be printed on the third row, it means we are almost at the end of the string.
        // We print the rest of the string.
        else {
          int remain = ins.length() - count;
          toShow = ins.substring(count + 16, count + remain);
          toShow.toCharArray(charBuf, 50);
          OrbitOledMoveTo(0, 24);
          OrbitOledDrawString(charBuf);
          return;
        }      
    }
}

/* ------------------------------------------------------------ */
/***  drawChessBoardVerticalLine
**
**  Parameters:
**    i   - offset in y coordinate
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Draw the vertical line of chess board
**    e.g. | | | | | | | |    
*/

void drawChessBoardVerticalLine(int i)
{
  OrbitOledMoveTo(3, 7+i);
  OrbitOledLineTo(3, 15+i);
  OrbitOledMoveTo(18, 7+i);
  OrbitOledLineTo(18, 15+i);
  OrbitOledMoveTo(33, 7+i);
  OrbitOledLineTo(33, 15+i);
  OrbitOledMoveTo(48, 7+i);
  OrbitOledLineTo(48, 15+i);
  OrbitOledMoveTo(63, 7+i);
  OrbitOledLineTo(63, 15+i);
  OrbitOledMoveTo(78, 7+i);
  OrbitOledLineTo(78, 15+i);
  OrbitOledMoveTo(93, 7+i);
  OrbitOledLineTo(93, 15+i);
  OrbitOledMoveTo(108, 7+i);
  OrbitOledLineTo(108, 15+i);
  OrbitOledMoveTo(123, 7+i);
  OrbitOledLineTo(123, 15+i);
}

/* ------------------------------------------------------------ */
/***  drawChessBoardHorizontalLine
**
**  Parameters:
**    i   - offset in y coordinate
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Draw the horizontal line of chess board
**    e.g. - - - - - - - -    
*/
void drawChessBoardHorizontalLine(int i)
{
  OrbitOledMoveTo(7, 3+i);
  OrbitOledLineTo(15, 3+i);
  OrbitOledMoveTo(22, 3+i);
  OrbitOledLineTo(30, 3+i);
  OrbitOledMoveTo(37, 3+i);
  OrbitOledLineTo(45, 3+i);
  OrbitOledMoveTo(52, 3+i);
  OrbitOledLineTo(60, 3+i);
  OrbitOledMoveTo(67, 3+i);
  OrbitOledLineTo(75, 3+i);
  OrbitOledMoveTo(82, 3+i);
  OrbitOledLineTo(90, 3+i);
  OrbitOledMoveTo(97, 3+i);
  OrbitOledLineTo(105, 3+i);
  OrbitOledMoveTo(112, 3+i);
  OrbitOledLineTo(120, 3+i);
}

/* ------------------------------------------------------------ */
/***  drawChessBoardCrossLine1
**
**  Parameters:
**    i   - offset in y coordinate
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Draw the cross line \/ of chess board 
*/
void drawChessBoardCrossLine1(int i) 
{
  OrbitOledMoveTo(52, 7+i);
  OrbitOledLineTo(60, 15+i);
  OrbitOledMoveTo(75, 7+i);
  OrbitOledLineTo(67, 15+i);
}

/* ------------------------------------------------------------ */
/***  drawChessBoardCrossLine2
**
**  Parameters:
**    i   - offset in y coordinate
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Draw the cross line /\ of chess board 
*/
void drawChessBoardCrossLine2(int i) 
{
  OrbitOledMoveTo(60, 7+i);
  OrbitOledLineTo(52, 15+i);
  OrbitOledMoveTo(67, 7+i);
  OrbitOledLineTo(75, 15+i);
}

/* ------------------------------------------------------------ */
/***  drawChessBoardPiece
**
**  Parameters:
**    index   - index of which row of chess pieces that will be shown
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Draw the index and index+1 rows of the chess pieces
*/
void drawChessBoardPiece(int index)
{
  for(int i = 0; i < 9; i++)
  {
    OrbitOledMoveTo(15*i,7);
    OrbitOledDrawChar(chessBoardPiece[index][i]);
  }
  for(int j = 0; j < 9; j++)
  {
    OrbitOledMoveTo(15*j,22);
    OrbitOledDrawChar(chessBoardPiece[index+1][j]);
  }
}

/* ------------------------------------------------------------ */
/***  drawChessBoardLineStyle1
**
**  Parameters:
**    none
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Draw borad line page with \/
*/
void drawChessBoardLineStyle1()
{
  drawChessBoardHorizontalLine(7);
  drawChessBoardVerticalLine(7);
  drawChessBoardHorizontalLine(15+7);
  drawChessBoardCrossLine1(7);
}


/* ------------------------------------------------------------ */
/***  drawChessBoardLineStyle2
**
**  Parameters:
**    none
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Draw borad line page with /\
*/
void drawChessBoardLineStyle2()
{
  drawChessBoardHorizontalLine(7);
  drawChessBoardVerticalLine(7);
  drawChessBoardHorizontalLine(15+7);
  drawChessBoardCrossLine2(7);
}

/* ------------------------------------------------------------ */
/***  drawChessBoardLineStyle3
**
**  Parameters:
**    none
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Draw the normal board line page
*/
void drawChessBoardLineStyle3()
{
  drawChessBoardHorizontalLine(7);
  drawChessBoardVerticalLine(7);
  drawChessBoardHorizontalLine(15+7);
}

/* ------------------------------------------------------------ */
/***  drawChessBoardLineStyle4
**
**  Parameters:
**    none
**
**  Return Value:
**    none
**
**  Errors:
**    none
**
**  Description:
**    Draw the board line page with spaces
*/
void drawChessBoardLineStyle4()
{
  drawChessBoardHorizontalLine(7);
  OrbitOledMoveTo(3, 14);
  OrbitOledLineTo(3, 22);
  OrbitOledMoveTo(123, 14);
  OrbitOledLineTo(123, 22);
  drawChessBoardHorizontalLine(15+7);
}


