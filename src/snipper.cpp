#include "snipper.h"
#include "cropwindow.h"
#include <QMouseEvent>
#include <QScreen>
#include <QGuiApplication>
#include <QPainter>
#include <QWindow>
#include <QApplication>

Snipper::Snipper(const QString &imagePath, QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    setWindowState(Qt::WindowFullScreen);
    setCursor(Qt::CrossCursor);

    if (imagePath.isEmpty() || !m_fullScreenPixmap.load(imagePath)) {
        // Fallback to grabWindow if loading fails (e.g. on X11)
        QScreen *screen = QGuiApplication::primaryScreen();
        m_fullScreenPixmap = screen->grabWindow(0);
    }
}

void Snipper::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_origin = event->pos();
        if (!m_rubberBand)
            m_rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
        m_rubberBand->setGeometry(QRect(m_origin, QSize()));
        m_rubberBand->show();
    }
}

void Snipper::mouseMoveEvent(QMouseEvent *event)
{
    if (m_rubberBand) {
        m_rubberBand->setGeometry(QRect(m_origin, event->pos()).normalized());
    }
}

#include <QDebug>

void Snipper::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_rubberBand) {
        m_rubberBand->hide();
        QRect rect = m_rubberBand->geometry();
        
        if (rect.width() > 5 && rect.height() > 5) {
            qreal dpr = devicePixelRatio();
            QRect physicalRect(rect.x() * dpr, rect.y() * dpr, 
                               rect.width() * dpr, rect.height() * dpr);
            
            physicalRect = physicalRect.intersected(m_fullScreenPixmap.rect());
            
            if (!physicalRect.isEmpty()) {
                QPixmap cropped = m_fullScreenPixmap.copy(physicalRect);
                cropped.setDevicePixelRatio(dpr);
                
                CropWindow *cw = new CropWindow(cropped);
                cw->show();
            } else {
                qApp->quit();
            }
        } else {
            qApp->quit();
        }
        
        close();
    }
}

void Snipper::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawPixmap(rect(), m_fullScreenPixmap);
    
    // Darken the background
    painter.fillRect(rect(), QColor(0, 0, 0, 100));
}

void Snipper::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        close();
        if (QApplication::topLevelWidgets().count() <= 1) {
             qApp->quit();
        }
    }
}
