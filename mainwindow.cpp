#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{    
    ui->setupUi(this);
    QFont font("Times");
    font.setItalic(true);
    font.setPixelSize(20);
    setFont(font);

    timer = new QTimer(this);
    time = QTime(0,0,0,0);

    lenguage = 0;
    regime = 0;
    oldScanfCode = 0;
    sheetWhichPressed = "";
    oldSheet = "";
    myKeyboard = new Keyboard();
    myKeyboard->Initialize();
    myKeyboard->ChangeToRus();
    ShowListOfUsers();
    ui->mess2->hide();
    ui->LanguageComboBox->addItem("Русский");
    ui->LanguageComboBox->addItem("Английский");
    ui->RegimeComboBox->addItem("Лентяй");
    ui->RegimeComboBox->addItem("Самостоятельный");
    ui->stackedWidget->setCurrentIndex(pageMain);
    ui->LayoutOfPage2->insertLayout(2, myKeyboard->MainLayout());
    ui->changeNameButton->setText("Привет, " + QString(user) + "!");

    connect(this, SIGNAL(EndLineEditing()), this, SLOT(LineEditingFinished()));
    connect(this, SIGNAL(retry()), this, SLOT(on_startLevel_clicked()));
    connect(this, SIGNAL(menu()), this, SLOT(on_menuButton_clicked()));
    connect(timer, SIGNAL(timeout()), this, SLOT(DisplayTime()));
    connect(this, SIGNAL(tolevel()), this, SLOT(on_start_clicked()));

}

MainWindow::~MainWindow()
{
    delete myKeyboard;
    delete ui;
}

void MainWindow::DisplayTime()
{
    time = time.addMSecs(1000);
    ui->TimeDisplay->setTime(time);
}

void MainWindow::on_startLevel_clicked()
{
    time = QTime(0,0,0,0);
    keyboardLayout = false;
    mistake = 0;
    position = 0;
    ui->mess2->hide();
    ui->input->clear();
    ui->input->setEnabled(true);
    ui->input->installEventFilter(this);
    ui->TimeDisplay->setTime(time);
    ui->stackedWidget->setCurrentIndex(pagePlay);
    ui->nextLevelButton->setDisabled(true);
    if (!sheetWhichPressed.isEmpty())
        myKeyboard->Key()[oldScanfCode].bot->setStyleSheet(sheetWhichPressed);
    SetTask();
    SetStartMessage();
    ui->input->setFocus();
    firstSymbol = true;
}

void MainWindow::SetStartMessage()
{
    QMessageBox *startLevelBox = new QMessageBox(this);
    startLevelBox->setWindowTitle("Печатка");
    if (lenguage == 0){
        startLevelBox->setText(QString(tr("<h1><i><center><font color = teal>Уровень %1. </font></i></h1>")
                                       .arg(QString::number(numberOfLess))));
        startLevelBox->setInformativeText("<h4><center><font color = royalblue>Поставте пальцы в "
                                          "исходную позицию: ФЫВА ОЛДЖ</font></h4>");
    }
    else {
        startLevelBox->setText(QString(tr("<h1><i><center><font color = teal>Уровень %1. </font></i></h1>")
                                       .arg(QString::number(numberOfLess))));
        startLevelBox->setInformativeText("<h4><center><font color = royalblue>Поставте пальцы в "
                                          "исходную позицию: ASDF JKL;</font></h4>");
    }
    startLevelBox->exec();
}

void MainWindow::SetTask()
{
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    QString less;
    less = "less" + QString::number(numberOfLess) + ".txt";
    QFile fLess(less);
    if(!fLess.open(QFile::ReadOnly | QFile ::Text)) {
        QMessageBox::information(this,"Ошибка","Неверный путь к файлу!");
        return;
    }

    QTextStream stream(&fLess);
    QString buffer = stream.readLine();
    int n;
    if (lenguage == 0)
        n = qrand() % TASKNUM;
    else
        n = (qrand() % TASKNUM) + TASKNUM;
    for (int i = 0; i < n; i++) {
        buffer = stream.readLine();
        stream.flush();
    }
    ui->task->setText(buffer);

    fLess.flush();
    fLess.close();
}

