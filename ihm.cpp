#include "ihm.h"
#include "./ui_ihm.h"

IHM::IHM(QWidget *parent): QWidget(parent), ui(new Ui::IHM)
{
    ui->setupUi(this);

    //Init YAW
    scene = new QGraphicsScene(ui->graphicsViewYaw->rect(), this);
    centerImage = QPixmap(":/images/Vue_top_boat.png");

    centerImageItem = new QGraphicsPixmapItem(centerImage);
    centerImageItem->setPos((ui->graphicsViewYaw->width() - centerImage.width()) / 2, (ui->graphicsViewYaw->height() - centerImage.height()) / 2);
    centerImageItem->setTransformOriginPoint(centerImage.width() / 2, centerImage.height() / 2); // Définir l'origine au centre de l'image
    centerImageItem->setData(Qt::UserRole, "centerImage");
    scene->addItem(centerImageItem);
    ui->graphicsViewYaw->setScene(scene);

    //Init ROW
    sceneRow = new QGraphicsScene(ui->graphicsViewRow->rect(), this);
    rowImage = QPixmap(":/images/Vue_cote_boat.png");

    rowImageItem = new QGraphicsPixmapItem(rowImage);
    rowImageItem->setPos((ui->graphicsViewRow->width() - rowImage.width()) / 2, (ui->graphicsViewRow->height() - rowImage.height()) / 2);
    rowImageItem->setTransformOriginPoint(rowImage.width()/2, rowImage.height()-5); // Définir l'origine au centre de l'image
    rowImageItem->setData(Qt::UserRole, "rowImage");
    sceneRow->addItem(rowImageItem);
    ui->graphicsViewRow->setScene(sceneRow);

    //Init PITCH
    scenePitch = new QGraphicsScene(ui->graphicsViewPitch->rect(), this);
    pitchImage = QPixmap(":/images/Vue_back_boat.png");

    pitchImageItem = new QGraphicsPixmapItem(pitchImage);
    pitchImageItem->setPos((ui->graphicsViewRow->width() - pitchImage.width()) / 2, (ui->graphicsViewPitch->height() - pitchImage.height()) / 2);
    pitchImageItem->setTransformOriginPoint(pitchImage.width()/2, pitchImage.height()-20); // Définir l'origine au centre de l'image
    pitchImageItem->setData(Qt::UserRole, "pitchImage");
    scenePitch->addItem(pitchImageItem);
    ui->graphicsViewPitch->setScene(scenePitch);

    QFontDatabase::addApplicationFont(":/font/RobotoMono.ttf");
    QFontDatabase::addApplicationFont(":/font/Poppins.ttf");
    QFont roboto("Roboto Mono", 14, QFont::Bold);
    QFont poppins("Poppins", 12, QFont::Bold);
    roboto.setStyleStrategy(QFont::PreferAntialias);
    poppins.setStyleStrategy(QFont::PreferAntialias);
    ui->angleSpinBox->setFont(roboto);
    ui->forceSpinBox->setFont(roboto);
    ui->hauteurSpinBox->setFont(roboto);
    ui->vitesseSpinBox->setFont(roboto);

    ui->angleText->setFont(poppins);
    ui->forceText->setFont(poppins);
    ui->hauteurText->setFont(poppins);
    ui->vitesseText->setFont(poppins);

    auto lineEditAngle = ui->angleSpinBox->findChild<QLineEdit*>();
    auto lineEditForce = ui->forceSpinBox->findChild<QLineEdit*>();
    auto lineEditHauteur = ui->hauteurSpinBox->findChild<QLineEdit*>();
    auto lineEditVitesse = ui->vitesseSpinBox->findChild<QLineEdit*>();

    lineEditAngle->setReadOnly(true);
    lineEditAngle->setFocusPolicy(Qt::NoFocus);

    lineEditForce->setReadOnly(true);
    lineEditForce->setFocusPolicy(Qt::NoFocus);

    lineEditHauteur->setReadOnly(true);
    lineEditHauteur->setFocusPolicy(Qt::NoFocus);

    lineEditVitesse->setReadOnly(true);
    lineEditVitesse->setFocusPolicy(Qt::NoFocus);

    connect(lineEditAngle, &QLineEdit::selectionChanged, [=](){
        if (lineEditAngle->hasSelectedText())    lineEditAngle->deselect();
    });
    connect(lineEditForce, &QLineEdit::selectionChanged, [=](){
        if (lineEditForce->hasSelectedText())    lineEditForce->deselect();
    });
    connect(lineEditHauteur, &QLineEdit::selectionChanged, [=](){
        if (lineEditHauteur->hasSelectedText())    lineEditHauteur->deselect();
    });
    connect(lineEditVitesse, &QLineEdit::selectionChanged, [=](){
        if (lineEditVitesse->hasSelectedText())    lineEditVitesse->deselect();
    });

    connect(ui->angleSpinBox, &QSpinBox::valueChanged, [=](){
        setAngleVent(ui->angleSpinBox->value());
    });
    connect(ui->forceSpinBox, &QSpinBox::valueChanged, [=](){
        setTws(ui->forceSpinBox->value());
    });
    connect(ui->hauteurSpinBox, &QDoubleSpinBox::valueChanged, [=](){
        setHauteurVague(ui->hauteurSpinBox->value());
    });
    connect(ui->vitesseSpinBox, &QDoubleSpinBox::valueChanged, [=](){
        setVitesseVague(ui->vitesseSpinBox->value());
    });
    /*QLineSeries *series = new QLineSeries();
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
        axisY->setRange(0, 20);
    }

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    ui->chartLayout->addWidget(chartView);
    chartView->resize(ui->chartLayout->sizeHint());
    chartView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    chart->axisX()->hide();
    chart->axisY()->hide();*/

    m_modbusserver = new Modbus_SRV(":/S420-6-API.csv", this);
    m_simulateur = new Simulateur(":/Class40.pol", m_modbusserver, this);

    QTimer *timer = new QTimer(this) ;
    connect(timer, &QTimer::timeout, this, &IHM::updateBoatRowPitch) ;    //connect le timeout() du timer à une fonction qui calcule roulis, tangage et vitesse azimut
    timer->start(20) ;
    m_modbusserver->setHautvague(ui->hauteurSpinBox->value());
    m_modbusserver->setTws(ui->forceSpinBox->value());
    m_modbusserver->setSwa(ui->angleSpinBox->value());
    setVitesseVague(ui->vitesseSpinBox->value());
}


