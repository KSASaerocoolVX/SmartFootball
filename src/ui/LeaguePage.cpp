#include "ui/LeaguePage.h"

#include <QFrame>
#include <QHeaderView>
#include <QLabel>
#include <QTableWidget>
#include <QVBoxLayout>
#include <algorithm>

namespace {

QTableWidgetItem* makeItem(const QString& text, Qt::Alignment align = Qt::AlignCenter) {
    auto* item = new QTableWidgetItem(text);
    item->setTextAlignment(align | Qt::AlignVCenter);
    return item;
}

}  // namespace

LeaguePage::LeaguePage(const std::vector<Team>& teams,
                       const std::vector<Player>& players,
                       QWidget* parent)
    : QWidget(parent) {
    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 18, 20, 18);

    auto* card = new QFrame(this);
    card->setObjectName("card");
    auto* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(22, 20, 22, 20);
    cardLayout->setSpacing(10);

    auto* title = new QLabel("League", card);
    title->setObjectName("pageTitle");
    auto* hint = new QLabel("Клубы лиги. Двойной клик по клубу откроет его игроков в Scouting.", card);
    hint->setObjectName("pageBody");

    // Клубы показываем по месту в таблице лиги.
    std::vector<Team> sortedTeams = teams;
    std::sort(sortedTeams.begin(), sortedTeams.end(), [](const Team& a, const Team& b) {
        return a.leaguePosition < b.leaguePosition;
    });

    auto* table = new QTableWidget(static_cast<int>(sortedTeams.size()), 6, card);
    table->setHorizontalHeaderLabels(
        {"#", "Клуб", "Код", "Игроков", "Ср. рейтинг", "Стоимость состава"});
    table->verticalHeader()->setVisible(false);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setSelectionMode(QAbstractItemView::SingleSelection);
    table->setAlternatingRowColors(true);
    table->setShowGrid(false);
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    table->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);

    for (int row = 0; row < static_cast<int>(sortedTeams.size()); ++row) {
        const Team& team = sortedTeams[row];

        int count = 0;
        double ratingSum = 0.0;
        double valueSum = 0.0;
        for (const Player& player : players) {
            if (player.teamId == team.id) {
                ++count;
                ratingSum += player.rating;
                valueSum += player.marketValueM;
            }
        }
        const double avgRating = count > 0 ? ratingSum / count : 0.0;

        auto* nameItem = makeItem(team.name, Qt::AlignLeft);
        nameItem->setData(Qt::UserRole, team.id);

        table->setItem(row, 0, makeItem(QString::number(team.leaguePosition)));
        table->setItem(row, 1, nameItem);
        table->setItem(row, 2, makeItem(team.shortName));
        table->setItem(row, 3, makeItem(QString::number(count)));
        table->setItem(row, 4, makeItem(QString::number(avgRating, 'f', 2)));
        table->setItem(row, 5, makeItem(QString("€%1M").arg(valueSum, 0, 'f', 1)));
    }

    connect(table, &QTableWidget::cellDoubleClicked, this, [this, table](int row, int) {
        const QTableWidgetItem* item = table->item(row, 1);
        if (item != nullptr) {
            emit teamActivated(item->data(Qt::UserRole).toUInt());
        }
    });

    cardLayout->addWidget(title);
    cardLayout->addWidget(hint);
    cardLayout->addWidget(table, 1);
    layout->addWidget(card, 1);
}
