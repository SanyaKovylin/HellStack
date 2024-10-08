#include <stdio.h>
#include "stack.h"

void print_int(FILE *fw, void* elem);

int main(void){
    int e = 12;
    SetLog("Stack.log");
    Stack st = {};
    STACK_ASSERT(&st);
    StackCtor(&st, 0, 4, '\r', print_int);
    for (int i = 1; i < 116; i++){
        StackPush(&st, &i);
    }

    DUMP(&st);

    for  (int i = 0; i < 100; i++){
        StackPop(&st, &e);
    }
    printf("%d", e);
    return 0;
}
void print_int(FILE *fw, void* elem) {
    fprintf(fw,"%d", *((int*) elem));
}
