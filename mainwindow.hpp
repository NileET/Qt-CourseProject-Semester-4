#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QList>
#include <QTranslator>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QActionGroup;
class TableModel;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  void switchLanguage(QAction *action);

  void actionOpen_triggered();
  void actionSave_triggered();
  void actionClose_triggered();

  void aboutProgramm();
  void customMenuRequested(QPoint pos);
  void actionAdd_triggered();
  void actionRemove_triggered();

private:
  Ui::MainWindow *ui;
  TableModel *_switches;

  QTranslator appTranslator;
  QActionGroup *languageActionGroup;
  QString qmPath;

  void createLanguageMenu();

  void openFile(const QString& fullFileName);
  void saveFile(const QString& fullFileName);
};
#endif // MAINWINDOW_HPP
