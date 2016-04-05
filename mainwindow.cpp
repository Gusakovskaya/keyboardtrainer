#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setCentralWidget(ui->stackedWidget);
    ui->mess2->hide();
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
    QString result = "";
    if (n == 0)
            result = "Молодец! Ты не допустил ни одной ошибки. Так держать!";
    else
        result.append("У тебя");
        result.append(n);
        result.append("ошибок.");
    ui->mess2->setText(result);
    ui->mess2->show();
    }
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}
