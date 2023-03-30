#ifndef MYDOUBLESPINBOX_H
#define MYDOUBLESPINBOX_H

#include <QDoubleSpinBox>
#include <QMouseEvent>
#include <QStylePainter>
#include <QStyleOptionSpinBox>

class MyDoubleSpinBox : public QDoubleSpinBox
{
    Q_OBJECT

public:
    explicit MyDoubleSpinBox(QWidget *parent = nullptr)
        : QDoubleSpinBox(parent)
    {
    }

signals:
    void ButtonReleased();
protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override
        {
            QDoubleSpinBox::mouseReleaseEvent(event);

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
#endif // MYDOUBLESPINBOX_H
