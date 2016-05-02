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

    void on_pushButton_clicked();

    void LineEditingFinished();
signals:
    void EndLineEditing();

private:
    Ui::MainWindow *ui;
    int mistake;
};

#endif // MAINWINDOW_H
