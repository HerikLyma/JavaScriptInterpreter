#ifndef JSCONSOLE_H
#define JSCONSOLE_H

#include <QDebug>
#include <QObject>

class JSConsole : public QObject
{
    Q_OBJECT
public:
    explicit JSConsole(QObject *parent = 0);
signals:
    void newLog(QString);
public slots:
    void log(QString msg);
};

#endif // JSCONSOLE_H
