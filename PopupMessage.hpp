#ifndef POPUPMESSAGE_H
#define POPUPMESSAGE_H

#include <QWidget>
#include <QString>

class QPushButton;
class QLabel;
class QTimer;

class PopupMessage : public QWidget
{
    Q_OBJECT

    QPushButton *m_pButtonOk;
    QLabel *m_pText;
    QTimer *m_pTimerEverySecond;
    QTimer *m_pTimerEveryThirtySeconds;

    QString getColor(int seed);
public:
    explicit PopupMessage(QWidget *parent = 0);
    void setText(QString &text);
signals:

public slots:
    void everySecond();
    void everyThirtySeconds();

    // QWidget interface
protected:
    virtual void showEvent(QShowEvent *);
    virtual void hideEvent(QHideEvent *);
};

#endif // POPUPMESSAGE_H
