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

signals:
    void EndLineEditing();
    void retry();

private:
    Ui::MainWindow *ui;
    int mistake;
    int NuberOfLess;
};

#endif // MAINWINDOW_H
