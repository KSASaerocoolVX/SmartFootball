#include "logic/ScoutController.h"

#include "logic/commands/FilterCommand.h"
#include "logic/commands/FindCommand.h"

#include <utility>

ScoutController::ScoutController(std::vector<Player> players)
    : m_originalPlayers(std::move(players)), m_players(m_originalPlayers) {
}

void ScoutController::setPlayers(std::vector<Player> players) {
    auto currentPlayers = players;
    m_originalPlayers = std::move(players);
    m_players = std::move(currentPlayers);
}

const std::vector<Player>& ScoutController::players() const {
    return m_players;
}

const std::vector<Player>& ScoutController::execute(const ICommand& command) {
    m_players = command.execute(m_players);
    return m_players;
}

const std::vector<Player>& ScoutController::find(const QString& query) {
    return execute(FindCommand(query));
}

const std::vector<Player>& ScoutController::filter(std::optional<long long> teamId,
                                                   const QString& position) {
    return execute(FilterCommand(teamId, position));
}

const std::vector<Player>& ScoutController::sort(SortField field, SortOrder order) {
    return execute(SortCommand(field, order));
}

const std::vector<Player>& ScoutController::reset() {
    m_players = m_originalPlayers;
    return m_players;
}
