#include <stdlib.h>
#include <stdio.h>
#include "../include/engine.h"
#include "../include/canvas.h"


void engine_init(Engine* engine){
    engine->head = NULL;
    engine->tail = NULL;
    engine->next_id = 1;
}

void engine_add_shape(Engine* engine, Shape* shape){
    if(!engine || !shape) return;

    if(!engine->head){
        engine->head = shape;
        engine->tail = shape;
    } else{
        engine->tail->next = shape;
        shape->prev = engine->tail;
        engine->tail = shape;
    }
}

void engine_delete_shape(Engine* engine, int id){
    Shape* current = engine->head;
    while(current != NULL){
        if(current->id==id){
           //how does the unlinking happen!
            if(current->prev) current ->prev->next = current->next;
            else engine->head = current->next;

            if(current->next) current->next->prev = current->prev;
            else engine->tail = current->prev;

            //clean the memory
            current->destroy(current);
            free(current);
            return;
        }
        current = current->next;
    }
}

Shape *engine_get_shape(Engine* engine, int id){
    Shape* current = engine->head;
    while(current!= NULL){
        if(current->id == id) return current;
        current = current->next;
    }
    return NULL;
}

void engine_render(Engine* engine, char** canvas){
    canvas_clear(canvas);
    Shape *current = engine->head;
    while(current != NULL){
        current->draw(current, canvas);
        current = current->next;
    }
    canvas_print(canvas);
}

void engine_cleanup(Engine* engine){
    Shape* current = engine->head;
    while(current !=NULL){
        Shape* next = current->next;
        current->destroy(current);
        free(current);
        current = next;
    }
    engine->head = NULL;
    engine->tail = NULL;

}
