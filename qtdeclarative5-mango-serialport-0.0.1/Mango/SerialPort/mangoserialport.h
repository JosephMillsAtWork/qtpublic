#ifndef MANGOSERIALPORT_H
#define MANGOSERIALPORT_H

#include <QtSerialPort/QSerialPort>

class MangoSerialPort : public QSerialPort
{
public:
    explicit MangoSerialPort(QObject *parent = 0);
    Q_ENUMS(BaudRate DataBits Direction FlowControl Parity PinoutSignal SerialPortError StopBits)

    //   PUBLIC FUNCTIONS
//    Q_INVOKABLE virtual	~QSerialPort(){}
    Q_INVOKABLE qint32	baudRate(Directions directions = AllDirections) const{
        return QSerialPort::baudRate(directions);
    }
    Q_INVOKABLE bool clear(Directions directions = AllDirections){
        return QSerialPort::clear(directions);
    }
    Q_INVOKABLE void clearError(){
        return QSerialPort::clearError();
    }
    Q_INVOKABLE DataBits dataBits() const{
        return QSerialPort::dataBits();
    }
    Q_INVOKABLE SerialPortError	error() const{
        return QSerialPort::error();
    }
    Q_INVOKABLE FlowControl	flowControl() const{
        return QSerialPort::flowControl();
    }
    Q_INVOKABLE bool flush(){
        return  QSerialPort::flush();
    }
//    Q_INVOKABLE Handle handle() const{
//        return QSerialPort::handle();
//    }
    Q_INVOKABLE bool isDataTerminalReady(){
        return QSerialPort::isDataTerminalReady();
    }
    Q_INVOKABLE bool isRequestToSend(){
        return QSerialPort::isRequestToSend();
    }
    Q_INVOKABLE bool open(OpenMode mode) {
        return QSerialPort::open(mode);
    }
    Q_INVOKABLE Parity parity() const{
        return QSerialPort::parity();
    }
    Q_INVOKABLE PinoutSignals pinoutSignals(){
        return QSerialPort::pinoutSignals();
    }
    Q_INVOKABLE QString portName() const{
        return QSerialPort::portName();
    }
    Q_INVOKABLE qint64 readBufferSize() const{
        return QSerialPort::readBufferSize();
    }
//    Q_INVOKABLE bool sendBreak(int duration = 0){
//        QSerialPort::sendBreak(duration);
//    }
    Q_INVOKABLE bool setBaudRate(qint32 baudRate, Directions directions = AllDirections){
        return QSerialPort::setBaudRate(baudRate,directions);
    }
    Q_INVOKABLE bool setBreakEnabled(bool set = true){
        return QSerialPort::setBreakEnabled(set);
    }
    Q_INVOKABLE bool setDataBits(DataBits dataBits){
        return QSerialPort::setDataBits(dataBits);
    }
    Q_INVOKABLE bool setDataTerminalReady(bool set){
        return QSerialPort::setDataTerminalReady(set);
    }
    Q_INVOKABLE bool setFlowControl(FlowControl flowControl){
        return QSerialPort::setFlowControl(flowControl);
    }
    Q_INVOKABLE bool setParity(Parity parity){
        return setParity(parity);
    }
    Q_INVOKABLE void setPort(const QSerialPortInfo &serialPortInfo){
        return QSerialPort::setPort(serialPortInfo);
    }
    Q_INVOKABLE void setPortName(const QString &name){
        return QSerialPort::setPortName(name);
    }
    Q_INVOKABLE void setReadBufferSize(qint64 size){
        return QSerialPort::setReadBufferSize(size);
    }
    Q_INVOKABLE bool setRequestToSend(bool set){
        return QSerialPort::setRequestToSend(set);
    }
    Q_INVOKABLE bool setStopBits(StopBits stopBits){
        return QSerialPort::setStopBits(stopBits);
    }
    Q_INVOKABLE StopBits stopBits() const{
        return QSerialPort::stopBits();
    }



//ReImplamented Function
    Q_INVOKABLE virtual bool atEnd() const{
        return QSerialPort::atEnd();
    }
    Q_INVOKABLE virtual qint64 bytesAvailable() const{
        return QSerialPort::bytesAvailable();
    }
    Q_INVOKABLE virtual qint64 bytesToWrite() const{
        return QSerialPort::bytesToWrite();
    }
    Q_INVOKABLE virtual bool canReadLine() const{
        return QSerialPort::canReadLine();
    }
    Q_INVOKABLE virtual void close(){
        return QSerialPort::close();
    }
    Q_INVOKABLE virtual bool isSequential() const{
        return QSerialPort::isSequential();
    }
    Q_INVOKABLE virtual bool waitForBytesWritten(int msecs){
        return QSerialPort::waitForBytesWritten(msecs);
    }
    Q_INVOKABLE virtual bool waitForReadyRead(int msecs){
        return QSerialPort::waitForReadyRead(msecs);
    }


//Signals
    Q_INVOKABLE void baudRateChanged(qint32 baudRate, QSerialPort::Directions directions){
        return QSerialPort::baudRateChanged(baudRate,directions);
    }
    Q_INVOKABLE void dataBitsChanged(QSerialPort::DataBits dataBits){
        return QSerialPort::dataBitsChanged(dataBits);
    }
    Q_INVOKABLE void dataTerminalReadyChanged(bool set){
        return QSerialPort::dataTerminalReadyChanged(set);
    }
    Q_INVOKABLE void error(QSerialPort::SerialPortError error){
        return QSerialPort::error(error);
    }
    Q_INVOKABLE void flowControlChanged(QSerialPort::FlowControl flow){
        return QSerialPort::flowControlChanged(flow);
    }
    Q_INVOKABLE void parityChanged(QSerialPort::Parity parity){
        return QSerialPort::parityChanged(parity);
    }
    Q_INVOKABLE void requestToSendChanged(bool set){
        return QSerialPort::requestToSendChanged(set);
    }
    Q_INVOKABLE void settingsRestoredOnCloseChanged(bool restore){
        return QSerialPort::settingsRestoredOnCloseChanged(restore);
    }
    Q_INVOKABLE void stopBitsChanged(QSerialPort::StopBits stopBits){
        return QSerialPort::stopBitsChanged(stopBits);
    }

//Reimplemented Protected Functions
    Q_INVOKABLE virtual qint64 readData(char *data, qint64 maxSize){
    return QSerialPort::readData(data,maxSize);
    }
    Q_INVOKABLE virtual qint64 readLineData(char * data, qint64 maxSize){
        return QSerialPort::readLineData(data,maxSize);
    }
    Q_INVOKABLE virtual qint64 writeData(const char * data, qint64 maxSize){
        return QSerialPort::writeData(data,maxSize);
    }

};

#endif // MANGOSERIALPORT_H
