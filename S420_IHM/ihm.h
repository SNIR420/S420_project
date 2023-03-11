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
    void setAngleBateau(double angleDeg);
private:
    Ui::IHM *ui;
    QGraphicsScene *scene;
<<<<<<< Updated upstream:S420_IHM/ihm.h
=======
    Simulateur *m_simulateur;
    Modbus_SRV *m_modbusserver;
    QGraphicsPixmapItem *centerImageItem;
>>>>>>> Stashed changes:ihm.h
};
#endif // IHM_H
