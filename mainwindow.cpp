#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <qstring.h>
#include <QTime>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentIndex(0);
    setCentralWidget(ui->stackedWidget);
    ui->mess2->hide();
    this->mistake = 0;
    this->NuberOfLess = 1;
    connect(this, SIGNAL(EndLineEditing()), this, SLOT(LineEditingFinished()));
    connect(this, SIGNAL(retry()), this, SLOT(on_start_clicked()));
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
    ui->input->clear();
    ui->nextLevelButton->setDisabled(true);
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    QString less = "less" + QString::number(this->NuberOfLess) + ".txt";
    QFile fLess(less);
    if(!fLess.open(QFile::ReadOnly | QFile ::Text))
    {
        QMessageBox::information(this,"Error","Path not correct!");
        return;
    }
    QTextStream stream(&fLess);
    QString buffer = stream.readLine();
    for (int i = 0; i < qrand() % 4; i++)
    {
        buffer = stream.readLine();
        stream.flush();
    }
    ui->task->setText(buffer);
    ui->mess2->hide();

    fLess.flush();
    fLess.close();
}

void MainWindow::on_input_textChanged(const QString &str)
{
    QString task = ui->task->text();
    int i;
    for (i = 0; i < str.size(); i++)
    {
        if (task[i] != str[i])
        {
            ui->input->backspace();
            this->mistake++;
        }
    }
    if ((task.size() == str.size()) && (str[i-1] == task[i-1]))
        emit EndLineEditing();
}

void MainWindow::on_menuButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::LineEditingFinished()
{
    if (this->mistake == 0)
        ui->mess2->setText("НИЧОСИ! Ниодной ошибки");
    else
        ui->mess2->setText(QString("you have %1 mistakes").arg(QString::number(this->mistake)));
        ui->mess2->show();
        ui->input->setDisabled(true);
    if (this->mistake <= 20)
        ui->nextLevelButton->setEnabled(true);
}


void MainWindow::on_retryButton_clicked()
{
    emit retry();
}

void MainWindow::on_nextLevelButton_clicked()
{
    this->NuberOfLess++;
    emit retry();
}
