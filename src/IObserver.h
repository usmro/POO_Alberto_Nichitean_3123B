#pragma once
#include <string>

// [POO - Design Pattern: Observer] Interfata pentru observatori
class IObserver {
public:
    virtual ~IObserver() = default;
    virtual void update(const std::string& query) = 0;
};