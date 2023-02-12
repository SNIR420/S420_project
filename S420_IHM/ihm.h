#ifndef IHM_H
#define IHM_H

#include <QWidget>
#include <QtWidgets>
#include <QModbusClient>
#include <QModbusDevice>

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
    void sendValues();
    void readValues();
private:
    Ui::IHM *ui;
    QModbusClient *modbusDevice;
};
#endif // IHM_H
