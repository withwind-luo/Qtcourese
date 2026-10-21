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
    connect(ui->btnPlus,&QPushButton::clicked,this,&MainWindow::btnBinaryOperatorClicked);
    connect(ui->btnMinus,&QPushButton::clicked,this,&MainWindow::btnBinaryOperatorClicked);
    connect(ui->btnMultiple,&QPushButton::clicked,this,&MainWindow::btnBinaryOperatorClicked);
    connect(ui->btnDivide,&QPushButton::clicked,this,&MainWindow::btnBinaryOperatorClicked);
    connect(ui->btnEqual,&QPushButton::clicked,this,&MainWindow::btnbtnEqualClicked);
    connect(ui->btnClear,&QPushButton::clicked,this,&MainWindow::btnNumClicked);
    connect(ui->btnClearAll,&QPushButton::clicked,this,&MainWindow::btnClearAllClicked);
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
    QString digit = qobject_cast<QPushButton*>(sender())->text();
    if(digit == "0" && operand == "0")
        digit = "";
    if(digit != "0" && operand == "0")
        operand = "";
    operand += digit;
    ui->display->setText(operand);

}

void MainWindow::btnBinaryOperatorClicked()
{
    opcode = qobject_cast<QPushButton*>(sender())->text();
    if(operand != "")
    {
        operands.push_back(operand);
        operand = "";
    }
    opcodes.push_back(opcode);

    QString result = calculation();
    ui->display->setText(result);
}

void MainWindow::btnbtnEqualClicked()
{
    if(operand != "")
    {
        operands.push_back(operand);
        operand = "";
    }

    QString result = calculation();
    ui->display->setText(result);
}

void MainWindow::btnPeriodClicked()
{
    if(!operand.contains("."))
        operand += qobject_cast<QPushButton*>(sender())->text();
    ui->display->setText(operand);
}

void MainWindow::btnDelClicked()
{
    operand = operand.left(operand.length() - 1);
    ui->display->setText(operand);
}

void MainWindow::btnClearAllClicked()
{
    operand.clear();
    ui->display->setText(operand);
}

QString MainWindow::calculation(bool *ok)
{
    Q_UNUSED(ok);

    double result = 0;
    if(operands.size() == 2 && opcodes.size() > 0)
    {
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        QString op = opcodes.front();
        opcodes.pop_front();

        if(op == "+")
        {
            result = operand1 +operand2;
        }
        else if(op == "−")
        {
            result = operand1 - operand2;
        }
        else if(op == "×")
        {
            result = operand1 * operand2;
        }
        else if(op == "÷")
        {
            result = operand1 / operand2;
        }

        // 把本次计算结果压回操作数栈，供连续运算使用
        QString resultStr = QString::number(result);
        operands.push_back(resultStr);
        return resultStr;
    }
    else
    {
        // 操作数不足以完成一次运算时，保持当前显示内容
        return ui->display->text();
    }
}

