#include "ihm.h"
#include "./ui_ihm.h"

#include <QModbusDataUnit>
#include <QModbusTcpClient>
#include <QModbusReply>
#include <QDebug>

IHM::IHM(QWidget *parent): QWidget(parent), ui(new Ui::IHM)
{
    ui->setupUi(this);

    // Connecter le bouton pushButton avec la fonction sendValues
    connect(ui->pushButton, &QPushButton::clicked, this, &IHM::sendValues);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &IHM::readValues);
    // Initialiser le client Modbus
    modbusDevice = new QModbusTcpClient(this);
    modbusDevice->setConnectionParameter(QModbusDevice::NetworkAddressParameter, "127.0.0.1");
    modbusDevice->setConnectionParameter(QModbusDevice::NetworkPortParameter, 502);
    modbusDevice->setTimeout(1000);
    modbusDevice->setNumberOfRetries(3);
    modbusDevice->connectDevice();
}

IHM::~IHM()
{
    delete ui;
}

void IHM::sendValues()
{
    int value = ui->doubleSpinBox_2->value();

    if (!modbusDevice)
        return;

    QModbusDataUnit writeUnit(QModbusDataUnit::HoldingRegisters, 16, 2);
    writeUnit.setValue(0, value);

    auto *reply = modbusDevice->sendWriteRequest(writeUnit, 1);

    if (!reply) {
        QMessageBox::critical(this, tr("Error"), tr("Write error: ") + modbusDevice->errorString());
    } else {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                if (reply->error() == QModbusDevice::ProtocolError) {
                    QMessageBox::critical(this, tr("Error"), tr("Write error: ") + reply->errorString());
                } else if (reply->error() != QModbusDevice::NoError) {
                    QMessageBox::critical(this, tr("Error"), tr("Write error: ") + reply->errorString());
                } else {
                    QMessageBox::information(this, tr("Success"), tr("Write success"));
                }

                reply->deleteLater();
            });
        } else {
            reply->deleteLater();
        }
    }
}

void IHM::readValues()
{

    if (!modbusDevice)
        return;
    QModbusDataUnit readUnit(QModbusDataUnit::HoldingRegisters, 16, 1);
    auto reply = modbusDevice->sendReadRequest(readUnit, 1);
    if (reply) {
        if (!reply->isFinished()) {
            connect(reply, &QModbusReply::finished, this, [this, reply]() {
                if (reply->error() == QModbusDevice::NoError) {
                    const auto registers = reply->result().values();
                    if (registers.size() == 1) {
                        const int value = static_cast<short>(registers[0]);
                        ui->lcdNumber->display(value);
                    }
                } else if (reply->error() == QModbusDevice::ProtocolError) {
                    qWarning() << tr("Read response error: %1 (Mobus exception: 0x%2)").arg(reply->errorString()).arg(reply->rawResult().exceptionCode(), -1, 16);
                } else {
                    qWarning() << tr("Read response error: %1 (code: 0x%2)").arg(reply->errorString()).arg(reply->error(), -1, 16);
                }

                reply->deleteLater();
            });
        } else {
            delete reply; // broadcast replies return immediately
        }
    } else {
        qWarning() << tr("Read error: ") + modbusDevice->errorString();
    }
}