void IHM::setAngleVent(int angleDeg){
    //crée un qpixmap à partir de l'emplacement de l'image à utiliser
    windImage = QPixmap(":/images/wind.png");
    angleDeg = (angleDeg+90)%360;
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
    qreal scaleFactorX = static_cast<qreal>(ui->graphicsViewRow->width()) / static_cast<qreal>(rowImage.width());
    qreal scaleFactorY = static_cast<qreal>(ui->graphicsViewRow->height()) / static_cast<qreal>(rowImage.height());
    qreal scaleFactor = qMin(scaleFactorX, scaleFactorY);
    //crée le nouvel item graphique associé à l'image

    QPixmap scaledWindImage = windImage.scaled(QSize(windImage.height() * scaleFactor, windImage.width() * scaleFactor), Qt::KeepAspectRatio, Qt::SmoothTransformation);    // Redimensionnement de l'item pixmap
    topLeftImageItem = new QGraphicsPixmapItem(scaledWindImage);

    //qDebug() << "Radius X" << ui->graphicsViewYaw->width()/3;
    //qDebug() << "Radius Y" << ui->graphicsViewYaw->height()/3;
    double angleRad = qDegreesToRadians(angleDeg);

    // Calcule les coordonées selon le cos/sin de l'angle en radian

    double x = (centerImageItem->x()-(6*scaleFactor)) - (ui->graphicsViewYaw->width()/3 * qCos(angleRad));
    double y = centerImageItem->y() - (ui->graphicsViewYaw->height()/3 * qSin(angleRad));

    // Définir la position de l'image et la faire pivoter autour de l'origine de backgroundItem
    topLeftImageItem->setPos(x, y+(80*scaleFactor));
    //qDebug() << "Scale :" << (80*scaleFactor);
    //ajoute l'image à la scene
    scene->addItem(topLeftImageItem);

    //Change le centre de rotation de l'image pour qu'il pivote sur lui-même
    topLeftImageItem->setTransformOriginPoint((scaledWindImage.width()/2), (scaledWindImage.height()/2)); // Définir l'origine de rotation au coin supérieur gauche de l'image

    // Faire tourner l'image selon l'angle donné
    topLeftImageItem->setRotation(angleDeg);

    // Attribuer la donné topLeftImage pour identifier l'image lors de la création de la prochaine et pouvoir la supprimer
    topLeftImageItem->setData(Qt::UserRole, "topLeftImage");

    //Réactualiser la scène pour éviter les bug visuels
    scene->update();

    m_modbusserver->setSwa(angleDeg);
}

void IHM::setTws(int tws){
    if(tws < 15){
        ui->progressBar->setStyleSheet("QProgressBar { background-color: #404040; border-radius: 15px; border: 4px solid black;} QProgressBar::chunk {border-radius: 9px; background-color: #00FF00;}");
    }
    else if(tws < 30){
        ui->progressBar->setStyleSheet("QProgressBar { background-color: #404040; border-radius: 15px; border: 4px solid black;} QProgressBar::chunk {border-radius: 9px; background-color: #7FFF00;}");
    }
    else if(tws < 45){
        ui->progressBar->setStyleSheet("QProgressBar { background-color: #404040; border-radius: 15px; border: 4px solid black;} QProgressBar::chunk {border-radius: 9px; background-color: #FFFF00;}");
    }
    else if(tws < 60){
        ui->progressBar->setStyleSheet("QProgressBar { background-color: #404040; border-radius: 15px; border: 4px solid black;} QProgressBar::chunk {border-radius: 9px; background-color: #FF7700;}");
    }
    else{
        ui->progressBar->setStyleSheet("QProgressBar { background-color: #404040; border-radius: 15px; border: 4px solid black;} QProgressBar::chunk {border-radius: 9px; background-color: #FF0000;}");
    }
    ui->progressBar->setValue(tws);
    m_modbusserver->setTws(tws);
    //TODO: style css pour la barre parce que le vert est moche ui->progressBar->setStyleSpeed();
}

