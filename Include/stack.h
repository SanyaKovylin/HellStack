#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <ctype.h>

#include "colors.h"

#ifndef NOOOOOOOOOOOOOO
    struct DebugInfo {
        const char *filename;
        size_t line;
        const char *name;
    };
#endif

struct Stack {

    #if !defined(NOCANS) && !defined(NOOOOOOOOOOOOOO)
        long int CanLeft;
    #endif

    void *src;
    size_t elsize;
    size_t pointer;
    size_t size;

    void (*FprintF)(FILE* flog, void* elem);
    char toxic;

    #ifndef NOOOOOOOOOOOOOO
        struct DebugInfo info;

        #ifndef NOCANS
            long int CanRight;
        #endif

    #endif
};

const float resizeval = 2;

enum StackError{
    ST_OK             = 0,
    EMPTY_STACK       = 1,
    EMPTY_SOURCE      = 2,
    STACK_OVERFLOW    = 3,
    LAZHA             = 4,
    POPALSYA_NA_HASHE = 5,
    LAZHA_V_STRUCTE   = 6,
};

const int DefaultSize = 8;

StackError StackCtor   (Stack *src, size_t length, size_t elsize,
                        char toxicvalue, void (*FprintFunc)(FILE* flog, void* elem));
StackError StackPush   (Stack *src, void *elem);
StackError StackPop    (Stack *src, void *elem);
StackError StackDump   (Stack *src, const char *file, const int line, const char *errname);
StackError StackCheck  (Stack *src );
StackError Resize      (Stack *src, size_t size, size_t lastsize);
StackError StackDtor   (Stack *src);

const char *Definition (StackError code );
void SetLog(const char* name);

#ifndef NOOOOOOOOOOOOOO
    #define STACK_ASSERT(st) \
        if(StackError c = StackCheck (&st)) \
        { \
            ChangeColourTo(Red);\
            fprintf(stderr, "%s\n",Definition(c));\
            fprintf(stderr ,"%s:%d\n" ,__FILE__, __LINE__);\
            ChangeColourTo(DefaultColor);\
            StackDump (&st, __FILE__, __LINE__, Definition(c));\
        }

    #define DUMP(st) StackDump (&st, __FILE__, __LINE__, "SimpleDump");

    #ifndef NOHASH
        #define DEBUG src->info = {__FILE__, Hash(src->src, (char *) src->src+src->size), var};
    #endif

#else
    #define STACK_ASSERT(st) ;
    #define DUMP(st) ;
    #define DEBUG ;
#endif

#endif //STACK_H_INCLUDED
