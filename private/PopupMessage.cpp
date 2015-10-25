#include "PopupMessage.hpp"

#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QTimer>
#include <QDebug>


PopupMessage::PopupMessage(QWidget *parent)
    : QWidget (parent)
    , m_pButtonOk (nullptr)
    , m_pText (nullptr)
    , m_pTimerEverySecond (nullptr)
    , m_pTimerEveryThirtySeconds (nullptr)
{
    setWindowFlags(Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint|Qt::Window);

    m_pButtonOk = new QPushButton("OK");
    m_pText = new QLabel ("Message");
    m_pTimerEverySecond = new QTimer(this);
    m_pTimerEveryThirtySeconds = new QTimer(this);

    m_pText->setStyleSheet("font: 18pt;");
    m_pText->setAlignment(Qt::AlignCenter);
    m_pText->setWordWrap(true);

    m_pTimerEverySecond->setInterval(1000);
    m_pTimerEveryThirtySeconds->setInterval(30 * 1000);
    m_pTimerEveryThirtySeconds->setSingleShot(true);

    connect (m_pButtonOk, &QPushButton::clicked, [&](){hide();});
    connect (m_pTimerEverySecond, &QTimer::timeout, this, &PopupMessage::everySecond);
    connect (m_pTimerEveryThirtySeconds, &QTimer::timeout, this, &PopupMessage::everyThirtySeconds);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addWidget(m_pText);
    mainLayout->addWidget(m_pButtonOk);

    setLayout(mainLayout);
    resize(QSize(800, 640));
}

void PopupMessage::setText(QString &text)
{
    m_pText->setText(text);
}

void PopupMessage::everySecond()
{
    m_pText->setStyleSheet("color:" + getColor(m_pTimerEveryThirtySeconds->remainingTime()/1000) + ";font: 18pt;");
    if(!m_pButtonOk->isEnabled()){
        m_pButtonOk->setText("OK (" + QString::number(m_pTimerEveryThirtySeconds->remainingTime()/1000) + ")");
    } else {
        m_pButtonOk->setText("OK");
    }
}

QString PopupMessage::getColor(int seed)
{
    QVector<QString> colors = {"red", "green", "blue", "black", "yellow", "marine", "orange", "purple"};
    return colors.at(seed%colors.size());
}

void PopupMessage::everyThirtySeconds()
{
    m_pButtonOk->setEnabled(true);
    m_pTimerEverySecond->stop();
    m_pButtonOk->setText("OK");
}

void PopupMessage::showEvent(QShowEvent *)
{
    m_pTimerEverySecond->start();
    m_pTimerEveryThirtySeconds->start();
    m_pButtonOk->setEnabled(false);
}

void PopupMessage::hideEvent(QHideEvent *)
{
    m_pTimerEverySecond->stop();
    m_pTimerEveryThirtySeconds->stop();
}
