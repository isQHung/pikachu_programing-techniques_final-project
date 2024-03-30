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
    char name[10];
    int point;
    int life;
};

void getPlayerInfo(Player&);

// Normal mode
struct Normal{
    int x,y;
    int isValid = 1, isSelected = 0;
    char c = ' ';

    void drawbox();
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
#endif