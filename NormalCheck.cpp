#include "NormalCheck.h"

bool nextcheck(Normal** board, int p1, int p2, int q1, int q2, bool draw) {
    if ((p1 == q1 + 1 || p1 == q1 - 1) && (p2 == q2)) { //doc
        if (board[p1][p2].c == board[q1][q2].c){
            if(draw){
                int y = max(p1,q1) + 1;
                setColor(10,0);
                gotoxy((p2+1)*10 + 5, (y)*4 - 1);
                cout << "^";
                gotoxy((p2+1)*10 + 5, (y)*4);
                cout << "|";
                gotoxy((p2+1)*10 + 5, (y)*4 + 1);
                cout << "v";
                setColor(15,0);
            }
            return true;
        }
    }
    if ((p2 == q2 + 1 || p2 == q2 - 1) && (p1 == q1)) {// ngang
        if (board[p1][p2].c == board[q1][q2].c){
            if (draw){
                //drawline
                int x = min(p2,q2) + 1;
                gotoxy(x*10 + 9,(p1+1)*4 + 2);
                setColor(10,0);
                cout << "<->";
                setColor(15,0);
            }
            return true;
        } 
    }
    return false;
}

bool linecheck(Normal** board, int p1, int p2, int q1, int q2) {
    if (p1 == q1) {
        int y, x, dem = 0;
        if (p2 > q2) {
            x = q2;
            y = p2;
        }
        else {
            x = p2;
            y = q2;
        }
        for (int i = x; i <= y; i++) {
            if (board[p1][i].isValid) {
                dem++;
                if (dem == 2) return false;
            }
        }
        if ((dem == 1) && ((!board[p1][p2].isValid && board[q1][q2].isValid) || (board[p1][p2].isValid && !board[q1][q2].isValid))) {//sai
            return true;
        }
        else if (dem == 0) {
            return true;
        }
        return false;
    }
    if (p2 == q2) {
        int x, y, dem = 0;
        if (p1 > q1) {
            x = q1;
            y = p1;
        }
        else {
            x = p1;
            y = q1;
        }
        for (int i = x; i <= y; i++) {
            if (board[i][p2].isValid) {
                dem++;
                if (dem == 2) return false;
            }
        }
        if ((dem == 1) && ((!board[p1][p2].isValid && board[q1][q2].isValid) || (board[p1][p2].isValid && !board[q1][q2].isValid))) {//sai
            return true;
        }
        else if (dem == 0) {
            return true;
        }
        return false;
    }
    return false;
}

bool Icheck_1(Normal** board, int p1, int p2, int q1, int q2, bool draw) {
    if (p1 == q1) {
        int y, x, dem = 0;
        if (p2 > q2) {
            x = q2;
            y = p2;
        }
        else {
            x = p2;
            y = q2;
        }
        for (int i = x + 1; i < y; i++) {
            if (board[p1][i].isValid) {
                return false;
            }
        }
        
        //drawline
        if (draw){
            setColor(10,0);
            gotoxy((x+1)*10 + 11,(p1+1)*4 + 2);
            cout << "<";
            for(int i = 0; i < (y-x-1)*10 - 3;i++){
                gotoxy((x+1)*10 + 12 + i, (p1+1)*4 + 2);
                cout << "-";
            }
            gotoxy((y+1)*10-1,(p1+1)*4 + 2);
            cout << ">";
            setColor(15,0);
        }

        return true;
    }
    if (p2 == q2) {
        int x, y, dem = 0;
        if (p1 > q1) {
            x = q1;
            y = p1;
        }
        else {
            x = p1;
            y = q1;
        }
        for (int i = x + 1; i < y; i++) {
            if (board[i][p2].isValid) {
                return false;
            }
        }
        // drawline
        if(draw){
            setColor(10,0);
            gotoxy((q2+1)*10 + 5,(x+1)*4 + 5);
            cout << "^";
            for(int i = 0; i < (y-x-1)*4 - 3;i++){
                gotoxy((q2+1)*10 + 5, (x+1)*4 + 6 +i);
                cout << "|";
            }
            gotoxy((q2+1)*10 + 5,(y+1)*4 - 1);
            cout << "v";
            setColor(15,0);
        }

        return true;
    }
    return false;
}

