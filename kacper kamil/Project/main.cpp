#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cctype>
#include <cstdlib>



#ifdef _WIN32
#include <conio.h> // for _getch()
#else
#include <unistd.h> // for read()
#endif

using namespace std;

// Function template to get user input of any type
template<typename T>
T getUserInput(const string& prompt) {
    T value;
    while (true) {
        cout << prompt;
        if (!(cin >> value)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again." << endl;
        }
        else {
            break;
        }
    }
    return value;
}

class Item {
protected:
    string name;
    string rarity;
    int value;
    int level;
public:

    Item(string name = "none", string rarity = "none", int value = 0, int level = 0) : name{ name }, rarity{ rarity }, value{ value }, level{ level } {}
    virtual ~Item() {}

    //function that will check rarity and will display it in color
    void checkRarity(string rarity)
    {
        if (rarity == "Common")
        {
            cout << name << endl;
        }
        else if (rarity == "Rare")
        {
            cout << "\033[1;34m" << name << "\033[0m" << endl;
        }
        else if (rarity == "Epic")
        {
            cout << "\033[1;35m" << name << "\033[0m" << endl;
        }
        else if (rarity == "Legendary")
        {
            cout << "\033[1;33m" << name << "\033[0m" << endl;
        }
    }

    void showInfoOfItem()
    {
        cout << "Name: ";
        checkRarity(rarity);
        cout << "Rarity: " << rarity << endl;
        cout << "Worth: " << value << endl;
        cout << "Level: " << level << endl;
    }

    string getName() const {
        return name;
    }

    string getRarity() const {
        return rarity;
    }

    int getValue() const {
        return value;
    }

    int getLevel() const {
        return level;
    }
};

class Weapon : public Item {
public:
    int damage;
    Weapon(string name = "Weapon", string rarity = "Common", int value = 100, int level = 0, int damage = 10) : Item(name, rarity, value, level), damage(damage) {}

    ~Weapon() {}

    // Overloaded showInfoOfItem() for Weapon
    void showInfoOfItem()
    {
        cout << "Name: ";
        checkRarity(rarity);
        cout << "Rarity: " << rarity << endl;
        cout << "Worth: " << value << endl;
        cout << "Level: " << level << endl;
        cout << "Damage: " << damage << endl;
    }
};

class Armor : public Item {
public:
    int armor;
    Armor(string name = "Armor", string rarity = "Common", int value = 100, int level = 0, int armor = 10) : Item(name, rarity, value, level), armor(armor) {}

    ~Armor() {}

    // Overloaded showInfoOfItem() for Armor
    void showInfoOfItem()
    {
        cout << "Name: ";
        checkRarity(rarity);
        cout << "Rarity: " << rarity << endl;
        cout << "Worth: " << value << endl;
        cout << "Level: " << level << endl;
        cout << "Armor: " << armor << endl;
    }
};


class Sword : public Weapon {
public:
    Sword(string name = "Sword", string rarity = "Common", int value = 100, int level = 0, int damage = 10) : Weapon(name, rarity, value, level, damage) {}

    ~Sword() {}

    // Overloaded showInfoOfItem() for Sword
    void showInfoOfItem()
    {
        cout << "Name: ";
        checkRarity(rarity);
        cout << "Rarity: " << rarity << endl;
        cout << "Worth: " << value << endl;
        cout << "Level: " << level << endl;
        cout << "Damage: " << damage << endl;
    }
};

class Bow : public Weapon {
public:
    Bow(string name = "Bow", string rarity = "Common", int value = 200, int level = 0, int damage = 8) : Weapon(name, rarity, value, level, damage) {}

    ~Bow() {}

    // Overloaded showInfoOfItem() for Bow
    void showInfoOfItem()
    {
        cout << "Name: ";
        checkRarity(rarity);
        cout << "Rarity: " << rarity << endl;
        cout << "Worth: " << value << endl;
        cout << "Level: " << level << endl;
        cout << "Damage: " << damage << endl;
    }
};

