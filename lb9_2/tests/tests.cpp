#include "GildedRose.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>


static int passed = 0;

#define CHECK(expr) do { if (!(expr)) throw std::runtime_error(std::string("FAILED: ") + #expr + " at line " + std::to_string(__LINE__)); ++passed; } while(0)

static Item next(Item item) { std::vector<Item> v{item}; GildedRose g(v); g.updateQuality(); return v[0];
}

struct CustomRule : QualityRule {

    void update(Item& item) const override { item.quality = 17;
    }

};

int main() {

    try {
        { auto i = next({"normal", 5, 10}); CHECK(i.sellIn == 4); CHECK(i.quality == 9); }
        { auto i = next({"normal", 0, 10}); CHECK(i.sellIn == -1); CHECK(i.quality == 8); }
        CHECK(next({"normal", -3, 0}).quality == 0);
        { auto i = next({"Aged Brie", 2, 10}); CHECK(i.quality == 11); CHECK(i.sellIn == 1); }
        CHECK(next({"Aged Brie", 0, 10}).quality == 12);
        CHECK(next({"Aged Brie", 0, 49}).quality == 50);
        { auto i = next({"Sulfuras, Hand of Ragnaros", 0, 80}); CHECK(i.quality == 80); CHECK(i.sellIn == 0); }
        CHECK(next({"Backstage passes to a TAFKAL80ETC concert", 11, 20}).quality == 21);
        CHECK(next({"Backstage passes to a TAFKAL80ETC concert", 10, 20}).quality == 22);
        CHECK(next({"Backstage passes to a TAFKAL80ETC concert", 5, 20}).quality == 23);
        CHECK(next({"Backstage passes to a TAFKAL80ETC concert", 1, 20}).quality == 23);
        CHECK(next({"Backstage passes to a TAFKAL80ETC concert", 0, 20}).quality == 0);
        CHECK(next({"Backstage passes to a TAFKAL80ETC concert", 5, 49}).quality == 50);
        CHECK(next({"FastAging", 3, 10}).quality == 8);
        CHECK(next({"FastAging", 0, 10}).quality == 6);
        CHECK(next({"FastAging", -1, 2}).quality == 0);
        { std::vector<Item> items{{"normal", 1, 8}, {"Aged Brie", 1, 8}};
          GildedRose g(items); g.updateQuality(); CHECK(items[0].quality == 7); CHECK(items[1].quality == 9); }
        { RuleRegistry registry; registry.registerRule("Custom", std::make_shared<CustomRule>());
          std::vector<Item> items{{"Custom", 1, 1}}; GildedRose g(items, registry);
          g.updateQuality(); CHECK(items[0].quality == 17); }
        { RuleRegistry registry; bool thrown = false;
          try { registry.registerRule("Bad", nullptr); } catch (const std::invalid_argument&) { thrown = true; }
          CHECK(thrown); }
        std::cout << "ALL TESTS PASSED: " << passed << " assertions\n";
        return 0;
    } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
