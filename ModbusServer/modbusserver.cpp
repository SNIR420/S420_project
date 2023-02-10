#include "modbusserver.h"

ModbusServer::ModbusServer(QObject *parent)
    : QObject(parent)
    , m_server(nullptr)
    , m_port(502)
{
}

ModbusServer::~ModbusServer()
{
    stopServer();
}

bool ModbusServer::startServer(quint16 port)
{
    m_port = port;

    m_server = new QTcpServer(this);
    connect(m_server, &QTcpServer::newConnection, this, &ModbusServer::onNewConnection);

    if (!m_server->listen(QHostAddress::Any, m_port)) {
        qCritical() << "Could not start server:" << m_server->errorString();
        return false;
    }

    qInfo() << "Server started on port" << m_port;
    return true;
}

void ModbusServer::stopServer()
{
    m_server->close();
    m_server->deleteLater();
    m_server = nullptr;

    qInfo() << "Server stopped";
}

void ModbusServer::onNewConnection()
{
    QTcpSocket *client = m_server->nextPendingConnection();

    qInfo() << "Client connected:" << client->peerAddress().toString();

    connect(client, &QTcpSocket::readyRead, this, &ModbusServer::onReadyRead);
    connect(client, &QTcpSocket::disconnected, this, &ModbusServer::onDisconnected);

    m_clients.append(client);
}

void ModbusServer::onReadyRead()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    while (client->bytesAvailable()) {
        QByteArray data = client->readAll();
        qInfo() << "Data received from client:" << client->peerAddress().toString();
        qInfo() << data;
    }
}

void ModbusServer::onDisconnected()
{
    QTcpSocket *client = qobject_cast<QTcpSocket *>(sender());

    qInfo() << "Client disconnected:" << client->peerAddress().toString();

    m_clients.removeOne(client);
    client->deleteLater();
}
