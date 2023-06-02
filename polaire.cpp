#include "polaire.h"

Polaire::Polaire(QString polFilePath)
    : QObject(nullptr)
    , m_polFilePath(polFilePath)
{
    QFile file(polFilePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Erreur : Impossible d'ouvrir le fichier Polaire";
        return;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.startsWith("#")) {
            continue;
        }
        QStringList values = line.split(QRegularExpression("\\s+"));
        QVector<double> data;
        for (int i = 0; i < values.size(); ++i) {
            bool ok;
            double value = values[i].toDouble(&ok);
            if (ok) {
                data.append(value);
            }
        }
        if (!data.isEmpty()) {
            m_polaireData.append(data);
        }
    }

    file.close();

    // Afficher les données Polaire
    for (int i = 1; i < m_polaireData.size(); ++i) {
        QVector<double> row = m_polaireData[i];
        for (int j = 1; j < row.size(); ++j) {
            //qDebug() << "m_polaireData[" << i << "][" << j << "] = " << row[j];
            if(vitesseMax < row[j]){
                vitesseMax = row[j];
            }
        }
    }

}
double Polaire::getMaxSpeed(double twa, double tws) {
    int x = -1, y = -1;
    int i, j, k = 0;

    if (tws == 0) return 0.0 ;
    if (tws > 0.0 && tws < 4.0) tws = 4.0 ;

    if (twa == 0) return 0.0 ;

    for(i = 0; i < m_polaireData.size(); i++) {
        //qDebug() << "x";
        if(m_polaireData[i][0] == twa) { // Trouver la ligne correspondant à l'angle d'attaque (twa)
            x = i;
        }
        for(j = 0; j < m_polaireData[j].size(); j++){
            //qDebug() << "y";
            if(m_polaireData[0][j] == tws) { // Trouver la ligne correspondant à l'angle d'attaque (tws)
                y = j;
            }
        }
    }
    if(x == -1 || y == -1){
        for(j = 0; m_polaireData[j][0] <= twa; j++);
        double x1 = m_polaireData[j][0];
        double x2 = m_polaireData[j-1][0];
        for(k = 0; m_polaireData[0][k] <= tws; k++);
        double y2 = m_polaireData[0][k];
        double y1 = m_polaireData[0][k-1];
        qDebug() << "x1: "<< x1 << "x2: " << x2 << "y1: " << y1 << "y2: " << y2 ;
        double test = (getMaxSpeed(x2, y1) - getMaxSpeed(x1, y1)) * (twa-x1)/ (x2-x1) + (getMaxSpeed(x1, y2) - getMaxSpeed(x1, y1)) * (tws-y1)/(y2-y1) + (getMaxSpeed(x2, y2) + getMaxSpeed(x1, y1) - getMaxSpeed(x2, y1) - getMaxSpeed(x1, y2)) * (twa-x1)/(x2-x1) * (tws-y1)/(y2-y1) + getMaxSpeed(x1, y1);
        return test;
    }
    return m_polaireData[x][y];
}

double Polaire::getMaxGite(double twa, double tws) {
    return (getMaxSpeed(twa, tws)* 30) / getAbsoluteMaxSpeed();
}
double Polaire::getGiteRatio(double twa, double tws, double ratio){

    double gite = getMaxGite(twa,tws)*ratio;
    return gite;
}

double Polaire::getAbsoluteMaxSpeed(){
    //cette fonction doit me retourner la vitesse max de la Polaire
    return vitesseMax;
}

double Polaire::getSpeedRatio(double twa, double tws, double ratio){
    return getMaxSpeed(twa, tws) * ratio ;
}
