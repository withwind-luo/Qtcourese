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
#include <QColorDialog>
#include <QTextCharFormat>
#include <QFontDialog>

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

    connect(ui->actionUndo,&QAction::triggered,this,&MainWindow::on_actionUndo_Trigger);
    connect(ui->actionRedo,&QAction::triggered,this,&MainWindow::on_actionRedo_Trigger);
    connect(ui->actionCut,&QAction::triggered,this,&MainWindow::on_actionCut_Trigger);
    connect(ui->actionCopy,&QAction::triggered,this,&MainWindow::on_actionCopy_Trigger);
    connect(ui->actionPaste,&QAction::triggered,this,&MainWindow::on_actionPaste_Trigger);

    connect(ui->actionFont,&QAction::triggered,this,&MainWindow::on_actionFont_Trigger);
    connect(ui->actionFontColor,&QAction::triggered,this,&MainWindow::on_actionFontColor_Trigger);
    connect(ui->actionBackgroundColor,&QAction::triggered,this,&MainWindow::on_actionBackgroundColor_Trigger);
    connect(ui->actionFontBackgroundColor,&QAction::triggered,this,&MainWindow::on_actionFontBackgroundColor_Trigger);
    connect(ui->actionWordWrap,&QAction::triggered,this,&MainWindow::on_actionWordWrap_Trigger);

    connect(ui->actionAbout,&QAction::triggered,this,&MainWindow::on_actionAbout_Trigger);
    connect(ui->actionFind,&QAction::triggered,this,&MainWindow::on_actionFind_Trigger);
    connect(ui->actionReplace,&QAction::triggered,this,&MainWindow::on_actionReplace_Trigger);
    connect(ui->textEdit,&QPlainTextEdit::textChanged,this,&MainWindow::on_textEdit_textChanged);
    connect(ui->textEdit,&QPlainTextEdit::undoAvailable,this,&MainWindow::on_textEdit_undoAvailable);
    connect(ui->textEdit,&QPlainTextEdit::redoAvailable,this,&MainWindow::on_textEdit_redoAvailable);
    connect(ui->textEdit,&QPlainTextEdit::copyAvailable,this,&MainWindow::on_textEdit_copyAvailable);

    statusLabel.setMaximumWidth(150);
    statusLabel.setText("length: " + QString::number(0) + "     lines:" + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCursorLabel.setMaximumWidth(150);
    statusCursorLabel.setText("Ln: " + QString::number(0) + "     COL:" + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("xxx"));
    ui->statusbar->addPermanentWidget(author);

    on_actionNew_Trigger();
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionPaste->setEnabled(false);


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

void MainWindow::on_textEdit_undoAvailable(bool available)
{
    ui->actionUndo->setEnabled(available);
}


void MainWindow::on_textEdit_redoAvailable(bool available)
{
    ui->actionRedo->setEnabled(available);
}

void MainWindow::on_textEdit_copyAvailable(bool available)
{
    ui->actionCopy->setEnabled(available);
    ui->actionCut->setEnabled(available);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(userEditConfirmed())
        event->accept();
    else
        event->ignore();
}

void MainWindow::on_actionUndo_Trigger()
{
    ui->textEdit->undo();
}

void MainWindow::on_actionRedo_Trigger()
{
    ui->textEdit->redo();
}

void MainWindow::on_actionCut_Trigger()
{
    ui->textEdit->cut();
    ui->actionPaste->setEnabled(true);
}

void MainWindow::on_actionCopy_Trigger()
{
    ui->textEdit->copy();
    ui->actionPaste->setEnabled(true);
}

void MainWindow::on_actionPaste_Trigger()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionFont_Trigger()
{
    if (!ui->textEdit->textCursor().hasSelection())
        return;

    bool ok;
    QFont font = QFontDialog::getFont(&ok, ui->textEdit->currentCharFormat().font(), this, "选择字体");
    if (!ok)
        return;

    QTextCharFormat fmt;
    fmt.setFont(font);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actionFontColor_Trigger()
{
    if (!ui->textEdit->textCursor().hasSelection())
        return;

    QColor color = QColorDialog::getColor(ui->textEdit->currentCharFormat().foreground().color(), this, "选择颜色");
    if (!color.isValid())
        return;

    QTextCharFormat fmt;
    fmt.setForeground(color);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}


void MainWindow::on_actionBackgroundColor_Trigger()
{
    QColor color = QColorDialog::getColor(Qt::black ,this , "选择颜色");
    if (color.isValid()) {
        ui->textEdit->setStyleSheet(QString("QPlainTextEdit {background-color: %1};").arg(color.name()));
    }
}

void MainWindow::on_actionFontBackgroundColor_Trigger()
{
    if (!ui->textEdit->textCursor().hasSelection())
        return;

    QColor color = QColorDialog::getColor(Qt::white, this, "选择字体背景色");
    if (!color.isValid())
        return;

    QTextCharFormat fmt;
    fmt.setBackground(color);
    ui->textEdit->mergeCurrentCharFormat(fmt);
}

void MainWindow::on_actionWordWrap_Trigger()
{
    QPlainTextEdit::LineWrapMode mode = ui->textEdit->lineWrapMode();
    if (mode == QPlainTextEdit::NoWrap) {
        ui->textEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);
        ui->actionWordWrap->setChecked(true);
    } else {
        ui->textEdit->setLineWrapMode(QPlainTextEdit::NoWrap);
        ui->actionWordWrap->setChecked(false);
    }
}
