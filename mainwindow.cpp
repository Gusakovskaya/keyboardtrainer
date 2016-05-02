#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <qstring.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    setCentralWidget(ui->stackedWidget);
    ui->mess2->hide();
    this->mistake = 0;

    connect(this, SIGNAL(EndLineEditing()), this, SLOT(LineEditingFinished()));
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
    this->mistake = 0;
    ui->input->setEnabled(true);
    QFile fLess("less1.txt");
    if(!fLess.open(QFile::ReadOnly | QFile ::Text))
    {
        QMessageBox::information(this,"Error","Path not correct!");
        return;
    }
    QTextStream stream(&fLess);
    QString buffer = stream.readAll();
    ui->task->setText(buffer);
    ui->mess2->hide();

    fLess.flush();
    fLess.close();
}

void MainWindow::on_input_textChanged(const QString &str)
{
    QString task = ui->task->text();
    for (int i = 0; i < str.size(); i++)
    {
        if (task[i] != str[i])
        {
            ui->input->backspace();
            this->mistake++;
        }
    }
    if (task.size() == str.size())
        emit EndLineEditing();
}

void MainWindow::on_pushButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
    ui->input->clear();
}

void MainWindow::LineEditingFinished()
{
    if (this->mistake == 0)
        ui->mess2->setText("НИЧОСИ! Ниодной ошибки");
    else
        ui->mess2->setText(QString("you have %1 mistakes").arg(QString::number(this->mistake)));
        ui->mess2->show();
        ui->input->setDisabled(true);

}

