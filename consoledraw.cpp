#include "consoledraw.hpp"

#include <stdio.h>

// sets the cursor location to a particular coordinate on the screen
//     (0, 0) is in the top left
void setCursorLocation(int x, int y)
{
    printf("\x1B[%d;%dH", y, x);
}

// print a character at a particular location on the screen
void printAt(int x, int y, char c)
{
    setCursorLocation(x,y);
    printf("%c", c);
    setCursorLocation(-x,-y);
}

// set the cursor to the top left
void resetCursor()
{
    printf("\e[;0m;");
}

// attempt to set the screen size (experimental)
void setScreenSize(int height, int width)
{
    printf("\e[8;%d;%dt", height, width);
}

// clear the screen
void resetScreen()
{
    printf("\x1b[1J\033[H");
}
