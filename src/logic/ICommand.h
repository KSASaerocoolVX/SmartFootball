#pragma once

#include "model/Player.h"

#include <vector>

class ICommand {
public:
    virtual ~ICommand() = default;

    // Команда читает входной список и возвращает новый результат.
    virtual std::vector<Player> execute(const std::vector<Player>& players) const = 0;
};
