#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->stackedWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_exit_clicked()
{
    close();
}

void MainWindow::on_start_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_input_textChanged(const QString &str)
{
    QString task = ui->task->text();
    int n = 0;
    for (int i = 0, j = 0; i < str.size(); i++, j++){
        if (task[i] != str[j]){
            ui->input->backspace();
            n++;
        }

    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
