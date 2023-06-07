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
    //centerImageItem->setTransformOriginPoint(centerImage.width() / 2, centerImage.height() / 2); // Définir l'origine au centre de l'image
    centerImageItem->setData(Qt::UserRole, "centerImage");
    centerImageItem->setTransformationMode(Qt::SmoothTransformation);
    centerImageItem->setZValue(1);
    scene->addItem(centerImageItem);

    bomeImage = QPixmap(":/images/Bome.png");
    bomeImageItem = new QGraphicsPixmapItem(bomeImage);
    bomeImageItem->setPos((ui->graphicsViewYaw->width() - bomeImage.width()) / 2, (ui->graphicsViewYaw->height() - bomeImage.height()) / 2);
    bomeImageItem->setTransformOriginPoint(bomeImage.width()/2, bomeImage.height()/2); // Définir l'origine au centre de l'image
    bomeImageItem->setData(Qt::UserRole, "bomeImage");
    bomeImageItem->setTransformationMode(Qt::SmoothTransformation);
    bomeImageItem->setZValue(2);
    scene->addItem(bomeImageItem);

    realBomeImage = QPixmap(":/images/Real_Bome.png");
    realBomeImageItem = new QGraphicsPixmapItem(realBomeImage);
    realBomeImageItem->setPos((ui->graphicsViewYaw->width() - realBomeImage.width()) / 2, (ui->graphicsViewYaw->height() - realBomeImage.height()) / 2);
    realBomeImageItem->setTransformOriginPoint(realBomeImage.width()/2, realBomeImage.height()/2); // Définir l'origine au centre de l'image
    realBomeImageItem->setData(Qt::UserRole, "realBomeImage");
    realBomeImageItem->setTransformationMode(Qt::SmoothTransformation);
    realBomeImageItem->setZValue(3);
    scene->addItem(realBomeImageItem);

    safranImage = QPixmap(":/images/Safran.png");
    safranImageItem = new QGraphicsPixmapItem(safranImage);
    //safranImageItem->setPos((ui->graphicsViewYaw->width() - safranImage.width()) / 2, (ui->graphicsViewYaw->height() - safranImage.height()) / 2);
    safranImageItem->setTransformOriginPoint(safranImage.width()/2, safranImage.height()/2); // Définir l'origine au centre de l'image
    safranImageItem->setData(Qt::UserRole, "safranImage");
    safranImageItem->setTransformationMode(Qt::SmoothTransformation);
    safranImageItem->setZValue(0);
    scene->addItem(safranImageItem);

    ui->graphicsViewYaw->setScene(scene);

    //Init ROW
    sceneRow = new QGraphicsScene(ui->graphicsViewRow->rect(), this);
    rowImage = QPixmap(":/images/Vue_cote_boat.png");

    rowImageItem = new QGraphicsPixmapItem(rowImage);
    rowImageItem->setPos((ui->graphicsViewRow->width() - rowImage.width()) / 2, (ui->graphicsViewRow->height() - rowImage.height()) / 2);
    rowImageItem->setTransformOriginPoint(rowImage.width()/2, rowImage.height()-5); // Définir l'origine au centre de l'image
    rowImageItem->setData(Qt::UserRole, "rowImage");
    rowImageItem->setTransformationMode(Qt::SmoothTransformation);
    rowImageItem->setZValue(1);
    sceneRow->addItem(rowImageItem);
    ui->graphicsViewRow->setScene(sceneRow);

    //Init PITCH
    scenePitch = new QGraphicsScene(ui->graphicsViewPitch->rect(), this);
    pitchImage = QPixmap(":/images/Vue_back_boat.png");

    pitchImageItem = new QGraphicsPixmapItem(pitchImage);
    pitchImageItem->setPos((ui->graphicsViewRow->width() - pitchImage.width()) / 2, (ui->graphicsViewPitch->height() - pitchImage.height()) / 2);
    pitchImageItem->setTransformOriginPoint(pitchImage.width()/2, pitchImage.height()-20); // Définir l'origine au centre de l'image
    pitchImageItem->setData(Qt::UserRole, "pitchImage");
    pitchImageItem->setTransformationMode(Qt::SmoothTransformation);

    textSpeedItem = new QGraphicsTextItem();
    textSpeedItem->setPos(ui->graphicsViewPitch->width()/2, ui->graphicsViewPitch->height()/2);
    scenePitch->addItem(textSpeedItem);
    scenePitch->addItem(pitchImageItem);
    ui->graphicsViewPitch->setScene(scenePitch);

    QFontDatabase::addApplicationFont(":/font/RobotoMono.ttf");
    QFontDatabase::addApplicationFont(":/font/Poppins.ttf");
    QFont roboto("Roboto Mono", 15, QFont::Bold);
    QFont poppins("Poppins", 12, QFont::Bold);
    roboto.setStyleStrategy(QFont::PreferAntialias);
    poppins.setStyleStrategy(QFont::PreferAntialias);
    ui->angleSpinBox->setFont(roboto);
    ui->forceSpinBox->setFont(roboto);
    ui->hauteurSpinBox->setFont(roboto);
    ui->vitesseSpinBox->setFont(roboto);
    ui->periodeSpinBox->setFont(roboto);

    ui->angleText->setFont(poppins);
    ui->forceText->setFont(poppins);
    ui->hauteurText->setFont(poppins);
    ui->vitesseText->setFont(poppins);
    ui->periodeText->setFont(poppins);
    ui->bomeText->setFont(poppins);

    auto lineEditAngle = ui->angleSpinBox->findChild<QLineEdit*>();
    auto lineEditForce = ui->forceSpinBox->findChild<QLineEdit*>();
    auto lineEditHauteur = ui->hauteurSpinBox->findChild<QLineEdit*>();
    auto lineEditVitesse = ui->vitesseSpinBox->findChild<QLineEdit*>();
    auto lineEditPeriode = ui->periodeSpinBox->findChild<QLineEdit*>();
    auto lineEditBome = ui->bomeSpinBox->findChild<QLineEdit*>();

    lineEditAngle->setReadOnly(true);
    lineEditAngle->setFocusPolicy(Qt::NoFocus);

    lineEditForce->setReadOnly(true);
    lineEditForce->setFocusPolicy(Qt::NoFocus);

    lineEditHauteur->setReadOnly(true);
    lineEditHauteur->setFocusPolicy(Qt::NoFocus);

    lineEditVitesse->setReadOnly(true);
    lineEditVitesse->setFocusPolicy(Qt::NoFocus);

    lineEditPeriode->setReadOnly(true);
    lineEditPeriode->setFocusPolicy(Qt::NoFocus);

    lineEditBome->setReadOnly(true);
    lineEditBome->setFocusPolicy(Qt::NoFocus);

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
    connect(lineEditPeriode, &QLineEdit::selectionChanged, [=](){
        if (lineEditPeriode->hasSelectedText())    lineEditPeriode->deselect();
    });
    connect(lineEditBome, &QLineEdit::selectionChanged, [=](){
        if (lineEditBome->hasSelectedText())    lineEditBome->deselect();
    });

    connect(ui->angleSpinBox, &QSpinBox::valueChanged, [=]() {
        setUiAngleVent(ui->angleSpinBox->value());
    });
    connect(ui->angleSpinBox, &MySpinBox::ButtonReleased, [=]() {
        sendSwa();
    });
    connect(ui->forceSpinBox, &MySpinBox::valueChanged, [=]() {
        setUiTws(ui->forceSpinBox->value());
    });
    connect(ui->forceSpinBox, &MySpinBox::ButtonReleased, [=]() {
        sendTws();
    });

    connect(ui->hauteurSpinBox, &MyDoubleSpinBox::ButtonReleased, [=]() {
        setHauteurVague(ui->hauteurSpinBox->value());
    });
    connect(ui->vitesseSpinBox, &MyDoubleSpinBox::ButtonReleased, [=]() {
        setVitesseVague(ui->vitesseSpinBox->value());
    });
    connect(ui->periodeSpinBox, &MyDoubleSpinBox::ButtonReleased, [=]() {
        setPeriodeVague(ui->periodeSpinBox->value());
    });

    connect(ui->progressBar, &MyProgressBar::pressed, this, &IHM::onProgressBarPressed);
    connect(ui->progressBar, &MyProgressBar::pressReleased, this, &IHM::sendTws);
    connect(ui->graphicsViewYaw, &MyGraphicsView::pressed, this, &IHM::onGraphicsViewPressed);
    connect(ui->graphicsViewYaw, &MyGraphicsView::pressReleased, this, &IHM::sendSwa);
    connect(ui->pbuClient, &QPushButton::clicked, this, &IHM::debugMode);
    m_modbusserver = new Modbus_SRV(":/S420-6-API.csv", this);
    m_simulateur = new Simulateur(":/Class40.pol", m_modbusserver, this);

    QTimer *timer = new QTimer(this) ;
    connect(timer, &QTimer::timeout, this, &IHM::updateBoatRowPitch) ;    //connect le timeout() du timer à une fonction qui calcule roulis, tangage et vitesse azimut
    timer->start(20);

    m_modbusserver->setHautvague(0.3);
    m_modbusserver->setTws(0);
    m_modbusserver->setSwa(0);
    m_modbusserver->setAngleAzimut(0.0);
    m_modbusserver->setRoulis(0.0);
    m_modbusserver->setTangage(0.0);
    setVitesseVague(2.0);
    setPeriodeVague(20.0);
}

