#include "TrayMenu.hpp"
#include "Settings.hpp"
#include "PopupMessage.hpp"

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication> // for qApp
#include <QMouseEvent>
#include <QMessageBox>
#include <QFileSystemWatcher>
#include <QSettings>
#include <QDir>
#include <QStringList>
#include <QDebug>

TrayMenu::TrayMenu(QWidget *parent)
    : QLabel (parent)
    , m_pTrayIcon (nullptr)
    , m_pTrayIconMenu (nullptr)
    , m_pExitAction (nullptr)
    , m_pSettingsWindow (nullptr)
    , m_pWatcher (nullptr)
    , m_pSettings (nullptr)
    , m_pPopup (nullptr)
{
    setWindowTitle("Message shower");

    m_pPopup = new PopupMessage(this);
    m_pSettings = new QSettings(this);
    m_pWatcher = new QFileSystemWatcher(this);
    m_pSettingsWindow = new Settings(this);
    m_pTrayIconMenu = new QMenu(this);

    QAction *showPopup = new QAction ("Показать сообщение", this);
    QAction *settings  = new QAction ("Настройки...", this);
    m_pExitAction = new QAction ("Выход", this);

    m_pWatcher->addPath(m_pSettings->value("/ClientMessenger/Path").toString());

    connect(showPopup, &QAction::triggered, this, &TrayMenu::onDirectoryChanged);
    connect(settings,  &QAction::triggered, this, &TrayMenu::showSettings);
    connect(m_pExitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(m_pSettingsWindow, &Settings::settingsChanged, [&](){
        for(auto dir: m_pWatcher->directories()){
            m_pWatcher->removePath(dir);
        }
        m_pWatcher->addPath(m_pSettings->value("/ClientMessenger/Path").toString());
    } );
    connect(m_pWatcher, &QFileSystemWatcher::directoryChanged, this, &TrayMenu::onDirectoryChanged);

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

bool TrayMenu::parseFile(QFile &path, QString &out_header, QString &out_message)
{
    bool ret = false;
    if(path.open(QIODevice::ReadOnly)){
        QStringList fileData(QString(path.readAll()).split(";"));
        if(fileData.size() >= 2){
            out_header = fileData.at(0);
            out_message = fileData.at(1);
        } else if (fileData.size() == 1) {
            out_header = "Внимание!"; //default header
            out_message = fileData.front();
        }
    }
    return ret;
}

void TrayMenu::onDirectoryChanged()
{
    QDir dir(m_pWatcher->directories().front());
    QFile messageFile(dir.filePath("message.txt"));
    if(messageFile.exists()){
        QString header;
        QString message;
        parseFile(messageFile, header, message);
        //<@todo m_pPopup->setHeader(header)
        m_pPopup->setText(message);
        m_pPopup->show();
//        QMessageBox::warning(this, header, message);
    }
}

void TrayMenu::showSettings()
{
    m_pSettingsWindow->show();
}
