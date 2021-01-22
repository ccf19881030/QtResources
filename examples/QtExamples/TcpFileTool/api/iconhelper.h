#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QObject>
#include <QFont>
#include <QFontDatabase>
#include <QMutex>
#include <QLabel>
#include <QAbstractButton>
#include <QIcon>
#include <QApplication>

class IconHelper : public QObject
{
private:
    explicit IconHelper(QObject *parent = 0);

    static IconHelper *_instance;

    QFont iconFont;
    QSize icoSize;
    QColor icoTextColor;
    int icoTextSize;

public:
    static IconHelper *Instance() {
        static QMutex mutex;
        if (!_instance) {
            QMutexLocker locker(&mutex);
            if (!_instance) {
                _instance = new IconHelper;
            }
        }
        return _instance;
    }

    void SetIcon(QLabel *lab, QChar c);
    void SetIcon(QAbstractButton *btn, QChar c);

    void SetIcon(QLabel *lab, QChar c, int size);
    void SetIcon(QAbstractButton *btn, QChar c, int size);

    void SetIcoMain(QLabel *labMain);
    void SetIcoMenu(QAbstractButton *btnMenu);
    void SetIcoMin(QAbstractButton *btnMin);
    void SetIcoMax(QAbstractButton *btnMax);
    void SetIcoNormal(QAbstractButton *btnNormal);
    void SetIcoClose(QAbstractButton *btnClose);

    void SetIcoMain(QLabel *labMain, int size);
    void SetIcoMenu(QAbstractButton *btnMenu, int size);
    void SetIcoMin(QAbstractButton *btnMin, int size);
    void SetIcoMax(QAbstractButton *btnMax, int size);
    void SetIcoNormal(QAbstractButton *btnNormal, int size);
    void SetIcoClose(QAbstractButton *btnClose, int size);

    void SetIcoSize(QSize icoSize) {
        this->icoSize = icoSize;
    }

    void SetIcoTextColor(QColor icoTextColor) {
        this->icoTextColor = icoTextColor;
    }

    void SetIcoTextSize(int icoTextSize) {
        this->icoTextSize = icoTextSize;
    }

    QIcon IcoMenu();
    QIcon IcoMin();
    QIcon IcoMax();
    QIcon IcoNormal();
    QIcon IcoClose();

    QIcon IcoMenu(QChar c);
    QIcon IcoMin(QChar c);
    QIcon IcoMax(QChar c);
    QIcon IcoNormal(QChar c);
    QIcon IcoClose(QChar c);

    QIcon Ico(QChar c);
    QIcon Ico(QChar c, int size);

};

#endif // ICONHELPER_H
