#include "Console.h"

// ref: https://technolads.com/gotoxy-function-in-c/ :: 15->24
void gotoxy(int a, int b){ //Custom gotoxy() function
    COORD coordinates; //Data type of co-ordinates
    coordinates.X = a; //Assign value to X- Co-ordinate
    coordinates.Y = b; //Assign value to Y Co-ordinate
    SetConsoleCursorPosition(hConsole, coordinates);
}

// ref: https://github.com/PhVanMin/Pikachuuu/blob/master/ConsoleSettings.cpp 11->17
void setCursor(bool visible) {
    CONSOLE_CURSOR_INFO lpCursor;
    lpCursor.bVisible = visible;
    lpCursor.dwSize = 20;
    SetConsoleCursorInfo(hConsole, &lpCursor);
}

//ref: https://cplusplus.com/forum/beginner/91349/ 35->39
// void setColor(int text, int background)
void setColor(int text = 15, int background = 0){
    // default: white text on black background
    // black,          //  0 text color - multiply by 16, for background colors
	// dark_blue,      //  1
	// dark_green,     //  2
	// dark_cyan,      //  3
	// dark_red,       //  4
	// dark_magenta,   //  5
	// dark_yellow,    //  6
	// light_gray,     //  7
	// dark_gray,      //  8
	// light_blue,     //  9
	// light_green,    // 10
	// light_cyan,     // 11
	// light_red,      // 12
	// light_magenta,  // 13
	// light_yellow,   // 14
	// white           // 15
    SetConsoleTextAttribute(hConsole, text + background*16);
}

//ref: https://github.com/PhVanMin/Pikachuuu/blob/master/ConsoleSettings.cpp 19->24
void resizeWindow(int x, int y) {
    RECT r;
    GetWindowRect(wConsole, &r);
    MoveWindow(wConsole, r.left, r.top, x, y, TRUE);
}

//ref: https://github.com/PhVanMin/Pikachuuu/blob/master/ConsoleSettings.cpp 26->37
void hideScrollBar() {
    CONSOLE_SCREEN_BUFFER_INFO screenBufferInfo;
    GetConsoleScreenBufferInfo(hConsole, &screenBufferInfo);

    COORD new_screen_buffer_size;

    new_screen_buffer_size.X = screenBufferInfo.srWindow.Right - screenBufferInfo.srWindow.Left + 1;
    new_screen_buffer_size.Y = screenBufferInfo.srWindow.Bottom - screenBufferInfo.srWindow.Top + 1;

    SetConsoleScreenBufferSize(hConsole, new_screen_buffer_size);
}

//ref: https://github.com/PhVanMin/Pikachuuu/blob/master/ConsoleSettings.cpp 39->43
void initWindow(int width, int length) {
    resizeWindow(width, length);
    hideScrollBar();
    setCursor(0);
    system("cls");
}