void IHM::debugMode(){
    if(isEnabled == false){
        isEnabled = true;
        delete m_simulateur;
        ui->periodeText->setText("Roulis (debug)");
        ui->periodeSpinBox->setMinimum(-40.0);
        ui->periodeSpinBox->setValue(0);
        ui->periodeSpinBox->setSingleStep(1);
        ui->periodeSpinBox->setMaximum(40.0);
        ui->periodeSpinBox->setSuffix("°");

        ui->vitesseText->setText("Tangage (debug)");
        ui->vitesseSpinBox->setMinimum(-40.0);
        ui->vitesseSpinBox->setValue(0);
        ui->vitesseSpinBox->setSingleStep(1);
        ui->vitesseSpinBox->setMaximum(40.0);
        ui->vitesseSpinBox->setSuffix("°");

        ui->hauteurText->setText("Angle Azi. (debug)");
        ui->hauteurSpinBox->setMinimum(0);
        ui->hauteurSpinBox->setSingleStep(1);
        ui->hauteurSpinBox->setMaximum(360);
        ui->hauteurSpinBox->setValue(m_modbusserver->getAngleAzimut());
        ui->hauteurSpinBox->setSuffix("°");
        ui->hauteurSpinBox->setWrapping(true);

        m_modbusserver->setRoulis(0);
        m_modbusserver->setTangage(0);
        textSpeedItem->setPlainText(QString::number(0,'f', 2));
    }
    else{
        isEnabled = false;
        m_simulateur = new Simulateur(":/Class40.pol", m_modbusserver, this);
        ui->periodeText->setText("Inter Vague");
        ui->periodeSpinBox->setMinimum(10.0);
        ui->periodeSpinBox->setValue(20.0);
        ui->periodeSpinBox->setSingleStep(1);
        ui->periodeSpinBox->setMaximum(20.0);
        ui->periodeSpinBox->setSuffix("s");

        ui->vitesseText->setText("Vitesse Vague");
        ui->vitesseSpinBox->setMinimum(-10.0);
        ui->vitesseSpinBox->setValue(2.0);
        ui->vitesseSpinBox->setSingleStep(0.1);
        ui->vitesseSpinBox->setMaximum(20.0);
        ui->vitesseSpinBox->setSuffix("m/s");

        ui->hauteurText->setText("Hauteur Vague");
        ui->hauteurSpinBox->setMinimum(0);
        ui->hauteurSpinBox->setValue(0.3);
        ui->hauteurSpinBox->setSingleStep(0.1);
        ui->hauteurSpinBox->setMaximum(20);
        ui->hauteurSpinBox->setSuffix("m");
        ui->hauteurSpinBox->setWrapping(false);

        m_modbusserver->setHautvague(ui->hauteurSpinBox->value());
        m_modbusserver->setTws(ui->forceSpinBox->value());
        m_modbusserver->setSwa(ui->angleSpinBox->value());
        setVitesseVague(ui->vitesseSpinBox->value());
        setPeriodeVague(ui->periodeSpinBox->value());
    }
}

