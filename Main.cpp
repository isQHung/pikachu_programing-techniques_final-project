#include "Menu.h"
#include "Menu.cpp"
#include "Normal.cpp"

// #include "Hard.h"

int main(){
    initWindow(1000,500);

    int status = 1;
    Player p;

    while (status != 3){
        status = Menu();
        switch (status){
            case 0:
                getPlayerInfo(p);
                normalMode(p,0);
                break;

            case 1:
                getPlayerInfo(p);
                //hardMode(p);
                break;

            case 2:
                readLeaderBoard();
                break;
            
            default:
                break;
        }
    }

    return 0;
}