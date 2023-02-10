#ifndef MODBUSSERVER_H
#define MODBUSSERVER_H

#include <QtNetwork>
#include <QtCore>
#include <QObject>

class ModbusServer : public QObject
{
    Q_OBJECT

public:
    ModbusServer(QObject *parent = nullptr);
    ~ModbusServer();

    bool startServer(quint16 port = 502);
    void stopServer();

private slots:
    void onNewConnection();
    void onReadyRead();
    void onDisconnected();

private:
    QTcpServer *m_server;
    QList<QTcpSocket *> m_clients;

    quint16 m_port;
};

#endif // MODBUSSERVER_H
