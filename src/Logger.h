#pragma once
#include "IObserver.h"

// [POO - Design Pattern: Observer] Clasa concreta care observa si scrie in log
class Logger : public IObserver {
public:
    void update(const std::string& query) override;
};