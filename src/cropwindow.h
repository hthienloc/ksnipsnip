#pragma once

#include <QWidget>
#include <QPixmap>

class CropWindow : public QWidget
{
    Q_OBJECT
public:
    explicit CropWindow(const QPixmap &pixmap, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    QPixmap m_pixmap;
    qreal m_scale = 1.0;
};
