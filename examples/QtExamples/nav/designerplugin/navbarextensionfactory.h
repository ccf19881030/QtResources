#ifndef NAVBAREXTENSIONFACTORY_H
#define NAVBAREXTENSIONFACTORY_H

#include <QtDesigner/QExtensionFactory>

class QExtensionManager;

class NavBarExtensionFactory : public QExtensionFactory
{
    Q_OBJECT

public:
    explicit NavBarExtensionFactory(QExtensionManager *parent = 0);
    
protected:
    QObject *createExtension(QObject *object, const QString &iid, QObject *parent) const;
};

#endif // NAVBAREXTENSIONFACTORY_H
