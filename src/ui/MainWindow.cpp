#include "ui/MainWindow.h"

#include <QButtonGroup>
#include <QFrame>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <vector>

namespace {

QWidget* createSectionPage(const QString& title,
                           const QString& placeholderText,
                           QWidget* parent) {
    auto* page = new QWidget(parent);
    auto* layout = new QVBoxLayout(page);
    layout->setContentsMargins(20, 18, 20, 18);

    auto* card = new QFrame(page);
    card->setObjectName("card");
    auto* cardLayout = new QVBoxLayout(card);
    cardLayout->setContentsMargins(22, 20, 22, 20);
    cardLayout->setSpacing(10);

    auto* heading = new QLabel(title, card);
    heading->setObjectName("pageTitle");

    auto* body = new QLabel(placeholderText, card);
    body->setObjectName("pageBody");
    body->setWordWrap(true);

    cardLayout->addWidget(heading);
    cardLayout->addWidget(body);
    cardLayout->addStretch(1);

    layout->addWidget(card, 1);
    return page;
}

}  // namespace

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setupUi();
    applyTheme();
}

void MainWindow::setupUi() {
    setWindowTitle("SmartFootball (Week 1 Skeleton)");
    resize(1040, 640);
    setMinimumSize(860, 540);

    auto* central = new QWidget(this);
    auto* outerHBox = new QHBoxLayout(central);
    outerHBox->setContentsMargins(0, 0, 0, 0);
    outerHBox->setSpacing(0);

    // Left Navigation Rail
    auto* rail = new QFrame(central);
    rail->setObjectName("navRail");
    rail->setFixedWidth(186);
    auto* railVBox = new QVBoxLayout(rail);
    railVBox->setContentsMargins(0, 14, 0, 14);
    railVBox->setSpacing(4);

    auto* brandTitle = new QLabel("SMARTFOOTBALL", rail);
    brandTitle->setObjectName("brandTitle");
    brandTitle->setContentsMargins(16, 0, 16, 0);
    auto* brandSub = new QLabel("FOOTBALL STATS", rail);
    brandSub->setObjectName("brandSub");
    brandSub->setContentsMargins(16, 0, 16, 12);
    railVBox->addWidget(brandTitle);
    railVBox->addWidget(brandSub);

    m_navGroup = new QButtonGroup(this);
    m_navGroup->setExclusive(true);

    m_pages = new QStackedWidget(central);

    struct NavSection {
        QString label;
        QString placeholder;
    };
    const std::vector<NavSection> sections = {
        {"League", "Планируются лиги и клубы."},
        {"Scouting", "Планируются игроки, поиск и фильтры."},
        {"Player Profile", "Планируется карточка игрока."},
        {"Compare", "Планируется сравнение игроков."},
        {"Shortlist", "Планируется список избранного."}
    };

    for (int i = 0; i < static_cast<int>(sections.size()); ++i) {
        auto* btn = new QPushButton(sections[i].label, rail);
        btn->setObjectName("navItem");
        btn->setCheckable(true);
        btn->setCursor(Qt::PointingHandCursor);
        m_navGroup->addButton(btn, i);
        railVBox->addWidget(btn);
        if (i == 0) {
            btn->setChecked(true);
        }

        m_pages->addWidget(createSectionPage(sections[i].label, sections[i].placeholder, m_pages));
    }
    railVBox->addStretch(1);

#if QT_VERSION >= QT_VERSION_CHECK(5, 15, 0)
    connect(m_navGroup, &QButtonGroup::idClicked, m_pages, &QStackedWidget::setCurrentIndex);
#else
    connect(m_navGroup, QOverload<int>::of(&QButtonGroup::buttonClicked),
            m_pages, &QStackedWidget::setCurrentIndex);
#endif

    // Right Main Area: Top Header + Pages + Bottom Status Bar
    auto* mainCol = new QVBoxLayout();
    mainCol->setContentsMargins(0, 0, 0, 0);
    mainCol->setSpacing(0);

    auto* topBar = new QFrame(central);
    topBar->setObjectName("topBar");
    topBar->setFixedHeight(52);
    auto* topHBox = new QHBoxLayout(topBar);
    topHBox->setContentsMargins(18, 8, 18, 8);
    auto* headerTitle = new QLabel("SmartFootball", topBar);
    headerTitle->setObjectName("headerTitle");
    auto* weekBadge = new QLabel("Week 1 Prototype", topBar);
    weekBadge->setObjectName("weekBadge");
    topHBox->addWidget(headerTitle);
    topHBox->addStretch(1);
    topHBox->addWidget(weekBadge);

    auto* statusBar = new QFrame(central);
    statusBar->setObjectName("footerBar");
    statusBar->setFixedHeight(26);
    auto* statusHBox = new QHBoxLayout(statusBar);
    statusHBox->setContentsMargins(16, 0, 16, 0);
    auto* statusLbl = new QLabel("SmartFootball Week 1 Qt5 Window Ready", statusBar);
    statusLbl->setObjectName("footerText");
    statusHBox->addWidget(statusLbl);
    statusHBox->addStretch(1);

    mainCol->addWidget(topBar);
    mainCol->addWidget(m_pages, 1);
    mainCol->addWidget(statusBar);

    outerHBox->addWidget(rail);
    outerHBox->addLayout(mainCol, 1);
    setCentralWidget(central);
}

void MainWindow::applyTheme() {
    setStyleSheet(
        "QMainWindow, QWidget { background-color: #14121f; color: #e2e8f0; font-family: 'Segoe UI', sans-serif; font-size: 9pt; }"
        "QLabel { background-color: transparent; }"
        "QFrame#navRail { background-color: #1b1829; border-right: 1px solid #312c4a; }"
        "QFrame#topBar { background-color: #1b1829; border-bottom: 1px solid #312c4a; }"
        "QFrame#footerBar { background-color: #110f1a; border-top: 1px solid #2a2540; }"
        "QFrame#card { background-color: #1f1c2e; border: 1px solid #312c4a; border-radius: 8px; }"

        "QLabel#brandTitle { color: #f8fafc; font-size: 12pt; font-weight: bold; letter-spacing: 1px; }"
        "QLabel#brandSub { color: #a78bfa; font-size: 8pt; font-weight: bold; letter-spacing: 1px; }"
        "QLabel#headerTitle { color: #f8fafc; font-size: 11.5pt; font-weight: bold; }"
        "QLabel#weekBadge { background-color: #7c3aed; color: #ffffff; border-radius: 5px; padding: 4px 10px; font-weight: bold; font-size: 8.5pt; }"
        "QLabel#pageTitle { color: #f8fafc; font-size: 15pt; font-weight: bold; }"
        "QLabel#pageSubtitle { color: #a78bfa; font-size: 10pt; font-weight: bold; }"
        "QLabel#pageBody { color: #cbd5e1; font-size: 9.5pt; }"
        "QLabel#footerText { color: #94a3b8; font-size: 8.5pt; }"

        "QPushButton#navItem { background-color: transparent; border: none; border-left: 3px solid transparent; border-radius: 0px; text-align: left; padding: 11px 16px; color: #94a3b8; font-size: 9.5pt; font-weight: bold; }"
        "QPushButton#navItem:hover { background-color: #231f36; color: #f8fafc; }"
        "QPushButton#navItem:checked { background-color: #2c2447; color: #ffffff; border-left: 3px solid #a78bfa; }"
    );
}
