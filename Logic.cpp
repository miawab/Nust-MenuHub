#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class menuItem {
    public:
    string name;
    int price;
    float rating;
    string type;
    menuItem() {
        name = "";
        price = 0;
        rating = 0.0f;
        type = "";
    }
    menuItem(string n, int p, float r, string t) {
        name = n;
        price = p;
        rating = r;
        type = t;
    }
};

menuItem tempMenu;

class cafe {
    public:
    menuItem menu[100];
    cafe(string fileName) {
        int i = 0;
        string nameStr, priceStr, ratingStr, typeStr, blank;
        ifstream file(fileName);
        while (true) {
            if (!getline(file, nameStr)) break;
                getline(file, priceStr);
                getline(file, ratingStr);
                getline(file, typeStr);
                menu[i].name = nameStr;
                menu[i].price = stoi(priceStr);
                menu[i].rating = stof(ratingStr);
                menu[i].type = typeStr;
                i++;
                getline(file, blank);
        }  
    } 
};





int itemCount(menuItem menu[]) {
    int count = 0;
    for (int i = 0; i < 100; i++) {
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
    //main is temperory and just to test
    cafe Inno("Inno.txt");
    int Innocount = itemCount(Inno.menu);

    cout << "Original Menu (" << Innocount << " items):\n";
    for (int i = 0; i < Innocount; i++) {
        cout << Inno.menu[i].name << " - " 
             << Inno.menu[i].price << " PKR - "
             << Inno.menu[i].rating << " stars - "
             << Inno.menu[i].type << endl;
    }

return 0;
}