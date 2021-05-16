#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QList>
#include <QTranslator>
#include "switch.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QActionGroup;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void switchLanguage(QAction *action);

  void on_actionOpen_triggered();

  void on_actionSave_triggered();


private:
  Ui::MainWindow *ui;
  QList<Switch> _switches;

  QTranslator appTranslator;
  QActionGroup *languageActionGroup;
  QString qmPath;

  void createLanguageMenu();

  void openFile(const QString& fullFileName);
  void saveFile(const QString& fullFileName);
};
#endif // MAINWINDOW_HPP
