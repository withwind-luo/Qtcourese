#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QMap>
#include <QKeyEvent>
#include <QPushButton>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    QString operand;
    QStack<QString> operands;
    QString opcode;
    QStack<QString> opcodes;
    QMap<int, QPushButton*> keyBtns;
    bool afterEquals = false;
    bool hasError = false;

private:
    void btnNumClicked();
    void btnBinaryOperatorClicked();
    void btnUnaryOperatorClicked();
    void btnbtnEqualClicked();
    void btnPeriodClicked();
    void btnDelClicked();
    void btnClearAllClicked();
    void btnClearEntryClicked();
    void resetState();
    virtual void keyPressEvent(QKeyEvent *event) override;
    QString calculation(bool *ok = NULL);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
