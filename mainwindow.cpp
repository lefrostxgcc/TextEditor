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
