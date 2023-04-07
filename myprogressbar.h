#ifndef MYPROGRESSBAR_H
#define MYPROGRESSBAR_H

#include <QProgressBar>
#include <QMouseEvent>
#include <QStylePainter>
#include <QStyleOptionSpinBox>

class MyProgressBar : public QProgressBar
{
    Q_OBJECT

public:
    explicit MyProgressBar(QWidget *parent = nullptr)
        : QProgressBar(parent)
    {
    }

signals:
    void pressed(QPoint point);
    void pressReleased();
protected:
    virtual void mouseMoveEvent(QMouseEvent* event) override{
        if(event->buttons() & Qt::LeftButton) {
            if(rect().contains(event->pos())){
                setMouseTracking(true);
                emit pressed(event->pos());
            }
            else{
                setMouseTracking(false);
            }
        }
    }

    virtual void mouseReleaseEvent(QMouseEvent* event) override{
        if (event->button() == Qt::LeftButton)
        {
            emit pressReleased();
            setMouseTracking(false); // Désactiver le suivi de la souris une fois le bouton relâché
        }
    }
};

#endif // MYPROGRESSBAR_H
