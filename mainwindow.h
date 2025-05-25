#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <iostream>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QFile>
#include <QString>
#include <QCompleter>
#include <QAbstractItemView>
// #include <QTextCodec>
#include <QLocale>
#include <QtTextToSpeech/QTextToSpeech>
#include <QtTextToSpeech/QTextToSpeechPlugin>
#include <QtSql/qsqlquery.h>
#include <QtSql/qsqldatabase.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
   Q_OBJECT

public:
   MainWindow(QWidget *parent = nullptr);
   ~MainWindow();

private:
   Ui::MainWindow *ui;
   int _fontSize = 12;
   QString _word;
   QString _wordF;
   // QTextCodec *codec = QTextCodec::codecForName("UTF-8");
   QString _ans;
   QString _ansF;
   QTextToSpeech _textToSpeechWord;
   QTextToSpeech _textToSpeechDefinition;

public slots:
   void on_pbSearch_clicked();
   void search();
   void searchF();
   void resize(int value);

private slots:
   void on_horizontalSlider_valueChanged(int value);
   void on_pbPronounce_clicked();
   void on_pbSearchFarsi_clicked();

   void on_leEnglish_returnPressed();

signals:
   void sliderChanged(int value);
};
#endif // MAINWINDOW_H
