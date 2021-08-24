#include <stdio.h>
#include <stdbool.h>
#define idx 100
typedef struct{
    int data[idx];
    int size;
}Stack;
void makenull_Stack(Stack *s){
    s->size=0;
}
bool empty_Stack(Stack *s){
    return s->size==0;
}
void push_Stack(Stack *s, int element){
    s->data[s->size]=element;
    s->size++;
}
int get_Stack(Stack *s){
    return s->data[s->size-1];
}

void delete_size(Stack *s){
    s->size--;
}
