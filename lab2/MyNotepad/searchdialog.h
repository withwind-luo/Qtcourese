#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QPlainTextEdit>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = nullptr ,QPlainTextEdit *textEdit = nullptr);
    ~SearchDialog();

private:
    Ui::SearchDialog *ui;

    QPlainTextEdit *pTextEdit;

    void on_btFindNext_clicked();
    void on_btCancel_clicked();
};

#endif // SEARCHDIALOG_H
