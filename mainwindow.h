#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QLinkedList>

namespace Ui {
class MainWindow;
}

typedef struct TUsers{
    QString name;
    int level;
}TUsers;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void keyPressEvent(QKeyEvent*e);
    void keyReleaseEvent(QKeyEvent * e);
    void CreateListOfUsers();
    void ShowListOfUsers();
    void WriteListToFile();

private:
    Ui::MainWindow *ui;
    int mistake;
    int NuberOfLess;
    QString user;
    QLinkedList<TUsers> listOfUser;


private slots:
    void on_exit_clicked();

    void on_start_clicked();

    void on_input_textChanged(const QString &arg1);

    void on_menuButton_clicked();

    void LineEditingFinished();

    void on_retryButton_clicked();

    void on_nextLevelButton_clicked();

    void on_changeNameButton_clicked();

    void on_returnToMenu_clicked();

    void on_create_clicked();

    void on_inputName_textChanged(const QString &arg1);

    void on_deleteName_clicked();

    void on_choose_clicked();

signals:
    void EndLineEditing();
    void retry();
    void menu();

};

#endif // MAINWINDOW_H
