#pragma once

#include "logic/ICommand.h"

#include <optional>

class FilterCommand : public ICommand {
public:
    FilterCommand(std::optional<long long> teamId, const QString& position);

    std::vector<Player> execute(const std::vector<Player>& players) const override;

private:
    std::optional<long long> m_teamId;
    QString m_position;
};
