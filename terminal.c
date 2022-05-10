#include<stdio.h>
#include<termios.h>
#include"terminal.h"

/* disables the need to press enter for player input
    and disables input echo in terminal */
void disableBuffer()
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag &= ~(ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}

/* re-enables echo and canon functionality */
void enableBuffer()
{
    struct termios mode;

    tcgetattr(0, &mode);
    mode.c_lflag |= (ECHO | ICANON);
    tcsetattr(0, TCSANOW, &mode);
}