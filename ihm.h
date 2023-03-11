#ifndef IHM_H
#define IHM_H

#include <QWidget>
#include <QtWidgets>
#include <QtMath>
#include <QChartView>
#include <QLineSeries>
#include <QValueAxis>
#include "simulateur.h"
#include "modbus_srv.h"
#include <QDebug>

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
    void setHauteurVague(float hauteur);
    void setTws(int tws);
private:
    Ui::IHM *ui;
    QGraphicsScene *scene;
    Simulateur *m_simulateur;
    Modbus_SRV *m_modbusserver;
    QGraphicsPixmapItem *centerImageItem;
};
#endif // IHM_H
