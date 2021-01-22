#ifndef TRACKEDITOR_H
#define TRACKEDITOR_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QTableWidget>
#include <QList>
#include <QPushButton>
#include <QVBoxLayout>
#include "trackdelegate.h"

namespace Ui {
class TrackEditor;
}

class Track
{
public:
    Track(const QString &title = "", int duration = 0);

    QString title;
    int duration;
};

class TrackEditor : public QDialog
{
    Q_OBJECT

public:
    explicit TrackEditor(QList<Track> *tracks, QWidget *parent = 0);
    ~TrackEditor();

    void done(int result);

private slots:
    void addTrack();

private:
    QTableWidget *tableWidget;
    QDialogButtonBox *buttonBox;
    QList<Track> *tracks;

private:
    Ui::TrackEditor *ui;
};

#endif // TRACKEDITOR_H
