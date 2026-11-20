#pragma once

#include <QMainWindow>

class QButtonGroup;
class QStackedWidget;

/**
 * @brief Minimal Week 1 Qt5 application window skeleton for SmartFootball.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void setupUi();
    void applyTheme();

    QButtonGroup* m_navGroup = nullptr;
    QStackedWidget* m_pages = nullptr;
};