void IHM::onGraphicsViewPressed(const QPoint& pos){
    MyGraphicsView* view = ui->graphicsViewYaw;
    QPointF center = view->mapToScene(view->rect().center());
    QPointF clickPos = view->mapToScene(pos);
    QPointF vector = clickPos - center;
    int angle = -1;
    angle = atan2(vector.y(), vector.x()) * 180 / M_PI + 90;
    if (angle > 0) {
        angle -= 360;
    }
    ui->angleSpinBox->setValue(-1*angle);
}

void IHM::onProgressBarPressed(const QPoint& pos){
    MyProgressBar* progressBar = ui->progressBar;
    int value = progressBar->minimum() + (pos.x() * (progressBar->maximum()+1 - progressBar->minimum())) / progressBar->width(); // Calcule la nouvelle valeur de la `QProgressBar` en fonction des coordonnées de la souris sur l'axe x
    if(value > progressBar->maximum())  value = 70;
    ui->forceSpinBox->setValue(value);
    setUiTws(value);
}

void IHM::sendTws(){
    m_modbusserver->setTws(ui->forceSpinBox->value());
}

void IHM::setPeriodeVague(float periode){
    if(isEnabled == true){
        m_modbusserver->setRoulis(periode);
    }
    else m_modbusserver->setIntervague(periode);
}

