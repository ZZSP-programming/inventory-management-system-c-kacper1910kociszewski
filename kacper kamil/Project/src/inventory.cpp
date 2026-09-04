#include "inventory.hpp"

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

namespace {
std::string toLower(std::string value) {
    std::transform(value.begin(), value.end(), value.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return value;
}
} // namespace

void clearScreen() {
    std::cout << "\033[2J\033[H";
}

char readInputKey() {
#ifdef _WIN32
    return static_cast<char>(_getch());
#else
    termios oldTermios{};
    tcgetattr(STDIN_FILENO, &oldTermios);
    termios newTermios = oldTermios;
    newTermios.c_lflag &= static_cast<unsigned int>(~(ICANON | ECHO));
    tcsetattr(STDIN_FILENO, TCSANOW, &newTermios);

    char ch = 0;
    const ssize_t bytesRead = read(STDIN_FILENO, &ch, 1);
    if (bytesRead != 1) {
        ch = 0;
    }

    tcsetattr(STDIN_FILENO, TCSANOW, &oldTermios);
    return ch;
#endif
}

Item::Item(std::string name, std::string rarity, int value, int level)
    : name(std::move(name)), rarity(std::move(rarity)), value(value), level(level) {}

void Item::printNameByRarity(std::ostream& os) const {
    if (rarity == "Rare") {
        os << "\033[1;34m" << name << "\033[0m";
    } else if (rarity == "Epic") {
        os << "\033[1;35m" << name << "\033[0m";
    } else if (rarity == "Legendary") {
        os << "\033[1;33m" << name << "\033[0m";
    } else {
        os << name;
    }
}

void Item::showInfo(std::ostream& os) const {
    os << "Name: ";
    printNameByRarity(os);
    os << '\n';
    os << "Rarity: " << rarity << '\n';
    os << "Worth: " << value << '\n';
    os << "Level: " << level << '\n';
}

const std::string& Item::getName() const { return name; }
const std::string& Item::getRarity() const { return rarity; }
int Item::getValue() const { return value; }
int Item::getLevel() const { return level; }

Weapon::Weapon(std::string name, std::string rarity, int value, int level, int damage)
    : Item(std::move(name), std::move(rarity), value, level), damage(damage) {}

void Weapon::showInfo(std::ostream& os) const {
    Item::showInfo(os);
    os << "Damage: " << damage << '\n';
}

int Weapon::getDamage() const { return damage; }

Armor::Armor(std::string name, std::string rarity, int value, int level, int armor)
    : Item(std::move(name), std::move(rarity), value, level), armor(armor) {}

void Armor::showInfo(std::ostream& os) const {
    Item::showInfo(os);
    os << "Armor: " << armor << '\n';
}

int Armor::getArmor() const { return armor; }

Sword::Sword(std::string name, std::string rarity, int value, int level, int damage)
    : Weapon(std::move(name), std::move(rarity), value, level, damage) {}

Bow::Bow(std::string name, std::string rarity, int value, int level, int damage)
    : Weapon(std::move(name), std::move(rarity), value, level, damage) {}

Shield::Shield(std::string name, std::string rarity, int value, int level, int armor)
    : Armor(std::move(name), std::move(rarity), value, level, armor) {}

Helmet::Helmet(std::string name, std::string rarity, int value, int level, int armor)
    : Armor(std::move(name), std::move(rarity), value, level, armor) {}

Chestplate::Chestplate(std::string name, std::string rarity, int value, int level, int armor)
    : Armor(std::move(name), std::move(rarity), value, level, armor) {}

Leggings::Leggings(std::string name, std::string rarity, int value, int level, int armor)
    : Armor(std::move(name), std::move(rarity), value, level, armor) {}

Equipment::Equipment(int rows, int cols, int level)
    : rows(rows), cols(cols), level(level), grid(rows) {
    for (auto& rowItems : grid) {
        rowItems.resize(cols);
    }
}

int Equipment::getRows() const { return rows; }
int Equipment::getCols() const { return cols; }

bool Equipment::inBounds(int row, int col) const {
    return row >= 0 && row < rows && col >= 0 && col < cols;
}

const Item* Equipment::getItem(int row, int col) const {
    if (!inBounds(row, col)) {
        return nullptr;
    }
    return grid[row][col].get();
}

Item* Equipment::getItem(int row, int col) {
    if (!inBounds(row, col)) {
        return nullptr;
    }
    return grid[row][col].get();
}

bool Equipment::addItem(std::unique_ptr<Item> item, int row, int col) {
    if (!item || !inBounds(row, col)) {
        return false;
    }

    if (!grid[row][col]) {
        grid[row][col] = std::move(item);
        return true;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!grid[i][j]) {
                grid[i][j] = std::move(item);
                return true;
            }
        }
    }

    return false;
}