class Shield : public Armor {
public:
    Shield(string name = "Shield", string rarity = "Common", int armor = 10, int value = 100, int level = 0) : Armor(name, rarity, armor, value, level) {}

    ~Shield() {}

    // Overloaded showInfoOfItem() for Shield
    void showInfoOfItem()
    {
        cout << "Name: ";
        checkRarity(rarity);
        cout << "Rarity: " << rarity << endl;
        cout << "Worth: " << value << endl;
        cout << "Level: " << level << endl;
        cout << "Armor: " << armor << endl;
    }
};

class Helmet : public Armor {
public:
    Helmet(string name = "Helmet", string rarity = "Common", int armor = 15, int value = 100, int level = 0) : Armor(name, rarity, armor, value, level) {}

    ~Helmet() {}

    // Overloaded showInfoOfItem() for Helmet
    void showInfoOfItem()
    {
        cout << "Name: ";
        checkRarity(rarity);
        cout << "Rarity: " << rarity << endl;
        cout << "Worth: " << value << endl;
        cout << "Level: " << level << endl;
        cout << "Armor: " << armor << endl;
    }
};

class Chestplate : public Armor {
public:
    Chestplate(string name = "Chestplate", string rarity = "Common", int armor = 25, int value = 100, int level = 0) : Armor(name, rarity, armor, value, level) {}

    ~Chestplate() {}

    // Overloaded showInfoOfItem() for Chestplate
    void showInfoOfItem()
    {
        cout << "Name: ";
        checkRarity(rarity);
        cout << "Rarity: " << rarity << endl;
        cout << "Worth: " << value << endl;
        cout << "Level: " << level << endl;
        cout << "Armor: " << armor << endl;
    }
};

class Leggings : public Armor {
public:
    Leggings(string name = "Leggings", string rarity = "Common", int armor = 20, int value = 100, int level = 0) : Armor(name, rarity, armor, value, level) {}

    ~Leggings() {}

    // Overloaded showInfoOfItem() for Leggings
    void showInfoOfItem()
    {
        cout << "Name: ";
        checkRarity(rarity);
        cout << "Rarity: " << rarity << endl;
        cout << "Worth: " << value << endl;
        cout << "Level: " << level << endl;
        cout << "Armor: " << armor << endl;
    }
};


