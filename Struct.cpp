#include "Struct.h"

//background
char bg[21][82] ={
    {" _______ _________ _        _______  _                                           "},
    {"(  ____ \\\\__   __/( (    /|(  ___  )( \\                                          "},
    {"| (    \\/   ) (   |  \\  ( || (   ) || (                                          "},
    {"| (__       | |   |   \\ | || (___) || |                                          "},
    {"|  __)      | |   | (\\ \\) ||  ___  || |                                          "},
    {"| (         | |   | | \\   || (   ) || |                                          "},
    {"| )      ___) (___| )  \\  || )   ( || (____/\\                                    "},
    {"|/       \\_______/|/    )_)|/     \\|(_______/                                    "},                                                            
    {" _______  _______  _______ _________ _______  _______ _________                  "},
    {"(  ____ )(  ____ )(  ___  )\\__    _/(  ____ \\(  ____ \\\\__   __/                 "},
    {"| (    )|| (    )|| (   ) |   )  (  | (    \\/| (    \\/   ) (                     "},
    {"| (____)|| (____)|| |   | |   |  |  | (__    | |         | |                     "},
    {"|  _____)|     __)| |   | |   |  |  |  __)   | |         | |                     "},
    {"| (      | (\\ (   | |   | |   |  |  | (      | |         | |                     "},
    {"| )      | ) \\ \\__| (___) ||\\_)  )  | (____/\\| (____/\\   | |                     "},
    {"|/       |/   \\__/(_______)(____/   (_______/(_______/   )_(                     "},
    {"                                                                                 "},
    {"          .-. .-.  .--.  .----. .----..-.  .-.   .----.   .--..-.  .-.           "},
    {"          | {_} | / {} \\ | {}  }| {}  }\\ \\/ /    | {}  \\ / {} \\\\ \\/ /            "},
    {"          | { } |/  /\\  \\| .--' | .--'  }  {     |     //  /\\  \\}  {             "},
    {"          `-' `-'`-'  `-'`-'    `-'     `--'     `----' `-'  `-'`--'             "},
};

char box[5][12] = {
            {" --------- "},
            {"|         |"},
            {"|         |"},
            {"|         |"},
            {" --------- "}
};

void Normal::drawbox(int background = 0){
    if (!isValid){
        setColor(6, 0);
        int h = 4,w = 10, exw = 1, exh = 1;
        if (x == 1){
            w = 11;
            exw = 0;
        }
        if (x == BOARDWIDTH){
            w = 11;
        }

        if(y == 1){
            h = 5;
            exh = 0;
        }
        for (int i = 0; i < h; i++){
            for (int j = 0; j < w; j++){
                gotoxy((x) * 10 + j + exw, (y) * 4 + i + exh);
                cout << bg[(y-1)*4 + i + exh][(x-1)*10 + j + exw];
            }
        }
        setColor(15, 0);
       return;//chi ve box khi hop le 
    } 

    setColor(15, 0);
    for(int i = 0; i < 5; i++){
    gotoxy(x*10, y*4 + i);
    cout << box[i];
    }
    
    if (isSelected && !background) background = 15; // mau trang
    else if (suggestions && !background) background = 8; // mau xam

    // ve nen
    setColor(15,background);
    for (int i = 1; i < 4; i++) {
        gotoxy(x * 10 + 1, y * 4 + i);
        cout << "         ";
    }
    // them c
    gotoxy(x*10+5,y*4+2);
    setColor(c%14 + 1, background);
    cout << "\e[1m" << c << "";
   
    setColor(15, 0);//reset color
}

void Normal::deletebox(){
    setColor(15,0);
    for(int i = 0; i < 5; i++){
        gotoxy(x*10, y*4 + i);
        cout << "           ";
    }

}


void displayBackground(int x, int y){

    setColor(6, 0);
    int h = 5,w = 11;
    
    for (int i = 0; i < h; i++){
        for (int j = 0; j < w; j++){
            gotoxy((x) * 10 + j, (y) * 4 + i);
            cout << bg[(y-1)*4 + i][(x-1)*10 + j];
        }
    }
    setColor(15, 0);
}

// void renderBackground(){
//     setColor(15, 0);
//     for(int i = 0; i < 21; i++){
//         gotoxy(10, i+4);
//         cout << bg[i];
//     }
// }

void displayStatus(bool win){
    if (win){
        char status[][50] = {
        {"\e[1m__   _____  _   _  __        _____ _   _ "},
        {"\e[1m\\ \\ / / _ \\| | | | \\ \\      / /_ _| \\ | |"},
        {"\e[1m \\ V / | | | | | |  \\ \\ /\\ / / | ||  \\| |"},
        {"\e[1m  | || |_| | |_| |   \\ V  V /  | || |\\  |"},
        {"\e[1m  |_| \\___/ \\___/     \\_/\\_/  |___|_| \\_|"},
    };
    setColor(10,0);
    for (int i = 0; i < 5; i++){
        gotoxy(45,10+i);
        cout << status[i];
    }
    }else{
        char status[][52] = {
        {"\e[1m__   _____  _   _   _     ___  ____  _____ "},
        {"\e[1m\\ \\ / / _ \\| | | | | |   / _ \\/ ___|| ____|"},
        {"\e[1m \\ V / | | | | | | | |  | | | \\___ \\|  _|  "},
        {"\e[1m  | || |_| | |_| | | |__| |_| |___) | |___ "},
        {"\e[1m  |_| \\___/ \\___/  |_____\\___/|____/|_____|"},
        };
        setColor(12,0);
        for (int i = 0; i < 5; i++){
            gotoxy(42,10+i);
            cout << status[i];
        }
    }
    setColor(15,0);
}

void getPlayerInfo(Player& p) {
    gotoxy(50, 12);
    cout << "Enter player name: ";
    cin.getline(p.name,50);
    // cin.ignore();
    p.life = 3;
    p.point = 0;
    p.help = 3;
}