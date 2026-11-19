#pragma once
#include "Item.h"
#include "QualityRules.h"
#include <vector>


class GildedRose {
public:
    std::vector<Item>& items;
    explicit GildedRose(std::vector<Item>& items);
    GildedRose(std::vector<Item>& items, const RuleRegistry& rules);
    void updateQuality();
private:
    RuleRegistry ownedRules_;
    const RuleRegistry* rules_;
};
