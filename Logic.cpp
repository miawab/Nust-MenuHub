#include <iostream>
#include <string>
using namespace std;

class menuItem {
    public:
    string name;
    int price;
    float rating;
    menuItem() {
        name = "";
        price = 0;
        rating = 0.0f;
    }
    menuItem(string n, int p, float r) {
        name = n;
        price = p;
        rating = r;
    }
};

menuItem tempMenu;

class cafe {
    public:
    string name;
    menuItem menu[50];

};


int itemCount(menuItem menu[]) {
    int count = 0;
    for (int i = 0; i < 50; i++) {
        if (menu[i].name != "")
            count++;
    }
    return count;
}

void sortAscendPrice(menuItem menu[]) {
    int realCount = itemCount(menu);

    for(int j=0; j<realCount;j++){
        for(int i=0; i<realCount-j-1; i++){
            if(menu[i].price > menu[i+1].price){
                tempMenu = menu[i];
                menu[i] = menu[i+1];
                menu[i+1] = tempMenu;
            }

        }
    }

};

void sortDescendPrice(menuItem menu[]) {
    int realCount = itemCount(menu);

    for(int j=0; j<realCount;j++){
        for(int i=0; i<realCount-j-1; i++){
            if(menu[i].price < menu[i+1].price){
                tempMenu = menu[i];
                menu[i] = menu[i+1];
                menu[i+1] = tempMenu;
            }

        }
    }

};

void sortName(menuItem menu[]) {
    int realCount = itemCount(menu);
    
    for(int j=0; j<realCount;j++){
        for(int i=0; i<realCount-j-1; i++){
            if(menu[i].name > menu[i+1].name){
                tempMenu = menu[i];
                menu[i] = menu[i+1];
                menu[i+1] = tempMenu;
            }

        }
    }

};

int main() {

return 0;
}