void IHM::setUiBome(int bome){
    bomeImageItem->setRotation(bome);
    bomeImageItem->setTransformationMode(Qt::SmoothTransformation);
    scene->update();
}

void IHM::setUiRealBome(){
    float angleReel = 360-ui->angleSpinBox->value();
    float angle = 0;
    //270 360 - 0 90 -- 90 à 270 pas de mouvement
    if(angleReel >= 270-m_modbusserver->getBomError() && angleReel <= 360){
        angle = (360-m_modbusserver->getSwa())+m_modbusserver->getBomError();
        ui->bomeSpinBox->setValue(360-angle);
        //qDebug() << "1";
    }
    else if(angleReel >= 0 && angleReel <= 90+m_modbusserver->getBomError()){
        angle = (360-m_modbusserver->getSwa())-m_modbusserver->getBomError();
        ui->bomeSpinBox->setValue(-angle);
        //qDebug() << "2";
    }
    else if(angleReel > 90+m_modbusserver->getBomError() && angleReel <= 180){
        angle = 90;
        ui->bomeSpinBox->setValue(-90);
        //qDebug() << "3";
    }
    else if(angleReel > 180 && angleReel < 270-m_modbusserver->getBomError()){
        angle = 270;
        ui->bomeSpinBox->setValue(90);
        //qDebug() << "4";
    }
    realBomeImageItem->setRotation(angle);
    realBomeImageItem->setTransformationMode(Qt::SmoothTransformation);
    scene->update();
}

