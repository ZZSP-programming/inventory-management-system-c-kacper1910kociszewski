#pragma once

#include <algorithm>
#include <cctype>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

template <typename T>
T getUserInput(const std::string& prompt) {
    T value;
    while (true) {
        std::cout << prompt;
        if (!(std::cin >> value)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please try again." << std::endl;
        } else {
            return value;
        }
    }
}

void clearScreen();
char readInputKey();

class Item {
protected:
    std::string name;
    std::string rarity;
    int value;
    int level;

public:
    Item(std::string name = "none", std::string rarity = "none", int value = 0, int level = 0);
    virtual ~Item() = default;

    virtual void showInfo(std::ostream& os = std::cout) const;

    const std::string& getName() const;
    const std::string& getRarity() const;
    int getValue() const;
    int getLevel() const;

protected:
    void printNameByRarity(std::ostream& os) const;
};

class Weapon : public Item {
public:
    Weapon(std::string name = "Weapon", std::string rarity = "Common", int value = 100, int level = 0, int damage = 10);

    void showInfo(std::ostream& os = std::cout) const override;
    int getDamage() const;

protected:
    int damage;
};

class Armor : public Item {
public:
    Armor(std::string name = "Armor", std::string rarity = "Common", int value = 100, int level = 0, int armor = 10);

    void showInfo(std::ostream& os = std::cout) const override;
    int getArmor() const;

protected:
    int armor;
};

class Sword : public Weapon {
public:
    Sword(std::string name = "Sword", std::string rarity = "Common", int value = 100, int level = 0, int damage = 10);
};

class Bow : public Weapon {
public:
    Bow(std::string name = "Bow", std::string rarity = "Common", int value = 200, int level = 0, int damage = 8);
};

class Shield : public Armor {
public:
    Shield(std::string name = "Shield", std::string rarity = "Common", int value = 100, int level = 0, int armor = 10);
};

class Helmet : public Armor {
public:
    Helmet(std::string name = "Helmet", std::string rarity = "Common", int value = 100, int level = 0, int armor = 15);
};

class Chestplate : public Armor {
public:
    Chestplate(std::string name = "Chestplate", std::string rarity = "Common", int value = 100, int level = 0, int armor = 25);
};

class Leggings : public Armor {
public:
    Leggings(std::string name = "Leggings", std::string rarity = "Common", int value = 100, int level = 0, int armor = 20);
};

class Equipment {
public:
    Equipment(int rows = 4, int cols = 5, int level = 1);

    int getRows() const;
    int getCols() const;

    const Item* getItem(int row, int col) const;
    Item* getItem(int row, int col);

    bool addItem(std::unique_ptr<Item> item, int row, int col);
    std::unique_ptr<Item> takeItem(int row, int col);
    bool deleteItem(int row, int col);
    bool moveItem(int row_of_item, int col_of_item, int row_to_swap, int col_to_swap);

    bool findPlaceForItem() const;
    std::optional<std::pair<int, int>> returnFreeSlot() const;

    std::vector<const Item*> searchItems(std::string name) const;

    void sortByLevel();
    void sortByRarity();
    void sortByValue();

    std::pair<int, int> moveInInventory(const std::string& title = "EQUIPMENT", const std::string& actionHint = "Use 'WASD' to move, 'Space' to select, 'Q' to quit") const;
    void displayEquipment(const std::string& title = "EQUIPMENT");

private:
    int rows;
    int cols;
    int level;
    std::vector<std::vector<std::unique_ptr<Item>>> grid;

    bool inBounds(int row, int col) const;
    void sortByComparator(const std::function<bool(const std::unique_ptr<Item>&, const std::unique_ptr<Item>&)>& comparator);
    void displayEquipmentForMoving(int row, int col, const std::string& title, const std::string& actionHint) const;
};

class Player {
public:
    Player(int money = 1000, int health = 100, int armour = 20, int level = 1);

    void displayStats() const;

    int getMoney() const;
    int increaseMoney(int amount);
    int decreaseMoney(int amount);

    Equipment& getEquipment();
    const Equipment& getEquipment() const;

private:
    int money;
    int health;
    int armour;
    int level;
    Equipment equipment;
};

class Store {
public:
    Store(int rows = 4, int cols = 5);

    void setPlayer(Player* playerRef);
    bool setItemInStore(std::unique_ptr<Item> item, int row, int col);

    const Item* getItemFromStore(int row, int col) const;

    bool buyItem(int row, int col);
    void displayStore();

private:
    Equipment equipment;
    Player* player;

    std::pair<int, int> moveInStore() const;
};

class Town {
public:
    Town(Player& player, Store& store);

    void townMenu();

private:
    Player& player;
    Store& store;
};

class Home {
public:
    Home(Player& player, Town& town, int days = 0);

    void homeMenu();

private:
    Player& player;
    Town& town;
    int days;
};

class Game {
public:
    Game();

    void bootUp();

private:
    std::unique_ptr<Player> player;
    std::unique_ptr<Store> store;
    std::unique_ptr<Town> town;
    std::unique_ptr<Home> home;

    void mainMenu();
};