class Equipment {
protected:
    int rows;
    int cols;
    int level;
    Item*** grid;

public:
    Equipment(int rows = 4, int cols = 5, int level = 1) : rows{ rows }, cols{ cols }, level{ level }
    {
        grid = new Item * *[rows];
        for (int i = 0; i < rows; i++)
        {
            grid[i] = new Item * [cols];
        }
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                grid[i][j] = nullptr;
            }
        }
    }
    ~Equipment()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                delete grid[i][j];
            }
        }
        for (int j = 0; j < rows; j++)
        {
            delete[] grid[j];
        }
        delete[] grid;
    }

    int getRows() const {
        return rows;
    }

    int getCols() const {
        return cols;
    }

    Item*** getGrid() const {
        return grid;
    }

    Item* getItem(int row, int col) const {
        if (row < 0 || row >= rows || col < 0 || col >= cols) {
            return nullptr;
        }
        return grid[row][col];
    }

    pair<int, int> moveInInventory() {
        int currentIndexRow = 0;
        int currentIndexCol = 0;

        displayEquipmentForMoving(currentIndexRow, currentIndexCol);

        char ch = 0;
        while (true) {
#ifdef _WIN32
            ch = _getch(); // Get a character without waiting for Enter
#else
            ch = getch(); // Get a character without waiting for Enter
#endif
            switch (ch) {
            case 'a':
                if (currentIndexCol > 0) {
                    --currentIndexCol;
                }
                break;
            case 'd':
                if (currentIndexCol < 5 - 1) {
                    ++currentIndexCol;
                }
                break;
            case 'w':
                if (currentIndexRow > 0) {
                    --currentIndexRow;
                }
                break;
            case 's':
                if (currentIndexRow < 4 - 1) {
                    ++currentIndexRow;
                }
                break;
            case 'q': // 'q' to quit
                cout << "Quitting..." << endl;
                displayEquipment();
                return make_pair(-1, -1); // Return invalid coordinates to indicate no selection
            case ' ': // Spacebar to select item
                if (grid[currentIndexRow][currentIndexCol] != nullptr) {
                    return make_pair(currentIndexRow, currentIndexCol); // Return coordinates if item found
                }
                break;
            }
            displayEquipmentForMoving(currentIndexRow, currentIndexCol);
        }
    }

    void sort_equipment_by_level()
    {
        // Create a vector to store sorted items
        vector<Item*> sortedItems;

        // Iterate through the grid and add non-null items to the vector
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] != nullptr) {
                    sortedItems.push_back(grid[i][j]);
                }
            }
        }

        // Sort the items based on level in descending order
        sort(sortedItems.begin(), sortedItems.end(), [](Item* a, Item* b) {
            return a->getLevel() > b->getLevel(); // Change to ">" for descending order
            });

        // Repopulate the grid with sorted items
        int k = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (k < sortedItems.size()) {
                    grid[i][j] = sortedItems[k++];
                }
                else {
                    grid[i][j] = nullptr; // Fill remaining grid cells with nullptr
                }
            }
        }
    }

    void sort_equipment_by_rarity()
    {
        unordered_map<string, int> rarityValues = {
            {"Common", 0},
            {"Rare", 1},
            {"Epic", 2},
            {"Legendary", 3}
        };

        vector<Item*> sortedItems;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] != nullptr) {
                    sortedItems.push_back(grid[i][j]);
                }
            }
        }

        sort(sortedItems.begin(), sortedItems.end(), [&](Item* a, Item* b) {
            return rarityValues[a->getRarity()] > rarityValues[b->getRarity()]; // ">" for descending order
            });

        // Repopulate the grid with sorted items
        int k = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (k < sortedItems.size()) {
                    grid[i][j] = sortedItems[k++];
                }
                else {
                    grid[i][j] = nullptr; // Fill remaining grid cells with nullptr
                }
            }
        }
    }

    void sort_equipment_by_value()
    {
        // Create a vector to store sorted items
        vector<Item*> sortedItems;

        // Iterate through the grid and add non-null items to the vector
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (grid[i][j] != nullptr) {
                    sortedItems.push_back(grid[i][j]);
                }
            }
        }

        // Sort the items based on value in descending order
        sort(sortedItems.begin(), sortedItems.end(), [](Item* a, Item* b) {
            return a->getValue() > b->getValue(); // ">" for descending order
            });

        // Repopulate the grid with sorted items
        int k = 0;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (k < sortedItems.size()) {
                    grid[i][j] = sortedItems[k++];
                }
                else {
                    grid[i][j] = nullptr; // Fill remaining grid cells with nullptr
                }
            }
        }
    }


    void displayEquipmentForMoving(int row, int col)
    {
        system("cls || clear");
        cout << "<EQUIPMENT>" << endl;
        cout << "+-----------------------------------------------+" << endl;
        for (int i = 0; i < rows; i++)
        {
            cout << "|";
            for (int j = 0; j < cols; j++)
            {
                if (i == row && j == col) {
                    cout << " [" << ">" << (grid[i][j] != nullptr ? grid[i][j]->getName() : "    ") << "<" << "]\t";
                }
                else {
                    cout << " [ " << (grid[i][j] != nullptr ? grid[i][j]->getName() : "    ") << " ]\t";
                }
            }
            cout << "\t|" << endl;
        }
        cout << "+-----------------------------------------------+" << endl;
        cout << endl;
        cout << "Use 'WASD' to move, 'Space' to select, 'Q' to quit" << endl;
        if (grid[row][col] != nullptr)
        {
            // Check if the item is a Weapon or Armor and call the corresponding function
            if (dynamic_cast<Armor*>(grid[row][col]) != nullptr)
            {
                Armor* armor = dynamic_cast<Armor*>(grid[row][col]);
                armor->showInfoOfItem();
            }
            else if (dynamic_cast<Weapon*>(grid[row][col]) != nullptr)
            {
                Weapon* weapon = dynamic_cast<Weapon*>(grid[row][col]);
                weapon->showInfoOfItem();
            }
            else
            {
                cout << "No item at this position." << endl;
            }
        }
    }

    void displayEquipment()
    {
        system("cls || clear");
        cout << "<EQUIPMENT>" << endl;
        cout << "+-----------------------------------------------+" << endl;
        for (int i = 0; i < rows; i++)
        {
            cout << "|";
            for (int j = 0; j < cols; j++)
            {
                cout << " [" << (grid[i][j] != nullptr ? grid[i][j]->getName() : "    ") << "] ";
            }
            cout << "\t|" << endl;
        }
        cout << "+-----------------------------------------------+" << endl;
        cout << endl;
        cout << "1. Check item" << endl;
        cout << "2. Move/Swap items" << endl;
        cout << "3. Sort by Level" << endl;
        cout << "4. Sort by Rarity" << endl;
        cout << "5. Sort by Value" << endl;
        cout << "6. Search for an item" << endl;
        cout << "7. Exit" << endl;

        int choice = getUserInput<int>("Enter your choice: ");
        switch (choice)
        {
        case 1:
        {
            moveInInventory();
            break;
        }
        case 2:
        {
            pair<int, int> selectedPosition = moveInInventory();
            if (selectedPosition.first != -1 && selectedPosition.second != -1)
			{
				pair<int, int> newPosition = moveInInventory();
				if (newPosition.first != -1 && newPosition.second != -1)
				{
					moveItem(selectedPosition.first, selectedPosition.second, newPosition.first, newPosition.second);
				}
			}
        }
        case 3:
        {
            sort_equipment_by_level();
            displayEquipment();
            break;
        }
        case 4:
        {
            sort_equipment_by_rarity();
            displayEquipment();
            break;
        }
        case 5:
        {
            sort_equipment_by_value();
            displayEquipment();
            break;
        }
        case 6:
        {
            string name;
            cout << "Enter the name of the item you are looking for: ";
            cin >> name;
            search_for_item(name);
            cout << "Press any key to continue..." << endl;
            cin.ignore();
            cin.get();
            displayEquipment();
            break;
        }
        case 7:
        {
            cout << "Exiting..." << endl;
            break;
        }
        default:
        {
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
        }
    }


    bool addItem(Item* item, int row, int col) {
        // Check if the given coordinates are within bounds
        if (row >= 0 && row < rows && col >= 0 && col < cols) {
            // Check if the grid slot is available
            if (grid[row][col] == nullptr) {
                // Slot is available, add the item
                grid[row][col] = item;
                return true; // Item added successfully
            }
            else {
                // Slot is occupied, try finding another available slot
                for (int i = 0; i < rows; ++i) {
                    for (int j = 0; j < cols; ++j) {
                        if (grid[i][j] == nullptr) {
                            // Found an empty slot, add the item here
                            grid[i][j] = item;
                            return true; // Item added successfully
                        }
                    }
                }
                // No available slots found
                return false;
            }
        }
        // Coordinates are out of bounds
        return false;
    }

    void moveItem(int row_of_item, int col_of_item, int row_to_swap, int col_to_swap)
    {
        Item* temp = grid[row_of_item][col_of_item];
        grid[row_of_item][col_of_item] = grid[row_to_swap][col_to_swap];
        grid[row_to_swap][col_to_swap] = temp;
    }


    void deleteItem(int row, int col)
    {
        grid[row][col] = nullptr;
    }

    bool findPlaceForItem()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == nullptr)
                {
                    return true;
                }
            }
        }
        return false;
    }

    pair<int, int> returnFreeSlot()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == nullptr)
                {
                    return make_pair(i, j);
                }
            }
        }
        return make_pair(-1, -1);
    }

    int getPlaceForItem()
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] == nullptr)
                {
                    return i * cols + j;
                }
            }
        }
        return -1;
    }

    //a function that will search for an item in the equipment creating a new list of items that match the search
    void search_for_item(string name)
    {
        // Convert the search string to lowercase for case-insensitive search
        transform(name.begin(), name.end(), name.begin(), ::tolower);

        vector<Item*> items;
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < cols; j++)
            {
                if (grid[i][j] != nullptr)
                {
                    // Convert the item name to lowercase for case-insensitive search
                    string itemName = grid[i][j]->getName();
                    transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);

                    // Check if the search string is a substring of the item name
                    if (itemName.find(name) != string::npos)
                    {
                        items.push_back(grid[i][j]);
                    }
                }
            }
        }
        if (items.empty())
        {
            cout << "No items found" << endl;
        }
        else
        {
            cout << "Items found:" << endl;
            for (int i = 0; i < items.size(); i++)
            {
                items[i]->showInfoOfItem(); // Call the showInfoOfItem function for each item
            }
        }
    }

};

