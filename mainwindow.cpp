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
    ui->mess2->hide();

    ShowListOfUsers();
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
    ui->changeNameButton->setText("Привет, " + QString(this->user) + "!");
    emit menu();
}

void MainWindow::on_create_clicked()
{
    TUsers user;
    user.level = 1;
    user.name = ui->inputName->text();
    QLinkedList<TUsers>::iterator iuser = this->listOfUser.begin();
    for (iuser = this->listOfUser.begin(); iuser != this->listOfUser.end(); iuser++)
        if ((*iuser).name == user.name)
        {
            QMessageBox::information(this,"Error","Такой пользователь уже существует");
            return;
        }
    this->listOfUser.append(user);
    WriteListToFile();
    ui->listWidget->addItem(user.name);

}

void MainWindow::on_inputName_textChanged(const QString &str)
{
    int i;
    for (i = 0; i < str.size(); i++)
        if (str[i] == ' ')
            ui->inputName->backspace();
}

void MainWindow::on_deleteName_clicked()
{
    QString username;

    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if (ui->listWidget->item(i)->isSelected())
        {
            username = ui->listWidget->item(i)->text();
            QLinkedList<TUsers>::iterator iuser = this->listOfUser.begin();
            for (iuser = this->listOfUser.begin(); iuser != this->listOfUser.end(); iuser++)
            {
                if ((*iuser).name == username)
                {
                    this->listOfUser.erase(iuser);
                    break;
                }
            }
            ui->listWidget->removeItemWidget(ui->listWidget->takeItem(i));
        }
    }
    ui->listWidget->setItemSelected(ui->listWidget->item(0),true);
    WriteListToFile();
}

void MainWindow::on_choose_clicked()
{
    QString username;

    for(int i = 0; i < ui->listWidget->count(); i++)
    {
        if (ui->listWidget->item(i)->isSelected())
        {
            username = ui->listWidget->item(i)->text();
            QLinkedList<TUsers>::iterator iuser = this->listOfUser.begin();
            for (iuser = this->listOfUser.begin(); iuser != this->listOfUser.end(); iuser++)
                if ((*iuser).name == username)
                {
                    this->user = (*iuser).name;
                    this->NuberOfLess = (*iuser).level;
                }
            break;
        }
    }
}

void MainWindow:: CreateListOfUsers(void)
{
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
        QStringList list = buffer.split(' ');
        TUsers user;
        user.name = list[0];
        user.level = list[1].toInt();
        this->listOfUser.append(user);
        stream.flush();
    }

    fuser.flush();
    fuser.close();
}

void MainWindow:: ShowListOfUsers()
{
    CreateListOfUsers();
    QLinkedList<TUsers>::iterator iuser = this->listOfUser.begin();
    this->user = (*iuser).name;
    this->NuberOfLess = (*iuser).level;

    for (iuser = this->listOfUser.begin(); iuser != this->listOfUser.end(); iuser++)
        ui->listWidget->addItem((*iuser).name);
}

void MainWindow:: WriteListToFile()
{
    QFile fuser("users.txt");
    if(!fuser.open(QFile::WriteOnly | QFile ::Text))
    {
        QMessageBox::information(this,"Error","Path not correct!");
        return;
    }

    QTextStream stream(&fuser);
    QLinkedList<TUsers>::iterator iuser = this->listOfUser.begin();
    for (iuser = this->listOfUser.begin(); iuser != this->listOfUser.end(); iuser++)
        stream << (*iuser).name << ' ' << (*iuser).level << '\n';

    fuser.flush();
    fuser.close();
}

void MainWindow::keyPressEvent(QKeyEvent *e) {

}

void MainWindow::keyReleaseEvent(QKeyEvent *e) {

}
