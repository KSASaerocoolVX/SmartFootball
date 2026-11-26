#pragma once

#include "logic/ScoutController.h"
#include "model/Team.h"

#include <QWidget>
#include <map>
#include <vector>

class QComboBox;
class QLabel;
class QLineEdit;
class QTableWidget;

/**
 * @brief Страница «Scouting»: список игроков с поиском, фильтрами и сортировкой.
 *
 * Саму выборку делает ScoutController (src/logic), страница только
 * собирает параметры из полей и показывает результат в таблице.
 */
class ScoutingPage : public QWidget {
    Q_OBJECT

public:
    ScoutingPage(const std::vector<Team>& teams,
                 const std::vector<Player>& players,
                 QWidget* parent = nullptr);

    // Сбросить фильтры и показать игроков одного клуба.
    void showTeam(unsigned int teamId);

private:
    void applyFilters();
    void resetFilters();
    void sortByColumn(int column);
    void fillTable(const std::vector<Player>& players);

    ScoutController m_scout;
    std::map<unsigned int, QString> m_teamNames;
    int m_totalPlayers = 0;

    QLineEdit* m_search = nullptr;
    QComboBox* m_teamBox = nullptr;
    QComboBox* m_positionBox = nullptr;
    QComboBox* m_sortFieldBox = nullptr;
    QComboBox* m_sortOrderBox = nullptr;
    QTableWidget* m_table = nullptr;
    QLabel* m_countLabel = nullptr;
};
