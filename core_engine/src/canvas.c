#include <stdio.h>
#include <stdlib.h>
#include "../include/canvas.h"

char** canvas_create(){
    char** canvas = malloc(CANVAS_HEIGHT * sizeof(*canvas));
    if(!canvas) return NULL;

    for(int i = 0; i< CANVAS_HEIGHT; i++){
        canvas[i] = malloc(CANVAS_WIDTH * sizeof(*canvas[i]));
        if(!canvas[i]){
            for(int j = 0; j < i; j++){
                free(canvas[j]);
            }
            free(canvas);
            return NULL;
        }
    }
    return canvas;
}

void canvas_clear(char** canvas){
    if(!canvas) return;
    for(int y=0; y< CANVAS_HEIGHT; y++){
        for(int x= 0; x< CANVAS_WIDTH; x++){
                canvas[y][x] = BG_CHAR;
        }
    }
}

void canvas_set_pixel( char** canvas, int x, int y, char c){
    if(!canvas) return;
    if(x>=0 && x<CANVAS_WIDTH && y>= 0 && y < CANVAS_HEIGHT){
        canvas[y][x] = c;
    }
}

void canvas_print(char** canvas){
    if(!canvas) return;
    for(int y=0; y< CANVAS_HEIGHT; y++){
        for(int x= 0; x< CANVAS_WIDTH; x++){
                putchar(canvas[y][x]);
        }
        putchar('\n');
    }
}

void canvas_free(char** canvas){
    if(!canvas) return;
    for(int y= 0; y< CANVAS_HEIGHT; y++){
        free(canvas[y]);
    }
    free(canvas);
}
