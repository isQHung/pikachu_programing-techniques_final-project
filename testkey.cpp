#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;

struct  player{
    char name[50];
    int point;
};


int main(){
    fstream fo("test.bin", ios::out | ios::binary);
    player p{"hi hello", 100}, *list = new player [10];
    // for (int i = 0; i < 10; i++){
        strcpy(p.name,"hello hi");
        p.point = 1;
        fo.write(reinterpret_cast<char*>(&p), sizeof(p)/2);
    // }
    fo.close();

    fstream fi("test.bin", ios::in | ios::binary);
    int i = 0;
    while(fi){
        fi.read(reinterpret_cast<char*>(&p), sizeof(p));
        // *(list + i) = p;
        cout << p.name << " " << p.point << endl;
        i++;
    }

    // for (int i = 0; i< 10; i++){
    //     cout << (list + i)->name << (list + i)->name << endl;
    // }
    fi.close();


}