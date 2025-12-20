#include <iostream>
#include <string>
#include <fstream>
#include <iomanip> // Required for formatting the category list
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
            try {
                menu[i].price = stoi(priceStr);
                menu[i].rating = stof(ratingStr);
            } catch (...) {
                menu[i].price = 0;
                menu[i].rating = 0.0;
            }
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
        sortAscendPrice();      
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
    // 1. Load Files for ALL 8 Cafes
    cafe Inno("Inno.txt");
    cafe C1("C1 Menu.txt");
    cafe C3("C3 Menu.txt");
    cafe C4("C4 menu.txt");
    cafe CoffeeLounge("Coffee Lounge Menu.txt");
    cafe Nice("Nice Menu.txt");
    cafe Retro("Retro Menu.txt");
    cafe S3H("S3H Cafe.txt");

    // 2. Setup Arrays
    cafe cafes[8] = {Inno, C1, C3, C4, CoffeeLounge, Nice, Retro, S3H};
    string cafeNames[8] = {
        "Inno", 
        "C1", 
        "C3", 
        "C4", 
        "Coffee Lounge", 
        "Nice", 
        "Retro", 
        "S3H"
    };
    int cafeCount = 8;

    int choice = -1;

    while (choice != 0) {
        cout << "\n--------------------------------\n";
        cout << "      NUST CAFE SYSTEM         \n";
        cout << "--------------------------------\n";
        cout << "1. Search by Category (View List)\n"; 
        cout << "2. Display Cafe Menu (Select Cafe)\n"; 
        cout << "3. Search Food Item (Global Name Search)\n"; 
        cout << "0. Quit\n";
        cout << "Enter selection: ";
        
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(100, '\n');
            continue;
        }

        // --- OPTION 1: SEARCH BY CATEGORY ---
        if (choice == 1) {
            string knownCategories[] = {
                "BBQ", "Bread", "Burger", "Chinese", "Coffee", "Dessert", 
                "Drinks", "Extra", "Fries", "HotDrink", "IceCream", "Juices", 
                "Paratha", "Pasta", "Pizza", "Rice", "Roll", "RollParatha", 
                "Rolls", "Salad", "Salan", "Sandwich", "Shakes", "Shawarma", 
                "Sides", "Slush", "Snacks", "Soda", "Soup", "Tea", "Wings"
            };
            int knownCount = 31;

            cout << "\nAvailable Categories:\n";
            for(int i = 0; i < knownCount; i++) {
                cout << left << setw(15) << knownCategories[i];
                if((i + 1) % 3 == 0) cout << endl;
            }
            cout << endl << endl;

            string catInput;
            cout << "Enter Category from above: ";
            cin.ignore();
            getline(cin, catInput);
            
            cout << "\n=== Category Results for: \"" << catInput << "\" ===\n\n";
            bool anyCatFound = false;

            for(int c = 0; c < cafeCount; c++) {
                bool headerPrinted = false; 
                int rCount = cafes[c].itemCount();
                
                for(int i = 0; i < rCount; i++) {
                    if(cafes[c].containsWordStartingWith(cafes[c].menu[i].type, catInput)) {
                        if(!headerPrinted) {
                            cout << "--- " << cafeNames[c] << " ---\n";
                            headerPrinted = true;
                        }
                        cout << cafes[c].menu[i].name << " - " 
                             << cafes[c].menu[i].price << " PKR - " 
                             << cafes[c].menu[i].type << endl;
                        anyCatFound = true;
                    }
                }
                if(headerPrinted) cout << endl;
            }
            
            if(!anyCatFound) {
                cout << "No items found for category \"" << catInput << "\".\n";
            }
        }
        
        // --- OPTION 2: CAFE SELECTION ---
        else if (choice == 2) {
            string inputName;
            cout << "Enter Cafe Name (Inno, C1, C3, C4, Coffee Lounge, Nice, Retro, S3H): ";
            cin.ignore(); 
            getline(cin, inputName); 

            int foundIndex = -1;
            
            for(int i = 0; i < cafeCount; i++) {
                if(cafes[i].containsWordStartingWith(cafeNames[i], inputName)) {
                    foundIndex = i;
                    break;
                }
            }

            if(foundIndex != -1) {
                char sortChoice = ' ';
                cafes[foundIndex].sortAscendPrice();
                
                while (sortChoice != 'Z') {
                    int rCount = cafes[foundIndex].itemCount();
                    
                    cout << "\n--- " << cafeNames[foundIndex] << " Menu (" << rCount << " items) ---\n";
                    for(int k=0; k<rCount; k++) {
                        cout << cafes[foundIndex].menu[k].name << " - " 
                             << cafes[foundIndex].menu[k].price << " PKR - " 
                             << cafes[foundIndex].menu[k].rating << " stars - "
                             << cafes[foundIndex].menu[k].type << endl;
                    }

                    cout << "\n[Sort Options]\n";
                    cout << "A: Ascending Price\n";
                    cout << "B: Descending Price\n";
                    cout << "C: Sort by Name\n";
                    cout << "Z: Back to Main Menu\n";
                    cout << "Enter choice: ";
                    cin >> sortChoice;
                    sortChoice = toupper(sortChoice);

                    if (sortChoice == 'A') {
                        cafes[foundIndex].sortAscendPrice();
                    }
                    else if (sortChoice == 'B') {
                        cafes[foundIndex].sortDescendPrice();
                    }
                    else if (sortChoice == 'C') {
                        cafes[foundIndex].sortName();
                    }
                }
            } else {
                cout << "Cafe not found! Check spelling.\n";
            }
        }
        
        // --- OPTION 3: GLOBAL SEARCH (NAME) ---
        else if (choice == 3) {
            string term;
            cout << "Enter food name to search: ";
            cin >> term;
            globalSearch(cafes, cafeNames, cafeCount, term);
        }
        

        else if (choice == 0) {
            cout << "Exiting...\n";
        }
    }

    return 0;
}