#include <QtCore>
#include "polaire.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // Créer une variable Polaire
    Polaire polaire("/home/projetbateau/Bureau/Class40.pol");

    return app.exec();
}
