#include "Normal.h"

void initBoard(Normal** &board, int increase = 0){
    board = new Normal * [BOARDHEIGTH];
    for(int i = 0; i < BOARDHEIGTH; i++){
        board[i] = new Normal [BOARDWIDTH];
        for (int j = 0; j < BOARDWIDTH; j++){
            board[i][j].x = j + 1;
            board[i][j].y = i + 1;
        }
    }

    //set random value
    if( increase > 5) increase = 5; // cố định độ khó tối đa
    int needSet = 20;
    while(needSet){
        char randValue = rand() % (10 + increase*2) + 65;
        int couple = 2;
        while (couple){
            int randIndex = rand()%40;
            if(board[randIndex % BOARDHEIGTH][randIndex % BOARDWIDTH].c == ' '){
                board[randIndex % BOARDHEIGTH][randIndex % BOARDWIDTH].c = randValue;
                couple--;
            }
        }
        needSet--;
    }
}

void deleteBoard(Normal** board) {
    for (int i = 0; i < BOARDHEIGTH; i++) {
        for (int j = 0; j < BOARDWIDTH; j++) {
            if (board[i][j].isValid) {
                board[i][j].deletebox();
                displayBackground(board[i][j].x,board[i][j].y);    
                Sleep(200);
            }
        }
    }

    for (int i = 0; i < BOARDHEIGTH; i++) {
        delete[]board[i];
    }
    delete[]board;
}

void renderBoard(Normal** board, int needhelp = 0){
    for(int i = 0; i < BOARDHEIGTH; i++)
        for(int j = 0; j  < BOARDWIDTH; j++)
            board[i][j].drawbox();
}