bool Lcheck(Normal** board, int p1, int p2, int q1, int q2, bool draw) {
    if (p1 == q1 || p2 == q2) {
        return false;
    }
    bool c1, c2;
    if (!board[p1][q2].isValid) {
        c1 = linecheck(board, p1, p2, p1, q2);
        c2 = linecheck(board, q1, q2, p1, q2);
        if (c1 && c2) {
            //drawline
            if(draw){
                setColor(10,0);
                if(p2 < q2){
                    int y = (p1+1)*4+2;
                    gotoxy((p2+1)*10 + 11,y);
                    cout << "<";
                    for(int i = 0; i < (q2-p2-1)*10+4;i++){
                        gotoxy((p2+1)*10 + 12 + i,y);
                        cout << "-";
                    }
                }else{
                    int y = (p1+1)*4+2;
                    gotoxy((p2+1)*10 - 1, y);
                    cout << ">";
                    for(int i = 0; i < (p2-q2-1)*10+4;i++){
                        gotoxy((p2+1)*10 - 2 - i,y);
                        cout << "-";
                    }
                    
                }

                if (q1 < p1){
                    int x = (q2 + 1)*10 + 5;
                    gotoxy(x, (q1+1)*4 + 5);
                    cout << "^";
                    for(int i = 0; i < (p1 - q1 - 1)*4; i++){
                        gotoxy(x,(q1+1)*4 + 6 + i);
                        cout << "|";
                    }
                }else{
                    int x = (q2 + 1)*10 + 5;
                    gotoxy(x, (q1+1)*4 - 1);
                    cout << "v";
                    for(int i = 0; i < (q1 - p1 - 1)*4; i++){
                        gotoxy(x,(q1+1)*4 - 2 - i);
                        cout << "|";
                    }
                setColor(15,0);
                }
            }
            return true;
        }
    }
    if (!board[q1][p2].isValid) {
        c1 = linecheck(board, p1, p2, q1, p2);
        c2 = linecheck(board, q1, q2, q1, p2);
        if (c1 && c2) {
            //drawline
            if(draw){
                setColor(10,0);
                if(q2 < p2){
                    int y = (q1+1)*4+2;
                    gotoxy((q2+1)*10 + 11,y);
                    cout << "<";
                    for(int i = 0; i < (p2-q2-1)*10+4;i++){
                        gotoxy((q2+1)*10 + 12 + i,y);
                        cout << "-";
                    }
                }else{
                    int y = (q1+1)*4+2;
                    gotoxy((q2+1)*10 - 1, y);
                    cout << ">";
                    for(int i = 0; i < (q2-p2-1)*10+4;i++){
                        gotoxy((q2+1)*10 - 2 - i,y);
                        cout << "-";
                    }
                    
                }

                if (p1 < q1){
                    int x = (p2 + 1)*10 + 5;
                    gotoxy(x, (p1+1)*4 + 5);
                    cout << "^";
                    for(int i = 0; i < (q1 - p1 - 1)*4; i++){
                        gotoxy(x,(p1+1)*4 + 6 + i);
                        cout << "|";
                    }
                }else{
                    int x = (p2 + 1)*10 + 5;
                    gotoxy(x, (p1+1)*4 - 1);
                    cout << "v";
                    for(int i = 0; i < (p1 - q1 - 1)*4; i++){
                        gotoxy(x,(p1+1)*4 - 2 - i);
                        cout << "|";
                    }
                setColor(15,0);
                }
            }
            return true;
        }
    }
    return false;
}

