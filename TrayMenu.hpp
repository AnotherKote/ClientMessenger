#ifndef TRAYMENU_H
#define TRAYMENU_H

#include <QLabel>

class QSystemTrayIcon;
class QMenu;
class QAction;
class Settings;
class QFileSystemWatcher;
class QSettings;

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

private slots:
    void showPopup();
    void showSettings();
public:
    TrayMenu(QWidget *parent = 0);
    ~TrayMenu();

};

#endif // TRAYMENU_H
