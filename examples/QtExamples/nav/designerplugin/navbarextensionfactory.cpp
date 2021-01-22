#include "navbarextensionfactory.h"
#include "navbarcontainerextension.h"
#include "navbar.h"

NavBarExtensionFactory::NavBarExtensionFactory(QExtensionManager *parent) :
    QExtensionFactory(parent)
{
}

QObject *NavBarExtensionFactory::createExtension(QObject *object, const QString &iid, QObject *parent) const
{
    NavBar *widget = qobject_cast<NavBar*>(object);

    if (widget && (iid == Q_TYPEID(QDesignerContainerExtension)))
        return new NavBarContainerExtension(widget, parent);
    else
        return 0;
}
