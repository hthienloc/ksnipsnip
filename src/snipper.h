#pragma once

#include <QWidget>
#include <QRubberBand>
#include <QPixmap>

class Snipper : public QWidget
{
    Q_OBJECT
public:
    explicit Snipper(const QString &imagePath, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private:
    QPixmap m_fullScreenPixmap;
    QPoint m_origin;
    QRubberBand *m_rubberBand = nullptr;
};
