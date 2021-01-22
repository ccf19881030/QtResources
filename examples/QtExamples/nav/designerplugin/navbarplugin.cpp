#include <QtDesigner/QExtensionFactory>
#include <QtDesigner/QExtensionManager>
#include <QtDesigner/QDesignerFormEditorInterface>
#include <QtDesigner/QDesignerFormWindowInterface>
#include <QtDesigner/QDesignerContainerExtension>
#include <QtDesigner/QDesignerPropertySheetExtension>
#include <QtPlugin>
#include <QIcon>

#include "navbarplugin.h"
#include "navbarextensionfactory.h"
#include "navbar.h"

NavBarPlugin::NavBarPlugin(QObject *parent) :
    QObject(parent)
{
    initialized = false;
}

QString NavBarPlugin::name() const
{
    return QLatin1String("NavBar");
}

QString NavBarPlugin::group() const
{
    return QLatin1String("Display Widgets [Examples]");
}

QString NavBarPlugin::toolTip() const
{
    return QString();
}

QString NavBarPlugin::whatsThis() const
{
    return QString();
}

QString NavBarPlugin::includeFile() const
{
    return QLatin1String("navbar.h");
}

QIcon NavBarPlugin::icon() const
{
    return QIcon();
}

bool NavBarPlugin::isContainer() const
{
    return true;
}

QWidget *NavBarPlugin::createWidget(QWidget *parent)
{
    NavBar *widget = new NavBar(parent);
    widget->setVisibleRows(0);
    connect(widget, SIGNAL(currentChanged(int)), SLOT(currentIndexChanged(int)));
    return widget;
}

bool NavBarPlugin::isInitialized() const
{
    return initialized;
}

void NavBarPlugin::initialize(QDesignerFormEditorInterface *formEditor)
{
    if(initialized)
        return;

    QExtensionManager *manager = formEditor->extensionManager();
    QExtensionFactory *factory = new NavBarExtensionFactory(manager);
    Q_ASSERT(manager != 0);
    manager->registerExtensions(factory, Q_TYPEID(QDesignerContainerExtension));

    initialized = true;
}

QString NavBarPlugin::domXml() const
{
    return QLatin1String(
        "<ui language=\"c++\">"
        "    <widget class=\"NavBar\" name=\"navbar\">"
        "        <widget class=\"QWidget\" name=\"page\" />"
        "    </widget>"
        "    <customwidgets>"
        "        <customwidget>"
        "            <class>NavBar</class>"
        "            <extends>QFrame</extends>"
        "            <addpagemethod>addPage</addpagemethod>"
        "        </customwidget>"
        "    </customwidgets>"
        "</ui>");
}

void NavBarPlugin::currentIndexChanged(int index)
{
    Q_UNUSED(index);
    NavBar *widget = qobject_cast<NavBar*>(sender());

    if (widget)
    {
        QDesignerFormWindowInterface *form = QDesignerFormWindowInterface::findFormWindow(widget);

        if (form)
            form->emitSelectionChanged();
    }
}
#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(navbarplugin, NavBarPlugin)
#endif
