#pragma once

#include "model/Player.h"
#include "model/Team.h"

#include <vector>

/**
 * @brief Временные демо-данные для проверки интерфейса (неделя 2).
 *
 * Значения примерные. Когда появятся LeagueRepository и XML-хранилище
 * (участник 1), окно будет брать данные оттуда, а этот файл можно удалить.
 */
namespace DemoData {

std::vector<Team> teams();
std::vector<Player> players();

}  // namespace DemoData
