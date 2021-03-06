/*
 * This file was generated by qdbusxml2cpp version 0.8
 * Command line was: qdbusxml2cpp -p OfonoManager ofono.xml org.ofono.Manager
 *
 * qdbusxml2cpp is Copyright (C) 2016 The Qt Company Ltd.
 *
 * This is an auto-generated file.
 * Do not edit! All changes made to it will be lost.
 */

#ifndef OFONOMANAGER_H
#define OFONOMANAGER_H

#include <QtCore/QObject>
#include <QtCore/QByteArray>
#include <QtCore/QList>
#include <QtCore/QMap>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtDBus/QtDBus>

/*
 * Proxy class for interface org.ofono.Manager
 */
class OrgOfonoManagerInterface: public QDBusAbstractInterface
{
    Q_OBJECT
public:
    static inline const char *staticInterfaceName()
    { return "org.ofono.Manager"; }

public:
    OrgOfonoManagerInterface(const QString &service, const QString &path, const QDBusConnection &connection, QObject *parent = 0);

    ~OrgOfonoManagerInterface();

public Q_SLOTS: // METHODS
    inline QDBusPendingReply<QVariantMap> GetModems()
    {
        QList<QVariant> argumentList;
        return asyncCallWithArgumentList(QStringLiteral("GetModems"), argumentList);
    }

Q_SIGNALS: // SIGNALS
    void ModemAdded(const QDBusObjectPath &path, const QVariantMap &properties);
    void ModemRemoved(const QDBusObjectPath &path);
};

namespace org {
  namespace ofono {
    typedef ::OrgOfonoManagerInterface Manager;
  }
}
#endif