void MainWindow::on_input_textChanged(const QString &str)
{
    QString task = ui->task->text();

    if (keyboardLayout){
        ui->input->backspace();
        keyboardLayout = false;
        return;
    }
    if (firstSymbol) {
        timer->start(1000);
        firstSymbol = false;
    }
    if (str == "")
        return;
    if (task.indexOf(str) != 0) {
        mistake++;
        if (regime == 0){
            ui->input->backspace();
            position--;
        }
        else
            ui->input->setStyleSheet(" color: red; ");
    }
    else {
        ui->input->setStyleSheet(" color: mediumspringgreen; ");
        position++;
    }

    if (position == ui->task->text().length())
        emit EndLineEditing();
}

void MainWindow::on_menuButton_clicked()
{
    ui->changeNameButton->setText("Привет, " + QString(user) + "!");
    ui->stackedWidget->setCurrentIndex(pageMain);
}

void MainWindow::LineEditingFinished()
{
    timer->stop();
    int speed = ui->task->text().length() * 60 / time.second();
    myKeyboard->Key()[oldScanfCode].bot->setStyleSheet(sheetWhichPressed);
    if (mistake == 0)
        ui->mess2->setText(QString("НИЧОСИ! Ниодной ошибки.%1 знаков в минуту.").arg(QString::number(speed)));
    else
        ui->mess2->setText(QString("%1 ошибок и %2 знаков в минуту.").arg(QString::number(mistake),
                                                                          QString::number(speed)));
    ui->mess2->show();
    ui->input->setDisabled(true);
    if (mistake <= 5) {
        ui->nextLevelButton->setEnabled(true);
        ui->nextLevelButton->setFocus();
    }
    else
        ui->retryButton->setFocus();
}

void MainWindow::on_retryButton_clicked()
{
    timer->stop();
    ui->input->setFocus();
    emit retry();
}

void MainWindow::on_start_clicked()
{
    ui->stackedWidget->setCurrentIndex(pageLevels);
    if (user == "King")
        return;
    if (numberOfLess == 1) {
        ui->level1->setEnabled(true);
        ui->level2->setEnabled(false);
        ui->level3->setEnabled(false);
    }
    if (numberOfLess == 2) {
        ui->level1->setEnabled(true);
        ui->level2->setEnabled(true);
        ui->level3->setEnabled(false);
    }
    if (numberOfLess == 3) {
        ui->level1->setEnabled(true);
        ui->level2->setEnabled(true);
        ui->level3->setEnabled(true);
    }
}

void MainWindow::on_nextLevelButton_clicked()
{
    if (numberOfLess != MAXLEVEL)
        numberOfLess++;
    else {
        SaveListToFile();
        numberOfLessRus = 1;
        EndOfGame();
        emit tolevel();
        return;
    }

    SaveListToFile();

    emit retry();
}

void MainWindow::on_changeNameButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(pageUser);
    ui->listWidget->setItemSelected(ui->listWidget->item(0),true);
}

void MainWindow::on_returnToMenu_clicked()
{
    emit menu();
}

void MainWindow::on_create_clicked()
{
    TUsers user;
    user.ruslevel = 1;
    user.englevel = 1;
    user.name = ui->inputName->text();
    QLinkedList<TUsers>::iterator iuser = listOfUser.begin();
    for (iuser = listOfUser.begin(); iuser != listOfUser.end(); iuser++)
        if (iuser->name == user.name) {
            QMessageBox::information(this,"Ошибка","Такой пользователь уже существует");
            return;
        }
    listOfUser.append(user);
    WriteListToFile();
    ui->listWidget->addItem(user.name);
}

void MainWindow::on_inputName_textChanged(const QString &str)
{
    int i;
    for (i = 0; i < str.size(); i++)
        if ((str[i] == ' ') || (('A' > str[i] || str[i] > 'Z') && ('a' > str[i] || str[i] > 'z')))
            ui->inputName->backspace();
}

