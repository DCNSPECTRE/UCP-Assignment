#ifndef TERMINAL_H
#define TERMINAL_H

/* Header file for terminal buffer control */
#include<stdio.h>
#include<termios.h>

void disableBuffer();
void enableBuffer();

#endif