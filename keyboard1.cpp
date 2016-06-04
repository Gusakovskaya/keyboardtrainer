#include "keyboard1.h"

Keyboard::Keyboard()
{
   num = "1234567890-=";
   rus = "йцукенгшщзхъфывапролджэёячсмитьбю.";
   eng = "qwertyuiop[]asdfghjkl;'`zxcvbnm,./";
   numbers = new QHBoxLayout;
   toprow = new QHBoxLayout;
   middlerow = new QHBoxLayout;
   lowrow = new QHBoxLayout;
   space = new QHBoxLayout;
   mainlayout = new QVBoxLayout;
   int i = 0, j = 10;
   for (i = 0, j = 10; i < 12 && j < 22; i++, j++) {
       KeyLetter item;
       item.rus = item.en = num[i];
       item.bot = new QPushButton(item.rus);
       key[j] = item;
       numbers->addWidget(item.bot);
   }
   for (i = 0, j = 24; i < 12 && j < 36; i++, j++) {
       KeyLetter item;
       item.rus = rus[i];
       item.en = eng[i];
       item.bot = new QPushButton(item.rus);
       key[j] = item;
       toprow->addWidget(item.bot);
   }
   for (i = 12, j = 38; i < 24 && j < 50; i++, j++) {
       KeyLetter item;
       item.rus = rus[i];
       item.en = eng[i];
       item.bot = new QPushButton(item.rus);
       key[j] = item;
       if (j != 49)
        middlerow->addWidget(item.bot);
       else
          numbers->insertWidget(0,item.bot);
   }
   for (i = 24, j = 52; i < 46 && j < 62; i++, j++) {
       KeyLetter item;
       item.rus = rus[i];
       item.en = eng[i];
       item.bot = new QPushButton(item.rus);
       key[j] = item;
       lowrow->addWidget(item.bot);
   }
   KeyLetter item;
   item.rus = item.en = " Enter ";
   item.bot = new QPushButton(item.rus);
   key[36] = item;
   middlerow->addWidget(item.bot);
   item.rus = item.en = " Caps ";
   item.bot = new QPushButton(item.rus);
   key[66] = item;
   middlerow->insertWidget(0,item.bot);
   item.rus = item.en = " Shift ";
   item.bot = new QPushButton(item.rus);
   key[62] = item;
   lowrow->addWidget(item.bot);
   item.bot = new QPushButton(item.rus);
   key[50] = item;
   lowrow->insertWidget(0,item.bot);
   item.rus = item.en = " Tab ";
   item.bot = new QPushButton(item.rus);
   key[23] = item;
   toprow->insertWidget(0,item.bot);
   item.rus = item.en = " \\ ";
   item.bot = new QPushButton(item.rus);
   key[51] = item;
   toprow->addWidget(item.bot);
   item.rus = item.en = "Backspase";
   item.bot = new QPushButton(item.rus);
   key[22] = item;
   numbers->addWidget(item.bot);
   item.rus = item.en = "";
   item.bot = new QPushButton();
   key[65] = item;
   space->addWidget(item.bot);
   mainlayout->addLayout(numbers);
   mainlayout->addLayout(toprow);
   mainlayout->addLayout(middlerow);
   mainlayout->addLayout(lowrow);
   mainlayout->addLayout(space);
   QList<int> keys = this->Key().uniqueKeys();
   for (int i = 0; i < keys.size(); i++) {
       this->Key()[keys[i]].bot->setStyleSheet("background-color: ivory;"
                                               "border-radius: 2px; "
                                               "font: italic 70% georgia, serif;"
                                               "border: 2px double ivory;");
       this->Key()[keys[i]].bot->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
       this->Key()[keys[i]].bot->setFocusPolicy(Qt::NoFocus);
   }
   keys.clear();
   keys << 10 << 11 << 24 << 38 << 52 << 61 << 47 << 48 << 33 << 34 << 35 << 19 << 20 << 21;
   for (int i = 0; i < keys.size(); i++) {
       this->Key()[keys[i]].bot->setStyleSheet("background-color: lime;"
                                               "border-radius: 2px; "
                                               "font: italic 70% georgia, serif;"
                                               "border: 2px double lime;");
       this->Key()[keys[i]].bot->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
   }
   keys.clear();
   keys << 12 << 25 << 39 << 53 << 60 << 46 << 32 << 18;
   for (int i = 0; i < keys.size(); i++) {
       this->Key()[keys[i]].bot->setStyleSheet("background-color: deepskyblue;"
                                               "border-radius: 2px; "
                                               "font: italic 70% georgia, serif;"
                                               "border: 2px double deepskyblue;");
       this->Key()[keys[i]].bot->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
   }
   keys.clear();
   keys << 13 << 26 << 40 << 54 << 59 << 45 << 31 << 17;
   for (int i = 0; i < keys.size(); i++) {
       this->Key()[keys[i]].bot->setStyleSheet("background-color: pink;"
                                               "border-radius: 2px; "
                                               "font: italic 70% georgia, serif;"
                                               "border: 2px double pink;");
       this->Key()[keys[i]].bot->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
   }
   keys.clear();
   keys << 14 << 15 << 27 << 28 << 41 << 42 << 55 << 56;
   for (int i = 0; i < keys.size(); i++) {
       this->Key()[keys[i]].bot->setStyleSheet("background-color: plum;"
                                               "border-radius: 2px; "
                                               "font: italic 70% georgia, serif;"
                                               "border: 2px double plum;");
       this->Key()[keys[i]].bot->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
   }
   keys.clear();
   keys << 16 << 29 << 30 << 43 << 44 << 57 << 58;
   for (int i = 0; i < keys.size(); i++) {
       this->Key()[keys[i]].bot->setStyleSheet("background-color: yellow;"
                                               "border-radius: 2px; "
                                               "font: italic 70% georgia, serif;"
                                               "border: 2px double yellow;");
       this->Key()[keys[i]].bot->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
   }
}

Keyboard::~Keyboard()
{
    delete mainlayout; 
}

void Keyboard:: ChangeToEng()
{
    QList<int> keys = this->Key().uniqueKeys();
    for (int i = 0; i < keys.size(); i++)
        this->Key()[keys[i]].bot->setText(this->Key()[keys[i]].en);
}

void Keyboard:: ChangeToRus()
{
    QList<int> keys = this->Key().uniqueKeys();
    for (int i = 0; i < keys.size(); i++)
        this->Key()[keys[i]].bot->setText(this->Key()[keys[i]].rus);
}

QMap<int, KeyLetter> Keyboard:: Key()
{
    return key;
}

QVBoxLayout* Keyboard:: MainLayout()
{
    return mainlayout;
}

