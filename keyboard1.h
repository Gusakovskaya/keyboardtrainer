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
    QHBoxLayout *topRow;
    QHBoxLayout *middleRow;
    QHBoxLayout *lowRow;
    QHBoxLayout *space;
    QVBoxLayout *mainLayout;

public:
    QString num;
    QString rus;
    QString eng;

    enum keys {   // перечисление сканкодов клавишь под Linux
        key1 = 10, key2, key3, key4, key5, key6, key7, key8, key9, key0,
        Minus, Equal, BackSpase,
        Tab, Q, W, E, R, T, Y, U, I, O, P, ParenLeft, ParenRight,
        Enter,
        A = 38, S, D, F, G, H, J, K, L, Colon, Comma,
        Apostrophe, ShiftLeft, Slash,
        Z, X, C, V, B, N, M, Less, Greater, Period, ShiftRight,
        Space = 65, CapsLock = 66
    };

    Keyboard();
    ~Keyboard();

    QVBoxLayout* MainLayout();
    QMap<int, KeyLetter> Key();

    void ChangeToEng();
    void ChangeToRus();
    void Initialize();
    void CreateKeyButtons(int& i, int lo, int hi, QHBoxLayout *layout);
    void CreateSpecialKeyButtons();
    void ColorKeyButtons(QList<int> &keys, QString color);

};

#endif // KEYBOARD_H
