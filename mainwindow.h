#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void on_buttonOpenFile_clicked();
    void on_buttonSaveFile_clicked();
    void on_buttonReplace_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
