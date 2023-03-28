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
#include <QTimer>
#include <QPropertyAnimation>
#include <QObject>

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
    void setHauteurVague(float hauteur);
    void setVitesseVague(double vitesse);
    void setTws(int tws);
    void updateBoatRowPitch();
    void setAngleVent(int angleDeg);
private:
    Ui::IHM *ui;
    QGraphicsScene *scene;
    QGraphicsScene *sceneRow;
    QGraphicsScene *scenePitch;
    Simulateur *m_simulateur;
    Modbus_SRV *m_modbusserver;
    QGraphicsPixmapItem *centerImageItem;
    QGraphicsPixmapItem *rowImageItem;
    QGraphicsPixmapItem *pitchImageItem;
    QPixmap centerImage;
    QPixmap rowImage;
    QPixmap pitchImage;
    QPixmap windImage;
protected:
    void resizeEvent(QResizeEvent *event)   override;
};
#endif // IHM_H
