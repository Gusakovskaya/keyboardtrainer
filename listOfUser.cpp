#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow:: CreateListOfUsers(void)
{
    QFile fuser("users.txt");
    if(!fuser.open(QFile::ReadWrite | QFile ::Text)) {
        QMessageBox::information(this,"Ошибка","Неверный путь к файлу!");
        return;
    }

    QTextStream stream(&fuser);
    QString buffer;

    while (!stream.atEnd()) {
        buffer = stream.readLine();
        QStringList list = buffer.split(' ');
        if (list.empty())
            continue;
        TUsers user;
        user.name = list[0];
        user.ruslevel = list[1].toInt();
        user.englevel = list[2].toInt();
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
    this->user = iuser->name;
    this->NumberOfLessRus = iuser->ruslevel;
    this->NumberOfLessEng = iuser->englevel;

    for (iuser = this->listOfUser.begin(); iuser != this->listOfUser.end(); iuser++)
        ui->listWidget->addItem(iuser->name);
}

void MainWindow:: WriteListToFile()
{
    QFile fuser("users.txt");
    if(!fuser.open(QFile::WriteOnly | QFile ::Text)) {
        QMessageBox::information(this,"Ошибка","Неверный путь к файлу!");
        return;
    }

    QTextStream stream(&fuser);
    QLinkedList<TUsers>::iterator iuser = this->listOfUser.begin();
    for (iuser = this->listOfUser.begin(); iuser != this->listOfUser.end(); iuser++)
        stream << (*iuser).name << ' ' << (*iuser).ruslevel << ' '
               << (*iuser).englevel << '\n';

    fuser.flush();
    fuser.close();
}

void MainWindow::SaveListToFile()
{
    QLinkedList<TUsers>::iterator iuser = this->listOfUser.begin();
    if (user != "King") {
        for (iuser = this->listOfUser.begin(); iuser != this->listOfUser.end(); iuser++)
            if ((*iuser).name == user) {
                (*iuser).ruslevel = this->NumberOfLessRus;
                (*iuser).englevel = this->NumberOfLessEng;
            }
        this->WriteListToFile();
    }
}
