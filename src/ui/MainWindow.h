#pragma once

#include <QMainWindow>

class QButtonGroup;
class QStackedWidget;
class ScoutingPage;

/**
 * @brief Main SmartFootball window: left navigation rail + stacked pages.
 *
 * Week 2: League and Scouting pages are real (catalog of clubs and players),
 * the other sections are still placeholders.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void setupUi();
    void applyTheme();
    void openPage(int index);

    QButtonGroup* m_navGroup = nullptr;
    QStackedWidget* m_pages = nullptr;
    ScoutingPage* m_scoutingPage = nullptr;
};