void IHM::setUiAngleVent(int angleDeg){
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

    double angleRad = qDegreesToRadians(180-angleDeg);

    // Calcule les coordonées selon le cos/sin de l'angle en radian

    double x = (centerImageItem->x()-(6*scaleFactor)) - (ui->graphicsViewYaw->width()/3 * qCos(angleRad));
    double y = centerImageItem->y() - (ui->graphicsViewYaw->height()/3 * qSin(angleRad));

    // Définir la position de l'image et la faire pivoter autour de l'origine de backgroundItem
    topLeftImageItem->setPos(x, y+(80*scaleFactor));

    //ajoute l'image à la scene
    scene->addItem(topLeftImageItem);

    //Change le centre de rotation de l'image pour qu'il pivote sur lui-même
    topLeftImageItem->setTransformOriginPoint((scaledWindImage.width()/2), (scaledWindImage.height()/2)); // Définir l'origine de rotation au coin supérieur gauche de l'image

    // Faire tourner l'image selon l'angle donné
    topLeftImageItem->setRotation(180-angleDeg);

    topLeftImageItem->setTransformationMode(Qt::SmoothTransformation);

    // Attribuer la donné topLeftImage pour identifier l'image lors de la création de la prochaine et pouvoir la supprimer
    topLeftImageItem->setData(Qt::UserRole, "topLeftImage");

    //Réactualiser la scène pour éviter les bug visuels
    scene->update();
}

void IHM::sendSwa(){
    m_modbusserver->setSwa(ui->angleSpinBox->value());

    if(360-ui->angleSpinBox->value() >= 270 && 360-ui->angleSpinBox->value() <= 360){
        setUiBome(360-ui->angleSpinBox->value());
    }
    else if(360-ui->angleSpinBox->value() >= 0 && 360-ui->angleSpinBox->value() <= 90){
        setUiBome(360-ui->angleSpinBox->value());
    }
    else if(360-ui->angleSpinBox->value() > 90 && 360-ui->angleSpinBox->value() <= 180){
        setUiBome(-270);
    }
    else{
        setUiBome(270);
    }
}

void IHM::setUiTws(int tws){
    if(tws < 15){
        ui->progressBar->setStyleSheet("QProgressBar { background-color: #404040; border-radius: 5px; border: 4px solid black;} QProgressBar::chunk {border-radius: 3px; background-color: #00FF00;}");
    }
    else if(tws < 30){
        ui->progressBar->setStyleSheet("QProgressBar { background-color: #404040; border-radius: 5px; border: 4px solid black;} QProgressBar::chunk {border-radius: 3px; background-color: #7FFF00;}");
    }
    else if(tws < 45){
        ui->progressBar->setStyleSheet("QProgressBar { background-color: #404040; border-radius: 5px; border: 4px solid black;} QProgressBar::chunk {border-radius: 3px; background-color: #FFFF00;}");
    }
    else if(tws < 60){
        ui->progressBar->setStyleSheet("QProgressBar { background-color: #404040; border-radius: 5px; border: 4px solid black;} QProgressBar::chunk {border-radius: 3px; background-color: #FF7700;}");
    }
    else{
        ui->progressBar->setStyleSheet("QProgressBar { background-color: #404040; border-radius: 5px; border: 4px solid black;} QProgressBar::chunk {border-radius: 3px; background-color: #FF0000;}");
    }
    ui->progressBar->setValue(tws);
}

void IHM::setAngleBoat(float angle) {

    m_modbusserver->setAngleAzimut(angle);
}

void IHM::setHauteurVague(float hauteur){
    if(isEnabled == true){
        setAngleBoat(hauteur);
    }
    else{
        m_modbusserver->setHautvague(hauteur);
    }
}

void IHM::setVitesseVague(double vitesse){
    if(isEnabled == true){
        m_modbusserver->setTangage(vitesse);
    }
    else{
        if(vitesse <= 1) vitesse = 1;
        m_modbusserver->setVitvague(vitesse);
    }
}

