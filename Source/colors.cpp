#include "colors.h"

void ChangeColourTo (Colour colour){

    HANDLE hConsole = GetStdHandle (STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute (hConsole, colour);
}
