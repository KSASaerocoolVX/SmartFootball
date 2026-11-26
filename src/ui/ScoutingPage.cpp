#include "ui/ScoutingPage.h"

#include <QComboBox>
#include <QFrame>
#include <QHBoxLayout>
#include <QHeaderView>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTableWidget>
#include <QVBoxLayout>
#include <optional>
#include <stdexcept>

namespace {

enum Column { ColName, ColTeam, ColPosition, ColRating, ColValue, ColGoals, ColAssists, ColTotal };

QTableWidgetItem* makeItem(const QString& text, Qt::Alignment align = Qt::AlignCenter) {
    auto* item = new QTableWidgetItem(text);
    item->setTextAlignment(align | Qt::AlignVCenter);
    return item;
}

// Цвет рейтинга как в FM: зелёный — сильный игрок, жёлтый — средний, оранжевый — слабее.
QColor ratingColor(double rating) {
    if (rating >= 7.3) {
        return QColor("#4ade80");
    }
    if (rating >= 6.9) {
        return QColor("#facc15");
    }
    return QColor("#fb923c");
}

// Какой столбец таблицы соответствует полю сортировки (и наоборот).
int columnForField(SortField field) {
    switch (field) {
    case SortField::Name: return ColName;
    case SortField::Rating: return ColRating;
    case SortField::MarketValue: return ColValue;
    case SortField::Goals: return ColGoals;
    case SortField::Assists: return ColAssists;
    }
    return ColRating;
}

std::optional<SortField> fieldForColumn(int column) {
    switch (column) {
    case ColName: return SortField::Name;
    case ColRating: return SortField::Rating;
    case ColValue: return SortField::MarketValue;
    case ColGoals: return SortField::Goals;
    case ColAssists: return SortField::Assists;
    default: return std::nullopt;
    }
}

}  // namespace

ScoutingPage::ScoutingPage(const std::vector<Team>& teams,
                           const std::vector<Player>& players,
                           QWidget* parent)
    : QWidget(parent), m_scout(players), m_totalPlayers(static_cast<int>(players.size())) {
    for (const Team& team : teams) {
        m_teamNames[team.id] = team.name;
    }

    auto* layout = new QVBoxLayout(this);
    layout->setContentsMargins(20, 18, 20, 18);

    auto* card = new QFrame(this);
    card->setObjectName("card");
    auto* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(22, 20, 22, 20);
    cardLayout->setSpacing(10);

    auto* title = new QLabel("Scouting", card);
    title->setObjectName("pageTitle");
    auto* hint = new QLabel("Поиск по имени, фильтр по клубу и позиции, сортировка. "
                            "Клик по заголовку столбца тоже сортирует.", card);
    hint->setObjectName("pageBody");

    // --- Строка 1: поиск и фильтры ---
    m_search = new QLineEdit(card);
    m_search->setPlaceholderText("Поиск по имени...");
    m_search->setClearButtonEnabled(true);

    m_teamBox = new QComboBox(card);
    m_teamBox->addItem("Все клубы", 0u);
    for (const Team& team : teams) {
        m_teamBox->addItem(team.name, team.id);
    }

    m_positionBox = new QComboBox(card);
    m_positionBox->addItem("Все позиции", QString());
    m_positionBox->addItem("GK — вратари", "GK");
    m_positionBox->addItem("DEF — защитники", "DEF");
    m_positionBox->addItem("MID — полузащитники", "MID");
    m_positionBox->addItem("FWD — нападающие", "FWD");

    auto* filterRow = new QHBoxLayout();
    filterRow->addWidget(m_search, 1);
    filterRow->addWidget(m_teamBox);
    filterRow->addWidget(m_positionBox);

    // --- Строка 2: сортировка и сброс ---
    m_sortFieldBox = new QComboBox(card);
    m_sortFieldBox->addItem("Рейтинг", static_cast<int>(SortField::Rating));
    m_sortFieldBox->addItem("Стоимость", static_cast<int>(SortField::MarketValue));
    m_sortFieldBox->addItem("Голы", static_cast<int>(SortField::Goals));
    m_sortFieldBox->addItem("Ассисты", static_cast<int>(SortField::Assists));
    m_sortFieldBox->addItem("Имя", static_cast<int>(SortField::Name));

    m_sortOrderBox = new QComboBox(card);
    m_sortOrderBox->addItem("По убыванию", static_cast<int>(SortOrder::Descending));
    m_sortOrderBox->addItem("По возрастанию", static_cast<int>(SortOrder::Ascending));

    auto* resetButton = new QPushButton("Сбросить", card);
    resetButton->setObjectName("secondaryButton");
    resetButton->setCursor(Qt::PointingHandCursor);

    auto* sortLabel = new QLabel("Сортировка:", card);
    sortLabel->setObjectName("pageBody");

    auto* sortRow = new QHBoxLayout();
    sortRow->addWidget(sortLabel);
    sortRow->addWidget(m_sortFieldBox);
    sortRow->addWidget(m_sortOrderBox);
    sortRow->addStretch(1);
    sortRow->addWidget(resetButton);

    // --- Таблица игроков ---
    m_table = new QTableWidget(0, 8, card);
    m_table->setHorizontalHeaderLabels(
        {"Игрок", "Клуб", "Поз.", "Рейтинг", "Стоимость", "Голы", "Ассисты", "Г+А"});
    m_table->verticalHeader()->setVisible(false);
    m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_table->setSelectionBehavior(QAbstractItemView::SelectRows);
    m_table->setSelectionMode(QAbstractItemView::SingleSelection);
    m_table->setAlternatingRowColors(true);
    m_table->setShowGrid(false);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    m_table->horizontalHeader()->setSectionResizeMode(ColTeam, QHeaderView::Stretch);
    m_table->horizontalHeader()->setSectionsClickable(true);
    m_table->horizontalHeader()->setSortIndicatorShown(true);

    m_countLabel = new QLabel(card);
    m_countLabel->setObjectName("pageBody");

    cardLayout->addWidget(title);
    cardLayout->addWidget(hint);
    cardLayout->addLayout(filterRow);
    cardLayout->addLayout(sortRow);
    cardLayout->addWidget(m_table, 1);
    cardLayout->addWidget(m_countLabel);
    layout->addWidget(card, 1);

    // Любое изменение параметров сразу пересчитывает таблицу.
    const auto comboChanged = QOverload<int>::of(&QComboBox::currentIndexChanged);
    connect(m_search, &QLineEdit::textChanged, this, &ScoutingPage::applyFilters);
    connect(m_teamBox, comboChanged, this, &ScoutingPage::applyFilters);
    connect(m_positionBox, comboChanged, this, &ScoutingPage::applyFilters);
    connect(m_sortFieldBox, comboChanged, this, &ScoutingPage::applyFilters);
    connect(m_sortOrderBox, comboChanged, this, &ScoutingPage::applyFilters);
    connect(resetButton, &QPushButton::clicked, this, &ScoutingPage::resetFilters);
    connect(m_table->horizontalHeader(), &QHeaderView::sectionClicked,
            this, &ScoutingPage::sortByColumn);

    applyFilters();
}

