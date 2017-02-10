#include "jsconsole.h"

JSConsole::JSConsole(QObject *parent) : QObject(parent)
{

}

void JSConsole::log(QString msg)
{
    qDebug() << "jsConsole: "<< msg;
    emit newLog(msg);
}
