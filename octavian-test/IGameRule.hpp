#pragma once 

#include <vector>

class IGameRule {
public:
	virtual int64_t calculateScore(const std::vector<ReelSymbol>& values) = 0;
};

class GameRuleMaxConsecutiveElements : public IGameRule {
public:
    int64_t calculateScore(const std::vector<ReelSymbol>& values) override {
        if (values.empty()) return 0;

        int maxCount = 1; // Минимум одна последовательность
        int currentCount = maxCount;

        for (size_t i = 1; i < values.size(); ++i) {
            if (values[i].getId() == values[i - 1].getId()) {
                ++currentCount;
                maxCount = std::max(maxCount, currentCount);
            }
            else {
                currentCount = 1;
            }
        }

        return maxCount > 1 ? static_cast<int64_t>(std::pow(5, maxCount)) : -10ll;
	}
};