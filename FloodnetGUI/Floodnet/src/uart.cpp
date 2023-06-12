#include "uart.h"

uart::uart(QObject *parent)
    : QObject{parent}
{
    m_serial = new QSerialPort(this);
    connect(m_serial,&QSerialPort::readyRead,this,&uart::readData);
    m_combolist = uart::serialPortGetAvailablePorts();
    QList<QString> data = uart::serialPortGetAvailablePorts();

}

void uart::openSerialPort(QString portName)
{
    m_serial->setPortName(portName);
     m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setBaudRate(115200);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);
    if(!m_serial->isOpen())
    {
        m_serial->open(QIODevice::ReadWrite);
    }
}


QList<QString> uart::comboList()
{
  return m_combolist;
}



void uart::closeSerialPort()
{
    if(m_serial->isOpen())
    {
        m_serial->close();
    }
}

void uart::writeData(const QByteArray &data)
{
    m_serial->write(data);
}

QByteArray uart::readData()
{
    QByteArray receive =  m_serial->readAll();
    emit uartnotice(receive);
    return  receive;
}

QList<QString> uart::serialPortGetAvailablePorts()
{
    uint8_t size =0;
    QList<QString> portList;
    QList<QSerialPortInfo> infos = QSerialPortInfo::availablePorts();
    size = infos.size();
    for(uint8_t index =0; index<infos.count(); index++)
    {
        portList.append(infos[index].portName());
    }
    return portList;
}
