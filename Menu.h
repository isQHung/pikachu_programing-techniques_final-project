#pragma once
#ifndef _MENU_H_
#define _MENU_H_

#include <iostream>
#include <conio.h>
#include <fstream>
// #include "Console.h"
#include "Struct.h"

// #include "Menu.cpp"

using namespace std;

void drawSelectedMenu(int, int, int);
int Menu();
void readLeaderBoard();
void writeLeaderBoard(Player);

#endif