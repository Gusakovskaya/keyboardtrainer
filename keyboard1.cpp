#include "keyboard1.h"

Keyboard::Keyboard()
{
    num = "1234567890-=";
    rus = "йцукенгшщзхъфывапролджэёячсмитьбю.";
    eng = "qwertyuiop[]asdfghjkl;'`zxcvbnm,./";
    numbers = NULL;
    topRow = NULL;
    middleRow = NULL;
    lowRow = NULL;
    space = NULL;
    mainLayout = NULL;
}

Keyboard::~Keyboard()
{
    delete mainLayout;
}

void Keyboard::Initialize()
{
    numbers = new QHBoxLayout;
    topRow = new QHBoxLayout;
    middleRow = new QHBoxLayout;
    lowRow = new QHBoxLayout;
    space = new QHBoxLayout;
    mainLayout = new QVBoxLayout;
    int i = 0;
    CreateKeyButtons(i, key1, BackSpase, numbers);
    i = 0;
    CreateKeyButtons(i, Q, Enter, topRow);
    CreateKeyButtons(i, A, ShiftLeft, middleRow);
    CreateKeyButtons(i, Z, ShiftRight, lowRow);
    CreateSpecialKeyButtons();
    mainLayout->addLayout(numbers);
    mainLayout->addLayout(topRow);
    mainLayout->addLayout(middleRow);
    mainLayout->addLayout(lowRow);
    mainLayout->addLayout(space);
    QList<int> keys = this->Key().uniqueKeys();
    ColorKeyButtons(keys, "ivory");
    keys << key1 << key2 << Q << A << Z << Period << Colon << Comma << P
         << ParenLeft << ParenRight << key0 << Minus << Equal;
    ColorKeyButtons(keys, "lime");
    keys << key3 << W << S << X << Greater << L << O << key9;
    ColorKeyButtons(keys, "deepskyblue");
    keys << key4 << E << D << C << Less << K << I << key8;
    ColorKeyButtons(keys, "pink");
    keys << key5 << key6 << R << T << F << G << V << B;
    ColorKeyButtons(keys, "plum");
    keys << key7 << Y << U << H << J << N << M;
    ColorKeyButtons(keys, "yellow");
}

void Keyboard::ColorKeyButtons(QList<int> &keys,QString color)
{
    for (int i = 0; i < keys.size(); i++) {
        this->Key()[keys[i]].bot->setStyleSheet("background-color:" + color +
                                                "; border-radius: 2px; "
                                                "font: italic 70% georgia, serif;"
                                                "border: 4px double" + color + ";");
        this->Key()[keys[i]].bot->setSizePolicy(QSizePolicy::Preferred,
                                                QSizePolicy::Preferred);
        this->Key()[keys[i]].bot->setFocusPolicy(Qt::NoFocus);
    }
    keys.clear();
}

void Keyboard::CreateKeyButtons(int& i, int lo, int hi, QHBoxLayout *layout)
{
    for (int j = lo; j < hi; i++, j++) {
        KeyLetter item;
        if (layout == numbers)
            item.rus = item.en = num[i];
        else {
            item.rus = rus[i];
            item.en = eng[i];
        }
        item.bot = new QPushButton(item.rus);
        key[j] = item;
        if (j != Apostrophe)
         layout->addWidget(item.bot);
        else
           numbers->insertWidget(0,item.bot);
    }
}

void Keyboard::CreateSpecialKeyButtons()
{
    KeyLetter item;
    item.rus = item.en = " Enter ";
    item.bot = new QPushButton(item.rus);
    key[Enter] = item;
    middleRow->addWidget(item.bot);
    item.rus = item.en = " Caps ";
    item.bot = new QPushButton(item.rus);
    key[CapsLock] = item;
    middleRow->insertWidget(0,item.bot);
    item.rus = item.en = "    Shift    ";
    item.bot = new QPushButton(item.rus);
    key[ShiftRight] = item;
    lowRow->addWidget(item.bot);
    item.bot = new QPushButton(item.rus);
    key[ShiftLeft] = item;
    lowRow->insertWidget(0,item.bot);
    item.rus = item.en = " Tab ";
    item.bot = new QPushButton(item.rus);
    key[Tab] = item;
    topRow->insertWidget(0,item.bot);
    item.rus = item.en = " \\ ";
    item.bot = new QPushButton(item.rus);
    key[Slash] = item;
    topRow->addWidget(item.bot);
    item.rus = item.en = "Backspase";
    item.bot = new QPushButton(item.rus);
    key[BackSpase] = item;
    numbers->addWidget(item.bot);
    item.rus = item.en = "";
    item.bot = new QPushButton();
    key[Space] = item;
    space->addWidget(item.bot);
}

void Keyboard::ChangeToEng()
{
    QList<int> keys = this->Key().uniqueKeys();
    for (int i = 0; i < keys.size(); i++)
        this->Key()[keys[i]].bot->setText(this->Key()[keys[i]].en);
}

void Keyboard::ChangeToRus()
{
    QList<int> keys = this->Key().uniqueKeys();
    for (int i = 0; i < keys.size(); i++)
        this->Key()[keys[i]].bot->setText(this->Key()[keys[i]].rus);
}

QMap<int, KeyLetter> Keyboard::Key()
{
    return key;
}

QVBoxLayout* Keyboard::MainLayout()
{
    return mainLayout;
}
