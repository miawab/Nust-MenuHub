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

class cafe {
    private:
    menuItem tempMenu;  
    
    public:
    menuItem menu[270];
    
    cafe(string fileName) {
        int i = 0;
        string nameStr, priceStr, ratingStr, typeStr, blank;
        ifstream file(fileName);
        
        if(!file.is_open()) {
            cout << "Error: Could not open file " << fileName << endl;
            return;
        }
        
        while (getline(file, nameStr)) {
            if(nameStr.empty()) continue;
            
            getline(file, priceStr);
            getline(file, ratingStr);
            getline(file, typeStr);
            
            if(!nameStr.empty() && nameStr.back() == '\r') nameStr.pop_back();
            if(!priceStr.empty() && priceStr.back() == '\r') priceStr.pop_back();
            if(!ratingStr.empty() && ratingStr.back() == '\r') ratingStr.pop_back();
            if(!typeStr.empty() && typeStr.back() == '\r') typeStr.pop_back();
            
            menu[i].name = nameStr;
            menu[i].price = stoi(priceStr);
            menu[i].rating = stof(ratingStr);
            menu[i].type = typeStr;
            i++;
            
            getline(file, blank);
        }
        
        file.close();
    }

        string toLower(string str) {
        string result = "";
        for(int i = 0; i < str.length(); i++) {
            result += tolower(str[i]);
        }
        return result;
    }
    
    bool startsWith(string word, string searchTerm) {
        if(searchTerm.length() > word.length()) {
            return false;
        }
        
        for(int i = 0; i < searchTerm.length(); i++) {
            if(word[i] != searchTerm[i]) {
                return false;
            }
        }
        return true;
    }
    
    bool containsWordStartingWith(string str, string searchTerm) {
        str = toLower(str);
        searchTerm = toLower(searchTerm);
        
        string currentWord = "";
        
        for(int i = 0; i <= str.length(); i++) {
            if(i == str.length() || str[i] == ' ') {
                if(currentWord != "" && startsWith(currentWord, searchTerm)) {
                    return true;
                }
                currentWord = "";
            } else {
                currentWord += str[i];
            }
        }
        
        return false;
    }
    
    int itemCount() {
        int count = 0;
        for (int i = 0; i < 270; i++) {
            if (menu[i].name != "")
                count++;
        }
        return count;
    }
    
    void sortAscendPrice() {
        int realCount = itemCount();
        
        for(int j = 0; j < realCount; j++) {
            for(int i = 0; i < realCount - j - 1; i++) {
                if(menu[i].price > menu[i+1].price) {
                    tempMenu = menu[i];
                    menu[i] = menu[i+1];
                    menu[i+1] = tempMenu;
                }
            }
        }
    }
    
    void sortDescendPrice() {
        int realCount = itemCount();
        
        for(int j = 0; j < realCount; j++) {
            for(int i = 0; i < realCount - j - 1; i++) {
                if(menu[i].price < menu[i+1].price) {
                    tempMenu = menu[i];
                    menu[i] = menu[i+1];
                    menu[i+1] = tempMenu;
                }
            }
        }
    }
    
    void sortName() {
        int realCount = itemCount();
        
        for(int j = 0; j < realCount; j++) {
            for(int i = 0; i < realCount - j - 1; i++) {
                if(menu[i].name > menu[i+1].name) {
                    tempMenu = menu[i];
                    menu[i] = menu[i+1];
                    menu[i+1] = tempMenu;
                }
            }
        }
    }

    void searchMenu(string searchTerm) {
    int realCount = itemCount();
    bool found = false;
    
    cout << "\nSearch Results for: \"" << searchTerm << "\"\n";
    
    for(int i = 0; i < realCount; i++) {
        if(containsWordStartingWith(menu[i].name, searchTerm)) {
            cout << menu[i].name << " - " 
                 << menu[i].price << " PKR - "
                 << menu[i].rating << " stars - "
                 << menu[i].type << endl;
            found = true;
        }
    }
    
    if(!found) {
        cout << "No items found matching \"" << searchTerm << "\"\n";
    }
}

    void displayMenu() {
        int realCount = itemCount();
        sortAscendPrice(); // Sorts in ascending price by default before printing the menu.        
        cout << "Original Menu (" << realCount << " items):\n";
        for (int i = 0; i < realCount; i++) {
            cout << menu[i].name << " - " 
                << menu[i].price << " PKR - "
                << menu[i].rating << " stars - "
                << menu[i].type << endl;
        }
    }
};

void globalSearch(cafe cafes[], string cafeNames[], int cafeCount, string searchTerm) {
    cout << "\n=== Global Search Results for: \"" << searchTerm << "\" ===\n\n";
    
    bool anyFound = false;
    
    for(int c = 0; c < cafeCount; c++) {
        cout << "--- " << cafeNames[c] << " ---\n";
        
        int realCount = cafes[c].itemCount();
        bool foundInThisCafe = false;
        
        for(int i = 0; i < realCount; i++) {
            if(cafes[c].containsWordStartingWith(cafes[c].menu[i].name, searchTerm)) {
                cout << cafes[c].menu[i].name << " - " 
                     << cafes[c].menu[i].price << " PKR - "
                     << cafes[c].menu[i].rating << " stars - "
                     << cafes[c].menu[i].type << endl;
                foundInThisCafe = true;
                anyFound = true;
            }
        }
        
        if(!foundInThisCafe) {
            cout << "No matches found in this cafe.\n";
        }
        
        cout << endl;
    }
    
    if(!anyFound) {
        cout << "No items found matching \"" << searchTerm << "\" in any cafe.\n";
    }
}

int main() {
    cafe Inno("Inno.txt");
    cafe C1("C1.txt");
    Inno.displayMenu();
    Inno.searchMenu("Burger");
    cafe cafes[2] = {Inno, C1};
    string cafeNames[2] = {"Inno Cafe", "C1 Cafe"};
    
    globalSearch(cafes, cafeNames, 2, "Bur");

return 0;
}