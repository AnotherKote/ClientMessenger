#include "Settings.hpp"

#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QBoxLayout>
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QSettings>

Settings::Settings(QWidget *parent)
    : QWidget (parent)
    , m_pWatchDir (nullptr)
    , m_pBrowseButton (nullptr)
    , m_pOkButton (nullptr)
    , m_pCancelButton (nullptr)
//    , m_SavedText ("")
//    , m_SavedPath ("")
    , m_pSettings (nullptr)
{
    setWindowFlags(Qt::Dialog);

    m_pWatchDir = new QLineEdit(this);
    m_pBrowseButton = new QPushButton(this); ///<@todo set folder icon for this button
    m_pTextEdit = new QTextEdit(this);
    m_pOkButton = new QPushButton(this);
    m_pCancelButton = new QPushButton(this);
    m_pSettings = new QSettings(this);

    m_pBrowseButton->setIcon(QIcon("://icon/folder.png"));
    m_pOkButton->setText("Хокей");
    m_pCancelButton->setText("Отмена-на");

    connect(m_pBrowseButton, &QPushButton::clicked, this, &Settings::browseButtonClicked);
    connect(m_pOkButton, &QPushButton::clicked, this, &Settings::okButtonClicked);
    connect(m_pCancelButton, &QPushButton::clicked, this, &Settings::close);

    m_pTextEdit->setText(m_pSettings->value("/ClientMessenger/Text").toString());
    m_pWatchDir->setText(m_pSettings->value("/ClientMessenger/Path").toString());

    QHBoxLayout *firstLine = new QHBoxLayout;
    firstLine->addWidget(m_pWatchDir);
    firstLine->addWidget(m_pBrowseButton);

    QHBoxLayout *buttonsLine = new QHBoxLayout;
    buttonsLine->addStretch(1);
    buttonsLine->addWidget(m_pOkButton);
    buttonsLine->addStretch(1);
    buttonsLine->addWidget(m_pCancelButton);
    buttonsLine->addStretch(1);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(firstLine);
    mainLayout->addWidget(m_pTextEdit);
    mainLayout->addLayout(buttonsLine);

    setLayout(mainLayout);
    resize(QSize(800, 480));
}

void Settings::browseButtonClicked()
{
    m_pWatchDir->setText(QFileDialog::getExistingDirectory());
}

void Settings::okButtonClicked()
{
    if(!QDir(m_pWatchDir->text()).exists()){
        QMessageBox::warning(this, "Ошибка", "Директории\n \"" + m_pWatchDir->text() + "\"\n не существует ");
    } else {
        m_pSettings->setValue("/ClientMessenger/Text", m_pTextEdit->toPlainText());
        m_pSettings->setValue("/ClientMessenger/Path", m_pWatchDir->text());
//        m_SavedText = m_pTextEdit->toPlainText();
//        m_SavedPath = m_pWatchDir->text();
        close();
        emit settingsChanged();
    }
}

