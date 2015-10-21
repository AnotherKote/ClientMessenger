#ifndef SETTINGS_H
#define SETTINGS_H

#include <QWidget>
//#include <QString>

class QLineEdit;
class QPushButton;
class QTextEdit;
class QSettings;

class Settings : public QWidget
{
    Q_OBJECT

private:
    QLineEdit *m_pWatchDir;
    QPushButton *m_pBrowseButton;
    QTextEdit *m_pTextEdit;
    QPushButton *m_pOkButton;
    QPushButton *m_pCancelButton;
    QSettings *m_pSettings;

//    QString m_SavedText;
//    QString m_SavedPath;
public:
    explicit Settings(QWidget *parent = 0);
//    QString text() const { return m_SavedText; }
//    QString path() const { return m_SavedPath; }

private slots:
    void browseButtonClicked();
    void okButtonClicked();

signals:
    void settingsChanged();
};

#endif // SETTINGS_H