class Player {
private:
    int money;
    int health;
    int armour;
    int level;
    Equipment equipment; // Player HAS-A Equipment

public:
    Player(int money = 1000, int health = 100, int armour = 20, int level = 1)
        : money{ money }, health{ health }, armour{ armour }, level{ level }, equipment() {}

    ~Player() {}

    void displayStats() {
        system("cls || clear");
        cout << "<PLAYER STATS>" << endl;
        cout << "+-------------------------+" << endl;
        cout << "Money: " << money << endl;
        cout << "Health: " << health << endl;
        cout << "Armour: " << armour << endl;
        cout << "Level: " << level << endl;
        cout << "+-------------------------+" << endl;
    }

    int getMoney() {
        return money;
    }

    int increaseMoney(int amount) {
        money += amount;
        return money;
    }

    int decreaseMoney(int amount) {
        money -= amount;
        return money;
    }

    pair<int, int> moveInPlayerInventory() {
        return equipment.moveInInventory();
    }

    Equipment& getEquipment() {
        return equipment;
    }

    void searchForItem(string name) {
        equipment.search_for_item(name);
    }

    void sortEquipmentByLevel() {
        equipment.sort_equipment_by_level();
    }

    void sortEquipmentByRarity() {
        equipment.sort_equipment_by_rarity();
    }

