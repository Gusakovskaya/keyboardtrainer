#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();



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

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

signals:
    void EndLineEditing();
    void retry();
    void menu();

private:
    Ui::MainWindow *ui;
    int mistake;
    int NuberOfLess;
    QString user;
public:
    bool flag;
};

#endif // MAINWINDOW_H
