#ifndef MYSPINBOX_H
#define MYSPINBOX_H

#include <QSpinBox>
#include <QMouseEvent>
#include <QStylePainter>
#include <QStyleOptionSpinBox>

class MySpinBox : public QSpinBox
{
    Q_OBJECT

public:
    explicit MySpinBox(QWidget *parent = nullptr)
        : QSpinBox(parent)
    {
    }

signals:
    void ButtonReleased();
protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override
        {
            QSpinBox::mouseReleaseEvent(event);

            if (event->button() == Qt::LeftButton)
            {
                const QPoint pos = event->pos();
                QStyleOptionSpinBox opt;
                this->initStyleOption(&opt);
                const QRect upRect = style()->subControlRect(QStyle::CC_SpinBox, &opt, QStyle::SC_SpinBoxUp, this);
                const QRect downRect = style()->subControlRect(QStyle::CC_SpinBox, &opt, QStyle::SC_SpinBoxDown, this);

                if (upRect.contains(pos))
                {
                    emit ButtonReleased();
                }
                else if (downRect.contains(pos))
                {
                    emit ButtonReleased();
                }
            }
        }
};
#endif // MYSPINBOX_H
