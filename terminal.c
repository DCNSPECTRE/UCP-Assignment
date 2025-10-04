#include "terminal.h"

void disableBuffer()
{
    struct termios mode;
    tcgetattr(STDIN_FILENO, &mode); /* Get current terminal settings */
    mode.c_lflag &= ~(ICANON | ECHO); /* Turn off canonical mode and echo */
    tcsetattr(STDIN_FILENO, TCSANOW, &mode); /* Apply new settings */
}

void enableBuffer()
{
    struct termios mode;
    tcgetattr(STDIN_FILENO, &mode);
    mode.c_lflag |= (ICANON | ECHO); /* Turn on canonical mode and echo */
    tcsetattr(STDIN_FILENO, TCSANOW, &mode);
}