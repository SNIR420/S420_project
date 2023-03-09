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