//ref: https://github.com/PhVanMin/Pikachuuu/blob/master/NormalMode.cpp#L56  56->323
void move(Normal** board, position& pos, int& status, Player& p, position selectedPos[], int& couple) {
    int temp, key;
    temp = _getch();
    if (temp && temp != 224) { // neu ko phai la dau mui ten
        if (temp == ESC_KEY) { // neu la ESC
            status = 2;
        }
        else if (temp == ENTER_KEY) { // neu la Enter
            if (pos.x == selectedPos[0].x && pos.y == selectedPos[0].y) {
                board[selectedPos[0].y][selectedPos[0].x].drawbox();
                Sleep(500);

                board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;
                couple = 2;
                selectedPos[0] = { -1, -1 };
                p.life--;
                gotoxy(70, 0);
                cout << "Life: " << p.life;
            } // kiem tra lap lai
            else {
                selectedPos[2 - couple].x = pos.x;
                selectedPos[2 - couple].y = pos.y;
                board[pos.y][pos.x].isSelected = 1;
                couple--;

                if (couple == 0) { // neu da chon 1 cap
                    if (board[selectedPos[0].y][selectedPos[0].x].c == board[selectedPos[1].y][selectedPos[1].x].c) {  // neu cap nay hop nhau
                        if (allcheck(board, selectedPos[0].y, selectedPos[0].x, selectedPos[1].y, selectedPos[1].x)) {
                            p.point += 20;
                            gotoxy(40, 0);
                            cout << "\e[0mPoint: " << p.point;

                            board[selectedPos[0].y][selectedPos[0].x].drawbox();
                            board[selectedPos[1].y][selectedPos[1].x].drawbox();
                            Sleep(500);

                            board[selectedPos[0].y][selectedPos[0].x].isValid = 0;
                            board[selectedPos[0].y][selectedPos[0].x].deletebox();
                            displayBackground(selectedPos[0].x+1, selectedPos[0].y+1);

                            board[selectedPos[1].y][selectedPos[1].x].isValid = 0;
                            board[selectedPos[1].y][selectedPos[1].x].deletebox();
                            displayBackground(selectedPos[1].x+1, selectedPos[1].y+1);


                            // kiem tra su dung help
                            bool isSuggestions = 0;
                            for(int i = 0; i < BOARDHEIGTH && !isSuggestions; i++){
                                for (int j = 0; j < BOARDWIDTH && !isSuggestions; j++){
                                    if (board[i][j].suggestions && board[i][j].isValid) isSuggestions = 1;
                                }
                            }

                            if (!isSuggestions){
                                p.help--;
                                gotoxy(100,0);
                                cout << "Help: " << p.help;
                            }

                        }
                        else {
                            board[selectedPos[0].y][selectedPos[0].x].drawbox();
                            board[selectedPos[1].y][selectedPos[1].x].drawbox();
                            Sleep(500);

                            p.life--;
                            gotoxy(70, 0);
                            setColor(15,0);
                            cout << "Life: " << p.life;
                        }
                    }
                    else {
                        board[selectedPos[0].y][selectedPos[0].x].drawbox();
                        board[selectedPos[1].y][selectedPos[1].x].drawbox();
                        Sleep(500);

                        p.life--;
                        gotoxy(70, 0);
                        cout << "Life: " << p.life;
                    }
                    // tra ve noi san xuat
                    board[selectedPos[0].y][selectedPos[0].x].isSelected = 0;
                    board[selectedPos[1].y][selectedPos[1].x].isSelected = 0;
                    couple = 2;
                    selectedPos[0] = { -1, -1 };
                    selectedPos[1] = { -1, -1 };

                    for (int i = pos.y; i < BOARDHEIGTH; i++) {
                        for (int j = pos.x; j < BOARDWIDTH; j++) {
                            if (board[i][j].isValid) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }

                    for (int i = 0; i <= pos.y; i++) { // chuyen den cell o tren
                        for (int j = 0; j <= pos.x; j++) {
                            if (board[i][j].isValid) {
                                pos.x = j;
                                pos.y = i;
                                return;
                            }
                        }
                    }
                }
            }
            
        }else if(temp == 104 && p.help > 0){ //neu la H key
            checkValidPairs(board, 1);// dua ra goi y 
        }
    }
    else //neu la dau mui ten
    {
        if ((pos.y != selectedPos[0].y || pos.x != selectedPos[0].x) && (pos.y != selectedPos[1].y || pos.x != selectedPos[1].x)) // ktra xem o nay co dang duoc chon hay khong
            board[pos.y][pos.x].isSelected = 0;
        switch (key = _getch())
        {
        case KEY_UP:
            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = pos.y - 1; j >= 0; j--) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y - 1; j >= 0; j--) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = BOARDHEIGTH - 1; j > pos.y; j--) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i >= 0; i--) {
                for (int j = BOARDHEIGTH - 1; j > pos.y; j--) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            break;
        case KEY_DOWN:
            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = pos.y + 1; j < BOARDHEIGTH; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = pos.y + 1; j < BOARDHEIGTH; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x; i < BOARDWIDTH; i++) {
                for (int j = 0; j < pos.y; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }

            for (int i = pos.x - 1; i >= 0; i--) {
                for (int j = 0; j < pos.y; j++) {
                    if (board[j][i].isValid) {
                        pos.x = i;
                        pos.y = j;
                        return;
                    }
                }
            }
            break;
        case KEY_LEFT:
            for (int i = pos.y; i >= 0; i--) {
                for (int j = pos.x - 1; j >= 0; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGTH; i++) {
                for (int j = pos.x - 1; j >= 0; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGTH; i++) {
                for (int j = BOARDWIDTH - 1; j > pos.x; j--) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }
            break;
        case KEY_RIGHT:
            for (int i = pos.y; i >= 0; i--) {
                for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGTH; i++) {
                for (int j = pos.x + 1; j < BOARDWIDTH; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y; i >= 0; i--) {
                for (int j = 0; j < pos.x; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }

            for (int i = pos.y + 1; i < BOARDHEIGTH; i++) {
                for (int j = 0; j < pos.x; j++) {
                    if (board[i][j].isValid) {
                        pos.x = j;
                        pos.y = i;
                        return;
                    }
                }
            }
        default:
            break;
        }
    }
}

void normalMode(Player &p, int increase = 0){
    srand(time(0));

    Normal** board;
    initBoard(board, increase);

    gotoxy(10, 0);
    cout << "Name: " << p.name;
    gotoxy(40, 0);
    cout << "Point: " << p.point;
    gotoxy(70, 0);
    cout << "Life: " << p.life;
    gotoxy(100, 0);
    cout << "Help: " << p.help;

    setColor(10,0);
    gotoxy(100, 12);
    cout << "Press arrow key to move";
    gotoxy(100, 13);
    cout << "Press Enter to delete";
    gotoxy(100, 14);
    cout << "Press ESC to quit";
    gotoxy(100, 15);
    cout << "Press H to get move suggestions";
    setColor(15,0);

    position selectedPos[] = { {-1, -1}, {-1, -1} };
    int couple = 2;
    position curPosition{ 0, 0 };
    int status = 0; //0. dang choi game
                    //1. het game
                    //2. nguoi choi chon thoat

    while (!status && p.life) {
        board[curPosition.y][curPosition.x].isSelected = 1;

        renderBoard(board);

        move(board, curPosition, status, p, selectedPos, couple);

        if ((!checkValidPairs(board, 0))) status = 1;
    }

    renderBoard(board);
    deleteBoard(board);
    Sleep(500);
    system("cls");

    if (p.life && status == 1) {
        displayStatus(1);
        gotoxy(50, 17);
        char c;
        cout << "Do you want to continue next game? (Y/N): ";
        cin >> c;
        cin.ignore();
        system("cls");
        if (c == 'y' || c == 'Y') normalMode(p, increase + 1); // tăng 1 độ khó nếu tiếp tục chơi
        else writeLeaderBoard(p);
    }
    else if (p.life == 0) {
        displayStatus(0);
        writeLeaderBoard(p);
        Sleep(2000);
    }
    system("cls");
}


// // test
// int main(){
//     Normal** board;
//     system("cls");
//     initBoard(board);
//     renderBoard(board);
//     getch();
//     deleteBoard(board);
//     gotoxy(0,0); cout << "Done";
//     getch();

//     return 0;
// }