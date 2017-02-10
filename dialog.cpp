#include "dialog.h"

Dialog::Dialog(QObject *parent) : QObject(parent)
{
}

QString Dialog::show(const QString &text, const QString &label) const
{
    return QInputDialog::getText(nullptr, text, label);
}
