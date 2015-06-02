/*
 * Joseph Mills
 */

#include "mangomodbusregistermodel.h"
#include <QScopedPointer>
#include <modbus/modbus.h>
#include <stdint.h>
/*!
  \qmltype MangoModbusRegisterModel
    \inqmlmodule Mango.Networking 0.1
    \ingroup Mango.Networking
    \inherits Item
    \since 5.3
 * used by qml to set a tcp file spo that one can look for bonjour/avahi services
 */

MangoModbusRegisterModel::MangoModbusRegisterModel(QObject *parent) :
    QAbstractListModel(parent),
    m_modbusContext(0),
    m_registers(new uint8_t[MODBUS_MAX_READ_BITS]),
    m_registerType(Coil),
    m_outputType(Integer16),
    m_registerReadAddr(0),
    m_registerReadSize(10),
    m_connected(false)
{
}

/*!
  /qmlsignal MangoModbusRegisterModel::connectToServer()
  Connects to the modbus server
  \qmlproperty string ip
    The ip address of the modbus server
  parma int port
  Returns false on error connecting
 */
bool MangoModbusRegisterModel::connectToServer(const QString &ip, int port)
{
    if (m_connected)
        disconnect();

    m_modbusContext = modbus_new_tcp(ip.toStdString().c_str(), port);

    if (m_modbusContext == 0)
        return false;

    if (modbus_connect(m_modbusContext) == -1)
        return false;

    m_connected = true;

    return true;
}
/*!
  \qmlsignal MangoModbusRegisterModel::isConnected()
  Returns True if the Mango Application is connected to modbus.
 */
bool MangoModbusRegisterModel::isConnected() const
{
    return m_connected;
}

/*!
  Disconnect from the modbus server
 */
void MangoModbusRegisterModel::disconnect()
{
    if (m_modbusContext) {
        modbus_close(m_modbusContext);
        modbus_free(m_modbusContext);
    }

    m_modbusContext = 0;
}

/*!
  Desctructor
 */
MangoModbusRegisterModel::~MangoModbusRegisterModel()
{
    disconnect();
}

/*!
  Gets the type of register we want to read
 */
MangoModbusRegisterModel::ModbusRegisterType MangoModbusRegisterModel::modbusRegisterType() const
{
    return m_registerType;
}

/*!
  Set what kind of register type we want to read

  @param datatype type of modbus register
 */
void MangoModbusRegisterModel::setModbusRegisterType(ModbusRegisterType datatype)
{
    m_registerType = datatype;
}

/*!
  @reimp
 */
int MangoModbusRegisterModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);

    if (m_registerType == Coil || m_registerType == Input)
        return m_numRead;

    switch (m_outputType) {
    case Integer16:
        return m_numRead;

    case Integer32:
    case Float:
    case FlippedFloat:
        return m_numRead / 2;

    case DoubleFloat:
        return m_numRead / 4;

    default:
        return m_numRead;
    }
}

/*!
  @reimp
 */
QVariant MangoModbusRegisterModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() < 0 || index.row() > m_numRead)
        return QVariant();

    if (role == Qt::DisplayRole) {
        switch (m_registerType) {
        case Coil:
        case Input:
            return m_registers[index.row()];

        case Register: {
            if (m_outputType == Integer16) {
                uint16_t *reg16 = reinterpret_cast<uint16_t *>(m_registers.data());
                return reg16[index.row()];
            } else if (m_outputType == Integer32) {
                uint32_t *reg32 = reinterpret_cast<uint32_t *>(m_registers.data());
                return reg32[index.row()];
            } else if (m_outputType == Float) {
                float *floattype = reinterpret_cast<float *>(m_registers.data());
                return floattype[index.row()];
            } else if (m_outputType == DoubleFloat) {
                double *doubletype = reinterpret_cast<double *>(m_registers.data());
                return doubletype[index.row()];
            }
        }
        }
    }

    return QVariant();
}

/*!
  Read registers from modbus server.
 */
void MangoModbusRegisterModel::readRegisters()
{
    beginResetModel();

    switch (m_registerType) {
    case Coil:
        m_numRead = modbus_read_bits(m_modbusContext, m_registerReadAddr, m_registerReadSize, m_registers.data());
        break;
    case Input:
        m_numRead = modbus_read_input_bits(m_modbusContext, m_registerReadAddr, m_registerReadSize, m_registers.data());
        break;
    case Register:
        m_numRead = modbus_read_registers(m_modbusContext, m_registerReadAddr, m_registerReadSize, reinterpret_cast<uint16_t *>(m_registers.data()));
        break;


    default:
        break;
    }

    endResetModel();
}

/*!
  How many register to read
 */
int MangoModbusRegisterModel::registerReadSize() const
{
    return m_registerReadSize;
}

/*!
  Sets how many registers to read
 */
void MangoModbusRegisterModel::setRegisterReadSize(int registerReadSize)
{
    m_registerReadSize = registerReadSize;
}

/*!
  Gets the starting address of registers to read

  @return
 */
int MangoModbusRegisterModel::registerReadAddr() const
{
    return m_registerReadAddr;
}

/*!
  Sets the starting address of registers to read

  @param registerReadAddr
 */
void MangoModbusRegisterModel::setRegisterReadAddr(int registerReadAddr)
{
    m_registerReadAddr = registerReadAddr;
}

/*!
  Returns the output type (interpretation of modbus registers)
 */
MangoModbusRegisterModel::OutputType MangoModbusRegisterModel::outputType() const
{
    return m_outputType;
}

/*!
  Sets the output type of modbus registers
 */
void MangoModbusRegisterModel::setOutputType(OutputType outputType)
{
    m_outputType = outputType;
}

