#ifndef NAVBARPLUGIN_H
#define NAVBARPLUGIN_H

#include <QObject>
#include <QtDesigner/QDesignerCustomWidgetInterface>

class NavBarPlugin : public QObject, public QDesignerCustomWidgetInterface
{
    Q_OBJECT
#if QT_VERSION >= 0x050000
    Q_PLUGIN_METADATA(IID "com.MitrichSoftware.NavBarDesignerPlugin")
#endif
    Q_INTERFACES(QDesignerCustomWidgetInterface)

public:
    explicit NavBarPlugin(QObject *parent = 0);
    
    QString  name() const;
    QString  group() const;
    QString  toolTip() const;
    QString  whatsThis() const;
    QString  includeFile() const;
    QIcon    icon() const;
    bool     isContainer() const;
    QWidget *createWidget(QWidget *parent);
    bool     isInitialized() const;
    void     initialize(QDesignerFormEditorInterface *formEditor);
    QString  domXml() const;

private slots:
    void currentIndexChanged(int index);

private:
    bool initialized;
};

#endif // NAVBARPLUGIN_H
