#pragma once
#ifndef _STRUCT_H_
#define _STRUCT_H_

#include <cstdlib>
#include "Console.h"

// #include "Struct.cpp"

#define BOARDHEIGTH 5
#define BOARDWIDTH 8

using namespace std;

struct Player{
    char name[50];
    int point;
    int life;
    int help;
};

void getPlayerInfo(Player&);

// Normal mode
struct Normal{
    int x,y;
    bool isValid = 1, isSelected = 0, suggestions = 0;
    char c = ' ';

    void drawbox(int);
    void deletebox();
};


//Hard mode
struct Hard{
    
};

struct position{
    int x,y;
};


//background
void displayBackground(int, int);
// void renderBackground();
void displayStatus(bool);
#endif