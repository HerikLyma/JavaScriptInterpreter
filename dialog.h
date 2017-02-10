#ifndef DIALOG_H
#define DIALOG_H

#include <QObject>
#include <QInputDialog>

class Dialog : public QObject
{
    Q_OBJECT
public:
    explicit Dialog(QObject *parent = nullptr);
public slots:    
    QString show(const QString &text, const QString &label) const;
};

#endif // DIALOG_H
