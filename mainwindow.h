#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QJSEngine>
#include <QJSValue>
#include <QDebug>
#include <QScrollBar>
#include <QCompleter>
#include <alert.h>
#include <jsconsole.h>
#include <dialog.h>
#include <highlighter.h>
#include <QFileDialog>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

    ~MainWindow();
private slots:
    void on_pshBtnExecute_clicked();

    void newMsg(QString msg);

    void on_pshBtnClear_clicked();

    void on_pshBtnClearCode_clicked();   

    void scrollToBottom();

    void on_actionOpen_File_triggered();

    void on_actionSave_file_triggered();

private:
    Ui::MainWindow *ui;        

    QJSEngine jsEngine;

    QString html;

    QString functions;

    JSConsole *console;

    Dialog *dialog;

    Alert *alert;

    QCompleter *completer;

    Highlighter *highlighter;   

    int execution = 0;
};

#endif // MAINWINDOW_H