void IHM::updateBoatRowPitch()
{
    sceneRow->update();
    scenePitch->update();
    if(ui->angleSpinBox->value() >= 0 && ui->angleSpinBox->value() <=80){
        m_modbusserver->setBom(ui->angleSpinBox->value());
    }
    else if(ui->angleSpinBox->value() >= 280 && ui->angleSpinBox->value() <=359){
        m_modbusserver->setBom(ui->angleSpinBox->value()-360);
    }
    else if(ui->angleSpinBox->value() >= 81 && ui->angleSpinBox->value() <=180){
        m_modbusserver->setBom(80);
    }
    else if(ui->angleSpinBox->value() >= 181 && ui->angleSpinBox->value() <=279){
        m_modbusserver->setBom(-80);
    }
    setUiRealBome();
    sendSwa();
    if(m_modbusserver->getVitazimut() > 0.1) m_modbusserver->setVitazimut(0.01);
    if (m_modbusserver->getClientConnected() > 0) {
        ui->pbuClient->setStyleSheet("QPushButton { image: url(:/images/icon_plug_on.png);  background-color: #00FF00;}");
    } else {
        ui->pbuClient->setStyleSheet("QPushButton {	image: url(:/images/icon_plug_off.png); background-color: #4D4D4D;}");
    }
    if(isEnabled == true){
        // Rechercher le QGraphicsTextItem existant dans la scène
        QGraphicsTextItem *textItem = nullptr;
        QList<QGraphicsItem *> items = scene->items();
        for (QGraphicsItem *item : items) {
            if (QGraphicsTextItem *ti = dynamic_cast<QGraphicsTextItem *>(item)) {
                textItem = ti;
                break;
            }
        }
        // Si le QGraphicsTextItem n'existe pas encore, le créer
        if (textItem == nullptr) {
            textItem = new QGraphicsTextItem();
            QPointF pos = ui->graphicsViewYaw->mapToScene(QPoint(10, 1));
            textItem->setPos(pos);
            scene->addItem(textItem);
        }

        QString text = "=[VENT]=\n\ntws: %1\nswa: %2\n\n=[BATEAU]=\n\nroulis: %3\ntangage: %4\nvit.azimut: %5\nangle.azimut: %6\nerror bome: %7\n\n=[VAGUE]=\n\nhauteur: %8\nvitesse: %9\ninter-vague: %10\n";
        textItem->setFont(QFont("Arial", 14));
        textItem->setPlainText(text.arg(QString::number(m_modbusserver->getTws()), QString::number(m_modbusserver->getSwa()), QString::number(m_modbusserver->getRoulis()), QString::number(m_modbusserver->getTangage()), QString::number(m_modbusserver->getVitazimut()), QString::number(m_modbusserver->getAngleAzimut()), QString::number(m_modbusserver->getBomError()), QString::number(m_modbusserver->getHautvague()), QString::number(m_modbusserver->getVitvague()), QString::number(m_modbusserver->getIntervague())));
        m_modbusserver->setTangage(ui->vitesseSpinBox->value());
        m_modbusserver->setRoulis(ui->periodeSpinBox->value());
        m_modbusserver->setVitazimut(0);
        pitchImageItem->setRotation(ui->periodeSpinBox->value());
        rowImageItem->setRotation(ui->vitesseSpinBox->value());
    }
    else{
        pitchImageItem->setRotation(m_modbusserver->getRoulis());
        rowImageItem->setRotation(m_modbusserver->getTangage());

        float angle = (m_modbusserver->getSafran()*45)/2;
        safranImageItem->setRotation(angle);
        safranImageItem->setTransformationMode(Qt::SmoothTransformation);
        m_modbusserver->setVitazimut(0.05*m_modbusserver->getSafran());

        QList<QGraphicsItem *> items = scene->items();
        for (QGraphicsItem *item : items) {
            if (QGraphicsTextItem *ti = dynamic_cast<QGraphicsTextItem *>(item)) {
                delete ti;
            }
        }
        QString textSpeed = "%1 kn";
        textSpeedItem->setFont(QFont("Poppins", 18));
        textSpeedItem->setPlainText(textSpeed.arg(QString::number(m_modbusserver->getSpeed(),'f', 2)));
    }
}

