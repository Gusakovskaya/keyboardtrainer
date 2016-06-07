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
        listOfUser.append(user);
        stream.flush();
    }

    fuser.flush();
    fuser.close();
}

void MainWindow:: ShowListOfUsers()
{
    CreateListOfUsers();
    QLinkedList<TUsers>::iterator iuser = listOfUser.begin();
    user = iuser->name;
    numberOfLessRus = iuser->ruslevel;
    numberOfLessEng = iuser->englevel;
    numberOfLess = numberOfLessRus;

    for (iuser = listOfUser.begin(); iuser != listOfUser.end(); iuser++)
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
    QLinkedList<TUsers>::iterator iuser = listOfUser.begin();
    for (iuser = listOfUser.begin(); iuser != listOfUser.end(); iuser++)
        stream << iuser->name << ' ' << iuser->ruslevel << ' '
               << iuser->englevel << '\n';

    fuser.flush();
    fuser.close();
}

void MainWindow::SaveListToFile()
{
      if (lenguage == 0 && (numberOfLess > numberOfLessRus))
        numberOfLessRus = numberOfLess;
      if (lenguage == 1 && (numberOfLess > numberOfLessEng))
        numberOfLessEng = numberOfLess;

    QLinkedList<TUsers>::iterator iuser = listOfUser.begin();
    if (user != "King") {
        for (iuser = listOfUser.begin(); iuser != listOfUser.end(); iuser++)
            if (iuser->name == user) {
                iuser->ruslevel = numberOfLessRus;
                iuser->englevel = numberOfLessEng;
            }
        WriteListToFile();
    }
}
