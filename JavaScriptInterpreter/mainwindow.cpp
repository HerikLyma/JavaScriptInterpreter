#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList list;
    list << "function" << "var" << "console" << "log" << "prompt" << "return"
         << "parseInt" << "parseFloat" << "Math" << "pow" << "alert" << "for"
         << "if" << "if else" << "else" << "while";

    completer   = new QCompleter(list, ui->txtEdtCode);
    highlighter = new Highlighter(ui->txtEdtCode->document());
    console     = new JSConsole(this);
    dialog      = new Dialog(this);
    alert       = new Alert(this);    

    connect(console, SIGNAL(newLog(QString)), this, SLOT(newMsg(QString)));
    connect(ui->txtEdtCode, SIGNAL(f5Pressed()), this, SLOT(on_pshBtnExecute_clicked()));

    QJSValue consoleObj = jsEngine.newQObject(console);
    QJSValue dialogObj  = jsEngine.newQObject(dialog);
    QJSValue alertObj   = jsEngine.newQObject(alert);

    jsEngine.globalObject().setProperty("console", consoleObj);
    jsEngine.globalObject().setProperty("dialog" , dialogObj);
    jsEngine.globalObject().setProperty("alerts" , alertObj);

    functions  = "function prompt(text, label) { return dialog.show(text, label); }";
    functions += "function alert(text) { alerts.show(text); }";
    functions += "function print(text) { console.log(text); }";


    ui->txtEdtCode->setCompleter(completer);
    ui->txtEdtCode->setTabStopWidth(24);

    QFont font("Times", 11);
    ui->txtEdtCode->setFont(font);        
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pshBtnExecute_clicked()
{        
    QString tmp = ui->txtEdtCode->toPlainText();
    ui->txtEdtCode->clear();
    ui->txtEdtCode->setPlainText(tmp);

    html += "<hr/><font color=\"red\"><b>Execution " + QString::number(execution) + "</b></font><hr/><br/>";
    ui->txtEdtResult->setHtml(html);
    QJSValue result = jsEngine.evaluate(functions + ui->txtEdtCode->toPlainText());    


    if(result.isError())
    {
        QString lineNumber = result.property("lineNumber").toString();
        QTextEdit::ExtraSelection highlight;
        highlight.cursor = ui->txtEdtCode->textCursor();
        highlight.cursor.setPosition(ui->txtEdtCode->document()->findBlockByLineNumber(lineNumber.toInt() - 1).position());
        highlight.format.setProperty(QTextFormat::FullWidthSelection, true);
        highlight.format.setBackground(Qt::red);
        QList<QTextEdit::ExtraSelection> extras;
        extras << highlight;
        ui->txtEdtCode->setExtraSelections( extras );

        html += "<b>" + result.toString() + ", line " + lineNumber + "</b><br/>";
        ui->txtEdtResult->setHtml(html);
        scrollToBottom();
    }
    ++execution;
}

void MainWindow::newMsg(QString msg)
{
    html += "<b>" + msg + "</b><br/>";
    ui->txtEdtResult->setHtml(html);
    scrollToBottom();
}

void MainWindow::on_pshBtnClear_clicked()
{
    html.clear();
    ui->txtEdtResult->clear();
    execution = 0;
}

void MainWindow::on_pshBtnClearCode_clicked()
{
    ui->txtEdtCode->clear();
}

void MainWindow::scrollToBottom()
{
    QScrollBar *scroll = ui->txtEdtResult->verticalScrollBar();
    scroll->setValue(scroll->maximum());
}

void MainWindow::on_actionOpen_File_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open JavaScript file", "", "JS(*.js)");
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::warning(this, "Open file error", file.errorString());
        }
        else
        {
            html = file.readAll();
            ui->txtEdtCode->clear();
            ui->txtEdtCode->setPlainText(html);
        }
        file.close();
    }
}

void MainWindow::on_actionSave_file_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Save JavaScript file", "", "JS(*.js)");
    if(!fileName.isEmpty())
    {
        if(!fileName.toLower().endsWith(".js"))
            fileName += ".js";
        QFile file(fileName);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::warning(this, "Save file error", file.errorString());
        }
        else
        {
            file.write(ui->txtEdtCode->toPlainText().toLatin1());
        }
        file.close();
    }
}

void MainWindow::showMaximized()
{
    QMainWindow::showMaximized();
    double height = ui->txtEdtCode->height();
    ui->txtEdtResult->setMaximumHeight(height / 1.5);
}
