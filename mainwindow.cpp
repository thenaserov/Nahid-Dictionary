#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
   this->setWindowTitle("N² Dictionary V-1.9");
   ui->pbSearch->setIcon(QIcon(":/Files/Icons/search.png"));
   ui->leEnglish->setFocus();
   ui->horizontalSlider->setValue(12);
   ui->horizontalSlider->setMinimum(4);
   ui->horizontalSlider->setMaximum(26);
   ui->textBrowser->setFontPointSize(_fontSize);
   QStringList keys;
   QFile       file(":/Files/dictionary.json");

   file.open(QIODevice::ReadOnly);
   QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
   QJsonObject   obj = doc.object();

   keys.append(obj.keys());
   QCompleter *completer = new QCompleter(keys, this);

   completer->setCaseSensitivity(Qt::CaseInsensitive);
   ui->leEnglish->setCompleter(completer);

   file.close();
   QStringList keysF;
   QFile       fileF(":/Files/dictionaryFa.json");

   fileF.open(QIODevice::ReadOnly);
   QJsonDocument docF = QJsonDocument::fromJson(fileF.readAll());
   QJsonObject   objF = doc.object();


   keys.append(objF.keys());
   QCompleter *completerF = new QCompleter(keys, this);

   completerF->setCaseSensitivity(Qt::CaseInsensitive);
   fileF.close();
}


MainWindow::~MainWindow()
{
   delete ui;
}


void MainWindow::search()
{
   _ans.clear();
   QFile filePhonetics(":/Files/phonetics.json");

   filePhonetics.open(QIODevice::ReadOnly);
   QJsonDocument docPhonetics = QJsonDocument::fromJson(filePhonetics.readAll());
   QJsonObject   objPhonetics = docPhonetics.object();

   _word = ui->leEnglish->text().toLower();
   _ans += "PRONOUNCIATION : ";
   _ans += "/";
   _ans += objPhonetics.value(_word).toString();
   _ans += "/";
   _ans += "\n";
   ui->textBrowser->setText(_ans);
   if (ui->textBrowser->toPlainText() == "")
   {
      ui->textBrowser->setText("Not found");
   }
   filePhonetics.close();
   QFile file(":/Files/dictionary.json");

   file.open(QIODevice::ReadOnly);
   QJsonDocument doc = QJsonDocument::fromJson(file.readAll());
   QJsonObject   obj = doc.object();

   _word = ui->leEnglish->text().toLower();
   _ans.append("\n" + obj.value(_word).toString());
   ui->textBrowser->setText(_ans);
   if (ui->textBrowser->toPlainText() == "")
   {
      ui->textBrowser->setText("Not found");
   }
   file.close();
}


void MainWindow::resize(int value)
{
   _fontSize = value;
   ui->textBrowser->setFontPointSize(_fontSize);
}


void MainWindow::on_pbSearch_clicked()
{
   search();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
   _fontSize = value;
   ui->textBrowser->setFontPointSize(_fontSize);
   ui->textBrowser->setText(_ans);
}


void MainWindow::on_pbPronounce_clicked()
{
   _textToSpeechWord.say(ui->leEnglish->text());
}


void MainWindow::on_leEnglish_returnPressed()
{
   if (ui->leEnglish->text().toLower() == "exit")
   {
      exit(1);
   }
   search();
}
