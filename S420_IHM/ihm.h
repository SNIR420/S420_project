#ifndef IHM_H
#define IHM_H

#include <QWidget>
#include <QtWidgets>
#include <QtMath>

QT_BEGIN_NAMESPACE
namespace Ui { class IHM; }
QT_END_NAMESPACE

class IHM : public QWidget
{
    Q_OBJECT
public:
    IHM(QWidget *parent = nullptr);
    ~IHM();
private slots:
    void setAngleVent(double angleDeg);
private:
    Ui::IHM *ui;
    QGraphicsScene *scene;
};
#endif // IHM_H
