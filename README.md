# HellStack

Here I want to present you my Stack

## If you want to use it in your program 
 1. Download the Source and Include directories
 2. Delete the "main.cpp" file
 3. Include the "stack.h" in your program

## If you want to make some operationd with stack
 1. Download all
 2. Edit the "main.cpp" as you want, the stack itsef in the "stack.h"
 3. Open the terminal, use commands "make clean" to clean the objects, "make" to build the project and "make run" to run your program

### Code usage 
>type name: Stack
>
>For init:
```c
StackError StackCtor   (Stack *src, size_t length, size_t elsize, char toxicvalue, void (*FprintFunc)(FILE* flog, void* elem));
```
>>!!Don't forget FprintFunc, which is for logging your stack
>For usage:
```c
StackError StackPush   (Stack *src, void *elem);
StackError StackPop    (Stack *src, void *elem);
```
>To turn off the debug function use:
```c
>#define NOOOOOOOOOOOOOO
```
> or >to off only canaries:
```c
#define NOCANS
```
>or to off only hash
```c
#define NOHASH
```
> to check and dump in debug mode
```c
STACK_ASSERT(Stack *stack)
DUMP(Stack *stack)
```
> set the log file (which is ```stderr``` by default) by:
```c
void SetLog(const char* filename);
```

### If you found a bug, please, write an issue on GitHub or [me](https://t.me/Tea2Taler)
