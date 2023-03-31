#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include <QStylePainter>
#include <QStyleOptionSpinBox>
#include <QApplication>

class MyGraphicsView : public QGraphicsView
{
    Q_OBJECT
private:
public:
    explicit MyGraphicsView(QWidget *parent = nullptr)
        : QGraphicsView(parent)
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

#endif // MYGRAPHICSVIEW_H