    void sortEquipmentByValue() {
        equipment.sort_equipment_by_value();
    }
};

class Store {
private:
    Equipment equipment;
    Player* player;
public:
    Store(int rows = 4, int cols = 5) : equipment(rows, cols), player(nullptr) {}
    ~Store() {}

    void setItemInStore(Item* item, int row, int col) {
        if (row >= 0 && row < equipment.getRows() && col >= 0 && col < equipment.getCols()) {
            equipment.getGrid()[row][col] = item;
        }
    }

    Item* getItemFromStore(int row, int col) {
        equipment.getItem(row, col);
    }

    void displayEquipmentForMoving(int row, int col) {
        system("cls || clear");
        cout << "<STORE>" << endl;
        cout << "+-----------------------------------------------+" << endl;
        for (int i = 0; i < equipment.getRows(); i++) {
            cout << "|";
            for (int j = 0; j < equipment.getCols(); j++) {
                if (i == row && j == col) {
                    cout << " [" << ">" << (equipment.getGrid()[i][j] != nullptr ? equipment.getGrid()[i][j]->getName() : "    ") << "<" << "]\t";
                }
                else {
                    cout << " [ " << (equipment.getGrid()[i][j] != nullptr ? equipment.getGrid()[i][j]->getName() : "    ") << " ]\t";
                }
            }
            cout << "\t|" << endl;
        }
        cout << "+-----------------------------------------------+" << endl;
        cout << endl;
        cout << "Use 'WASD' to move, 'Space' to select, 'Q' to quit" << endl;
        if (equipment.getGrid()[row][col] != nullptr) {
            // Check if the item is a Weapon or Armor and call the corresponding function
            if (dynamic_cast<Armor*>(equipment.getGrid()[row][col]) != nullptr) {
                Armor* armor = dynamic_cast<Armor*>(equipment.getGrid()[row][col]);
                armor->showInfoOfItem();
            }
            else if (dynamic_cast<Weapon*>(equipment.getGrid()[row][col]) != nullptr) {
                Weapon* weapon = dynamic_cast<Weapon*>(equipment.getGrid()[row][col]);
                weapon->showInfoOfItem();
            }
            else {
                cout << "No item at this position." << endl;
            }
        }
    }

