#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QTranslator>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class QActionGroup;
class TableModel;
class ProxyModel;
class Graphics;

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  /**
   * @brief MainWindow - конструктор класса
   */
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private slots:
  /**
   * @brief switchLanguage - триггер смены языка
   * @param action
   */
  void switchLanguage(QAction *action);

  /**
   * @brief setModified - сделать окно модифицированным
   */
  void setModified();

  /**
   * @brief actionNew_triggered - открытие нового окна MainWindow
   */
  void actionNew_triggered();

  /**
   * @brief actionOpen_triggered - триггер открытия файла
   */
  void actionOpen_triggered();

  /**
   * @brief actionSave_triggered - триггер сохранения текущего файла
   */
  void actionSave_triggered();

  /**
   * @brief actionSaveAs_triggered - триггер сохранения файла как ...
   */
  void actionSaveAs_triggered();

  /**
   * @brief actionClose_triggered - триггер закрытия файла
   */
  void actionClose_triggered();

  /**
   * @brief aboutProgramm - триггер вызова диалогового окна "О программе"
   */
  void aboutProgramm();

  /**
   * @brief customMenuRequested - вызов контекстного меню таблицы нажатием ПКМ
   * @param pos - позиция вызова контекстного меню
   */
  void customMenuRequested(QPoint pos);

  /**
   * @brief actionAdd_triggered - триггер добавления записи
   */
  void actionAdd_triggered();

  /**
   * @brief actionRemove_triggered - триггер удаления записи
   */
  void actionRemove_triggered();

  /**
   * @brief lineEditFind_textChanged - вызов фильрации (поиска) по всей таблице при вводе текста в виджет
   * @param text - содержание самого виджета
   */
  void lineEditFind_textChanged(const QString& text);

  /**
   * @brief actionPrice_triggered - открытие графика цен
   */
  void actionPrice_triggered();

  /**
   * @brief actionPortCount_triggered - открытие графика количества портов
   */
  void actionPortCount_triggered();

  /**
   * @brief actionVolume_triggered - открытие графика
   */
  void actionVolume_triggered();

private:
  /**
   * @brief ui - указатель на поля, созданные в Qt Designer
   */
  Ui::MainWindow *ui;

  /**
   * @brief _switches - указатель на модель таблицы, которая хранит все данные
   */
  TableModel *_switches;

  /**
   * @brief proxyModel - указатель на модель таблицы, которая позволяет осуществить поиск и сортировку
   */
  ProxyModel *proxyModel;

  /**
   * @brief contextTableMenu - указатель на контекстное меню
   */
  QMenu *contextTableMenu;

  /**
   * @brief appTranslator - переводчик приложения
   */
  QTranslator appTranslator;

  /**
   * @brief languageActionGroup - указатель на группу с выбором языка (Английский, Русский, Немецкий)
   */
  QActionGroup *languageActionGroup;

  /**
   * @brief qmPath - местоположение .qm файлов с содержанием переводов
   */
  QString qmPath;

  /**
   * @brief currentFileName - текущий открытый файл
   */
  QString currentFileName;

  /**
   * @brief currentLanguage - текущий выбранный язык
   */
  QString currentLanguage;

  /**
   * @brief isUntitled - проверка имени файла на подлиность
   */
  bool isUntitled;

  /**
   * @brief createConnections - создание всех connect'ов
   */
  void createConnections();

  /**
   * @brief createLanguageMenu - создание языкового меню
   */
  void createLanguageMenu();

  /**
   * @brief openFile - открытие файла
   * @param fullFileName - имя открываемого файла
   */
  void openFile(const QString& fullFileName);

  /**
   * @brief saveFile - сохранение файла
   * @param fullFileName - имя сохраняемого файла
   */
  void saveFile(const QString& fullFileName);

  /**
   * @brief setCurrentFile - задание имени текущего файла
   * @param fullFileName - имя сохраняемого файла
   */
  void setCurrentFile(const QString& fullFileName);

  /**
   * @brief readSettings - чтение настроек интерфейса с прошлой сессии
   */
  void readSettings();

  /**
   * @brief writeSettings - сохранение настроек интерфейса текущей сессии
   */
  void writeSettings();


  Graphics* createChart();

protected:
  /**
   * @brief Событие наведения файла на программу
   * @param event Объект класса события QDragEnterEvent
   */
  void dragEnterEvent(QDragEnterEvent* event) override;
  /**
   * @brief Событие на отпускание файла в программу
   * @param event Объект класса события QDropEvent
   */
  void dropEvent(QDropEvent* event) override;
};
#endif // MAINWINDOW_HPP
