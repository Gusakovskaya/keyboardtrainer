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
    this->setFont(font);
    lenguage = 0;
    regime = 0;
    oldScanfCode = 0;
    timer = new QTimer(this);
    if (timer == NULL)
        ErrorMemory();
    time = QTime(0,0,0,0);
    ui->LanguageComboBox->addItem("Русский");
    ui->LanguageComboBox->addItem("Английский");
    ui->RegimeComboBox->addItem("Лентяй");
    ui->RegimeComboBox->addItem("Самостоятельный");
    ui->stackedWidget->setCurrentIndex(0);
    sheetWhichPressed = "";
    oldSheet = "";
    ui->mess2->hide();
    mykeyboard = new Keyboard();
    if (mykeyboard == NULL)
        ErrorMemory();
    mykeyboard->ChangeToRus();
    ui->LayoutOfPage2->insertLayout(2, mykeyboard->MainLayout());
    ShowListOfUsers();
    ui->changeNameButton->setText("Привет, " + QString(this->user) + "!");

    connect(this, SIGNAL(EndLineEditing()), this, SLOT(LineEditingFinished()));
    connect(this, SIGNAL(retry()), this, SLOT(on_start_clicked()));
    connect(this, SIGNAL(menu()), this, SLOT(on_menuButton_clicked()));
    connect(timer, SIGNAL(timeout()), this, SLOT(DisplayTime()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DisplayTime()
{
    time = time.addMSecs(1000);
    ui->TimeDisplay->setTime(time);
}

void MainWindow::on_exit_clicked()
{
    close();
}

void MainWindow::on_start_clicked()
{
    time = QTime(0,0,0,0);
    keyboardLayout = false;

    ui->TimeDisplay->setTime(time);
    ui->stackedWidget->setCurrentIndex(2);
    this->mistake = 0;
    this->position = 0;
    ui->input->setEnabled(true);
    ui->input->clear();
    ui->nextLevelButton->setDisabled(true);
    if (!sheetWhichPressed.isEmpty())
        mykeyboard->Key()[oldScanfCode].bot->setStyleSheet(sheetWhichPressed);
    ui->input->installEventFilter(this);
    QTime midnight(0,0,0);
    qsrand(midnight.secsTo(QTime::currentTime()));
    QString less;
    if (lenguage == 0)
        less = "less" + QString::number(this->NumberOfLessRus) + ".txt";
    else
        less = "less" + QString::number(this->NumberOfLessEng) + ".txt";
    QFile fLess(less);
    if(!fLess.open(QFile::ReadOnly | QFile ::Text)) {
        QMessageBox::information(this,"Ошибка","Неверный путь к файлу!");
        return;
    }

    QTextStream stream(&fLess);
    QString buffer = stream.readLine();
    int n;
    if (lenguage == 0)
        n = qrand() % 4;
    else
        n = (qrand() % 4) + 5;
    for (int i = 0; i < n; i++) {
        buffer = stream.readLine();
        stream.flush();
    }
    ui->task->setText(buffer);
    ui->mess2->hide();

    QMessageBox *startLevelBox = new QMessageBox(this);
    if (startLevelBox == NULL)
        ErrorMemory();
    startLevelBox->setWindowTitle("Печатка");
    if (lenguage == 0){
        startLevelBox->setText(QString(tr("<h1><i><center><font color = teal>Уровень %1. </font></i></h1>")
                                       .arg(QString::number(NumberOfLessRus))));
        startLevelBox->setInformativeText("<h4><center><font color = royalblue>Поставте пальцы в "
                                          "исходную позицию: ФЫВА ОЛДЖ</font></h4>");
    } else {
        startLevelBox->setText(QString(tr("<h1><i><center><font color = teal>Уровень %1. </font></i></h1>")
                                       .arg(QString::number(NumberOfLessEng))));
        startLevelBox->setInformativeText("<h4><center><font color = royalblue>Поставте пальцы в "
                                          "исходную позицию: ASDF JKL;</font></h4>");
    }
    startLevelBox->exec();
    ui->input->setFocus();
    firstSymbol = true;
    fLess.flush();
    fLess.close();
}

void MainWindow::on_input_textChanged(const QString &str)
{
    QString task = ui->task->text();
    int i;

    flagPos = true;
    if (keyboardLayout){
        ui->input->backspace();
        keyboardLayout = false;
        return;
    }
    if (firstSymbol) {
        timer->start(1000);
        firstSymbol = false;
    }
    for (i = 0; i < str.size(); i++) {
        if (task[i] != str[i]) {
            this->mistake++;
            if (regime == 0){
                ui->input->backspace();
                if (position != 0)
                position = position - 2;
            }
            else {
                ui->input->setStyleSheet(" color: red; ");
                if (position == 0 )
                    position = 0;
                else
                    position--;
            }
            break;
        }
        else {
            ui->input->setStyleSheet(" color: mediumspringgreen; ");
            if (flagPos) {
                position++;
                flagPos = false;
            }
        }
    }
    if (position == ui->task->text().length())
        emit EndLineEditing();
}

void MainWindow::on_menuButton_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::LineEditingFinished()
{
    timer->stop();
    int speed = ui->task->text().length() * 60 / time.second();
    mykeyboard->Key()[oldScanfCode].bot->setStyleSheet(sheetWhichPressed);
    if (this->mistake == 0)
        ui->mess2->setText(QString("НИЧОСИ! Ниодной ошибки.%1 знаков в минуту.").arg(QString::number(speed)));
    else
        ui->mess2->setText(QString("%1 ошибок и %2 знаков в минуту.").arg(QString::number(this->mistake),
                                                                          QString::number(speed)));
        ui->mess2->show();
        ui->input->setDisabled(true);
    if (this->mistake <= 5) {
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

void MainWindow::on_nextLevelButton_clicked()
{
    if (lenguage == 0) {
        if (this->NumberOfLessRus != MAXLEVEL)
            this->NumberOfLessRus++;
        else {
            this->NumberOfLessRus = 1;
            EndOfGame();
            ui->stackedWidget->setCurrentIndex(0);
            return;
        }
    }
    else {
        if (this->NumberOfLessEng != MAXLEVEL)
            this->NumberOfLessEng++;
        else {
            this->NumberOfLessEng = 1;
            EndOfGame();
            ui->stackedWidget->setCurrentIndex(0);
            return;
        }
    }
    QLinkedList<TUsers>::iterator iuser = this->listOfUser.begin();
    if (user != "King")
    {
        for (iuser = this->listOfUser.begin(); iuser != this->listOfUser.end(); iuser++)
            if ((*iuser).name == user) {
                (*iuser).ruslevel = this->NumberOfLessRus;
                (*iuser).englevel = this->NumberOfLessEng;
            }
        this->WriteListToFile();
    }

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
    user.ruslevel = 1;
    user.englevel = 1;
    user.name = ui->inputName->text();
    QLinkedList<TUsers>::iterator iuser = this->listOfUser.begin();
    for (iuser = this->listOfUser.begin(); iuser != this->listOfUser.end(); iuser++)
        if ((*iuser).name == user.name) {
            QMessageBox::information(this,"Ошибка","Такой пользователь уже существует");
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
        if ((str[i] == ' ') || (('A' > str[i] || str[i] > 'Z') && ('a' > str[i] || str[i] > 'z')))
            ui->inputName->backspace();
}

void MainWindow::on_deleteName_clicked()
{
    QString username;

    for(int i = 0; i < ui->listWidget->count(); i++) {
        if (ui->listWidget->item(i)->isSelected()) {
            username = ui->listWidget->item(i)->text();
            QLinkedList<TUsers>::iterator iuser = this->listOfUser.begin();
            for (iuser = this->listOfUser.begin(); iuser != this->listOfUser.end(); iuser++) {
                if ((*iuser).name == username) {
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

    for(int i = 0; i < ui->listWidget->count(); i++) {
        if (ui->listWidget->item(i)->isSelected()) {
            username = ui->listWidget->item(i)->text();
            QLinkedList<TUsers>::iterator iuser = this->listOfUser.begin();
            for (iuser = this->listOfUser.begin(); iuser != this->listOfUser.end(); iuser++)
                if ((*iuser).name == username) {
                    this->user = (*iuser).name;
                    this->NumberOfLessRus = (*iuser).ruslevel;
                    this->NumberOfLessEng = (*iuser).englevel;
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

            if ( ((10 <= i) && (i <= 36)) || ((38 <= i) && (i <= 62))
                 || (i == 65) || (i == 66)) {
                if (oldScanfCode != 0)
                    mykeyboard->Key()[oldScanfCode].bot->setStyleSheet(oldSheet);
                sheetWhichPressed = mykeyboard->Key()[i].bot->styleSheet();
                if (keyEvent->text() == QString(ui->task->text().at(position)))
                    mykeyboard->Key()[i].bot->setStyleSheet(sheetWhichPressed +
                                                            "border: 2px double green;");
                else {
                    if (mykeyboard->Key()[i].en == QString(ui->task->text().at(position))
                            || mykeyboard->Key()[i].rus == QString(ui->task->text().at(position))) {
                        QMessageBox::information(this,"Печатка","Смените раскладку!");
                        keyboardLayout = true;
                    }
                    mykeyboard->Key()[i].bot->setStyleSheet(sheetWhichPressed +
                                                            "border: 2px double red;");
                }
                oldScanfCode = i;
                oldSheet = sheetWhichPressed;
                if (i == 22) {
                    if (regime == 0){
                        if (position == 1)
                            position = 0;
                        else if (position != 0)
                            position = position - 2;
                    }
                    else {
                        if (position != 0 &&
                                ui->input->text()[ui->input->text().size() - 2]
                                    == ui->task->text()[position - 1])
                            position--;
                    }
                }
            }
        }
        return false;
    } else
        return QMainWindow::eventFilter(obj, event);
}

void MainWindow::on_ToMenuFromSettings_clicked()
{
    emit menu();
}

void MainWindow::on_settings_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_LanguageComboBox_activated(int index)
{
    if (index == 1){
        mykeyboard->ChangeToEng();
        lenguage = 1;
    }
    else{
        mykeyboard->ChangeToRus();
        lenguage = 0;
    }
}

void MainWindow::on_RegimeComboBox_activated(int index)
{
        regime = index;
}

void MainWindow::EndOfGame()
{
    QMessageBox end;
    end.about(this, tr("Печатка"), tr("<h1> <tt><font color = mediumpurple> <center> Урашкии!"
                               "Поздравляшки! </font> </tt> </h1>"));
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

void MainWindow::ErrorMemory()
{
    QMessageBox::information(this, "Ошибка", "Не удалось выделить память");
    mykeyboard->~Keyboard();
    this->~MainWindow();
    exit(0);
}
