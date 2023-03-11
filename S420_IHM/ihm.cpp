#include "ihm.h"
#include "./ui_ihm.h"

IHM::IHM(QWidget *parent): QWidget(parent), ui(new Ui::IHM)
{
    //modbus = new Modbus_SRV(this, ...)
    //simulateur = new Simulateur(this, ...)

    ui->setupUi(this);

    //Image de fond
<<<<<<< Updated upstream:S420_IHM/ihm.cpp
    QPixmap pixmap("C:/Users/ligni/Desktop/S420_project/S420_IHM/images/background.png");
    QBrush brush(pixmap);

    QGraphicsRectItem *backgroundItem = new QGraphicsRectItem(ui->graphicsView->rect());
    backgroundItem->setRect(ui->graphicsView->rect());
    backgroundItem->setBrush(brush);
=======
    QPixmap pixmap("C:/Users/ligni/Desktop/S420_PROJET/S420_project/images/background.png");
    QBrush brush(pixmap);

    ui->graphicsView->setBackgroundBrush(pixmap);
>>>>>>> Stashed changes:ihm.cpp

    scene = new QGraphicsScene(ui->graphicsView->rect(), this);
    //scene->addItem(backgroundItem);

    //Image Bateau
<<<<<<< Updated upstream:S420_IHM/ihm.cpp
    QPixmap centerImage("C:/Users/ligni/Desktop/S420_project/S420_IHM/images/boat.png");
    QGraphicsPixmapItem *centerImageItem = new QGraphicsPixmapItem(centerImage);
=======
    QPixmap centerImage("C:/Users/ligni/Desktop/S420_PROJET/S420_project/images/boat.png");
    centerImageItem = new QGraphicsPixmapItem(centerImage);
>>>>>>> Stashed changes:ihm.cpp
    centerImageItem->setPos((ui->graphicsView->width() - centerImage.width()) / 2, (ui->graphicsView->height() - centerImage.height()) / 2);
    centerImageItem->setTransformOriginPoint(centerImage.width() / 2, centerImage.height() / 2); // Définir l'origine au centre de l'image
    centerImageItem->setData(Qt::UserRole, "centerImage");


    scene->addItem(centerImageItem);
<<<<<<< Updated upstream:S420_IHM/ihm.cpp
=======

    QLineSeries *series = new QLineSeries();
    float x;
    for (x = 4.7; x <= 10.9; x += 0.1) {
        float y = 0 * sin(x);
        series->append(x, y);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axisY());
    if (axisY) {
        axisY->setRange(-1*0, 20);
    }

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartLayout->addWidget(chartView);
    chartView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    chartView->resize(ui->chartLayout->sizeHint());
    chart->axisX()->hide();
    chart->axisY()->hide();

    ui->chartLayout->addWidget(chartView);
    chartView->resize(ui->chartLayout->sizeHint());

>>>>>>> Stashed changes:ihm.cpp
    ui->graphicsView->setScene(scene);
    //ui->graphicsView->setFixedSize(scene->width(), scene->height());

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
            topLeftImageItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
            scene->removeItem(topLeftImageItem);
            break;
        }
    }

    //crée le nouvel item graphique associé à l'image
    topLeftImageItem = new QGraphicsPixmapItem(topLeftImage);

    qDebug() << "Radius X" << ui->graphicsView->width()/3;
    qDebug() << "Radius Y" << ui->graphicsView->height()/3;
    double angleRad = qDegreesToRadians(angleDeg);

    // Calcule les coordonées selon le cos/sin de l'angle en radian
    /*qDebug() << "X" << centerImageItem->x();
    qDebug() << "Y" << centerImageItem->y();*/

    double x = (centerImageItem->x()-45) - (ui->graphicsView->width()/3 * qCos(angleRad));
    double y = centerImageItem->y() - (ui->graphicsView->height()/3 * qSin(angleRad));

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

void IHM::setAngleBateau(double angleDeg){
    QPixmap centerImage("C:/Users/ligni/Desktop/S420_project/S420_IHM/images/boat.png");
    QGraphicsPixmapItem *centerImageItem = nullptr;
    QList<QGraphicsItem*> items = scene->items();
    for (QGraphicsItem *item : items) {
        if (item->type() == QGraphicsPixmapItem::Type && item->data(Qt::UserRole) == "centerImage") {
            centerImageItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
            scene->removeItem(centerImageItem);
            break;
        }
    }
    centerImageItem = new QGraphicsPixmapItem(centerImage);
    centerImageItem->setPos((ui->graphicsView->width() - centerImage.width()) / 2, (ui->graphicsView->height() - centerImage.height()) / 2);
    centerImageItem->setTransformOriginPoint(centerImage.width() / 2, centerImage.height() / 2); // Définir l'origine au centre de l'image
    centerImageItem->setData(Qt::UserRole, "centerImage");
    centerImageItem->setRotation(angleDeg);
    scene->addItem(centerImageItem);
}

<<<<<<< Updated upstream:S420_IHM/ihm.cpp
=======
void IHM::setTws(int tws){
    ui->progressBar->setValue(tws);
    //TODO: style css pour la barre parce que le vert est moche ui->progressBar->setStyleSpeed();
}

void IHM::setHauteurVague(float hauteur){
    // Obtenir l'objet contenu à la position i
    auto item = ui->chartLayout->itemAt(0);
    // Vérifier si l'objet est un graphique
    if (auto plot = qobject_cast<QChartView *>(item->widget())) {
        ui->chartLayout->removeItem(item);
        delete plot;
    }
    QLineSeries *series = new QLineSeries();
    float x;
    for (x = 4.7; x <= 10.9; x += 0.1) {
        float y = hauteur * sin(x);
        series->append(x, y);
    }

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();

    QValueAxis *axisY = qobject_cast<QValueAxis*>(chart->axisY());
    if (axisY) {
        axisY->setRange(-1*hauteur, 20);
    }

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartLayout->addWidget(chartView);
    chartView->resize(ui->chartLayout->sizeHint());
    chartView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    chart->axisX()->hide();
    chart->axisY()->hide();

    m_modbusserver->setHautvague(hauteur);
}

>>>>>>> Stashed changes:ihm.cpp
IHM::~IHM()
{
    delete ui;
}
