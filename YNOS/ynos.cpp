#include "ynos.h"

static int const numberofkeys = 40;
char keytitle[numberofkeys] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
bool keystate[numberofkeys];

static int const maxnumberofwindows = 16;

bool getInput(char c) { return (GetAsyncKeyState(c) & 0x8000) ? 1 : 0; }

void getInputs() {
    for (int i = 0; i < numberofkeys; i++) {
        keystate[i] = getInput(keytitle[i]);
    }
}

int main() {
    srand(time(0));
    SetConsoleTitle("WhyNotOS...?");
    Window wins[maxnumberofwindows];
    for (int i = 0; i < maxnumberofwindows; i++) {
        wins[i] = Window(rand() % 16 + 2, rand() % 16 + 2, rand() % 4 + 46, rand() % 4 + 14);
    }
    while (true) {
        getInputs();
        for (int i = 0; i < maxnumberofwindows; i++) { wins[i].put(); }
        screen.print();
        Sleep(1000);
        clearScreen();
    }
    return 0;
}