bool Zcheck(Normal** board, int p1, int p2, int q1, int q2, bool draw) {
    if (p1 == q1 || p2 == q2) {
        return false;
    }
    bool c1, c2, c3;
    int x1, x2, y1, y2;
    // z ngang
    if (q2 < p2) {
        x1 = q2;y1 = q1;
        x2 = p2;y2 = p1;
    }
    else {
        x1 = p2; y1 = p1;
        x2 = q2; y2 = q1;
    }
    for (int i = x1 + 1; i < x2; i++) {
        c3 = linecheck(board, p1, i, q1, i);
        if (c3) {
            c1 = linecheck(board, p1, p2, p1, i);
            c2 = linecheck(board, q1, q2, q1, i);
            if (c1 && c2){
                //drawline
                if(draw){
                    setColor(10,0);
                    //vertical line
                    int mi_y = min(y1,y2);
                    for(int j = 0; j < abs(y2-y1)*4 + 1;j++){
                        gotoxy((i+1)*10 + 5, (mi_y+1)*4 + 2 + j);
                        cout <<"|";
                    }

                    //horizontal line
                    gotoxy((x1+1)*10 + 11, (y1+1)*4+2);
                    cout << "<";
                    for(int j = 0; j < (i - x1 - 1)*10 + 4;j++){
                        gotoxy((x1+1)*10 + 12 + j, (y1+1)*4+2);
                        cout << "-";
                    }

                    for(int j = 0; j < (x2 - i - 1)*10 + 4;j++){
                        gotoxy((x2+1)*10 -2 - j, (y2+1)*4+2);
                        cout << "-";
                    }
                    gotoxy((x2+1)*10 - 1, (y2+1)*4+2);
                    cout << ">";
                    setColor(15,0);
                }

                return true;
            }
        }
    }
    // z doc
    if (q1 < p1) {
        y1 = q1; x1 = q2;
        y2 = p1; x2 = p2;
    }
    else {
        y1 = p1; x1 = p2;
        y2 = q1; x2 = q2;
    }
    for (int i = y1 + 1; i < y2; i++) {
        c3 = linecheck(board, i, p2, i, q2);
        if (c3) {
            c1 = linecheck(board, p1, p2, i, p2);
            c2 = linecheck(board, q1, q2, i, q2);
            if (c1 && c2){
                //drawline
                if (draw){
                    setColor(10,0);
                    //vertical line
                    gotoxy((x1+1)*10 + 5, (y1+1)*4 + 5);
                    cout << "^";
                    for (int j = 0; j < (i - y1 - 1)*4 + 1; j++){
                        gotoxy((x1+1)*10 + 5, (y1+1)*4 + 6 + j);
                        cout << "|";
                    }

                    for (int j = 0; j < (y2 - i - 1)*4 + 1; j++){
                        gotoxy((x2+1)*10 + 5, (y2+1)*4 - 2 - j);
                        cout << "|";
                    }
                    gotoxy((x2+1)*10 + 5, (y2+1)*4 - 1);
                    cout << "v";

                    //horizontal line
                    int mi_x = min(x1,x2);
                    for(int j = 0; j < abs(x1-x2)*10 + 1; j++){
                        gotoxy((mi_x+1)*10 + 5 + j, (i+1)*4 + 2);
                        cout << "-";
                    }

                    setColor(15,0);
                }
                return true;
            }
        }
    }
    return false;
}

