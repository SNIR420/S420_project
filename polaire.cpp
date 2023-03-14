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
    for (int i = 0; i < m_polaireData.size(); ++i) {
        QVector<double> row = m_polaireData[i];
        for (int j = 0; j < row.size(); ++j) {
            qDebug() << "m_polaireData[" << i << "][" << j << "] = " << row[j];
        }
    }

}
double Polaire::getMaxSpeed(double twa, double tws) {
    int x, y = 0;
    int j, k = 0;

    for(int i = 0; i < m_polaireData.size(); i++) {
        if(m_polaireData[i][0] == twa) { // Trouver la ligne correspondant à l'angle d'attaque (twa)
           x = i;
        }
        for(int j = 0; j < m_polaireData[j].size(); j++){
            if(m_polaireData[0][j] == tws) { // Trouver la ligne correspondant à l'angle d'attaque (tws)
               y = j;
            }
        }
    }
        /*else
        {
            for(j = 0; m_polaireData[j][0] < twa; j++);
            qDebug() << "x1" << m_polaireData[j][0];
            qDebug() << "x2" << m_polaireData[j-1][0];
            x = 0;
        }*/
    /*else
        {
            for(k = 0; m_polaireData[0][k] < tws; k++);
            qDebug() << "y1" << m_polaireData[0][k];
            qDebug() << "y2" << m_polaireData[0][k-1];
            y = 0;
        }*/
    return m_polaireData[x][y];
}
