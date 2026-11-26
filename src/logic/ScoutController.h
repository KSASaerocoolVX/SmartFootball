#pragma once

#include "logic/commands/SortCommand.h"

#include <optional>

class ScoutController {
public:
    explicit ScoutController(std::vector<Player> players = {});

    void setPlayers(std::vector<Player> players);
    const std::vector<Player>& players() const;

    const std::vector<Player>& execute(const ICommand& command);
    const std::vector<Player>& find(const QString& query);
    const std::vector<Player>& filter(std::optional<long long> teamId = std::nullopt,
                                      const QString& position = {});
    const std::vector<Player>& sort(SortField field,
                                    SortOrder order = SortOrder::Ascending);
    const std::vector<Player>& reset();

private:
    std::vector<Player> m_originalPlayers;
    std::vector<Player> m_players;
};
