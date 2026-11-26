#include "logic/commands/FilterCommand.h"

#include "model/Team.h"

#include <algorithm>
#include <iterator>
#include <stdexcept>

FilterCommand::FilterCommand(std::optional<long long> teamId, const QString& position)
    : m_teamId(teamId), m_position(position.trimmed()) {
    if (m_teamId && !Team::isValidId(*m_teamId)) {
        throw std::invalid_argument("Invalid team ID");
    }
    if (!m_position.isEmpty() && !Player::isValidPosition(m_position)) {
        throw std::invalid_argument("Invalid player position");
    }
}

std::vector<Player> FilterCommand::execute(const std::vector<Player>& players) const {
    if (!m_teamId && m_position.isEmpty()) {
        return players;
    }

    std::vector<Player> result;
    std::copy_if(players.begin(), players.end(), std::back_inserter(result),
                 [this](const Player& player) {
                     return (!m_teamId || player.teamId == *m_teamId) &&
                            (m_position.isEmpty() ||
                             player.position.trimmed().compare(m_position, Qt::CaseInsensitive) == 0);
                 });
    return result;
}
