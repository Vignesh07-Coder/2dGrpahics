#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "../include/engine.h"
#include "../include/canvas.h"

void init_terminal(){
    initscr();
    cbreak();
    noecho();
    keypad(stdcr, TRUE);
    curs_set(0);
    nodedelay(stdscr, TRUE);
        }