    void displayEquipmentForBuying(int row, int col) {
        system("cls || clear");
        cout << "<STORE>" << endl;
        cout << "+-----------------------------------------------+" << endl;
        for (int i = 0; i < equipment.getRows(); i++) {
            cout << "|";
            for (int j = 0; j < equipment.getCols(); j++) {
                if (i == row && j == col) {
                    cout << " [" << ">" << (equipment.getGrid()[i][j] != nullptr ? equipment.getGrid()[i][j]->getName() : "    ") << "<" << "]\t";
                }
                else {
                    cout << " [ " << (equipment.getGrid()[i][j] != nullptr ? equipment.getGrid()[i][j]->getName() : "    ") << " ]\t";
                }
            }
            cout << "\t|" << endl;
        }
        cout << "+-----------------------------------------------+" << endl;
        cout << endl;
        cout << "Use 'WASD' to move, 'Enter' to buy, 'Q' to quit" << endl;
        if (equipment.getGrid()[row][col] != nullptr) {
            // Check if the item is a Weapon or Armor and call the corresponding function
            if (dynamic_cast<Armor*>(equipment.getGrid()[row][col]) != nullptr) {
                Armor* armor = dynamic_cast<Armor*>(equipment.getGrid()[row][col]);
                armor->showInfoOfItem();
            }
            else if (dynamic_cast<Weapon*>(equipment.getGrid()[row][col]) != nullptr) {
                Weapon* weapon = dynamic_cast<Weapon*>(equipment.getGrid()[row][col]);
                weapon->showInfoOfItem();
            }
            else {
                cout << "No item at this position." << endl;
            }
        }
    }

    void deleteItemFromStore(int row, int col) {
        equipment.deleteItem(row, col);
    }

    void buyItem(Item* item, int row, int col) {
        if (player != nullptr) {
            int itemValue = item->getValue();
            if (player->getMoney() >= itemValue) {
                player->decreaseMoney(itemValue);
                cout << "You bought " << item->getName() << " for " << itemValue << " gold." << endl;
                // Now make the player choose a slot to put the item in
                pair<int, int> freeSlot = player->getEquipment().returnFreeSlot();
                if (freeSlot.first != -1 && freeSlot.second != -1) {
                    if (player->getEquipment().addItem(item, freeSlot.first, freeSlot.second)) {
                        cout << "Item added to your inventory." << endl;
                        // Delete the item from the store after buying
                        equipment.deleteItem(row, col);
                    }
                    else {
                        cout << "Failed to add item to your inventory. Your inventory may be full." << endl;
                        // Refund the money
                        player->increaseMoney(itemValue);
                    }
                }
                else {
                    cout << "Failed to add item to your inventory. Your inventory may be full." << endl;
                    // Refund the money
                    player->increaseMoney(itemValue);
                }
            }
            else {
                cout << "You don't have enough money to buy " << item->getName() << "." << endl;
            }
        }
    }

    void sellItem(int row, int col) {
        if (player != nullptr && equipment.getItem(row, col) != nullptr) {
            Item* itemToSell = equipment.getItem(row, col);
            equipment.deleteItem(row, col);
            int sellValue = static_cast<int>(itemToSell->getValue() * 0.5); // Selling at half price
            player->increaseMoney(sellValue);
            cout << "You sold " << itemToSell->getName() << " for " << sellValue << " gold." << endl;
        }
        else {
            cout << "There is no item in this slot" << endl;
        }
    }