void MainWindow::on_deleteName_clicked()
{
    QString username;

    for(int i = 0; i < ui->listWidget->count(); i++) {
        if (ui->listWidget->item(i)->isSelected()) {
            username = ui->listWidget->item(i)->text();
            if (username == "King")
                return;
            QLinkedList<TUsers>::iterator iuser = listOfUser.begin();
            for (iuser = listOfUser.begin(); iuser != listOfUser.end(); iuser++) {
                if (iuser->name == username) {
                    listOfUser.erase(iuser);
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

    for(int i = 0; i < ui->listWidget->count(); i++) {
        if (ui->listWidget->item(i)->isSelected()) {
            username = ui->listWidget->item(i)->text();
            QLinkedList<TUsers>::iterator iuser = listOfUser.begin();
            for (iuser = listOfUser.begin(); iuser != listOfUser.end(); iuser++)
                if (iuser->name == username) {
                    user = iuser->name;
                    numberOfLessRus = iuser->ruslevel;
                    numberOfLessEng = iuser->englevel;
                    if (lenguage == 0)
                        numberOfLess = numberOfLessRus;
                    else
                        numberOfLess = numberOfLessEng;
                    emit menu();
                }
            break;
        }
    }
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->input) {
        if (event->type() == QEvent::KeyPress) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
            int i = keyEvent->nativeScanCode();
            if ( ((myKeyboard->key1 <= i) && (i <= myKeyboard->Enter))
                 || ((myKeyboard->A <= i) && (i <= myKeyboard->ShiftRight))
                 || (i == myKeyboard->Space) || (i == myKeyboard->CapsLock)) {
                if (oldScanfCode != 0)
                    myKeyboard->Key()[oldScanfCode].bot->setStyleSheet(oldSheet);
                sheetWhichPressed = myKeyboard->Key()[i].bot->styleSheet();
                if (keyEvent->text() == QString(ui->task->text().at(position)))
                    myKeyboard->Key()[i].bot->setStyleSheet(sheetWhichPressed +
                                                            "border: 2px double green;");
                else {
                    CheckKeyboardLayout(keyEvent->text());
                    myKeyboard->Key()[i].bot->setStyleSheet(sheetWhichPressed +
                                                            "border: 2px double red;");
                }
                oldScanfCode = i;
                oldSheet = sheetWhichPressed;
                if (i == myKeyboard->BackSpase)
                    BackSpacePressed();
            }
        }
        return false;
    } else
        return QMainWindow::eventFilter(obj, event);
}

void MainWindow:: BackSpacePressed()
{
    if (regime == 0){
        if (position == 1)
            position = 0;
        else if (position != 0)
            position = position - 2;
    }
    else {
        if (position != 0 &&
                ui->input->text()[ui->input->text().size() - 2]
                    == ui->task->text()[position - 1]) {
            if (position != 0 && ui->input->text()[ui->input->text().size() - 1]
                    == ui->task->text()[position - 1])
                position -= 2;
            else
                position--;
        }
    }
}

void MainWindow::CheckKeyboardLayout(QString keyText)
{
    for (int j = 0; j < myKeyboard->rus.size(); j++)
    if (keyText != QString(".") && ((keyText == QString(myKeyboard->rus[j]) && lenguage == 1)
            || (keyText == QString(myKeyboard->eng[j]) && lenguage == 0))) {
        QMessageBox::information(this,"Печатка","Смените раскладку!");
        keyboardLayout = true;
    }
}

void MainWindow::on_LanguageComboBox_activated(int index)
{
    if (index == 1) {
        myKeyboard->ChangeToEng();
        lenguage = 1;
        numberOfLess = numberOfLessEng;
    }
    else {
        myKeyboard->ChangeToRus();
        lenguage = 0;
        numberOfLess = numberOfLessRus;
    }
}

void MainWindow::EndOfGame()
{
    QMessageBox end;
    end.about(this, tr("Печатка"), tr("<h1> <tt><font color = mediumpurple> <center> Урашкии!"
                               "Поздравляшки! </font> </tt> </h1>"));
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

void MainWindow::on_ToMenuFromSettings_clicked()
{
    emit menu();
}

void MainWindow::on_settings_clicked()
{
    ui->stackedWidget->setCurrentIndex(pageSettings);
}

void MainWindow::on_exit_clicked()
{
    close();
}

void MainWindow::on_RegimeComboBox_activated(int index)
{
    regime = index;
}

void MainWindow::on_goToMenu_clicked()
{
    emit menu();
}

void MainWindow::on_level1_clicked()
{
    numberOfLess = 1;
}

void MainWindow::on_level2_clicked()
{
    numberOfLess = 2;
}

void MainWindow::on_level3_clicked()
{
    numberOfLess = 3;
}