std::unique_ptr<Item> Equipment::takeItem(int row, int col) {
    if (!inBounds(row, col)) {
        return nullptr;
    }
    std::unique_ptr<Item> item = std::move(grid[row][col]);
    grid[row][col] = nullptr;
    return item;
}

bool Equipment::deleteItem(int row, int col) {
    if (!inBounds(row, col) || !grid[row][col]) {
        return false;
    }
    grid[row][col].reset();
    return true;
}

bool Equipment::moveItem(int row_of_item, int col_of_item, int row_to_swap, int col_to_swap) {
    if (!inBounds(row_of_item, col_of_item) || !inBounds(row_to_swap, col_to_swap)) {
        return false;
    }
    std::swap(grid[row_of_item][col_of_item], grid[row_to_swap][col_to_swap]);
    return true;
}

bool Equipment::findPlaceForItem() const {
    return returnFreeSlot().has_value();
}

std::optional<std::pair<int, int>> Equipment::returnFreeSlot() const {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (!grid[i][j]) {
                return std::make_pair(i, j);
            }
        }
    }
    return std::nullopt;
}

std::vector<const Item*> Equipment::searchItems(std::string name) const {
    std::vector<const Item*> items;
    const std::string searchName = toLower(std::move(name));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j]) {
                std::string itemName = toLower(grid[i][j]->getName());
                if (itemName.find(searchName) != std::string::npos) {
                    items.push_back(grid[i][j].get());
                }
            }
        }
    }

    return items;
}

void Equipment::sortByComparator(const std::function<bool(const std::unique_ptr<Item>&, const std::unique_ptr<Item>&)>& comparator) {
    std::vector<std::unique_ptr<Item>> sortedItems;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j]) {
                sortedItems.push_back(std::move(grid[i][j]));
            }
        }
    }

    std::sort(sortedItems.begin(), sortedItems.end(), comparator);

    int index = 0;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (index < static_cast<int>(sortedItems.size())) {
                grid[i][j] = std::move(sortedItems[index++]);
            } else {
                grid[i][j] = nullptr;
            }
        }
    }
}

void Equipment::sortByLevel() {
    sortByComparator([](const std::unique_ptr<Item>& a, const std::unique_ptr<Item>& b) {
        return a->getLevel() > b->getLevel();
    });
}

void Equipment::sortByRarity() {
    static const std::unordered_map<std::string, int> rarityValues = {
        {"Common", 0},
        {"Rare", 1},
        {"Epic", 2},
        {"Legendary", 3},
    };

    sortByComparator([&](const std::unique_ptr<Item>& a, const std::unique_ptr<Item>& b) {
        const int aValue = rarityValues.count(a->getRarity()) ? rarityValues.at(a->getRarity()) : -1;
        const int bValue = rarityValues.count(b->getRarity()) ? rarityValues.at(b->getRarity()) : -1;
        return aValue > bValue;
    });
}

void Equipment::sortByValue() {
    sortByComparator([](const std::unique_ptr<Item>& a, const std::unique_ptr<Item>& b) {
        return a->getValue() > b->getValue();
    });
}