    void displayStore() {
        bool runningStore = true;
        while (runningStore) {
            system("cls || clear");
            cout << "<STORE>" << endl;
            cout << "+-----------------------------------------------+" << endl;
            for (int i = 0; i < equipment.getRows(); i++) {
                cout << "|";
                for (int j = 0; j < equipment.getCols(); j++) {
                    cout << " [" << (equipment.getGrid()[i][j] != nullptr ? equipment.getGrid()[i][j]->getName() : "     ") << "]";
                }
                cout << "\t|" << endl;
            }
            cout << "+-----------------------------------------------+" << endl;
            cout << endl;
            cout << "1. Check items" << endl;
            cout << "2. Buy an item" << endl;
            cout << "3. Exit" << endl;

            int choice = getUserInput<int>("Enter your choice: ");
            switch (choice) {
            case 1: {
                moveInStore();
                break;
            }
            case 2: {
                // Buying an item
                pair<int, int> selectedPosition = moveInStoreToBuy();
                if (selectedPosition.first != -1 && selectedPosition.second != -1) {
                    // Get the item at the selected position
                    Item* itemToBuy = equipment.getItem(selectedPosition.first, selectedPosition.second);
                    if (itemToBuy != nullptr) {
                        // Attempt to buy the item
                        buyItem(itemToBuy, selectedPosition.first, selectedPosition.second);
                    }
                }
                break;
            }
            case 3: {
                cout << "Exiting..." << endl;
                runningStore = false;
                break;
            }
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }



    pair<int, int> moveInStore() {
        int currentIndexRow = 0;
        int currentIndexCol = 0;

        displayEquipmentForMoving(currentIndexRow, currentIndexCol);

        char ch = 0;
        while (true) {
#ifdef _WIN32
            ch = _getch(); // Get a character without waiting for Enter
#else
            ch = getch(); // Get a character without waiting for Enter
#endif
            switch (ch) {
            case 'a':
                if (currentIndexCol > 0) {
                    --currentIndexCol;
                }
                break;
            case 'd':
                if (currentIndexCol < equipment.getCols() - 1) {
                    ++currentIndexCol;
                }
                break;
            case 'w':
                if (currentIndexRow > 0) {
                    --currentIndexRow;
                }
                break;
            case 's':
                if (currentIndexRow < equipment.getRows() - 1) {
                    ++currentIndexRow;
                }
                break;
            case 'q': // 'q' to quit
                cout << "Quitting..." << endl;
                return make_pair(-1, -1); // Return invalid coordinates to indicate no selection
            case ' ': // Spacebar to select item
                if (equipment.getGrid()[currentIndexRow][currentIndexCol] != nullptr) {
                    return make_pair(currentIndexRow, currentIndexCol); // Return coordinates if item found
                }
                break;
            }
            displayEquipmentForMoving(currentIndexRow, currentIndexCol);
        }
    }
    pair<int, int> moveInStoreToBuy() {
        int currentIndexRow = 0;
        int currentIndexCol = 0;

        while (true) {
            displayEquipmentForBuying(currentIndexRow, currentIndexCol);

            char ch = 0;
#ifdef _WIN32
            ch = _getch(); // Get a character without waiting for Enter
#else
            ch = getch(); // Get a character without waiting for Enter
#endif
            switch (ch) {
            case 'a':
                if (currentIndexCol > 0) {
                    --currentIndexCol;
                }
                break;
            case 'd':
                if (currentIndexCol < equipment.getCols() - 1) {
                    ++currentIndexCol;
                }
                break;
            case 'w':
                if (currentIndexRow > 0) {
                    --currentIndexRow;
                }
                break;
            case 's':
                if (currentIndexRow < equipment.getRows() - 1) {
                    ++currentIndexRow;
                }
                break;
            case 'q': // 'q' to quit
                cout << "Quitting..." << endl;
                return make_pair(-1, -1); // Return invalid coordinates to indicate no selection
            case ' ': // Space key to buy item
                // If the current position contains an item, try to buy it
                if (equipment.getGrid()[currentIndexRow][currentIndexCol] != nullptr) {
                    Item* itemToBuy = equipment.getItem(currentIndexRow, currentIndexCol);
                    // Buy the item if it exists
                    if (itemToBuy != nullptr) {
                        buyItem(itemToBuy, currentIndexRow, currentIndexCol);
                        return make_pair(-1, -1); // Return invalid coordinates after buying
                    }
                }
                break;
            }
        }
    }

};

class Town {
private:
    Player* player;
    Store* store;

public:
    Town(Player* player, Store* store) : player(player), store(store)
    {
        Item* sword = new Sword("Sword", "Common", 100, 1, 10);
        Item* bow = new Bow("Bow", "Rare", 200, 1, 8);
        Item* shield = new Shield("Shield", "Epic", 100, 1, 10);
        Item* helmet = new Helmet("Helmet", "Legendary", 100, 1, 15);

        store->setItemInStore(sword, 0, 0);
        store->setItemInStore(bow, 0, 1);
        store->setItemInStore(shield, 0, 2);
        store->setItemInStore(helmet, 0, 3);
    }
    ~Town() {}

    void townMenu()
    {
        bool runningTownMenu = true;
        while (runningTownMenu) {
            system("cls || clear");
            cout << "\nTOWN MENU" << endl;
            cout << "1. Visit Store" << endl;
            cout << "2. See Equipment" << endl;
            cout << "3. Go back Home" << endl;
            int choice = getUserInput<int>("Enter your choice: ");

            switch (choice) {
            case 1:
                store->displayStore();
                break;
            case 2:
                player->getEquipment().displayEquipment();
                break;
            case 3:
                cout << "Leaving town..." << endl;
                runningTownMenu = false;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }
};

class Home {
private:
    Player* player;
    Town* town;
    int days;

public:
    Home(Player* player, Town* town, int days = 0) : player(player), town(town), days(days) {}
    ~Home() {}

    //make menu for the home that will have option to press 'e' to enter the equipment
    void homeMenu()
    {
        bool runningHomeMenu = true;
        while (runningHomeMenu)
        {
            system("cls || clear");
            cout << "\nHOME MENU" << endl;
            cout << "Days: " << days << endl;
            cout << "1. Go to Town" << endl;
            cout << "2. Display Stats" << endl;
            cout << "3. See Equipment" << endl;
            cout << "4. Exit Game" << endl;
            int choice = getUserInput<int>("Enter your choice: ");

            switch (choice)
            {
            case 1:
                cout << "Going to town..." << endl;
                town->townMenu();
                break;
            case 2:
                player->displayStats();
                cout << "Press any key to continue..." << endl;
                cin.ignore();
                cin.get();
                break;
            case 3:
                player->getEquipment().displayEquipment();
                break;
            case 4:
                cout << "Exiting the home menu." << endl;
                runningHomeMenu = false;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }

};

class Game {
private:
    Player* player;
    Town* town;
    Home* home;

public:
    Game() : player(new Player()), town(new Town(player, new Store())), home(new Home(player, town))
    {
        // Add some items to the player's equipment
        Item* sword = new Sword("Sword", "Common", 234, 1, 10);
        Item* bow = new Bow("Bow", "Rare", 800, 1, 8);
        Item* shield = new Shield("Shield", "Epic", 480, 1, 10);
        Item* helmet = new Helmet("Helmet", "Legendary", 1200, 1, 15);

        player->getEquipment().addItem(sword, 0, 0);
        player->getEquipment().addItem(bow, 0, 1);
        player->getEquipment().addItem(shield, 0, 2);
        player->getEquipment().addItem(helmet, 0, 3);
    }
    ~Game()
    {
        delete home;
        delete town;
        delete player;
    }

    void bootUp()
    {
        cout << "Welcome to the Game!" << endl;
        mainMenu();
    }

    void mainMenu()
    {
        bool runningMainMenu = true;
        while (runningMainMenu)
        {
            system("cls || clear");
            cout << "\nMAIN MENU" << endl;
            cout << "1. Start Game" << endl;
            cout << "2. Exit" << endl;
            int choice = getUserInput<int>("Enter your choice: ");

            switch (choice)
            {
            case 1:
                home->homeMenu();
                break;
            case 2:
                cout << "Exiting the game. Goodbye!" << endl;
                runningMainMenu = false;
                return;
            default:
                cout << "Invalid choice. Please try again." << endl;
                break;
            }
        }
    }
};

int main()
{
    Game game;
    game.bootUp();

    return 0;
}