#ifndef ALERT_H
#define ALERT_H

#include <QObject>
#include <QMessageBox>

class Alert : public QObject
{
    Q_OBJECT
public:
    explicit Alert(QObject *parent = 0);
public slots:
    void show(const QString &text);
};

#endif // ALERT_H
