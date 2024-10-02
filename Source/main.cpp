#include <stdio.h>
#include "stack.h"

void print_int(FILE *fw, void* elem);

int main(void){
    Stack st = {};
    STACK_ASSERT(st);
    StackCtor(&st, 8, 4, '\r', print_int);
    for (int i = 1; i < 116; i++)
        StackPush(&st, &i);
    int e = 12;
    DUMP(st);
    for  (int i = 0; i < 100; i++){
        StackPop(&st, &e);
        printf("%d\n",e);
    }
    printf("%d",e);
    return 0;
}

void print_int(FILE *fw, void* elem) {
    fprintf(fw,"%d", *((int*) elem));
}