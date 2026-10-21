#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>

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

private:
    void btnNumClicked();
    void btnBinaryOperatorClicked();
    void btnbtnEqualClicked();
    void btnPeriodClicked();
    void btnDelClicked();
    void btnClearAllClicked();
    QString calculation(bool *ok = NULL);
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