void Equipment::displayEquipmentForMoving(int row, int col, const std::string& title, const std::string& actionHint) const {
    clearScreen();
    std::cout << '<' << title << '>' << std::endl;
    std::cout << "+-----------------------------------------------+" << std::endl;

    for (int i = 0; i < rows; ++i) {
        std::cout << '|';
        for (int j = 0; j < cols; ++j) {
            const std::string itemName = grid[i][j] ? grid[i][j]->getName() : "    ";
            if (i == row && j == col) {
                std::cout << " [>" << itemName << "<]\t";
            } else {
                std::cout << " [ " << itemName << " ]\t";
            }
        }
        std::cout << "\t|" << std::endl;
    }

    std::cout << "+-----------------------------------------------+" << std::endl;
    std::cout << actionHint << std::endl;

    if (grid[row][col]) {
        grid[row][col]->showInfo();
    } else {
        std::cout << "No item at this position." << std::endl;
    }
}

std::pair<int, int> Equipment::moveInInventory(const std::string& title, const std::string& actionHint) const {
    int currentIndexRow = 0;
    int currentIndexCol = 0;

    displayEquipmentForMoving(currentIndexRow, currentIndexCol, title, actionHint);

    while (true) {
        const char ch = readInputKey();
        switch (ch) {
        case 'a':
            if (currentIndexCol > 0) {
                --currentIndexCol;
            }
            break;
        case 'd':
            if (currentIndexCol < cols - 1) {
                ++currentIndexCol;
            }
            break;
        case 'w':
            if (currentIndexRow > 0) {
                --currentIndexRow;
            }
            break;
        case 's':
            if (currentIndexRow < rows - 1) {
                ++currentIndexRow;
            }
            break;
        case 'q':
            return std::make_pair(-1, -1);
        case ' ':
            if (grid[currentIndexRow][currentIndexCol]) {
                return std::make_pair(currentIndexRow, currentIndexCol);
            }
            break;
        default:
            break;
        }

        displayEquipmentForMoving(currentIndexRow, currentIndexCol, title, actionHint);
    }
}