bool Ucheck(Normal** board, int p1, int p2, int q1, int q2, bool draw) {
    if (p1 == q1){
        int mi_x = min(p2,q2);
        if (p1 == 0){
        // cung nam o bien tren
            if (draw){
                //drawline
                setColor(10,0);
                gotoxy((p2+1)*10 + 5, (p1+1)*4 - 2);
                cout  <<  "|";
                gotoxy((p2+1)*10 + 5, (p1+1)*4 - 1);
                cout  <<  "v";
                gotoxy((q2+1)*10 + 5, (q1+1)*4 - 2);
                cout  <<  "|";
                gotoxy((q2+1)*10 + 5, (q1+1)*4 - 1);
                cout  <<  "v";
                for(int i = 0; i < abs(p2 - q2)*10 + 1; i++){
                    gotoxy((mi_x + 1)*10 + 5 + i,(p1+1)*4 - 3);
                    cout << "-";
                }
                setColor(15,0);
            }
            return true;
        }else if (p1 == BOARDHEIGTH - 1){
        // cung nam o bien duoi
            if(draw){
                setColor(10,0);
                gotoxy((p2+1)*10 + 5, (p1+1)*4 + 6);
                cout  <<  "|";
                gotoxy((p2+1)*10 + 5, (p1+1)*4 + 5);
                cout  <<  "^";
                gotoxy((q2+1)*10 + 5, (q1+1)*4 + 6);
                cout  <<  "|";
                gotoxy((q2+1)*10 + 5, (q1+1)*4 + 5);
                cout  <<  "^";
                for(int i = 0; i < abs(p2 - q2)*10 + 1; i++){
                    gotoxy((mi_x + 1)*10 + 5 + i,(p1+1)*4 + 7);
                    cout << "-";
            }
            setColor(15,0);
            }
            return true;
        }
        
    }else if (p2 == q2){
        int mi_y = min(p1,q1);
        if(p2 == 0){
        // cung nam o bien trai
            if(draw){
                setColor(10,0);
                gotoxy((p2+1)*10 - 3, (p1+1)*4 + 2);
                cout  <<  "--";
                gotoxy((p2+1)*10 - 1, (p1+1)*4 + 2);
                cout  <<  ">";
                gotoxy((q2+1)*10 - 3, (q1+1)*4 + 2);
                cout  <<  "--";
                gotoxy((q2+1)*10 - 1, (q1+1)*4 + 2);
                cout  <<  ">";
                for(int i = 0; i < abs(p1 - q1)*4 - 1; i++){
                    gotoxy((p2 + 1)*10 - 3, (mi_y+1)*4 + 3 + i);
                    cout << "|";
                }
                setColor(15,0);
            }
            return true;
        }else if( q2 == BOARDWIDTH - 1){
        // cung nam o bien phai
            if(draw){
                setColor(10,0);
                gotoxy((p2+1)*10 + 12, (p1+1)*4 + 2);
                cout  <<  "--";
                gotoxy((p2+1)*10 + 11, (p1+1)*4 + 2);
                cout  <<  "<";
                gotoxy((q2+1)*10 + 12, (q1+1)*4 + 2);
                cout  <<  "--";
                gotoxy((q2+1)*10 + 11, (q1+1)*4 + 2);
                cout  <<  "<";
                for(int i = 0; i < abs(p1 - q1)*4 - 1; i++){
                    gotoxy((p2 + 1)*10 + 13, (mi_y+1)*4 + 3 + i);
                    cout << "|";
                }
                setColor(15,0);
            }
            return true;
        }
    }

    // if (((p1 == q1) && (p1 == 0 || p1 == BOARDHEIGTH - 1) || ((p2 == q2) && (p2 == 0 || q2 == BOARDWIDTH - 1)))) {
    //     return true;
    // }
    bool c1, c2, c3;
    int x1, x2, y1, y2;
    if (q2 < p2) {
        x1 = q2; y1 = q1;
        x2 = p2; y2 = p1;
    }
    else {
        x1 = p2; y1 = p1;
        x2 = q2; y2 = q1;
    }
    for (int i = 0; i < BOARDWIDTH; i++) {
        if (i <= x1 || i >= x2) {
            c3 = linecheck(board, p1, i, q1, i);
            if (c3) {
                c1 = linecheck(board, p1, p2, p1, i);
                c2 = linecheck(board, q1, q2, q1, i);
                if (c1 && c2) {
                    //drawline
                    if (draw){
                        setColor(10,0);
                        //vertical line
                        int mi_y = min(y1,y2);
                        for(int j = 0; j < abs(y2-y1)*4 + 1;j++){
                            gotoxy((i+1)*10 + 5, (mi_y+1)*4 + 2 + j);
                            cout <<"|";
                        }
                        
                        //horizontal line
                        if (i <= x1){
                            for (int j = 0; j < (x1 - i -1)*10 + 4; j++){
                                gotoxy((i+1)*10 + 5 + j, (y1+1)*4 + 2);
                                cout << "-";
                            }
                            for (int j = 0; j < (x2 - i -1)*10 + 4; j++){
                                gotoxy((i+1)*10 + 5 + j, (y2+1)*4 + 2);
                                cout << "-";
                            }
                            gotoxy((x1+1)*10 - 1, (y1+1)*4 + 2);
                            cout << ">";
                            gotoxy((x2+1)*10 - 1, (y2+1)*4 + 2);
                            cout << ">";
                        }
                        if (i >= x2){
                            for (int j = 0; j < (i - x1 -1)*10 + 4; j++){
                                gotoxy((i+1)*10 + 5 - j, (y1+1)*4 + 2);
                                cout << "-";
                            }
                            for (int j = 0; j < (i - x1 -1)*10 + 4; j++){
                                gotoxy((i+1)*10 + 5 - j, (y2+1)*4 + 2);
                                cout << "-";
                            }
                            gotoxy((x1+1)*10 + 11, (y1+1)*4 + 2);
                            cout << "<";
                            gotoxy((x2+1)*10 + 11, (y2+1)*4 + 2);
                            cout << "<";
                        }

                        setColor(15,0);
                    }
                    return true;
                }
            }
            else if (i == 0 || i == (BOARDWIDTH - 1)) {
                c1 = linecheck(board, p1, p2, p1, i);
                c2 = linecheck(board, q1, q2, q1, i);
                if ((c1 && c2) || (c1 && q2 == i) || (p2 == i && c2)) {
                    if(i == 0){
                        //here
                    }

                    return true;
                }
            }
        }
    }

    if (q1 < p1) {
        y1 = q1; x1 = q2;
        y2 = p1; x2 = p2;
    }
    else {
        y1 = p1;
        y2 = q1;
    }
    for (int i = 0; i < BOARDHEIGTH; i++) {
        if (i <= y1 || i >= y2) {
            c3 = linecheck(board, i, p2, i, q2);
            if (c3) {
                c1 = linecheck(board, p1, p2, i, p2);
                c2 = linecheck(board, q1, q2, i, q2);
                if (c1 && c2) {
                    return true;
                }
            }
            else if (i == 0 || i == (BOARDHEIGTH - 1)) {
                c1 = linecheck(board, p1, p2, i, p2);
                c2 = linecheck(board, q1, q2, i, q2);
                if ((c1 && c2) || (c1 && q1 == i) || (p1 == i && c2)) {
                    return true;
                }
            }
        }
    }
    return false;
}

