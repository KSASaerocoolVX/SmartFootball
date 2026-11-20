#include "ui/MainWindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QFont>
#include <QGuiApplication>

int main(int argc, char* argv[]) {
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling, true);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps, true);
#if QT_VERSION >= QT_VERSION_CHECK(5, 14, 0)
    QGuiApplication::setHighDpiScaleFactorRoundingPolicy(
        Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif

    QApplication app(argc, argv);
    app.setFont(QFont("Segoe UI", 9));

    MainWindow window;
    window.show();
    return app.exec();
}
