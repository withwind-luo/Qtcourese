#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // 所有按钮复用同一个槽，槽内通过 sender() 区分具体按键
    connect(ui->btnNum0,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnNum1,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnNum2,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnNum3,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnNum4,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnNum5,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnNum6,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnNum7,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnNum8,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnNum9,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnPeriod,&QPushButton::clicked,this,&MainWindow::btnPeriodClicked);
    connect(ui->btnPlus,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnMinus,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnMultiple,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnDivide,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnEqual,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnClear,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnClearAll,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnDel,&QPushButton::clicked,this,&MainWindow::btnDelClicked);
    connect(ui->btnSign,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnPercentage,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnInverse,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnSquare,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnSqrt,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnNumClicked()
{
    QString str = ui->display->text();
    QString str2 = qobject_cast<QPushButton*>(sender())->text();
    str += str2;
    ui->display->setText(str);

}

void MainWindow::btnPeriodClicked()
{
    QString str = ui->display->text();
    QString str2 = qobject_cast<QPushButton*>(sender())->text();
    if(!str.contains("."))
        str += str2;
    ui->display->setText(str);
}

void MainWindow::btnDelClicked()
{
    QString str = ui->display->text();
    str =str.left(str.length() - 1);
    ui->display->setText(str);
}
