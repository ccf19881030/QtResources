#ifndef PREFERENCEDIALOG_H
#define PREFERENCEDIALOG_H

#include <QWidget>
#include <QStackedLayout>
#include <QListWidget>
#include <QCheckBox>
#include <QGroupBox>
#include <QLineEdit>
#include <QRadioButton>
#include <QDialogButtonBox>
#include <QLabel>

namespace Ui {
class PreferenceDialog;
}

class PreferenceDialog : public QWidget
{
    Q_OBJECT

public:
    explicit PreferenceDialog(QWidget *parent = 0);
    ~PreferenceDialog();

private:
    Ui::PreferenceDialog *ui;

private:
    void createAppearancePage();
    void createWebBrowserPage();
    void createMailAndNewsPage();
    void createAdvancedPage();

    QStackedLayout *stackedLayout;
    QListWidget *listWidget;
    QWidget *appearancePage;
    QWidget *webBrowserPage;
    QWidget *mailAndNewsPage;
    QWidget *advancedPage;
    QDialogButtonBox *buttonBox;

    QGroupBox *openGroupBox;
    QCheckBox *webBrowserCheckBox;
    QCheckBox *mailEditorCheckBox;
    QCheckBox *newsgroupCheckBox;
    QGroupBox *toolbarsGroupBox;
    QRadioButton *picturesAndTextRadioButton;
    QRadioButton *picturesOnlyRadioButton;
    QRadioButton *textOnlyRadioButton;
    QCheckBox *tooltipsCheckBox;
    QCheckBox *webSiteIconsCheckBox;
    QCheckBox *resizeImagesCheckBox;

    QGroupBox *displayGroupBox;
    QRadioButton *blankRadioButton;
    QRadioButton *homeRadioButton;
    QRadioButton *lastRadioButton;
    QGroupBox *homeGroupBox;
    QLabel *locationLabel;
    QLineEdit *locationLineEdit;
    QGroupBox *webButtonsGroupBox;
    QCheckBox *bookmarksCheckBox;
    QCheckBox *goCheckBox;
    QCheckBox *homeCheckBox;
    QCheckBox *searchCheckBox;
    QCheckBox *printCheckBox;

    QGroupBox *generalGroupBox;
    QCheckBox *confirmCheckBox;
    QCheckBox *rememberCheckBox;
    QGroupBox *mailButtonsGroupBox;
    QCheckBox *fileCheckBox;
    QCheckBox *nextCheckBox;
    QCheckBox *stopCheckBox;
    QCheckBox *junkCheckBox;

    QGroupBox *featuresGroupBox;
    QCheckBox *javaCheckBox;
    QCheckBox *ftpCheckBox;
    QLineEdit *ftpLineEdit;
};

#endif // PREFERENCEDIALOG_H
