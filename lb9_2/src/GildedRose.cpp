#include "GildedRose.h"

GildedRose::GildedRose(std::vector<Item>& items) : items(items), rules_(&ownedRules_) {}

GildedRose::GildedRose(std::vector<Item>& items, const RuleRegistry& rules)
    : items(items), rules_(&rules) {}


void GildedRose::updateQuality() {
    for (auto& item : items) rules_->forItem(item.name).update(item);
}
