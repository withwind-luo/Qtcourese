#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QMessageBox>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionNew,&QAction::triggered,this,&MainWindow::on_actionNew_Trigger);
    connect(ui->actionOpen,&QAction::triggered,this,&MainWindow::on_actionOpen_Trigger);
    connect(ui->actionSave,&QAction::triggered,this,&MainWindow::on_actionSave_Trigger);
    connect(ui->actionSaveAs,&QAction::triggered,this,&MainWindow::on_actionSaveAs_Trigger);
    connect(ui->actionExit,&QAction::triggered,this,&QWidget::close);

    connect(ui->actionAbout,&QAction::triggered,this,&MainWindow::on_actionAbout_Trigger);
    connect(ui->actionFind,&QAction::triggered,this,&MainWindow::on_actionFind_Trigger);
    connect(ui->actionReplace,&QAction::triggered,this,&MainWindow::on_actionReplace_Trigger);
    connect(ui->textEdit,&QPlainTextEdit::textChanged,this,&MainWindow::on_textEdit_textChanged);

    statusLabel.setMaximumWidth(150);
    statusLabel.setText("length: " + QString::number(0) + "     lines:" + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCursorLabel.setMaximumWidth(150);
    statusCursorLabel.setText("Ln: " + QString::number(0) + "     COL:" + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("xxx"));
    ui->statusbar->addPermanentWidget(author);


}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::userEditConfirmed()
{
    if(textChanged){
        QString path = (filePath != "") ? filePath : "无标题.txt";

        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("提示");
        msg.setText(QString("是否将更改保存到\n") + "\"" + path + "\" ?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        int r = msg.exec();
        switch (r) {
        case QMessageBox::Yes:
            on_actionSave_Trigger();
            if(textChanged)
                return false;
            break;
        case QMessageBox::No:
            textChanged = false;
            break;
        case QMessageBox::Cancel:
            return false;
        }
    }
    return true;
}

void MainWindow::on_actionNew_Trigger()
{
    if(!userEditConfirmed())
        return;

    ui->textEdit->clear();
    filePath.clear();
    this->setWindowTitle(tr("新建文本文件 - 编辑器"));
    textChanged = false;
}

void MainWindow::on_actionOpen_Trigger()
{
    if(!userEditConfirmed())
        return;

    QString path = QFileDialog::getOpenFileName(this ,"打开文件" , "." ,tr("Text file (*.txt);;All (*.*)"));
    QFile file(path);

    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this ,"..", "打开文件失败");
        return;
    }

    filePath = path;

    QTextStream in (&file);
    QString text = in.readAll();
    ui->textEdit->setPlainText(text);
    file.close();

    this->setWindowTitle(QFileInfo(path).absoluteFilePath());
    textChanged = false;
}

void MainWindow::on_actionSave_Trigger()
{
    if(filePath.isEmpty())
    {
        on_actionSaveAs_Trigger();
        return;
    }

    QFile file(filePath);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this ,"保存", "保存文件失败");
        return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());
    textChanged = false;
}

void MainWindow::on_actionSaveAs_Trigger()
{
    QString path = QFileDialog::getSaveFileName(this ,"另存为" , "." ,tr("Text file (*.txt);;All (*.*)"));
    if(path.isEmpty())
        return;

    QFile file(path);

    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this ,"另存为", "保存文件失败");
        return;
    }

    filePath = path;

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();

    this->setWindowTitle(QFileInfo(path).absoluteFilePath());
    textChanged = false;
}

void MainWindow::on_actionAbout_Trigger()
{
    AboutDialog dlg;
    dlg.exec();
}

void MainWindow::on_actionFind_Trigger()
{
    SearchDialog dlg;
    dlg.exec();
}

void MainWindow::on_actionReplace_Trigger()
{
    ReplaceDialog dlg;
    dlg.exec();
}

void MainWindow::on_textEdit_textChanged()
{
    if( !textChanged ){
        if(!(this->windowTitle().contains("*")))
            this->setWindowTitle("*" + this->windowTitle());
        textChanged = true;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(userEditConfirmed())
        event->accept();
    else
        event->ignore();
}
