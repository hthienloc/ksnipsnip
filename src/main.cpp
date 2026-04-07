#include <QApplication>
#include <QProcess>
#include <QFile>
#include "snipper.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setQuitOnLastWindowClosed(false); // Manually handle exit
    
    QString tempPath = QStringLiteral("/tmp/ksnipsnip.png");
    
    // Capture screen using spectacle on Wayland
    QProcess proc;
    proc.start(QStringLiteral("spectacle"), {
        QStringLiteral("--background"), 
        QStringLiteral("--nonotify"), 
        QStringLiteral("--output"), 
        tempPath
    });
    proc.waitForFinished();
    
    Snipper *s = new Snipper(tempPath);
    s->showFullScreen();
    
    return a.exec();
}
