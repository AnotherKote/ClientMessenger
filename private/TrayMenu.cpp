#include "TrayMenu.hpp"
#include "Settings.hpp"

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication> // for qApp
#include <QMouseEvent>
#include <QMessageBox>
#include <QFileSystemWatcher>
#include <QSettings>
#include <QDebug>

TrayMenu::TrayMenu(QWidget *parent)
    : QLabel (parent)
    , m_pTrayIcon (nullptr)
    , m_pTrayIconMenu (nullptr)
    , m_pExitAction (nullptr)
    , m_pSettingsWindow (nullptr)
    , m_pWatcher (nullptr)
    , m_pSettings (nullptr)
{
    setWindowTitle("Message shower");

    m_pSettings = new QSettings(this);
    m_pWatcher = new QFileSystemWatcher(this);
    m_pSettingsWindow = new Settings(this);
    m_pTrayIconMenu = new QMenu(this);

    QAction *showPopup = new QAction ("Показать сообщение", this);
    QAction *settings  = new QAction ("Настройки...", this);
    m_pExitAction = new QAction ("Выход", this);

    m_pWatcher->addPath(m_pSettings->value("/ClientMessenger/Path").toString());

    connect(showPopup, &QAction::triggered, this, &TrayMenu::showPopup);
    connect(settings,  &QAction::triggered, this, &TrayMenu::showSettings);
    connect(m_pExitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(m_pSettingsWindow, &Settings::settingsChanged, [&](){
        for(auto dir: m_pWatcher->directories()){
            m_pWatcher->removePath(dir);
        }
        m_pWatcher->addPath(m_pSettings->value("/ClientMessenger/Path").toString());
    } );
    connect(m_pWatcher, &QFileSystemWatcher::directoryChanged, this, &TrayMenu::showPopup);

    m_pTrayIconMenu->addAction(showPopup);
    m_pTrayIconMenu->addAction(settings);
    m_pTrayIconMenu->addAction(m_pExitAction);

    m_pTrayIcon = new QSystemTrayIcon(this);
    m_pTrayIcon->setContextMenu(m_pTrayIconMenu);
    m_pTrayIcon->setIcon(QIcon(":/icon/main.ico"));
    m_pTrayIcon->show();
}

TrayMenu::~TrayMenu()
{
}

void TrayMenu::showPopup()
{
    QMessageBox::warning(this, "Внимание! Внимание! Говорит Германия!", m_pSettings->value("/ClientMessenger/Text").toString());
}

void TrayMenu::showSettings()
{
    m_pSettingsWindow->show();
}
