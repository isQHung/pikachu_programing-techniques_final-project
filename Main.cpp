#include "Menu.h"
#include "Normal.h"
#include "Diffmode.h"

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
                difficultMode(p);
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