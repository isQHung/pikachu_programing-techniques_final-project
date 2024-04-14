#pragma once
#include "Diffmodecheck.h"
#include<conio.h>
#include<time.h>

void push(CELL_2*&, CELL_2*);
void initList(CELL_2**);
void deleteList(CELL_2**);
void renderList(CELL_2**);
void move(CELL_2**, position&, int&, Player&, position[], int&);
void difficultMode(Player&);