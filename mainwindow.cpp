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
    setCentralWidget(ui->stackedWidget);
    ui->stackedWidget->setCurrentIndex(0);
    ui->mess2->hide();

    QFile fuser("users.txt");
    if(!fuser.open(QFile::ReadWrite | QFile ::Text))
    {
        QMessageBox::information(this,"Error","Path not correct!");
        return;
    }

    QTextStream stream(&fuser);
    QString buffer;

    buffer = stream.readLine();
    QStringList list = buffer.split(' ');
    ui->listWidget->addItem(list[0]);
    if (this->flag)
    {
        this->user = list[0];
        this->NuberOfLess = list[1].toInt();
    }

    while (!stream.atEnd())
    {
        buffer = stream.readLine();
        QStringList list = buffer.split(' ');
        ui->listWidget->addItem(list[0]);
        stream.flush();
    }

    fuser.flush();
    fuser.close();

    this->mistake = 0;
    ui->changeNameButton->setText("Привет, " + QString(this->user) + "!");

    connect(this, SIGNAL(EndLineEditing()), this, SLOT(LineEditingFinished()));
    connect(this, SIGNAL(retry()), this, SLOT(on_start_clicked()));
    connect(this, SIGNAL(menu()), this, SLOT(on_menuButton_clicked()));
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

    ui->stackedWidget->setCurrentIndex(2);
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

void MainWindow::on_changeNameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
    ui->listWidget->setItemSelected(ui->listWidget->item(0),true);
}

void MainWindow::on_returnToMenu_clicked()
{
    emit menu();
}

void MainWindow::on_create_clicked()
{
    QString userName = ui->inputName->text();
    QFile fuser("users.txt");
    if(!fuser.open(QFile::ReadWrite | QFile ::Text))
    {
        QMessageBox::information(this,"Error","Path not correct!");
        return;
    }

    QTextStream stream(&fuser);
    QString buffer;

    while (!stream.atEnd())
    {
        buffer = stream.readLine();
        stream.flush();
        if (buffer.contains(userName))
        {
            QMessageBox::information(this,"Error","Такой пользователь уже существует");
            return;
        }
    }
    stream << userName + " 1\n";

    ui->listWidget->addItem(userName);

    fuser.flush();
    fuser.close();
}

void MainWindow::on_inputName_textChanged(const QString &str)
{
    int i;
    for (i = 0; i < str.size(); i++)
        if (str[i] == ' ')
            ui->inputName->backspace();
}

void MainWindow::on_pushButton_clicked()
{
    QString username;
    QFile fuser("users.txt");
    if(!fuser.open(QFile::ReadWrite | QFile ::Text))
    {
        QMessageBox::information(this,"Error","Path not correct!");
        return;
    }
    QTextStream stream(&fuser);
    QString buffer;

    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if (ui->listWidget->item(i)->isSelected())
        {
            username = ui->listWidget->item(i)->text();
            QVector<QString> text;
            while (!stream.atEnd())
            {
                buffer = stream.readLine();
                stream.flush();
                if (!buffer.contains(username))
                {
                    text.push_back(buffer);
                }
            }
            stream.seek(0);
            stream << text.data();
            ui->listWidget->removeItemWidget(ui->listWidget->item(i));
        }
    }
    ui->listWidget->setItemSelected(ui->listWidget->item(0),true);
    fuser.flush();
    fuser.close();
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->listWidget->setItemSelected(ui->listWidget->item(0),false);
    QString username;
    QFile fuser("users.txt");
    if(!fuser.open(QFile::ReadWrite | QFile ::Text))
    {
        QMessageBox::information(this,"Error","Path not correct!");
        return;
    }
    QTextStream stream(&fuser);
    QString buffer;

    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if (ui->listWidget->item(i)->isSelected())
        {
            username = ui->listWidget->item(i)->text();
            while (!stream.atEnd())
            {
                buffer = stream.readLine();
                stream.flush();
                if (!buffer.contains(username))
                {
                    QStringList list = buffer.split(' ');
                    this->user = list[0];
                    this->NuberOfLess = list[1].toInt();
                    break;
                }
            }
        }
    }
    this->flag = false;
    fuser.flush();
    fuser.close();
}
