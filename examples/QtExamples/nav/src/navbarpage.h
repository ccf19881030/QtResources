#ifndef NAVBARPAGE_H
#define NAVBARPAGE_H

#include <QAction>
#include <QToolButton>

struct NavBarPage
{
    QToolButton *button;
    QAction     *action;

    inline void    setText(const QString &text)   { action->setText(text);       }
    inline void    setIcon(const QIcon &icon)     { action->setIcon(icon);       }
    inline void    setName(const QString &name)   { action->setObjectName(name); }
    inline void    setEnabled(bool enabled)       { action->setEnabled(enabled); }
    inline void    setVisible(bool visible)       { action->setVisible(visible);
                                                    button->setVisible(visible); }
    inline QString text() const                   { return action->text();       }
    inline QIcon   icon() const                   { return action->icon();       }
    inline QString name() const                   { return action->objectName(); }
    inline bool    isEnabled() const              { return action->isEnabled();  }
    inline bool    isVisible() const              { return action->isVisible();  }
};

QList<NavBarPage> sortNavBarPageList(const QList<NavBarPage> &pages, const QStringList &order);

#endif // NAVBARPAGE_H
