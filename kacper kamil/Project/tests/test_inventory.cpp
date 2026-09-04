#include "inventory.hpp"

#include <cassert>
#include <memory>
#include <string>

namespace {

void test_add_and_move_item() {
    Equipment eq(2, 2);
    assert(eq.addItem(std::make_unique<Sword>("Alpha", "Common", 10, 1, 3), 0, 0));
    assert(eq.addItem(std::make_unique<Bow>("Beta", "Rare", 20, 2, 4), 0, 1));

    assert(eq.getItem(0, 0) != nullptr);
    assert(eq.getItem(0, 1) != nullptr);

    assert(eq.moveItem(0, 0, 1, 1));
    assert(eq.getItem(1, 1) != nullptr);
    assert(eq.getItem(1, 1)->getName() == "Alpha");
}

void test_sort_by_value_descending() {
    Equipment eq(2, 2);
    eq.addItem(std::make_unique<Sword>("Low", "Common", 10, 1, 3), 0, 0);
    eq.addItem(std::make_unique<Sword>("High", "Common", 100, 1, 3), 0, 1);
    eq.sortByValue();

    assert(eq.getItem(0, 0) != nullptr);
    assert(eq.getItem(0, 0)->getName() == "High");
}

void test_search_case_insensitive() {
    Equipment eq(2, 2);
    eq.addItem(std::make_unique<Helmet>("DragonHelm", "Epic", 40, 5, 15), 0, 0);
    const auto matches = eq.searchItems("dragon");

    assert(matches.size() == 1);
    assert(matches[0]->getName() == "DragonHelm");
}

void test_store_buy_item_and_money_change() {
    Player player(500, 100, 20, 1);
    Store store(2, 2);
    store.setPlayer(&player);
    store.setItemInStore(std::make_unique<Sword>("ShopSword", "Common", 200, 1, 10), 0, 0);

    const int beforeMoney = player.getMoney();
    assert(store.buyItem(0, 0));
    assert(player.getMoney() == beforeMoney - 200);

    bool found = false;
    for (int r = 0; r < player.getEquipment().getRows(); ++r) {
        for (int c = 0; c < player.getEquipment().getCols(); ++c) {
            const Item* item = player.getEquipment().getItem(r, c);
            if (item && item->getName() == "ShopSword") {
                found = true;
            }
        }
    }
    assert(found);
}

void test_inventory_full_edge_case() {
    Equipment eq(1, 1);
    assert(eq.addItem(std::make_unique<Sword>("Only", "Common", 10, 1, 3), 0, 0));
    assert(!eq.addItem(std::make_unique<Sword>("Extra", "Common", 10, 1, 3), 0, 0));
}

void test_invalid_coordinates() {
    Equipment eq(2, 2);
    assert(!eq.addItem(std::make_unique<Sword>("X", "Common", 10, 1, 3), -1, 0));
    assert(eq.getItem(5, 5) == nullptr);
    assert(!eq.moveItem(0, 0, 5, 5));
}

} // namespace

int main() {
    test_add_and_move_item();
    test_sort_by_value_descending();
    test_search_case_insensitive();
    test_store_buy_item_and_money_change();
    test_inventory_full_edge_case();
    test_invalid_coordinates();
    return 0;
}
