#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_buttonOpenFile_clicked()
{
    QString filename = QFileDialog::getOpenFileName();

    if (filename.isEmpty())
        return;

    QFile file{filename};
    file.open(QIODevice::ReadOnly);

    if (!file.isOpen())
    {
        QMessageBox::warning(nullptr, "Ошибка", "Ошибка чтения файла " + filename);
        return;
    }

    ui->fileContent->setPlainText(QTextStream{&file}.readAll());
}

void MainWindow::on_buttonSaveFile_clicked()
{
    QString filename = QFileDialog::getSaveFileName();

    if (filename.isEmpty())
        return;

    QFile file{filename};
    file.open(QIODevice::WriteOnly);

    if (!file.isOpen())
    {
        QMessageBox::warning(nullptr, "Ошибка", "Ошибка сохранения файла " + filename);
        return;
    }

    QTextStream(&file) << ui->fileContent->toPlainText();
}

void MainWindow::on_buttonReplace_clicked()
{
    const QString searchText  {ui->searchPattern->text()};
    const QString replaceText {ui->replacingText->text()};

    constexpr QTextDocument::FindFlags flags {QTextDocument::FindCaseSensitively | QTextDocument::FindWholeWords};

    QTextCursor cursor;
    cursor.setPosition(0);
    ui->fileContent->setTextCursor(cursor);

    while (ui->fileContent->find(searchText, flags))
        ui->fileContent->insertPlainText(replaceText);
}
