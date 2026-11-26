#pragma once

#include "model/Player.h"
#include "model/Team.h"

#include <QWidget>
#include <vector>

/**
 * @brief Страница «League»: таблица клубов лиги с короткой сводкой по составу.
 *
 * Двойной клик по клубу отправляет сигнал teamActivated, и окно открывает
 * игроков этого клуба на странице Scouting.
 */
class LeaguePage : public QWidget {
    Q_OBJECT

public:
    LeaguePage(const std::vector<Team>& teams,
               const std::vector<Player>& players,
               QWidget* parent = nullptr);

signals:
    void teamActivated(unsigned int teamId);
};
