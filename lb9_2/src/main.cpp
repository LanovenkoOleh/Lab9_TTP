#include "GildedRose.h"
#include <iostream>
int main() {
    std::cout << "=== Kata 2: Gilded Rose ===\n";
    std::vector<Item> items = {
        {"Normal item", 2, 10}, {"Aged Brie", 2, 0},
        {"Sulfuras, Hand of Ragnaros", 0, 80},
        {"Backstage passes to a TAFKAL80ETC concert", 5, 20},
        {"FastAging", 2, 20}
    };
    GildedRose app(items);
    for (int day = 0; day < 4; ++day) {
        std::cout << "\nDay " << day << '\n';
        for (const auto& item : items)
            std::cout << item.name << " | sellIn=" << item.sellIn
                      << " | quality=" << item.quality << '\n';
        app.updateQuality();
    }
}
