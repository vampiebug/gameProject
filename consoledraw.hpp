#ifndef CONSOLEDRAW_H
#define CONSOLEDRAW_H

// operations 
#define BOLD    "\x1b[1m"
#define U_ON    "\x1b[4m"
#define INVERT  "\x1b[7m"
#define BLNK_ON "\x1b[5m"
#define BLNK_OFF "\x1b[25m"
#define U_OFF   "\x1b[24m"
#define LGRN    "\x1b[92m"

// Foreground 
#define KNRM  "\x1B[0m"
#define KBLK  "\x1B[30m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
#define KPNK  "\x1b[38;5;197m"
#define ORNG  "\x1b[38;5;202m"

// Background
#define BBLK  "\x1B[40m"
#define BRED  "\x1B[41m"
#define BGRN  "\x1B[42m"
#define BYEL  "\x1B[43m"
#define BBLU  "\x1B[44m"
#define BMAG  "\x1B[45m"
#define BCYN  "\x1B[46m"
#define BWHT  "\x1B[47m"

void setCursorLocation(int x, int y);
void printAt(int x, int y, char c);
void resetCursor();
void setScreenSize(int height, int width);
void resetScreen();

#endif
