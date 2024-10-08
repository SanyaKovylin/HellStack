#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

#include "stack.h"
#include "stackdef.h"

template <typename T>
inline T val (T value) { return StackCheck(value);}

#define val(value) ( value )
#define verified  || val(src)
#define Max(x, y) (x) > (y) ? (x) : (y)

const char *var = "src";
FILE *flog = stderr;

StackError StackCtor (Stack *src, size_t length, size_t elsize, char toxicvalue, void (*FprintFunc)(FILE* flog, void* elem)){

    #if !defined(NOCANS) && !defined(NOOOOOOOOOOOOOO)
        src->data = (void *) calloc (1, length * elsize + 2*Cansize);
        memcpy(src->data, Can, Cansize);
    #else
        src->data = (void *) calloc (1, length * elsize);
    #endif

    if (src->data == NULL) return EMPTY_SOURCE;

    src->elsize = elsize;
    src->FprintF = FprintFunc;
    src->size = length * elsize;
    src->toxic = toxicvalue;

    #if !defined(NOCANS) && !defined(NOOOOOOOOOOOOOO)
        src->data = (void *) ((char *) src->data + Cansize);
        memcpy((char*) src->data +  src->elsize * length, Can, Cansize);
        src->CanRight = CanStruct;
        src->CanLeft = CanStruct;
    #endif

    src->pointer = 0;

    STACK_ASSERT(src);
    return StackCheck(src);
}

StackError StackDtor(Stack *src){
    STACK_ASSERT(src);

    #if !defined(NOOOOOOOOOOOOOO) && !defined(NOCANS)
        free((char *)src->data - Cansize);
    #else
        free(src->data);
    #endif

    src->pointer = 0;
    src->size = 0;
    src->toxic = 0;

    #if !defined(NOOOOOOOOOOOOOO) && !defined(NOCANS)
        src->CanLeft = 0;
        src->CanRight = 0;
        src->info = {};
    #endif

    src->elsize = 0;
    src->FprintF = NULL;
    src->data = NULL;
    //TODO setvbuf
    return ST_OK;
}

StackError StackPush (Stack *src, void* elem){
    STACK_ASSERT(src);

    if (src->pointer == src->size) {
        Resize(src, (int)((float) src->size * resizeval)) verified;
    }

    if (src->size == 0) {
        Resize(src, DefaultSize) verified;
    }

    memcpy((char*) src->data + src->pointer, elem, src->elsize);

    src->pointer += src->elsize;

    DEBUG;

    STACK_ASSERT(src);
    return StackCheck(src);
}

static StackError Resize(Stack *src, size_t size) {
    STACK_ASSERT(src);

    src->size =  Max(size, DefaultSize * src->elsize);

    #if !defined(NOCANS) && !defined(NOOOOOOOOOOOOOO)

        void *buf = (void*) realloc ((char*) src->data - Cansize, src->size + 2*Cansize);

        if (!buf) return EMPTY_STACK;
        if (src->pointer < src->size)
            memset((char *)buf + src->pointer + Cansize, src->toxic, src->size - src->pointer);

        src->data = (char *)buf + Cansize;
        memcpy((char*)src->data + src->size, Can, Cansize);
    #else
        void *buf = (void*) realloc ((char*) src->data, src->size);
        if (!buf) return EMPTY_STACK;
        src->data = (char *)buf;
    #endif

    DEBUG;

    DUMP(src);
    STACK_ASSERT(src);
    return StackCheck(src);
}


StackError StackPop (Stack *src, void *elem){
    STACK_ASSERT(src);

    if (src->pointer == 0)
        return I_CHTO_YA_DOLZHEN_PUSHIT;

    src->pointer -= src->elsize;
    memcpy(elem , (char*) src->data + src->pointer, src->elsize);
    memset((char*) src->data + src->pointer, 0, src->elsize);

    DEBUG;

    if (src->pointer <= (int) ((float)src->size / resizeval) && src->size > DefaultSize){
        Resize(src, (int)((float)src->size / resizeval)) verified;
    }

    DEBUG;

    STACK_ASSERT(src);
    return StackCheck(src);
}

