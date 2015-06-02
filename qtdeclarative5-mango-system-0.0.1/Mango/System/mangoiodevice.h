#ifndef MANGOIODEVICE_H
#define MANGOIODEVICE_H
#include <QIODevice>
class MangoIODevice : public QIODevice
{
    Q_OBJECT
public:
    explicit MangoIODevice(QObject *parent = 0);

    // public functions
    Q_INVOKABLE virtual bool atEnd() const{
        return QIODevice::atEnd();
    }
    Q_INVOKABLE virtual qint64 bytesAvailable() const{
        return QIODevice::bytesAvailable();
    }
    Q_INVOKABLE virtual qint64 bytesToWrite() const {
        return QIODevice::bytesToWrite();
    }
    Q_INVOKABLE virtual bool canReadLine() const {
        return QIODevice::canReadLine();
    }
    Q_INVOKABLE virtual void close(){
        return QIODevice::close();
    }
    Q_INVOKABLE QString errorString() const{
        return QIODevice::errorString();
    }
//    Q_INVOKABLE bool getChar(char * c) const{
//        return QIODevice::getChar(c);
//    }
    Q_INVOKABLE bool isOpen() const {
        return QIODevice::isOpen();
    }
    Q_INVOKABLE bool isReadable() const {
        return QIODevice::isReadable();
    }
    Q_INVOKABLE virtual bool isSequential() const {
        return QIODevice::isSequential();
    }
    Q_INVOKABLE bool isTextModeEnabled() const {
        return QIODevice::isTextModeEnabled();
    }
    Q_INVOKABLE bool isWritable() const {
        return QIODevice::isWritable();
    }
    Q_INVOKABLE virtual bool open(OpenMode mode){
        return QIODevice::open(mode);
    }
    Q_INVOKABLE OpenMode openMode() const{
        return QIODevice::openMode();
    }
    Q_INVOKABLE qint64 peek(char *data, qint64 maxSize){
        return QIODevice::peek(data,maxSize);
    }
    Q_INVOKABLE QByteArray peek(qint64 maxSize){
        return QIODevice::peek(maxSize);
    }
    Q_INVOKABLE virtual qint64 pos() const{
        return QIODevice::pos();
    }
    Q_INVOKABLE bool putChar(char c){
        return QIODevice::putChar(c);
    }
    Q_INVOKABLE qint64 read(char *data, qint64 maxSize){
        return QIODevice::read(data,maxSize);
    }
    Q_INVOKABLE QByteArray read(qint64 maxSize){
        return QIODevice::read(maxSize);
    }
    Q_INVOKABLE QByteArray readAll(){
        return QIODevice::readAll();
    }
    Q_INVOKABLE qint64 readLine(char *data, qint64 maxSize){
        return QIODevice::readLine(data,maxSize);
    }
    Q_INVOKABLE QByteArray readLine(qint64 maxSize = 0){
        return QIODevice::readLine(maxSize);
    }
    Q_INVOKABLE virtual bool reset(){
        return QIODevice::reset();
    }
    Q_INVOKABLE virtual bool seek(qint64 pos){
        return QIODevice::seek(pos);
    }
    Q_INVOKABLE void setTextModeEnabled(bool enabled){
        return QIODevice::setTextModeEnabled(enabled);
    }
    Q_INVOKABLE virtual qint64 size() const{
        return QIODevice::size();
    }
    Q_INVOKABLE void ungetChar(char c){
        return QIODevice::ungetChar(c);
    }
    Q_INVOKABLE virtual bool waitForBytesWritten(int msecs){
        return QIODevice::waitForBytesWritten(msecs);
    }
    Q_INVOKABLE virtual bool waitForReadyRead(int msecs){
        return QIODevice::waitForReadyRead(msecs);
    }
    Q_INVOKABLE qint64	write(const char *data, qint64 maxSize){
        return QIODevice::write(data,maxSize);
    }
    Q_INVOKABLE qint64	write(const char *data){
        return QIODevice::write(data);
    }
    Q_INVOKABLE qint64	write(const QByteArray &byteArray){
        return QIODevice::write(byteArray);
    }


//     signals
    Q_INVOKABLE void aboutToClose(){
    return QIODevice::aboutToClose();
    }
    Q_INVOKABLE void bytesWritten(qint64 bytes){
    return QIODevice::bytesWritten(bytes);
    }
    Q_INVOKABLE void readChannelFinished(){
    return QIODevice::readChannelFinished();
    }
    Q_INVOKABLE void readyRead(){
    return QIODevice::readyRead();
    }


//    Protected Functions
   Q_INVOKABLE virtual qint64 readData(char *data, qint64 maxSize){
   return QIODevice::readData(data,maxSize);
   }
   Q_INVOKABLE virtual qint64 readLineData(char *data, qint64 maxSize){
   return QIODevice::readLineData(data,maxSize);
   }
   Q_INVOKABLE void setErrorString(const QString &str){
   return QIODevice::setErrorString(str);
   }
   Q_INVOKABLE void	setOpenMode(OpenMode openMode){
   return QIODevice::setOpenMode(openMode);
   }
   Q_INVOKABLE virtual qint64	writeData(const char *data, qint64 maxSize){
   return QIODevice::writeData(data,maxSize);
   }
};

#endif // MANGOIODEVICE_H
