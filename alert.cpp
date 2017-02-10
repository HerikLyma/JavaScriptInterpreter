#include "alert.h"

Alert::Alert(QObject *parent) : QObject(parent)
{

}

void Alert::show(const QString &text)
{
    QMessageBox::information(nullptr, "Alert", text);
}
