#ifndef CANVAS_H
#define CANVAS_H

#define CANVAS_WIDTH 80
#define CANVAS_HEIGHT 24

#define PIXEL_CHAR '*'
#define BG_CHAR '_'
/*allocating a 2d array of dimensions CANVAS_WIDTH * CANVAS_HEIGHT in memory
retruns a pointer to the array*/
char** canvas_create();
void canvas_clear(char** canvas);
/*inserts a char at x,y.
drops the pixel if they are out of bounds */
void canvas_set_pixel(char** canvas, int x, int y, char c);
/*Print the 2d array to stdout */
void canvas_print(char** canvas);
void canvas_free(char** canvas);






#endif