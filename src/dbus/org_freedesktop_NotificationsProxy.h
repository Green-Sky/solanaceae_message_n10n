#ifndef ORG_FREEDESKTOP_NOTIFICATIONSPROXY_H
#define ORG_FREEDESKTOP_NOTIFICATIONSPROXY_H

#include <dbus-cxx.h>
#include <memory>
#include <stdint.h>
#include <string>
class org_freedesktop_NotificationsProxy
 : public DBus::InterfaceProxy {
protected:
org_freedesktop_NotificationsProxy(std::string name );
public:
    static std::shared_ptr<org_freedesktop_NotificationsProxy> create(std::string name = "org.freedesktop.Notifications" );
    std::vector<std::string> GetCapabilities( );
    uint32_t Notify(std::string app_name, uint32_t replaces_id, std::string app_icon, std::string summary, std::string body, std::vector<std::string> actions, std::map<std::string,DBus::Variant> hints, int32_t expire_timeout );
    void CloseNotification(uint32_t id );
    DBus::MultipleReturn<std::string,std::string,std::string,std::string> GetServerInformation( );
    std::shared_ptr<DBus::SignalProxy<void(uint32_t,uint32_t)>> signal_NotificationClosed( );
    std::shared_ptr<DBus::SignalProxy<void(uint32_t,std::string)>> signal_ActionInvoked( );
protected:
    std::shared_ptr<DBus::MethodProxy<std::vector<std::string>()>>  m_method_GetCapabilities;
    std::shared_ptr<DBus::MethodProxy<uint32_t(std::string,uint32_t,std::string,std::string,std::string,std::vector<std::string>,std::map<std::string,DBus::Variant>,int32_t)>>  m_method_Notify;
    std::shared_ptr<DBus::MethodProxy<void(uint32_t)>>  m_method_CloseNotification;
    std::shared_ptr<DBus::MethodProxy<DBus::MultipleReturn<std::string,std::string,std::string,std::string>()>>  m_method_GetServerInformation;
    std::shared_ptr<DBus::SignalProxy<void(uint32_t,uint32_t)>> m_signalproxy_NotificationClosed;
    std::shared_ptr<DBus::SignalProxy<void(uint32_t,std::string)>> m_signalproxy_ActionInvoked;
};
#endif /* ORG_FREEDESKTOP_NOTIFICATIONSPROXY_H */
