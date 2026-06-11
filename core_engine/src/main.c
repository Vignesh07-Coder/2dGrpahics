#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include "../include/engine.h"
#include "../include/canvas.h"

void init_terminal(){
    initscr(); //starting the ncrses mode
    cbreak(); //disable the terminal line buffering
    noecho(); //not to echo the keystrokes 
    keypad(stdscr, TRUE);
    curs_set(0);
    nodelay(stdscr, TRUE);
        }

int main(){
    Engine eng;
    engine_init(&eng);
    char** canvas = canvas_create();
    if(!canvas){
        fprintf(stderr, "Failed to create canvas.\n");
        return 1;
    }

    init_terminal();

    int cursor_x = CANVAS_WIDTH/2;
    int cursor_y = CANVAS_HEIGHT/2;
    int running = 1;

    engine_add_shape(&eng, create_line(eng.next_id++, 0, 10, CANVAS_WIDTH -1, 10));

    while(running){
        int ch = getch();
        switch(ch){
        case KEY_UP :   if(cursor_y > 0) cursor_y--; break;
        case KEY_DOWN : if(cursor_y < CANVAS_HEIGHT - 1) cursor_y++; break;
        case KEY_LEFT : if(cursor_x > 0) cursor_x--; break;
        case KEY_RIGHT : if(cursor_x < CANVAS_WIDTH - 1) cursor_x++; break;
    
        case 'c':// drop a circle at the cursor
            engine_add_shape(&eng, create_circle(eng.next_id++, cursor_x, cursor_y, 4));
            break;

        case 'l':// drop a circle at the cursor
            engine_add_shape(&eng, create_line(eng.next_id++, cursor_x, cursor_y, cursor_x + 10, cursor_y + 5));
            break;
        case 'x' : //delete the last node added, like an undo operation
        if(eng.next_id > 1){
            engine_delete_shape(&eng, --eng.next_id);
        }
        break;
        case 'q' :
        running = 0;
        break;// quit
    }

    // Updating and the rasterization model
    // letting the engine drawing all the shapes to the off-screen 2D array

    canvas_clear(canvas);
     Shape* current = eng.head;
     while(current != NULL){
        current->draw(current, canvas);
        current = current->next;
     }

     //overlay th euser's cursor on the array (represented by 'X')
     canvas_set_pixel(canvas, cursor_x, cursor_y, 'X');

     // Render view 
     //Blasting the 2d array to the ncurses window
     for(int y= 0; y< CANVAS_HEIGHT; y++){
        move(y, 0);
        for(int x = 0; x< CANVAS_WIDTH; x++){
                addch(canvas[y][x]);
        }
    }
    //Adding the UI instructions to the scree at the bottom
    mvprintw(CANVAS_HEIGHT, 0, " ARROWS : Move | 'c' : Circle | 'l' : Line | 'x' : Undo | 'q' : Quit");
    refresh(); // telling the ncurses to update the physical screen
    //Delay to prevent the 100% CPU usage
    napms(16); // 60 Frames per second
}

//Cleanup and exit

endwin();
engine_cleanup(&eng);
canvas_free(canvas);
printf("Engine Shutdown Complete!..\nMemory freed.\n");
return 0;

}        
