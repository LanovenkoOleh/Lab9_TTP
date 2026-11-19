#include "Item.h"
#include <vector>

void updateQualityBefore(std::vector<Item>& items) {
    for (auto& item : items) {

        if (item.name == "Sulfuras, Hand of Ragnaros") continue;

        if (item.name == "Aged Brie") {

            --item.sellIn;

            if (item.quality < 50) ++item.quality;

            if (item.sellIn < 0 && item.quality < 50) ++item.quality;

        } 
        else if (item.name == "Backstage passes to a TAFKAL80ETC concert") {

            int add = item.sellIn <= 5 ? 3 : (item.sellIn <= 10 ? 2 : 1);

            --item.sellIn;

            if (item.sellIn < 0) item.quality = 0;

            else { item.quality += add; if (item.quality > 50) item.quality = 50; 
            }
        } 
        else {
            --item.sellIn;

            item.quality -= item.sellIn < 0 ? 2 : 1;

            if (item.quality < 0) item.quality = 0;

        }
    }
}
