#include "searchdialog.h"
#include "ui_searchdialog.h"
#include <QMessageBox>

SearchDialog::SearchDialog(QWidget *parent ,QPlainTextEdit *textEdit)
    : QDialog(parent)
    , ui(new Ui::SearchDialog)
{
    ui->setupUi(this);

    pTextEdit = textEdit;

    connect(ui->btFindNext,&QPushButton::clicked,this,&SearchDialog::on_btFindNext_clicked);
    connect(ui->btCancel,&QPushButton::clicked,this,&SearchDialog::on_btCancel_clicked);

    ui->rbDown->setChecked(true);
}

void SearchDialog::on_btFindNext_clicked()
{
    QString target = ui->SearchText->text();
    QString text = pTextEdit->toPlainText();
    QTextCursor c = pTextEdit->textCursor();
    int index = -1;

    if (ui->rbDown->isChecked())
    {
        index = text.indexOf(target, c.position() ,ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0)
        {
            c.setPosition(index);
            c.setPosition(index + target.length(), QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(c);
        }
    }
    else if (ui->rbUp->isChecked())
    {
        index = text.lastIndexOf(target, c.position() - target.length() - 1 ,ui->cbCaseSensetive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0)
        {
            c.setPosition(index + target.length());
            c.setPosition(index, QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(c);
        }
    }

    if(index < 0)
    {
        QMessageBox::warning(this, "查找", QString("找不到 \"%1\"").arg(target));
    }
}

void SearchDialog::on_btCancel_clicked()
{

}

SearchDialog::~SearchDialog()
{
    delete ui;
}
