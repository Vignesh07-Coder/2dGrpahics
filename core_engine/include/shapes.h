#ifndef SHAPES_H
#define SHAPES_H

typedef enum {CIRCLE, RECTANGLE, LINE, TRINAGLE} ShapeType;
//Forward declaration to tell the complier to recognize this as a struct, so that it doesnt throw error below even when not intialized
typedef struct Shape Shape;

typedef void(*DrawFunc)(Shape* self, char** canvas);
typedef void(*DestroyFunc)(Shape* self);
/*the above functions have a polymorphic behaviour*/
 struct Shape{
    int id;
    ShapeType type;
    void* specific_data;
    DrawFunc draw;
    DestroyFunc destroy;
    Shape* prev;
    Shape* next;

 };

 typedef struct {
    int x,y;
    int width, height;
 }RectangeleData;

 typedef struct{
    int x, y;
    int radius;
 }CircleData;

 typedef struct{
    int x1, y1;
    int x2, y2;
}LineData;

typedef struct{
    int x1, y1;
    int x2, y2;
    int x3, y3;
}TriangleData;


//Constructors
//Allocate the Shape, the specific data, and wireuo the functions
Shape* create_circle(int id, int x, int y, int radius);
Shape* create_rectangle(int id, int x, int y, int w, int h);
Shape* create_line(int id, int x1, int y1, int x2, int y2);
Shape* create_triangle(int id, int x1, int y1, int x2, int y2, int x3, int y3);

#endif
