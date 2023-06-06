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
#include <QPropertyAnimation>
#include <QObject>
#include <QMouseEvent>
#include <QGraphicsOpacityEffect>

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
    void debugMode();

    void onGraphicsViewPressed(const QPoint& pos);
    void onProgressBarPressed(const QPoint& pos);

    void sendSwa();
    void sendTws();

    void setHauteurVague(float hauteur);
    void setPeriodeVague(float periode);
    void setVitesseVague(double vitesse);

    void setUiAngleVent(int angleDeg);
    void setUiBome(int bome);
    void setUiRealBome();
    void setUiTws(int tws);
    void setAngleBoat(float angle);

    void updateBoatRowPitch();

private:
    Ui::IHM *ui;
    QGraphicsScene *scene;
    QGraphicsScene *sceneRow;
    QGraphicsScene *scenePitch;
    Simulateur *m_simulateur;
    Modbus_SRV *m_modbusserver;
    QGraphicsPixmapItem *centerImageItem;
    QGraphicsPixmapItem *bomeImageItem;
    QGraphicsPixmapItem *realBomeImageItem;
    QGraphicsPixmapItem *rowImageItem;
    QGraphicsPixmapItem *pitchImageItem;
    QGraphicsPixmapItem *safranImageItem;
    QPixmap centerImage;
    QPixmap bomeImage;
    QPixmap realBomeImage;
    QPixmap rowImage;
    QPixmap pitchImage;
    QPixmap windImage;
    QPixmap safranImage;
    QPixmap scaledCenterImage;
    QPixmap scaledSafranImage;
    qreal factor;
    QGraphicsTextItem *textItem;
    QGraphicsTextItem *textSpeedItem;
    bool isEnabled = false;
protected:
    void resizeEvent(QResizeEvent *event)   override;
};
#endif // IHM_H