void Equipment::displayEquipment(const std::string& title) {
    bool running = true;

    while (running) {
        clearScreen();
        std::cout << '<' << title << '>' << std::endl;
        std::cout << "+-----------------------------------------------+" << std::endl;
        for (int i = 0; i < rows; ++i) {
            std::cout << '|';
            for (int j = 0; j < cols; ++j) {
                std::cout << " [" << (grid[i][j] ? grid[i][j]->getName() : "    ") << "] ";
            }
            std::cout << "\t|" << std::endl;
        }
        std::cout << "+-----------------------------------------------+" << std::endl;

        std::cout << "1. Check item" << std::endl;
        std::cout << "2. Move/Swap items" << std::endl;
        std::cout << "3. Sort by Level" << std::endl;
        std::cout << "4. Sort by Rarity" << std::endl;
        std::cout << "5. Sort by Value" << std::endl;
        std::cout << "6. Search for an item" << std::endl;
        std::cout << "7. Exit" << std::endl;

        const int choice = getUserInput<int>("Enter your choice: ");
        switch (choice) {
        case 1: {
            moveInInventory(title);
            break;
        }
        case 2: {
            const auto selectedPosition = moveInInventory(title);
            if (selectedPosition.first != -1 && selectedPosition.second != -1) {
                const auto newPosition = moveInInventory(title);
                if (newPosition.first != -1 && newPosition.second != -1) {
                    moveItem(selectedPosition.first, selectedPosition.second, newPosition.first, newPosition.second);
                }
            }
            break;
        }
        case 3:
            sortByLevel();
            break;
        case 4:
            sortByRarity();
            break;
        case 5:
            sortByValue();
            break;
        case 6: {
            std::string name;
            std::cout << "Enter the name of the item you are looking for: ";
            std::cin >> name;
            const auto items = searchItems(name);
            if (items.empty()) {
                std::cout << "No items found" << std::endl;
            } else {
                std::cout << "Items found:" << std::endl;
                for (const Item* item : items) {
                    item->showInfo();
                }
            }
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        }
        case 7:
            running = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
}

Player::Player(int money, int health, int armour, int level)
    : money(money), health(health), armour(armour), level(level), equipment() {}

void Player::displayStats() const {
    clearScreen();
    std::cout << "<PLAYER STATS>" << std::endl;
    std::cout << "+-------------------------+" << std::endl;
    std::cout << "Money: " << money << std::endl;
    std::cout << "Health: " << health << std::endl;
    std::cout << "Armour: " << armour << std::endl;
    std::cout << "Level: " << level << std::endl;
    std::cout << "+-------------------------+" << std::endl;
}

int Player::getMoney() const { return money; }
int Player::increaseMoney(int amount) { return money += amount; }
int Player::decreaseMoney(int amount) { return money -= amount; }
Equipment& Player::getEquipment() { return equipment; }
const Equipment& Player::getEquipment() const { return equipment; }

Store::Store(int rows, int cols) : equipment(rows, cols), player(nullptr) {}

void Store::setPlayer(Player* playerRef) { player = playerRef; }

bool Store::setItemInStore(std::unique_ptr<Item> item, int row, int col) {
    return equipment.addItem(std::move(item), row, col);
}

const Item* Store::getItemFromStore(int row, int col) const {
    return equipment.getItem(row, col);
}

bool Store::buyItem(int row, int col) {
    if (!player) {
        return false;
    }

    const Item* selectedItem = equipment.getItem(row, col);
    if (!selectedItem) {
        std::cout << "There is no item in this slot." << std::endl;
        return false;
    }

    const int itemValue = selectedItem->getValue();
    if (player->getMoney() < itemValue) {
        std::cout << "You don't have enough money to buy " << selectedItem->getName() << "." << std::endl;
        return false;
    }

    auto itemToMove = equipment.takeItem(row, col);
    if (!itemToMove) {
        return false;
    }

    auto freeSlot = player->getEquipment().returnFreeSlot();
    if (!freeSlot) {
        std::cout << "Failed to add item to your inventory. Your inventory may be full." << std::endl;
        equipment.addItem(std::move(itemToMove), row, col);
        return false;
    }

    player->decreaseMoney(itemValue);
    if (player->getEquipment().addItem(std::move(itemToMove), freeSlot->first, freeSlot->second)) {
        std::cout << "You bought an item for " << itemValue << " gold." << std::endl;
        return true;
    }

    player->increaseMoney(itemValue);
    std::cout << "Failed to add item to your inventory. Your inventory may be full." << std::endl;
    return false;
}

std::pair<int, int> Store::moveInStore() const {
    return equipment.moveInInventory("STORE", "Use 'WASD' to move, 'Space' to select, 'Q' to quit");
}

void Store::displayStore() {
    bool runningStore = true;

    while (runningStore) {
        clearScreen();
        std::cout << "<STORE>" << std::endl;
        std::cout << "+-----------------------------------------------+" << std::endl;
        for (int i = 0; i < equipment.getRows(); ++i) {
            std::cout << '|';
            for (int j = 0; j < equipment.getCols(); ++j) {
                const Item* item = equipment.getItem(i, j);
                std::cout << " [" << (item ? item->getName() : "    ") << "] ";
            }
            std::cout << "\t|" << std::endl;
        }
        std::cout << "+-----------------------------------------------+" << std::endl;

        std::cout << "1. Check items" << std::endl;
        std::cout << "2. Buy an item" << std::endl;
        std::cout << "3. Exit" << std::endl;

        const int choice = getUserInput<int>("Enter your choice: ");
        switch (choice) {
        case 1:
            moveInStore();
            break;
        case 2: {
            const auto selectedPosition = moveInStore();
            if (selectedPosition.first != -1 && selectedPosition.second != -1) {
                buyItem(selectedPosition.first, selectedPosition.second);
                std::cout << "Press Enter to continue..." << std::endl;
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cin.get();
            }
            break;
        }
        case 3:
            runningStore = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
}

Town::Town(Player& player, Store& store) : player(player), store(store) {
    store.setPlayer(&player);

    store.setItemInStore(std::make_unique<Sword>("Sword", "Common", 100, 1, 10), 0, 0);
    store.setItemInStore(std::make_unique<Bow>("Bow", "Rare", 200, 1, 8), 0, 1);
    store.setItemInStore(std::make_unique<Shield>("Shield", "Epic", 100, 1, 10), 0, 2);
    store.setItemInStore(std::make_unique<Helmet>("Helmet", "Legendary", 100, 1, 15), 0, 3);
}

void Town::townMenu() {
    bool runningTownMenu = true;
    while (runningTownMenu) {
        clearScreen();
        std::cout << "\nTOWN MENU" << std::endl;
        std::cout << "1. Visit Store" << std::endl;
        std::cout << "2. See Equipment" << std::endl;
        std::cout << "3. Go back Home" << std::endl;

        const int choice = getUserInput<int>("Enter your choice: ");
        switch (choice) {
        case 1:
            store.displayStore();
            break;
        case 2:
            player.getEquipment().displayEquipment("EQUIPMENT");
            break;
        case 3:
            runningTownMenu = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
}

Home::Home(Player& player, Town& town, int days) : player(player), town(town), days(days) {}

void Home::homeMenu() {
    bool runningHomeMenu = true;
    while (runningHomeMenu) {
        clearScreen();
        std::cout << "\nHOME MENU" << std::endl;
        std::cout << "Days: " << days << std::endl;
        std::cout << "1. Go to Town" << std::endl;
        std::cout << "2. Display Stats" << std::endl;
        std::cout << "3. See Equipment" << std::endl;
        std::cout << "4. Exit Game" << std::endl;

        const int choice = getUserInput<int>("Enter your choice: ");
        switch (choice) {
        case 1:
            town.townMenu();
            break;
        case 2:
            player.displayStats();
            std::cout << "Press Enter to continue..." << std::endl;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            break;
        case 3:
            player.getEquipment().displayEquipment("EQUIPMENT");
            break;
        case 4:
            runningHomeMenu = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
}

Game::Game()
    : player(std::make_unique<Player>()),
      store(std::make_unique<Store>()),
      town(std::make_unique<Town>(*player, *store)),
      home(std::make_unique<Home>(*player, *town)) {
    player->getEquipment().addItem(std::make_unique<Sword>("Sword", "Common", 234, 1, 10), 0, 0);
    player->getEquipment().addItem(std::make_unique<Bow>("Bow", "Rare", 800, 1, 8), 0, 1);
    player->getEquipment().addItem(std::make_unique<Shield>("Shield", "Epic", 480, 1, 10), 0, 2);
    player->getEquipment().addItem(std::make_unique<Helmet>("Helmet", "Legendary", 1200, 1, 15), 0, 3);
}

void Game::bootUp() {
    std::cout << "Welcome to the Game!" << std::endl;
    mainMenu();
}

void Game::mainMenu() {
    bool runningMainMenu = true;
    while (runningMainMenu) {
        clearScreen();
        std::cout << "\nMAIN MENU" << std::endl;
        std::cout << "1. Start Game" << std::endl;
        std::cout << "2. Exit" << std::endl;

        const int choice = getUserInput<int>("Enter your choice: ");
        switch (choice) {
        case 1:
            home->homeMenu();
            break;
        case 2:
            runningMainMenu = false;
            break;
        default:
            std::cout << "Invalid choice. Please try again." << std::endl;
            break;
        }
    }
}
