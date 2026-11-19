#pragma once
#include "Item.h"
#include <memory>
#include <string>
#include <unordered_map>

class QualityRule {
public:
    virtual ~QualityRule() = default;
    virtual void update(Item& item) const = 0;
};

class NormalRule final : public QualityRule {
public: void update(Item& item) const override;
};

class AgedBrieRule final : public QualityRule {
public: void update(Item& item) const override;
};

class SulfurasRule final : public QualityRule {
public: void update(Item& item) const override;
};

class BackstageRule final : public QualityRule {
public: void update(Item& item) const override;
};

class FastAgingRule final : public QualityRule {
public: void update(Item& item) const override;
};

class RuleRegistry {
public:
    using RulePtr = std::shared_ptr<const QualityRule>;
    RuleRegistry();
    void registerRule(const std::string& name, RulePtr rule);
    const QualityRule& forItem(const std::string& name) const;
private:
    std::unordered_map<std::string, RulePtr> rules_;
    RulePtr defaultRule_;
};