void IHM::resizeEvent(QResizeEvent *event){
    qreal scaleFactorX = static_cast<qreal>(event->size().width()) / static_cast<qreal>(centerImage.width());
    qreal scaleFactorY = static_cast<qreal>(event->size().height()) / static_cast<qreal>(centerImage.height());
    qreal scaleFactor = qMin(scaleFactorX, scaleFactorY);
    factor = scaleFactor;
    QList<QGraphicsItem*> items = ui->graphicsViewYaw->scene()->items();
    for (QGraphicsItem *item : items) {
        if (item->type() == QGraphicsPixmapItem::Type && item->data(Qt::UserRole) == "centerImage") {
            centerImageItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(item);
        }
    }

    scaledCenterImage = QPixmap(centerImage.scaled(QSize(centerImage.height() * scaleFactor, centerImage.width() * scaleFactor), Qt::KeepAspectRatio, Qt::SmoothTransformation));    // Redimensionnement de l'item pixmap
    centerImageItem->setPixmap(scaledCenterImage);
    centerImageItem->setPos((ui->graphicsViewYaw->scene()->width() - scaledCenterImage.width())/2, (ui->graphicsViewYaw->scene()->height() - scaledCenterImage.height())/2);
    centerImageItem->setData(Qt::UserRole, "centerImage");

    QPixmap scaledBomeImage = bomeImage.scaled(QSize(bomeImage.height() * scaleFactor, bomeImage.width() * scaleFactor), Qt::KeepAspectRatio, Qt::SmoothTransformation);    // Redimensionnement de l'item pixmap
    bomeImageItem->setPixmap(scaledBomeImage);
    bomeImageItem->setPos((ui->graphicsViewYaw->scene()->width() - scaledBomeImage.width())/2, (ui->graphicsViewYaw->scene()->height() - scaledBomeImage.height())/2);
    bomeImageItem->setData(Qt::UserRole, "bomeImage");
    bomeImageItem->setTransformOriginPoint(scaledBomeImage.width()/2, 55*scaleFactor);

    QPixmap scaledRealBomeImage = realBomeImage.scaled(QSize(realBomeImage.height() * scaleFactor, realBomeImage.width() * scaleFactor), Qt::KeepAspectRatio, Qt::SmoothTransformation);    // Redimensionnement de l'item pixmap
    realBomeImageItem->setPixmap(scaledRealBomeImage);
    realBomeImageItem->setPos((ui->graphicsViewYaw->scene()->width() - scaledRealBomeImage.width())/2, (ui->graphicsViewYaw->scene()->height() - scaledRealBomeImage.height())/2);
    realBomeImageItem->setData(Qt::UserRole, "realBomeImage");
    realBomeImageItem->setTransformOriginPoint(scaledRealBomeImage.width()/2, 55*scaleFactor);

    scaledSafranImage = QPixmap(safranImage.scaled(QSize(safranImage.height() * scaleFactor, safranImage.width() * scaleFactor), Qt::KeepAspectRatio, Qt::SmoothTransformation));    // Redimensionnement de l'item pixmap
    safranImageItem->setPixmap(scaledSafranImage);
    safranImageItem->setPos((ui->graphicsViewYaw->scene()->width() - scaledSafranImage.width())/2, (ui->graphicsViewYaw->scene()->height() + ((-5*scaleFactor)+scaledCenterImage.height()))/2);
    safranImageItem->setData(Qt::UserRole, "safranImage");
    safranImageItem->setTransformOriginPoint(scaledSafranImage.width()/2, scaleFactor*3);

    scaleFactorX = static_cast<qreal>(event->size().width()) / static_cast<qreal>(pitchImage.width());
    scaleFactorY = static_cast<qreal>(event->size().height()) / static_cast<qreal>(pitchImage.height());
    scaleFactor = qMin(scaleFactorX, scaleFactorY);
    // Récupération de l'item pixmap dans le QGraphicsView
    pitchImageItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(ui->graphicsViewPitch->scene()->items().first());

    QPixmap scaledPitchImage = pitchImage.scaled(QSize(pitchImage.height() * scaleFactor, pitchImage.width() * scaleFactor), Qt::KeepAspectRatio, Qt::SmoothTransformation);    // Redimensionnement de l'item pixmap
    ui->graphicsViewPitch->setMaximumWidth((scaledPitchImage.height()*2)+50);
    pitchImageItem->setPixmap(scaledPitchImage);
    pitchImageItem->setPos((ui->graphicsViewPitch->scene()->width() - scaledPitchImage.width())/2, (ui->graphicsViewPitch->scene()->height() - scaledPitchImage.height())/2);
    pitchImageItem->setData(Qt::UserRole, "pitchImage");
    pitchImageItem->setTransformOriginPoint(scaledPitchImage.width()/2, scaledPitchImage.height()-(1*scaleFactor));

    textSpeedItem->setPos(ui->graphicsViewPitch->width()/2, ui->graphicsViewPitch->height()/2);

    scaleFactorX = static_cast<qreal>(ui->graphicsViewRow->width()) / static_cast<qreal>(rowImage.width());
    scaleFactorY = static_cast<qreal>(ui->graphicsViewRow->height()) / static_cast<qreal>(rowImage.height());
    scaleFactor = qMin(scaleFactorX, scaleFactorY);
    // Récupération de l'item pixmap dans le QGraphicsView
    rowImageItem = qgraphicsitem_cast<QGraphicsPixmapItem*>(ui->graphicsViewRow->scene()->items().first());

    QPixmap scaledRowImage = rowImage.scaled(QSize(rowImage.height() * scaleFactor, rowImage.width() * scaleFactor), Qt::KeepAspectRatio, Qt::SmoothTransformation);    // Redimensionnement de l'item pixmap
    ui->graphicsViewRow->setMaximumWidth(ui->graphicsViewPitch->maximumWidth());
    rowImageItem->setPixmap(scaledRowImage);
    rowImageItem->setPos((ui->graphicsViewRow->scene()->width() - scaledRowImage.width())/2, (ui->graphicsViewRow->scene()->height() - scaledRowImage.height())/2);
    rowImageItem->setData(Qt::UserRole, "rowImage");
    rowImageItem->setTransformOriginPoint(scaledRowImage.width()/2, scaledRowImage.height()-(5*scaleFactor));

    QString size = QString::number(32+(scaleFactor*1.15));
    QString border = QString::number(11+(scaleFactor*0.75));
    QString styleSheetSpin = "QSpinBox{"
                         "border-radius: %2px;"
                         "font-family: \"Roboto Mono\";"
                         "background-color: #ffffff;"
                         "color: black;"
                         "}"
                         "QSpinBox:up-button {"
                         "subcontrol-position: left;"
                         "height: %1px;"
                         "width: %1px;"
                         "image: url(:/images/icon_plus.png);"
                         "}"
                         "QSpinBox:down-button {"
                         "subcontrol-position: right;"
                         "height: %1px;"
                         "width: %1px;"
                         "image: url(:/images/icon_minus.png);"
                          "}";
    QString styleSheetDouble = "QDoubleSpinBox{"
                             "border-radius: %2px;"
                             "font-family: \"Roboto Mono\";"
                             "background-color: #ffffff;"
                             "color: black;"
                             "}"
                             "QDoubleSpinBox:up-button {"
                             "subcontrol-position: left;"
                             "height: %1px;"
                             "width: %1px;"
                             "image: url(:/images/icon_plus.png);"
                             "}"
                             "QDoubleSpinBox:down-button {"
                             "subcontrol-position: right;"
                             "height: %1px;"
                             "width: %1px;"
                             "image: url(:/images/icon_minus.png);"
                             "}";
    ui->angleSpinBox->setStyleSheet(styleSheetSpin.arg(size, border));
    ui->forceSpinBox->setStyleSheet(styleSheetSpin.arg(size, border));
    ui->periodeSpinBox->setStyleSheet(styleSheetDouble.arg(size, border));
    ui->vitesseSpinBox->setStyleSheet(styleSheetDouble.arg(size, border));
    ui->hauteurSpinBox->setStyleSheet(styleSheetDouble.arg(size, border));
    ui->bomeSpinBox->setStyleSheet(styleSheetSpin.arg(size, border));
}

IHM::~IHM()
{
    delete ui;
}
