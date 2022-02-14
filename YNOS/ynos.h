#pragma once
#ifndef YNOS_H_BY_YANGSY56302_
#define YNOS_H_BY_YANGSY56302_

#include <iostream>
#include <string>
#include <random>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <algorithm>
#include <iterator>
#include <list>
#include <conio.h>
#include <windows.h>

using std::cout;
using std::endl;
using std::flush;
using std::string;
using std::list;

using Color = WORD;

HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);

bool gotoPos(short x, short y) {
    COORD pos = { x, y };
    SetConsoleCursorPosition(hout, pos);
    return true;
}

void setColor(Color c) { SetConsoleTextAttribute(hout, c); }

#define FOREGROUND_GREY FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE
#define FOREGROUND_WHITE FOREGROUND_GREY | FOREGROUND_INTENSITY
#define BACKGROUND_GREY BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE
#define BACKGROUND_WHITE BACKGROUND_GREY | BACKGROUND_INTENSITY

class Screen {
private:
    static int const screenx = 120;
    static int const screeny = 40;
    char pixel[screenx][screeny];
    Color color[screenx][screeny];
    char gui[4] = { '[', ']', '=', '|' };
public:
    Screen() {
        for (int i = 0; i < screenx; i++) {
            for (int j = 0; j < screeny; j++) {
                pixel[i][j] = ' ';
                color[i][j] = FOREGROUND_WHITE;
            }
        }
    }
    ~Screen() {}
    void put(int x, int y, char c, Color t = 0) {
        if (x >= 0 && x < screenx && y >= 0 && y < screeny) {
            pixel[x][y] = c;
            if (t != 0) { color[x][y] = t; }
        }
    }
    void clear() {
        for (int i = 0; i < screenx; i++) {
            for (int j = 0; j < screeny; j++) {
                pixel[i][j] = ' ';
                color[i][j] = FOREGROUND_WHITE;
            }
        }
    }
    void print() {
        setColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
        cout.put(gui[0]).put(gui[1]);
        for (int i = 0; i < screenx; i++) { cout.put(gui[2]); }
        cout.put(gui[0]).put(gui[1]);
        cout << endl;
        for (int j = 0; j < screeny; j++) {
            cout.put(gui[3]).put(gui[3]);
            for (int i = 0; i < screenx; i++) {
                setColor(color[i][j]);
                cout.put(pixel[i][j]);
            }
            setColor(FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
            cout.put(gui[3]).put(gui[3]);
            cout << endl;
        }
        cout.put(gui[0]).put(gui[1]);
        for (int i = 0; i < screenx; i++) { cout.put(gui[2]); }
        cout.put(gui[0]).put(gui[1]);
    }
};

Screen screen;

void clearScreen() { screen.clear(); system("cls"); }

void tick() { Sleep(1000); }

class Window {
private:
    short xstart, ystart, xend, yend;
    string title, icon;
    char gui[4] = { '[', ']', '=', '|' };
public:
    Window() {
        xstart = 4; ystart = 4;
        xend = 52; yend = 20;
        title = "No Title";
        icon = "..";
    }
    Window(short x, short y, short x2 = 48, short y2 = 16, string t = "No Title", string i = "..") {
        xstart = x; ystart = y;
        xend = x + x2; yend = y + y2;
        title = t; icon = i;
    }
    ~Window() {}
    void put() {
        // 点
        screen.put(xstart - 2, ystart - 3, gui[0], FOREGROUND_WHITE);
        screen.put(xstart - 1, ystart - 3, gui[1], FOREGROUND_WHITE);
        screen.put(xend, ystart - 3, gui[0], FOREGROUND_WHITE);
        screen.put(xend + 1, ystart - 3, gui[1], FOREGROUND_WHITE);
        screen.put(xstart - 2, ystart - 1, gui[0], FOREGROUND_WHITE);
        screen.put(xstart - 1, ystart - 1, gui[1], FOREGROUND_WHITE);
        screen.put(xend, ystart - 1, gui[0], FOREGROUND_WHITE);
        screen.put(xend + 1, ystart - 1, gui[1], FOREGROUND_WHITE);
        screen.put(xstart - 2, yend, gui[0], FOREGROUND_WHITE);
        screen.put(xstart - 1, yend, gui[1], FOREGROUND_WHITE);
        screen.put(xend, yend, gui[0], FOREGROUND_WHITE);
        screen.put(xend + 1, yend, gui[1], FOREGROUND_WHITE);
        // 边框
        for (int i = xstart; i < xend; i++) {
            screen.put(i, ystart - 3, gui[2], FOREGROUND_WHITE);
            screen.put(i, ystart - 1, gui[2], FOREGROUND_WHITE);
            screen.put(i, yend, gui[2], FOREGROUND_WHITE);
        }
        screen.put(xstart - 2, ystart - 2, gui[3], FOREGROUND_WHITE);
        screen.put(xstart - 1, ystart - 2, gui[3], FOREGROUND_WHITE);
        screen.put(xend, ystart - 2, gui[3], FOREGROUND_WHITE);
        screen.put(xend + 1, ystart - 2, gui[3], FOREGROUND_WHITE);
        for (int j = ystart; j < yend; j++, FOREGROUND_WHITE) {
            screen.put(xstart - 2, j, gui[3], FOREGROUND_WHITE);
            screen.put(xstart - 1, j, gui[3], FOREGROUND_WHITE);
            screen.put(xend, j, gui[3], FOREGROUND_WHITE);
            screen.put(xend + 1, j, gui[3], FOREGROUND_WHITE);
        }
        // 内部填充
        for (int i = xstart; i < xend; i++) {
            screen.put(i, ystart - 2, ' ', FOREGROUND_WHITE);
            for (int j = ystart; j < yend; j++) {
                screen.put(i, j, ' ', FOREGROUND_WHITE);
            }
        }
        // 标题
        screen.put(xstart, ystart - 2, icon[0], FOREGROUND_GREY);
        screen.put(xstart + 1, ystart - 2, icon[1], FOREGROUND_GREY);
        if (title.size() <= xend - xstart - 8) {
            for (int i = 0; i < title.size(); i++) {
                screen.put(xstart + 2 + i, ystart - 2, title[i], FOREGROUND_GREY);
            }
        }
        else {
            for (int i = 0; i < xend - xstart - 8; i++) {
                screen.put(xstart + 2 + i, ystart - 2, title[i], FOREGROUND_GREY);
            }
        }
        screen.put(xend - 6, ystart - 2, '_', FOREGROUND_GREY);
        screen.put(xend - 5, ystart - 2, '_', FOREGROUND_GREY);
        screen.put(xend - 4, ystart - 2, gui[0], FOREGROUND_GREY);
        screen.put(xend - 3, ystart - 2, gui[1], FOREGROUND_GREY);
        screen.put(xend - 2, ystart - 2, '>', FOREGROUND_RED | FOREGROUND_INTENSITY);
        screen.put(xend - 1, ystart - 2, '<', FOREGROUND_RED | FOREGROUND_INTENSITY);
    }
};

#endif