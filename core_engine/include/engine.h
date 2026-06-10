#ifndef ENGINE_H
#define ENGINE_H

#include "shapes.h"

typedef struct{
    Shape* head;
    Shape* tail;
    int next_id;
    
}Engine;
void engine_init(Engine* engine);
void engine_add_shape(Engine* engine, Shape* shape);
void engine_delete_shape(Engine* engine, int id);
void engine_get_shape(Engine* engine, int id);
void engine_render(Engine* engine, char** canvas);
void engine_cleanup(Engine* engine);


#endif 