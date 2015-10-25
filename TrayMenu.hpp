#ifndef TRAYMENU_H
#define TRAYMENU_H

#include <QLabel>
#include <QFile>

class QSystemTrayIcon;
class QMenu;
class QAction;
class Settings;
class QFileSystemWatcher;
class QSettings;
class PopupMessage;

class TrayMenu : public QLabel
{
    Q_OBJECT

private:
    QSystemTrayIcon *m_pTrayIcon;
    QMenu *m_pTrayIconMenu;
    QAction *m_pExitAction;
    Settings *m_pSettingsWindow;
    QFileSystemWatcher *m_pWatcher;
    QSettings *m_pSettings;
    PopupMessage *m_pPopup;

    bool parseFile(QFile &path, QString &out_header, QString &out_message);
private slots:
    void onDirectoryChanged();
    void showSettings();
public:
    TrayMenu(QWidget *parent = 0);
    ~TrayMenu();

};

#endif // TRAYMENU_H
