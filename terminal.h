#ifndef TERMINAL_H
#define TERMINAL_H

#include <stdio.h>
#include <unistd.h>
#include <termios.h>

void disableBuffer();
void enableBuffer();

#endif