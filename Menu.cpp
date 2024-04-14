#include "Menu.h"

void drawSelectedMenu(int choice, int text_color, int text_background){
    char options[][12]={
        "NORMAL",
        "HARD",
        "LEADERBOARD",
        "EXIT",
    };
    setColor(choice + 9, text_background);
    for (int i = 0; i < 3; i++) {
        gotoxy(60, 11 + i+ choice*3);
        cout << "             ";
    }
    gotoxy(67 - strlen(options[choice])/2 - 1,11 + choice*3 + 1);
    cout << "\e[1m" << options[choice];
}

int Menu(){
    system("cls");
    char title[6][68] = {
        " ______    __   __  ___      ___       ______  __    __   __    __",
        "|   _  \\  |  | |  |/  /     /   \\     /      ||  |  |  | |  |  |  |",
        "|  |_)  | |  | |  '  /     /  ^  \\   |  ,----'|  |__|  | |  |  |  |",
        "|   ___/  |  | |    <     /  /_\\  \\  |  |     |   __   | |  |  |  |",
        "|  |      |  | |  .  \\   /  _____  \\ |  `----.|  |  |  | |  `--'  |",
        "|__|      |__| |__|\\__\\ /__/     \\__\\ \\______||__|  |__|  \\______/",
    };

    for(int i = 0; i < 6; i++){
        gotoxy(35,i+2);
        for(int j = 0; j < 68; j++){
            setColor(j/6%6 + 9,0);
            cout << title[i][j];
        }

    }
    
    // for(int i = 0; i < 4; i++)
    //     drawSelectedMenu(i,i,0);

    //Options menu - selecting display
    int choice[4]={0,0,0,0}, cur = 0;

    while(1){
        for(int i = 0; i < 4; i++)
        drawSelectedMenu(i,i,0);

        choice[cur] = 1;
        if (choice[0]){
            drawSelectedMenu(0,0,15);
        }else if (choice[1]){
            drawSelectedMenu(1,1,15);
        }else if (choice[2]){
            drawSelectedMenu(2,2,15); 
        }else if ( choice[3]){
            drawSelectedMenu(3,3,15);
        }
        
        int temp = getch();
        if (temp != 224 && temp){
            if(temp == ENTER_KEY){
                setColor(15,0);
                system("cls");
                return cur;
            }
        }else{
            choice[cur] = 0;
            int key = getch();
            switch (key){
                case KEY_UP:
                    if (cur > 0) cur--;
                    else cur = 3;
                    break;

                case KEY_DOWN:
                    if (cur < 3) cur++;
                    else cur = 0;
                    break;
            
                default:
                    break;
            }
        }
    }

    return 0;
}

void readLeaderBoard(){
    gotoxy(60, 5);
    setColor(10,0);
    cout << "\e[1m"<<"LEADERBOARD"<<"\e[0m";
    gotoxy(30, 6);
    setColor(10,0);
    cout << "NAME";
    gotoxy(100, 6);
    setColor(10,0);
    cout << "POINT";
    
    gotoxy(30,7);
    setColor(15,0);
    for (int i = 0; i < 75; i++)
        cout << "=";
    
    ifstream ifile("leaderboard.bin", ios::in | ios::binary);
    if(ifile){
        Player p;
        int i = 0;
        while(ifile.read((char*) &p,sizeof(Player))){
            // ifile.read(reinterpret_cast <char*>(&p),sizeof(p));
            // ifile.read((char*) &p,sizeof(Player));
            
            if (i < 4) setColor(11,0); // doi mau cho 3 play dung dau
            else setColor(15,0);

            gotoxy(30,8+i*2);
            cout << p.name;
            gotoxy(100,8+i*2);
            cout << p.point;
            i++;
            gotoxy(30,7+i*2);
            setColor(15,0);
            for (int i = 0; i < 75; i++)
                cout << "-";
        }
        ifile.close();
    }
    getch();
    system("cls");
}


void writeLeaderBoard(Player p){
    ifstream ifile("leaderboard.bin", ios::in | ios::binary);
    if(ifile){
        Player* plist = new Player [10], temp;
        int count = 0;
        while(ifile.read((char *) &temp, sizeof(temp))){
            // ifile.read(reinterpret_cast<char *>(&temp), sizeof(temp));
            // ifile.read((char *) &temp, sizeof(temp));
            *(plist + count) = temp;
            count++;
        }
        // if (!count) cout << "no before";
        //find the right rating
        int index = count - 1;
        for (index; index >= 0; index --){
            if (p.point <= plist[index].point)
                break;
        }

        //insert new player
         if (count < 10) {
            for (int i = count; i > index + 1; i--) {
                plist[i] = plist[i - 1];
            }
            plist[index + 1] = p;
            count++;
        }
        else {
            if (index != count - 1) {
                for (int i = count - 1; i > index + 1; i--) {
                    plist[i] = plist[i - 1];
                }
                plist[index + 1] = p;
            }
        }

        ifile.close();

        ofstream ofile("leaderboard.bin", ios::out | ios::binary);
        for(int i = 0; i < count; i++){
            ofile.write((char *) &plist[i], sizeof(plist[i]));
        }
        ofile.close();
        delete [] plist;
    }else{
        ofstream ofile("leaderboard.bin", ios::out | ios::binary);
        ofile.write((char *) &p, sizeof(Player));
        ofile.close();
    }

}

//testing
// int main(){
//     Player p{"test2", 200};
//     writeLeaderBoard(p);
//     Menu();
//     readLeaderBoard();

//     return 0;
// }