void IHM::setHauteurVague(float hauteur){
    /*auto item = ui->chartLayout->itemAt(0);
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
    chart->axisY()->hide();*/

    m_modbusserver->setHautvague(hauteur);
}

void IHM::setVitesseVague(double vitesse){
    if(vitesse <= 1) vitesse = 1;
    m_modbusserver->setVitvague(vitesse);
}

void IHM::updateBoatRowPitch()
{
    pitchImageItem->setRotation(m_modbusserver->getRoulis());
    rowImageItem->setRotation(m_modbusserver->getTangage());
    sceneRow->update();
    scenePitch->update();
}

void IHM::resizeEvent(QResizeEvent *event){
    qreal scaleFactorX = static_cast<qreal>(event->size().width()) / static_cast<qreal>(centerImage.width());
    qreal scaleFactorY = static_cast<qreal>(event->size().height()) / static_cast<qreal>(centerImage.height());
    qreal scaleFactor = qMin(scaleFactorX, scaleFactorY);

    QList<QGraphicsItem*> items = ui->graphicsViewYaw->scene()->items();
    for (QGraphicsItem *item : items) {
        if (item->type() == QGraphicsPixmapItem::Type && item->data(Qt::UserRole) == "centerImage") {
            centerImageItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
        }
    }

    QPixmap scaledCenterImage = centerImage.scaled(QSize(centerImage.height() * scaleFactor, centerImage.width() * scaleFactor), Qt::KeepAspectRatio, Qt::SmoothTransformation);    // Redimensionnement de l'item pixmap
    centerImageItem->setPixmap(scaledCenterImage);
    centerImageItem->setPos((ui->graphicsViewYaw->scene()->width() - scaledCenterImage.width())/2, (ui->graphicsViewYaw->scene()->height() - scaledCenterImage.height())/2);
    centerImageItem->setData(Qt::UserRole, "centerImage");

    scaleFactorX = static_cast<qreal>(ui->graphicsViewRow->width()) / static_cast<qreal>(rowImage.width());
    scaleFactorY = static_cast<qreal>(ui->graphicsViewRow->height()) / static_cast<qreal>(rowImage.height());
    scaleFactor = qMin(scaleFactorX, scaleFactorY);
    // Récupération de l'item pixmap dans le QGraphicsView
    rowImageItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(ui->graphicsViewRow->scene()->items().first());

    QPixmap scaledRowImage = rowImage.scaled(QSize(rowImage.height() * scaleFactor, rowImage.width() * scaleFactor), Qt::KeepAspectRatio, Qt::SmoothTransformation);    // Redimensionnement de l'item pixmap
    rowImageItem->setPixmap(scaledRowImage);
    rowImageItem->setPos((ui->graphicsViewRow->scene()->width() - scaledRowImage.width())/2, (ui->graphicsViewRow->scene()->height() - scaledRowImage.height())/2);
    rowImageItem->setData(Qt::UserRole, "rowImage");
    rowImageItem->setTransformOriginPoint(scaledRowImage.width()/2, scaledRowImage.height()-(5*scaleFactor));

    scaleFactorX = static_cast<qreal>(event->size().width()) / static_cast<qreal>(pitchImage.width());
    scaleFactorY = static_cast<qreal>(event->size().height()) / static_cast<qreal>(pitchImage.height());
    scaleFactor = qMin(scaleFactorX, scaleFactorY);
    // Récupération de l'item pixmap dans le QGraphicsView
    pitchImageItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(ui->graphicsViewPitch->scene()->items().first());

    QPixmap scaledPitchImage = pitchImage.scaled(QSize(pitchImage.height() * scaleFactor, pitchImage.width() * scaleFactor), Qt::KeepAspectRatio, Qt::SmoothTransformation);    // Redimensionnement de l'item pixmap
    pitchImageItem->setPixmap(scaledPitchImage);
    pitchImageItem->setPos((ui->graphicsViewPitch->scene()->width() - scaledPitchImage.width())/2, (ui->graphicsViewPitch->scene()->height() - scaledPitchImage.height())/2);
    pitchImageItem->setData(Qt::UserRole, "pitchImage");
    pitchImageItem->setTransformOriginPoint(scaledPitchImage.width()/2, scaledPitchImage.height()-(1*scaleFactor));
}

IHM::~IHM()
{
    delete ui;
}