bool allcheck(Normal** board, int p1, int p2, int q1, int q2, bool draw) {
    if (nextcheck(board, p1, p2, q1, q2)) {
        return true;
    }
    else if (Icheck_1(board, p1, p2, q1, q2, draw)) {
        return true;
    }
    else if (Lcheck(board, p1, p2, q1, q2, draw)) {
        return true;
    }
    else if (Zcheck(board, p1, p2, q1, q2, draw)) {
        return true;
    }
    else if (Ucheck(board, p1, p2, q1, q2, draw)) {
        return true;
    }
    return false;
}

bool checkValidPairs(Normal** board, bool needhelp) {
    char check = 'A';
    while (check >= 'A' && check <= 'Z') {
        int cnt = 0;
        int* pos = new int[BOARDHEIGTH * BOARDWIDTH];
        for (int i = 0; i < BOARDHEIGTH; i++) {
            for (int j = 0; j < BOARDWIDTH; j++) {
                if (board[i][j].c == check && board[i][j].isValid) {
                    pos[cnt++] = i;
                    pos[cnt++] = j;
                }
            }
        }
        for (int i = 0; i < cnt - 2; i += 2) {
            for (int j = i + 2; j < cnt; j += 2) {
                if (allcheck(board, pos[i], pos[i + 1], pos[j], pos[j + 1], 0)) {
                    if (needhelp){
                        board[pos[i]][pos[i + 1]].suggestions = 1;
                        board[pos[j]][pos[j + 1]].suggestions = 1;
                    }
                    delete[] pos;
                    return true;
                }
            }
        }
        check++;
        delete[] pos;
    }
    return false;
}