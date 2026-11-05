#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "aboutdialog.h"
#include "searchdialog.h"
#include "replacedialog.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionAbout,&QAction::triggered,this,&MainWindow::on_actionAbout_Trigger);
    connect(ui->actionFind,&QAction::triggered,this,&MainWindow::on_actionFind_Trigger);
    connect(ui->actionReplace,&QAction::triggered,this,&MainWindow::on_actionReplace_Trigger);

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
