#include "cropwindow.h"
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>
#include <QWheelEvent>
#include <QWindow>

CropWindow::CropWindow(const QPixmap &pixmap, QWidget *parent)
    : QWidget(parent), m_pixmap(pixmap)
{
    // Clean frameless window without aggressive stay-on-top hints
    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);
    
    // Set logical size
    resize(m_pixmap.width(), m_pixmap.height());
}

void CropWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);
    
    QRect targetRect = rect();
    painter.drawPixmap(targetRect, m_pixmap);
}

void CropWindow::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // Wayland native move
        if (windowHandle()) {
            windowHandle()->startSystemMove();
        }
        event->accept();
    } else if (event->button() == Qt::RightButton) {
        close();
        qApp->quit(); // Ensure the process exits
    }
}

void CropWindow::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
}

void CropWindow::wheelEvent(QWheelEvent *event)
{
    qreal delta = event->angleDelta().y();
    qreal factor = (delta > 0) ? 1.1 : 0.9;
    
    m_scale *= factor;
    
    // Calculate new size based on logical pixels
    QSize baseLogicalSize(m_pixmap.width(), m_pixmap.height());
    QSize newSize = baseLogicalSize * m_scale;
    
    resize(newSize);
    
    event->accept();
}

void CropWindow::enterEvent(QEnterEvent *event)
{
    setCursor(Qt::OpenHandCursor);
    QWidget::enterEvent(event);
}

void CropWindow::leaveEvent(QEvent *event)
{
    unsetCursor();
    QWidget::leaveEvent(event);
}
