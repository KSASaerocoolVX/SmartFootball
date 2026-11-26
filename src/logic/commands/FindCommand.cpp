#include "logic/commands/FindCommand.h"

#include <algorithm>
#include <iterator>

FindCommand::FindCommand(const QString& query) : m_query(query.trimmed()) {
}

std::vector<Player> FindCommand::execute(const std::vector<Player>& players) const {
    if (m_query.isEmpty()) {
        return players;
    }

    std::vector<Player> result;
    std::copy_if(players.begin(), players.end(), std::back_inserter(result),
                 [this](const Player& player) {
                     return player.name.contains(m_query, Qt::CaseInsensitive);
                 });
    return result;
}
