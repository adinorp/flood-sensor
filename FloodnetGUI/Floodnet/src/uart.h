#ifndef UART_H
#define UART_H

#include <QObject>
#include <QSerialPortInfo>
#include <QByteArray>
#include <QSerialPort>
#include <QDebug>
#include <QTimer>

class uart : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QStringList comboList READ comboList )
public:
    explicit uart(QObject *parent = nullptr);
    QList<QString> comboList();

public slots:
    void openSerialPort(QString portName);
    void closeSerialPort();
    void writeData(const QByteArray &data);
    QByteArray readData();
    QList<QString> serialPortGetAvailablePorts();

signals:
    void uartnotice(QString data);
private:
    QSerialPort *m_serial = nullptr;
    QTimer *m_time = nullptr;
    QList<QString> m_combolist;


};

#endif // UART_H
