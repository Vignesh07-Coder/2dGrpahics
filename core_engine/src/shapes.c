#include <stdlib.h>
#include <math.h>
#include "../include/shapes.h"
#include "../include/canvas.h"

static void draw_circle( Shape* self, char** canvas){
  CircleData* c = (CircleData*)self->specific_data;
   //  inside this Shape, the specific_data actually points to a CircleData object
    int x = c->radius;
    int y = 0;
    int err =0;

    while(x>=y){
        canvas_set_pixel(canvas, c-> x+x, c->y+y, PIXEL_CHAR);
        canvas_set_pixel(canvas, c-> x+y, c->y+x, PIXEL_CHAR);
        canvas_set_pixel(canvas, c-> x-y, c->y+x, PIXEL_CHAR);
        canvas_set_pixel(canvas, c-> x-x, c->y+y, PIXEL_CHAR);
        canvas_set_pixel(canvas, c-> x-y, c->y-x, PIXEL_CHAR);
        canvas_set_pixel(canvas, c-> x+y, c->y-x, PIXEL_CHAR);
        canvas_set_pixel(canvas, c-> x+x, c->y-y, PIXEL_CHAR);
     
        if(err <= 0){
            y+= 1;
            err+= 2*y + 1;
        }
        if( err >0){
            x-=1;
            err -= 2*x +1;
        }
    
    }
}

static void draw_line(Shape * self, char** canvas){
    LineData* l = (LineData*)self ->specific_data;
    int dx = abs(l->x2 - l->x1), sx = l->x1 < l->x2 ? 1 : -1;
    int dy = abs(l->y2 - l->y1), sy = l->y1 < l->y2 ? 1 : -1;
    int err = dx + dy, e2;

    int x = l->x1;
    int y = l->y1;

    while(1){
        canvas_set_pixel(canvas, x, y, PIXEL_CHAR);
        if(x == l->x2 && y == l->y2) break;
        e2 = 2 * err;
        if(e2 >= dy){ err +=dy ; x += sx; }
        if(e2 >= dx){ err +=dx ; y += sy; }
    
    }
}

static void destroy_generic(Shape* self){
    if(self->specific_data){
        free(self->specific_data);
    }
}
Shape* create_circle(int id, int x, int y, int radius){
    Shape* s = (Shape*)malloc(sizeof(Shape));
    CircleData* data = (CircleData*)malloc(sizeof(CircleData));
    
    data->x = x; data->y = y; data->radius = radius;

    s->id = id;
    s->type = CIRCLE;
    s->specific_data = data;
    s->draw = draw_circle;
    s->destroy = destroy_generic;
    s->prev = NULL; s->next = NULL;

    return s;
}

Shape* create_line(int id, int x, int y, int radius){
    Shape* s = (Shape*)malloc(sizeof(Shape));
    LineData* data = (LineData*)malloc(sizeof(LineData));
    
    data->x1 = x1; data->y1 = y1; data->x2 = x2; data->y2 = y2; 

    s->id = id;
    s->type = LINE;
    s->specific_data = data;
    s->draw = draw_line;
    s->destroy = destroy_generic;
    s->prev = NULL; s->next = NULL;

    return s;
}