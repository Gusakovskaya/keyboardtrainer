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

    while (!stream.atEnd())
        ReadUser(stream);

    fuser.flush();
    fuser.close();
}

void MainWindow::ReadUser(QTextStream& stream)
{
    QString buffer;
    buffer = stream.readLine();
    QStringList list = buffer.split(' ');
    if (list.empty())
        return;
    TUsers user;
    user.name = list[0];
    user.ruslevel = list[1].toInt();
    user.englevel = list[2].toInt();
    user.rusWin = list[3].toInt();
    user.engWin = list[4].toInt();
    int hi;
    if (user.ruslevel == MAXLEVEL && user.rusWin == 1)
        hi = MAXLEVEL;
    else
        hi = user.ruslevel - 1;
    for (int i = 0; i < hi; i++){
        buffer = stream.readLine();
        list = buffer.split(' ');
        TLevel item;
        item.numOfLevel = list[0].toInt();
        item.numOfMistake = list[1].toInt();
        item.time = list[2].toInt();
        user.levelsRus.append(item);
    }
    if (user.englevel == MAXLEVEL && user.engWin == 1)
        hi = MAXLEVEL;
    else
        hi = user.englevel - 1;
    for (int i = 0; i < hi; i++){
        buffer = stream.readLine();
        list = buffer.split(' ');
        TLevel item;
        item.numOfLevel = list[0].toInt();
        item.numOfMistake = list[1].toInt();
        item.time = list[2].toInt();
        user.levelsEng.append(item);
    }
    listOfUser.append(user);
    stream.flush();
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
    for (iuser = listOfUser.begin(); iuser != listOfUser.end(); iuser++) {
        stream << iuser->name << ' ' << iuser->ruslevel << ' '
               << iuser->englevel << ' ' << iuser->rusWin << ' '
               << iuser->engWin << '\n';
        QLinkedList<TLevel>::iterator ilevel = iuser->levelsRus.begin();
        for (ilevel = iuser->levelsRus.begin(); ilevel != iuser->levelsRus.end(); ilevel++) {
            stream << ilevel->numOfLevel << ' ' << ilevel->numOfMistake
                   << ' ' << ilevel->time << '\n';
        }
        for (ilevel = iuser->levelsEng.begin(); ilevel != iuser->levelsEng.end(); ilevel++) {
            stream << ilevel->numOfLevel << ' ' << ilevel->numOfMistake
                   << ' ' << ilevel->time << '\n';
        }
    }

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
                if (lenguage == 0 && gameOver)
                    iuser->rusWin = 1;
                if (lenguage == 1 && gameOver)
                    iuser->engWin = 1;
            if (lenguage == 0)
               SaveLevelResult(iuser->levelsRus);
            else
               SaveLevelResult(iuser->levelsEng);
            }
        WriteListToFile();
    }
}

void MainWindow::SaveLevelResult(QLinkedList<TLevel>& levels)
{
    QLinkedList<TLevel>::iterator ilevel = levels.begin();
    for (ilevel = levels.begin(); ilevel != levels.end(); ilevel++)
        if ((ilevel->numOfLevel == numberOfLess - 1 && !gameOver)
                || ilevel->numOfLevel == MAXLEVEL )
            break;
    if (ilevel == levels.end()) {
        TLevel item;
        if (gameOver)
            item.numOfLevel = numberOfLess;
        else
            item.numOfLevel = numberOfLess - 1;
        item.numOfMistake = mistake;
        item.time = time.second();
        levels.append(item);
    }
    else {
        if (ilevel->numOfMistake > mistake && ilevel->time > time.second()) {
            ilevel->numOfMistake = mistake;
            ilevel->time = time.second();
        }
    }
}