static StackError StackCheck (Stack *src) {

    if (src == NULL)                                 return EMPTY_STACK    ;
    if (src->data == NULL)                            return EMPTY_SOURCE   ;
    if (src->elsize == 0)                            return UNINIT_STACK   ;
    if (src->pointer > src->size && src->size != 0)  return STACK_OVERFLOW ;
    if (!src->FprintF)                               return I_KAK_PECHATAT ;

    #if !defined(NOCANS) && !defined(NOOOOOOOOOOOOOO)
        if (memcmp((char*)src->data - Cansize, Can, Cansize) ||
            memcmp((char *)src->data + src->size, Can, Cansize)) {
            return LAZHA;}
        if (src->CanLeft != CanStruct || src->CanRight != CanStruct) {
        return LAZHA_V_STRUCTE;}
    #endif

    #if !defined(NOHASH) && !defined(NOOOOOOOOOOOOOO)
        if (src->size && (Hash(src->data, (char *)src->data + src->size) != src->info.line)) return POPALSYA_NA_HASHE;
    #endif

    return ST_OK;
}

static StackError StackDump(Stack *src, const char *file, const int line, const char *errname) {

    fprintf(flog, "Dump from %s:%d\n", file, line);

    fprintf(flog, "Error type: %s\n", errname);
    if (src->data != NULL){

        #if !defined(NOHASH) && !defined(NOOOOOOOOOOOOOO)
            for (size_t i = 0; i < Cansize; i++){
                    fprintf(flog, "[%c]", *((char*)src->data + i - Cansize));
            }
            fputs("\n", flog);
        #endif

        for (size_t i = 0; i < src->size / src->elsize; i++){
            if (i < src->pointer/src->elsize) {
                fputs("* [", flog);
                src->FprintF(flog, (char *)src->data + src->elsize*i);
                fputs("]\n", flog);
            }
            else {
                fprintf(flog, "  [NONE] \n");
            }
        }

        #if !defined(NOHASH) && !defined(NOOOOOOOOOOOOOO)
            for (size_t i = 0; i < Cansize; i++){
                    fprintf(flog, "[%c]", *((char*)src->data + src->size + i));
            }
            fprintf(flog, "\n");
        #endif
    }
    fprintf(flog,"\n--------------------------------------------------------------------------------\n");
    return StackCheck(src);

}

static size_t Hash(void* st, void* end) { //Adler32

    assert((char *) end > (char *) st);

    unsigned short Low = 1;
    unsigned short High = 0;

    for (size_t i = 0; i < (size_t) ((char*) end - (char *) st); i++) {

        Low += *(((unsigned char *) st) + i);
        High += Low;
    }

    return (High << 16) | Low;
}

void SetLog(const char* name){
    flog = fopen(name, "w");
    setvbuf(flog, 0, _IONBF, 0);
}

#pragma GCC diagnostic ignored "-Wswitch-default"
#pragma GCC diagnostic ignored "-Wreturn-type"
const char *Definition (StackError code ){
#define DEF_ERR(elem) case(elem): return #elem;
    switch (code) {
        DEF_ERR(ST_OK)
        DEF_ERR(EMPTY_STACK)
        DEF_ERR(EMPTY_SOURCE)
        DEF_ERR(STACK_OVERFLOW)
        DEF_ERR(LAZHA)
        DEF_ERR(POPALSYA_NA_HASHE)
        DEF_ERR(LAZHA_V_STRUCTE)
        DEF_ERR(UNINIT_STACK)
        DEF_ERR(INVALID_POINTER)
        DEF_ERR(I_KAK_PECHATAT)
        DEF_ERR(I_CHTO_YA_DOLZHEN_PUSHIT)
        default: return "OTKUDA VY VZYALI ETU OSHIBKY?";
    }
}
#pragma GCC diagnostic error "-Wswitch-default"
#pragma GCC diagnostic error "-Wreturn-type"
