#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <QPushButton>
#include <QString>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QMap>
#include <QList>
#include <QStackedWidget>
#include <QMessageBox>

struct KeyLetter{
    QPushButton *bot;
    QString en;
    QString rus;
};

class Keyboard:QObject
{
    Q_OBJECT

private:
    QMap<int, KeyLetter> key;
    QHBoxLayout *numbers;
    QHBoxLayout *toprow;
    QHBoxLayout *middlerow;
    QHBoxLayout *lowrow;
    QHBoxLayout *space;
    QVBoxLayout *mainlayout;

public:
    QString num;
    QString rus;
    QString eng;

    Keyboard();
    ~Keyboard();

    QVBoxLayout* MainLayout();
    QMap<int, KeyLetter> Key();

    void ChangeToEng();
    void ChangeToRus();

};

#endif // KEYBOARD_H
