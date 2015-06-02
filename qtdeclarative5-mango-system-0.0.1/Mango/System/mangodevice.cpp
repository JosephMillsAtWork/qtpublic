/*
 * Joseph Mills
 */

#include "mangodevice.h"

#ifdef Q_OS_ANDROID
#include <QAndroidJniObject>
#endif

#ifdef Q_OS_IOS
#include <sys/sysctl.h>
#endif
/*!
 * \qmltype MangoDevice
 * \inqmlmodule Mango 0.1
 * \ingroup Mango
 * \inherits Item
 * \since 5.3
 *  The MangoDevice Qml Plugin. A simple plugin that can retuen the id of a device.
 */

/*!
\qmlproperty string MangoDevice::deviceModelIdentifier
returns back the model id also see deviceModelIdentifier()
*/


/*!
  \qmlsignal MangoDevice::deviceModelIdentifier()
  returns the device model id
*/
MangoDevice* MangoDevice::m_pInstance = NULL;
QString MangoDevice::m_deviceModelIdentifier = "";

MangoDevice* MangoDevice::instance(QQmlEngine *engine) {
    if (!m_pInstance) {
        m_pInstance = new MangoDevice(engine);
    }
    return m_pInstance;
}

MangoDevice::MangoDevice(QObject *parent) :
    QObject(parent)
{
#if defined(Q_OS_IOS)
    static const char key[] = "hw.machine";

    size_t size;
    sysctlbyname(key, NULL, &size, NULL, 0);

    char value[size];
    sysctlbyname(key, &value, &size, NULL, 0);

    m_deviceModelIdentifier = QString::fromLatin1(value);
#elif defined (Q_OS_ANDROID)
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    QAndroidJniObject resource = activity.callObjectMethod("getResources","()Landroid/content/res/Resources;");
    QAndroidJniObject configuration = resource.callObjectMethod("getConfiguration","()Landroid/content/res/Configuration;");

    int screenLayout = configuration.getField<int>("screenLayout");
    int SCREENLAYOUT_SIZE_MASK = 0x0000000f;
    int SCREENLAYOUT_SIZE_LARGE = 0x00000003;
    bool isLargeScreen = (screenLayout & SCREENLAYOUT_SIZE_MASK) >= SCREENLAYOUT_SIZE_LARGE;
    if (isLargeScreen) m_deviceModelIdentifier = "AndroidTablet";
    else m_deviceModelIdentifier = "AndroidPhone";
#else
    m_deviceModelIdentifier = "desktop";
#endif
    emit dataChanged();
}

QObject* MangoDevice::singletontype_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(scriptEngine)
    return MangoDevice::instance(engine);
}
