#include "replacedialog.h"
#include "ui_replacedialog.h"
#include <QMessageBox>

ReplaceDialog::ReplaceDialog(QWidget *parent ,QPlainTextEdit *textEdit)
    : QDialog(parent)
    , ui(new Ui::ReplaceDialog)
{
    ui->setupUi(this);

    pTextEdit = textEdit;

    connect(ui->btFindNext,&QPushButton::clicked,this,&ReplaceDialog::on_btFindNext_clicked);
    connect(ui->btReplace,&QPushButton::clicked,this,&ReplaceDialog::on_btReplace_clicked);
    connect(ui->btReplaceAll,&QPushButton::clicked,this,&ReplaceDialog::on_btReplaceAll_clicked);
    connect(ui->btCancel,&QPushButton::clicked,this,&ReplaceDialog::on_btCancel_clicked);

    ui->rbDown->setChecked(true);
}

void ReplaceDialog::on_btFindNext_clicked()
{
    QString target = ui->searchText->text();
    if (target == "" || pTextEdit == nullptr)
        return;

    QString text = pTextEdit->toPlainText();
    QTextCursor c = pTextEdit->textCursor();
    int index = -1;

    if (ui->rbDown->isChecked())
    {
        index = text.indexOf(target, c.position() ,ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0)
        {
            c.setPosition(index);
            c.setPosition(index + target.length(), QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(c);
        }
    }
    else if (ui->rbUp->isChecked())
    {
        index = text.lastIndexOf(target, c.position() - target.length() - 1 ,ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);
        if (index >= 0)
        {
            c.setPosition(index + target.length());
            c.setPosition(index, QTextCursor::KeepAnchor);
            pTextEdit->setTextCursor(c);
        }
    }

    if (index < 0)
    {
        QMessageBox::warning(this, "查找", QString("找不到 \"%1\"").arg(target));
    }
}

void ReplaceDialog::on_btReplace_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->targetText->text();

    if ((pTextEdit != nullptr) && (target != "")) {
        QString selText = pTextEdit->textCursor().selectedText();
        if ( selText == target ) {
            pTextEdit->insertPlainText(to);
        }
        on_btFindNext_clicked();
    }

}

void ReplaceDialog::on_btReplaceAll_clicked()
{
    QString target = ui->searchText->text();
    QString to = ui->targetText->text();

    if ( (pTextEdit != nullptr) && (target != "") && (to != "") ) {
        QString text = pTextEdit->toPlainText();

        text.replace(target, to, ui->cbCaseSensitive->isChecked() ? Qt::CaseSensitive : Qt::CaseInsensitive);

        pTextEdit->clear();
        pTextEdit->insertPlainText(text);
    }

}

void ReplaceDialog::on_btCancel_clicked()
{
    reject();
}

ReplaceDialog::~ReplaceDialog()
{
    delete ui;
}