void ScoutingPage::showTeam(unsigned int teamId) {
    resetFilters();
    const int index = m_teamBox->findData(teamId);
    if (index >= 0) {
        m_teamBox->setCurrentIndex(index);
    }
}

void ScoutingPage::applyFilters() {
    std::optional<long long> teamId;
    const unsigned int selectedTeam = m_teamBox->currentData().toUInt();
    if (selectedTeam != 0) {
        teamId = selectedTeam;
    }
    const QString position = m_positionBox->currentData().toString();
    const auto field = static_cast<SortField>(m_sortFieldBox->currentData().toInt());
    const auto order = static_cast<SortOrder>(m_sortOrderBox->currentData().toInt());

    // Каждый раз начинаем с полного списка, чтобы ослабление фильтра возвращало игроков.
    try {
        m_scout.reset();
        m_scout.find(m_search->text());
        m_scout.filter(teamId, position);
        fillTable(m_scout.sort(field, order));
    } catch (const std::invalid_argument& error) {
        m_countLabel->setText(QString("Ошибка параметров: %1").arg(error.what()));
        return;
    }

    m_table->horizontalHeader()->setSortIndicator(
        columnForField(field),
        order == SortOrder::Ascending ? Qt::AscendingOrder : Qt::DescendingOrder);
}

void ScoutingPage::resetFilters() {
    m_search->clear();
    m_teamBox->setCurrentIndex(0);
    m_positionBox->setCurrentIndex(0);
    m_sortFieldBox->setCurrentIndex(0);
    m_sortOrderBox->setCurrentIndex(0);
    applyFilters();
}

void ScoutingPage::sortByColumn(int column) {
    const std::optional<SortField> field = fieldForColumn(column);
    if (!field) {
        applyFilters();  // по этому столбцу не сортируем, просто вернуть стрелку на место
        return;
    }

    const int fieldIndex = m_sortFieldBox->findData(static_cast<int>(*field));
    if (fieldIndex == m_sortFieldBox->currentIndex()) {
        // Повторный клик по тому же столбцу меняет направление.
        m_sortOrderBox->setCurrentIndex(m_sortOrderBox->currentIndex() == 0 ? 1 : 0);
    } else {
        m_sortFieldBox->setCurrentIndex(fieldIndex);
    }
}

void ScoutingPage::fillTable(const std::vector<Player>& players) {
    const int rows = static_cast<int>(players.size());
    m_table->setRowCount(rows);

    for (int row = 0; row < rows; ++row) {
        const Player& player = players[row];
        const auto team = m_teamNames.find(player.teamId);
        const QString teamName = team != m_teamNames.end() ? team->second : QString("—");

        auto* ratingItem = makeItem(QString::number(player.rating, 'f', 1));
        ratingItem->setForeground(ratingColor(player.rating));

        m_table->setItem(row, ColName, makeItem(player.name, Qt::AlignLeft));
        m_table->setItem(row, ColTeam, makeItem(teamName, Qt::AlignLeft));
        m_table->setItem(row, ColPosition, makeItem(player.position));
        m_table->setItem(row, ColRating, ratingItem);
        m_table->setItem(row, ColValue, makeItem(player.formattedMarketValue()));
        m_table->setItem(row, ColGoals, makeItem(QString::number(player.goals)));
        m_table->setItem(row, ColAssists, makeItem(QString::number(player.assists)));
        m_table->setItem(row, ColTotal, makeItem(QString::number(player.goalContributions())));
    }

    m_countLabel->setText(rows > 0
        ? QString("Найдено игроков: %1 из %2").arg(rows).arg(m_totalPlayers)
        : QString("Никого не нашли — попробуйте ослабить фильтры или нажмите «Сбросить»."));
}
