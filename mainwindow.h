#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QSound>
#include <keyboard1.h>
#include <QApplication>
#include <QMainWindow>
#include <QKeyEvent>
#include <QLinkedList>
#include <QWidget>
#include <QDockWidget>
#include <QFont>
#include <QComboBox>
#include <QTime>
#include <QTimer>
#include <QMessageBox>
#include <QFile>
#include <QDir>
#include <QTextStream>
#include <qstring.h>
#include <QFont>
#include <QKeyEvent>
#include <QTranslator>

#define MAXLEVEL 3
#define TASKNUM 5

namespace Ui {
class MainWindow;
}

struct TUsers{
    QString name;
    int ruslevel;
    int englevel;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void CreateListOfUsers();
    void ShowListOfUsers();
    void WriteListToFile();
    void SaveListToFile();
    void EndOfGame();
    void SetTask();
    void SetStartMessage();
    void CheckKeyboardLayout(QString keyText);
    void BackSpacePressed();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::MainWindow *ui;
    int position;
    bool firstSymbol;
    bool keyboardLayout; // true - была смена раскладки клавиатуры
    int mistake;
    int numberOfLess;
    int numberOfLessRus;
    int numberOfLessEng;
    int lenguage; // русский 0, англ 1
    QTime time;
    QTimer *timer;
    QString sheetWhichPressed;
    QString oldSheet;
    int oldScanfCode;
    int regime; // простой 0, сложный 1
    QString user;
    QLinkedList<TUsers> listOfUser;
    Keyboard *myKeyboard;
    enum pageOfStackWidget{
        pageMain, pageUser, pagePlay, pageSettings, pageLevels
    };

private slots:
    void on_exit_clicked();

    void on_start_clicked();

    void on_input_textChanged(const QString &arg1);

    void on_menuButton_clicked();

    void LineEditingFinished();

    void DisplayTime();

    void on_retryButton_clicked();

    void on_nextLevelButton_clicked();

    void on_changeNameButton_clicked();

    void on_returnToMenu_clicked();

    void on_create_clicked();

    void on_inputName_textChanged(const QString &arg1);

    void on_deleteName_clicked();

    void on_choose_clicked();

    void on_ToMenuFromSettings_clicked();

    void on_settings_clicked();

    void on_LanguageComboBox_activated(int index);

    void on_RegimeComboBox_activated(int index);

    void on_startLevel_clicked();

    void on_goToMenu_clicked();

    void on_level1_clicked();

    void on_level2_clicked();

    void on_level3_clicked();

signals:
    void EndLineEditing();

    void retry();

    void menu();

    void tolevel();
};

#endif // MAINWINDOW_H
