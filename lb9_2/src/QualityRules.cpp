#include "QualityRules.h"
#include <algorithm>
#include <stdexcept>

namespace {

void decrease(Item& item, int amount) { item.quality = std::max(0, item.quality - amount); }

void increase(Item& item, int amount) { item.quality = std::min(50, item.quality + amount); }

}

void NormalRule::update(Item& item) const {

    --item.sellIn;

    decrease(item, item.sellIn < 0 ? 2 : 1);
}

void AgedBrieRule::update(Item& item) const {

    --item.sellIn;

    increase(item, item.sellIn < 0 ? 2 : 1);
}
void SulfurasRule::update(Item&) const { /* legendary item never changes */ }

void BackstageRule::update(Item& item) const {

    const int increaseBy = item.sellIn <= 5 ? 3 : (item.sellIn <= 10 ? 2 : 1);
    --item.sellIn;
    if (item.sellIn < 0) item.quality = 0;
    else increase(item, increaseBy);
}

void FastAgingRule::update(Item& item) const {
    --item.sellIn;
    decrease(item, item.sellIn < 0 ? 4 : 2);
}

RuleRegistry::RuleRegistry() : defaultRule_(std::make_shared<NormalRule>()) {
    registerRule("Aged Brie", std::make_shared<AgedBrieRule>());
    registerRule("Sulfuras, Hand of Ragnaros", std::make_shared<SulfurasRule>());
    registerRule("Backstage passes to a TAFKAL80ETC concert", std::make_shared<BackstageRule>());
    registerRule("FastAging", std::make_shared<FastAgingRule>());
}

void RuleRegistry::registerRule(const std::string& name, RulePtr rule) {
    if (!rule) throw std::invalid_argument("Rule must not be null");
    rules_[name] = std::move(rule);
}

const QualityRule& RuleRegistry::forItem(const std::string& name) const {
    const auto it = rules_.find(name);
    return *(it == rules_.end() ? defaultRule_ : it->second);
}
