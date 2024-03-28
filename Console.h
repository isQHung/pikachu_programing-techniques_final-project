#pragma once
#ifndef _CONSOLE_H_
#define _CONSOLE_H_

#include<Windows.h>
#include <iostream>

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC_KEY 27
#define ENTER_KEY 13

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
HWND wConsole = GetConsoleWindow();

//Cursor setting
void gotoxy(int, int);
void setCursor(bool);
void setColor(int, int);

//Window setting
void resizeWindow(int, int );
void hideScrollBar();
void initWindow(int, int);

//Selecting
void drawSelectedMenu(int, int , int );

#endif