#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "math.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 键盘按键 -> 对应按钮的映射
    keyBtns = {
        {Qt::Key_0, ui->btnNum0},
        {Qt::Key_1, ui->btnNum1},
        {Qt::Key_2, ui->btnNum2},
        {Qt::Key_3, ui->btnNum3},
        {Qt::Key_4, ui->btnNum4},
        {Qt::Key_5, ui->btnNum5},
        {Qt::Key_6, ui->btnNum6},
        {Qt::Key_7, ui->btnNum7},
        {Qt::Key_8, ui->btnNum8},
        {Qt::Key_9, ui->btnNum9},
        {Qt::Key_Period, ui->btnPeriod},
        {Qt::Key_Plus, ui->btnPlus},
        {Qt::Key_Minus, ui->btnMinus},
        {Qt::Key_Asterisk, ui->btnMultiple},
        {Qt::Key_Slash, ui->btnDivide},
        {Qt::Key_multiply, ui->btnMultiple},
        {Qt::Key_division, ui->btnDivide},
        {Qt::Key_Equal, ui->btnEqual},
        {Qt::Key_Return, ui->btnEqual},
        {Qt::Key_Enter, ui->btnEqual},
        {Qt::Key_Backspace, ui->btnDel},
        {Qt::Key_Escape, ui->btnClearAll},
        {Qt::Key_Percent, ui->btnPercentage},
    };

    // 数字键的鼠标点击连接（键盘事件通过 keyBtns 找到按钮后 animateClick）
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
    connect(ui->btnSign,&QPushButton::clicked,this,&MainWindow::btnUnaryOperatorClicked);
    connect(ui->btnPercentage,&QPushButton::clicked,this,&MainWindow::btnUnaryOperatorClicked);
    connect(ui->btnInverse,&QPushButton::clicked,this,&MainWindow::btnUnaryOperatorClicked);
    connect(ui->btnSquare,&QPushButton::clicked,this,&MainWindow::btnUnaryOperatorClicked);
    connect(ui->btnSqrt,&QPushButton::clicked,this,&MainWindow::btnUnaryOperatorClicked);
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

void MainWindow::btnUnaryOperatorClicked()
{
    if(operand != "")
    {
        double result = operand.toDouble();

        QString op = qobject_cast<QPushButton*>(sender())->text();
        if(op == "%")
            result /= 100;
        else if(op == "1/x")
            result = 1 / result;
        else if(op == "x²")
            result *= result;
        else if(op == "²√x")
            result = sqrt(result);
        else if(op == "±")
            result = -result;

        operand = QString::number(result);
        ui->display->setText(operand);
    }
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
    operands.clear();
    ui->display->setText(operand);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    QPushButton *btn = keyBtns.value(event->key(), nullptr);
    if (btn)
        btn->animateClick();
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

