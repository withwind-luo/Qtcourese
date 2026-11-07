#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QCloseEvent>

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

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow *ui;

    QLabel statusCursorLabel;
    QLabel statusLabel;
    QString filePath;
    bool textChanged = false;

    void on_actionNew_Trigger();
    void on_actionOpen_Trigger();
    void on_actionSave_Trigger();
    void on_actionSaveAs_Trigger();
    void on_actionUndo_Trigger();
    void on_actionRedo_Trigger();
    void on_actionCut_Trigger();
    void on_actionCopy_Trigger();
    void on_actionPaste_Trigger();
    void on_textEdit_textChanged();
    void on_textEdit_undoAvailable(bool available);
    void on_textEdit_redoAvailable(bool available);
    void on_textEdit_copyAvailable(bool available);
    bool userEditConfirmed();

    void on_actionAbout_Trigger();
    void on_actionFind_Trigger();
    void on_actionReplace_Trigger();
};
#endif // MAINWINDOW_H
