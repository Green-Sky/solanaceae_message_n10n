#include "org_freedesktop_NotificationsProxy.h"

org_freedesktop_NotificationsProxy::org_freedesktop_NotificationsProxy(std::string name ) : DBus::InterfaceProxy( name ){
m_method_GetCapabilities = this->create_method<std::vector<std::string>()>("GetCapabilities");
m_method_Notify = this->create_method<uint32_t(std::string,uint32_t,std::string,std::string,std::string,std::vector<std::string>,std::map<std::string,DBus::Variant>,int32_t)>("Notify");
m_method_CloseNotification = this->create_method<void(uint32_t)>("CloseNotification");
m_method_GetServerInformation = this->create_method<DBus::MultipleReturn<std::string,std::string,std::string,std::string>()>("GetServerInformation");
m_signalproxy_NotificationClosed = this->create_signal<void(uint32_t,uint32_t)>( "NotificationClosed" );
m_signalproxy_ActionInvoked = this->create_signal<void(uint32_t,std::string)>( "ActionInvoked" );

}
std::shared_ptr<org_freedesktop_NotificationsProxy> org_freedesktop_NotificationsProxy::create(std::string name ){
return std::shared_ptr<org_freedesktop_NotificationsProxy>( new org_freedesktop_NotificationsProxy( name ));

}
std::vector<std::string> org_freedesktop_NotificationsProxy::GetCapabilities( ){
return (*m_method_GetCapabilities)();

}
uint32_t org_freedesktop_NotificationsProxy::Notify(std::string app_name, uint32_t replaces_id, std::string app_icon, std::string summary, std::string body, std::vector<std::string> actions, std::map<std::string,DBus::Variant> hints, int32_t expire_timeout ){
return (*m_method_Notify)(app_name,replaces_id,app_icon,summary,body,actions,hints,expire_timeout);

}
void org_freedesktop_NotificationsProxy::CloseNotification(uint32_t id ){
(*m_method_CloseNotification)(id);

}
DBus::MultipleReturn<std::string,std::string,std::string,std::string> org_freedesktop_NotificationsProxy::GetServerInformation( ){
return (*m_method_GetServerInformation)();

}
std::shared_ptr<DBus::SignalProxy<void(uint32_t,uint32_t)>> org_freedesktop_NotificationsProxy::signal_NotificationClosed( ){
return m_signalproxy_NotificationClosed;

}
std::shared_ptr<DBus::SignalProxy<void(uint32_t,std::string)>> org_freedesktop_NotificationsProxy::signal_ActionInvoked( ){
return m_signalproxy_ActionInvoked;

}
