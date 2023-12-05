#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QJsonArray>

///
/// \brief MainWindow::MainWindow
/// \param parent
///
MainWindow::MainWindow(QWidget *parent)
   : QMainWindow(parent)
   , ui(new Ui::MainWindow)
{
   ui->setupUi(this);
//   this->setStyleSheet("background: #648880;background: linear-gradient(to right, #f6f1d3, #648880, #293f50);");
   // ----------------------------------------------------------------------------------
   this->setWindowTitle("N² Dictionary V-1.8");
   // UI/UX
   ui->pbSearch->setIcon(QIcon(":/Files/Icons/search.png"));
   // ui->pbSearchFarsi->setIcon(QIcon(":/Files/Icons/search.png"));
//   ui->pbSearch->setIconSize(QSize(65, 65));
//   this->setStyleSheet("background:url(C:/Users/Naser Rezayi/Downloads/17275258.jpg)");
//   ui->tabWidget->setStyleSheet("opacity : 0.5;");
   ui->leEnglish->setFocus();
//   this->setAttribute(Qt::WA_TranslucentBackground);
//   this->setWindowFlags(Qt::FramelessWindowHint);
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
   // ui->horizontalSliderFarsi->setValue(12);
   // ui->horizontalSliderFarsi->setMinimum(4);
   // ui->horizontalSliderFarsi->setMaximum(26);
   // ui->textBrowserFarsi->setFontPointSize(_fontSize);
   QStringList keysF;
   QFile       fileF(":/Files/dictionaryFa.json");

   fileF.open(QIODevice::ReadOnly);
   QJsonDocument docF = QJsonDocument::fromJson(fileF.readAll());
   QJsonObject   objF = doc.object();


   keys.append(objF.keys());
   QCompleter *completerF = new QCompleter(keys, this);

   completerF->setCaseSensitivity(Qt::CaseInsensitive);
   // ui->leFarsi->setCompleter(completerF);
   fileF.close();
}


///
/// \brief MainWindow::~MainWindow
///
MainWindow::~MainWindow()
{
   delete ui;
}


///
/// \brief MainWindow::search
///
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


///
/// \brief MainWindow::searchF
///
void MainWindow::searchF()
{
   QFile fileF(":/Files/dictionaryFa.json");

   fileF.open(QIODevice::ReadOnly);
   QJsonDocument docF = QJsonDocument::fromJson(fileF.readAll());
   QJsonObject   objF = docF.object();

   // _wordF = ui->leFarsi->text().toLower();
   qDebug() << (objF[_wordF]);

////   _ansF = objF.value(_wordF).toString().toUtf8();
////   foreach(QString word, var)
////   {
////      _ansF.append(word.toUtf8());
////      _ansF.append("\n");
////   }
////   ui->textBrowserFarsi->setText(_ansF);
////   qDebug() << _ansF;
////   if (ui->textBrowserFarsi->toPlainText() == "")
////   {
////      ui->textBrowserFarsi->setText("یافت نشد!");
////   }
////   qDebug() << objF.value("love");
//   fileF.close();
}


///
/// \brief MainWindow::resize
/// \param value
///
void MainWindow::resize(int value)
{
   _fontSize = value;
   ui->textBrowser->setFontPointSize(_fontSize);
}


///
/// \brief MainWindow::on_pbSearch_clicked
///
void MainWindow::on_pbSearch_clicked()
{
   // if (ui->leEnglish->text().toLower() == "exit")
   // {
   //    exit(1);
   // }
   search();
}


///
/// \brief MainWindow::on_horizontalSlider_valueChanged
/// \param value
///
void MainWindow::on_horizontalSlider_valueChanged(int value)
{
   _fontSize = value;
   ui->textBrowser->setFontPointSize(_fontSize);
   ui->textBrowser->setText(_ans);
}


///
/// \brief MainWindow::on_pbPronounce_clicked
///
void MainWindow::on_pbPronounce_clicked()
{
   _textToSpeechWord.say(ui->leEnglish->text());
}


///
/// \brief MainWindow::on_pbSearchFarsi_clicked
///
void MainWindow::on_pbSearchFarsi_clicked()
{
   // if (ui->leFarsi->text().toLower() == "خروج")
   // {
   //    exit(1);
   // }
   // searchF();
}


///
/// \brief MainWindow::on_leEnglish_returnPressed
///
void MainWindow::on_leEnglish_returnPressed()
{
   if (ui->leEnglish->text().toLower() == "exit")
   {
      exit(1);
   }
   search();
}
