#include "ihm.h"
#include "./ui_ihm.h"

IHM::IHM(QWidget *parent): QWidget(parent), ui(new Ui::IHM)
{
    //modbus = new Modbus_SRV(this, ...)
    //simulateur = new Simulateur(this, ...)

    ui->setupUi(this);

    //Image de fond
    QPixmap pixmap("C:/Users/ligni/Desktop/S420_project/S420_IHM/images/background.png");
    QBrush brush(pixmap);

    QGraphicsRectItem *backgroundItem = new QGraphicsRectItem(ui->graphicsView->rect());
    backgroundItem->setRect(ui->graphicsView->rect());
    backgroundItem->setBrush(brush);

    scene = new QGraphicsScene(ui->graphicsView->rect(), this);
    scene->addItem(backgroundItem);

    //Image Bateau
    QPixmap centerImage("C:/Users/ligni/Desktop/S420_project/S420_IHM/images/boat.png");
    QGraphicsPixmapItem *centerImageItem = new QGraphicsPixmapItem(centerImage);
    centerImageItem->setPos((ui->graphicsView->width() - centerImage.width()) / 2, (ui->graphicsView->height() - centerImage.height()) / 2);
    centerImageItem->setTransformOriginPoint(centerImage.width() / 2, centerImage.height() / 2); // Définir l'origine au centre de l'image
    scene->addItem(centerImageItem);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(scene->width(), scene->height());

    connect(ui->pushButton, &QPushButton::clicked, this, [=](){
        setAngleVent(ui->doubleSpinBox->value());
    });
}


void IHM::setAngleVent(double angleDeg){
    //crée un qpixmap à partir de l'emplacement de l'image à utiliser
    QPixmap topLeftImage("C:/Users/ligni/Desktop/S420_project/S420_IHM/images/wind.png");
    QGraphicsPixmapItem *topLeftImageItem = nullptr;

    // Vérifie que l'image n'est pas déjà présente sur la scène et la supprime si c'est le cas
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem *item : items) {
        if (item->type() == QGraphicsPixmapItem::Type && item->data(Qt::UserRole) == "topLeftImage") {
            // If the item exists, remove it from the scene
            topLeftImageItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
            scene->removeItem(topLeftImageItem);
            break;
        }
    }
    //crée le nouvel item graphique associé à l'image
    topLeftImageItem = new QGraphicsPixmapItem(topLeftImage);

    // Définir le rayon et l'angle de rotation
    double radius = 200.0;
    double angleRad = qDegreesToRadians(angleDeg);

    // Calcule les coordonées selon le cos/sin de l'angle en radian
    double x, y = 250;

    x = 250 - (radius * qCos(angleRad));
    y = 250 - (radius * qSin(angleRad));

    // Définir la position de l'image et la faire pivoter autour de l'origine de backgroundItem
    topLeftImageItem->setPos(x+24, y+24);

    //ajoute l'image à la scene
    scene->addItem(topLeftImageItem);

    //Change le centre de rotation de l'image pour qu'il pivote sur lui-même
    topLeftImageItem->setTransformOriginPoint((topLeftImage.width()/2), (topLeftImage.height()/2)); // Définir l'origine de rotation au coin supérieur gauche de l'image

    // Faire tourner l'image selon l'angle donné
    topLeftImageItem->setRotation(angleDeg);

    // Attribuer la donné topLeftImage pour identifier l'image lors de la création de la prochaine et pouvoir la supprimer
    topLeftImageItem->setData(Qt::UserRole, "topLeftImage");

    //Réactualiser la scène pour éviter les bug visuels
    scene->update();
}

IHM::~IHM()
{
    delete ui;
}
