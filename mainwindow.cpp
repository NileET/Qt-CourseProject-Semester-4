#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "aboutprogramm.hpp"
#include "tablemodel.hpp"
#include "proxymodel.hpp"

#include <QFileDialog>
#include <QFile>
#include <QLibraryInfo>
#include <QActionGroup>
#include <QMessageBox>
#include <QTextStream>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
  , _switches(new TableModel(this))
  , proxyModel(new ProxyModel(this))
{
  ui->setupUi(this);

  this->setWindowTitle(tr("Switch"));

  ui->tableView->setModel(proxyModel);
  // Включение сортировки
  ui->tableView->setSortingEnabled(true);
  // Сортировка по id
  ui->tableView->sortByColumn(0, Qt::AscendingOrder);
  // Растягивание последнего столбца
  ui->tableView->horizontalHeader()->setStretchLastSection(true);
  // Выравнивание колонок по содержимому таблицы
  ui->tableView->resizeColumnsToContents();
  // Установка переводчика
  qApp->installTranslator(&appTranslator);
  // Местоположение каталога с файлами перевода
  qmPath = qApp->applicationDirPath() + "/translations";

  createConnections();
  createLanguageMenu();
}

void MainWindow::createConnections()
{
  // Вызов "О программе"
  connect(ui->actionAboutProgramm, &QAction::triggered,  this, &MainWindow::aboutProgramm);
  // Вызов контекстного меню
  connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customMenuRequested(QPoint)));
  // Вызов открытия файла
  connect(ui->actionOpen  , &QAction::triggered, this, &MainWindow::actionOpen_triggered);
  // Вызов сохранения файла
  connect(ui->actionSave  , &QAction::triggered, this, &MainWindow::actionSave_triggered);
  // Вызов закрытия файла
  connect(ui->actionClose , &QAction::triggered, this, &MainWindow::actionClose_triggered);
  // Вызов добавления записи
  connect(ui->actionAdd   , &QAction::triggered, this, &MainWindow::actionAdd_triggered);
  // Вызов удаления записи
  connect(ui->actionRemove, &QAction::triggered, this, &MainWindow::actionRemove_triggered);
}

MainWindow::~MainWindow()
{
  delete proxyModel;
  delete _switches;
  delete languageActionGroup;
  delete ui;
}

void MainWindow::switchLanguage(QAction *action)
{
  // Определяем локаль, которую выбрал пользователь
  QString localeFile = action->data().toString();

  // Загружаем перевод, выбранный пользователем
  appTranslator.load(localeFile, qmPath);

  ui->retranslateUi(this);
}

void MainWindow::createLanguageMenu()
{
  languageActionGroup = new QActionGroup(this);
  // Ставим связь пунктов меню со слотом смены языка приложения
  connect(languageActionGroup, &QActionGroup::triggered, this, &MainWindow::switchLanguage);
  // Определяем каталог, где лежат файлы переводов "*.qm"
  QDir dir(qmPath);

  QStringList fileNames = dir.entryList(QStringList("CourseProject_*.qm"));

  for (int i = 0; i < fileNames.size(); i++) {

      QString locale = fileNames[i];

      // Создаём временную переменную перевода для языкового пункта меню
      QTranslator translator;
      translator.load(fileNames[i], qmPath);

      QString language = translator.translate("MainWindow",
                                              "English");
      QAction *action = new QAction(tr("&%1 %2")
                                           .arg(i + 1)
                                           .arg(language),
                                           this);
      action->setCheckable(true);
      action->setData(locale);
      // Добавляем i-ый пункт в меню на нашей форме "mainwindow.ui"
      ui->menuLanguage->addAction(action);
      // Добавляем i-ый пункт в единую группу пунктов
      languageActionGroup->addAction(action);
      // Задаём  английский язык в качестве выбранного по умолчанию
      if (language == "English") {
          action->setChecked(true);
        }
    }
}

void MainWindow::actionOpen_triggered()
{
  if (_switches->rowCount(QModelIndex())) {

      return;
    }

  QString fileName = QFileDialog::getOpenFileName(this, tr("Open Document"));

  if (!fileName.isEmpty()) {
      openFile(fileName);
    }
}

void MainWindow::openFile(const QString& fullFileName)
{
  QFile file(fullFileName);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
      QMessageBox::warning(this,
                           tr("Open Document"),
                           tr("Can not read file %1:\n%2")
                           .arg(QFileInfo(fullFileName).fileName(), file.errorString()));
      return;
    }

  QTextStream in(&file);
  QApplication::setOverrideCursor(Qt::WaitCursor);

  // Цикл заполнения данных из файла
  while (!in.atEnd()) {
      QString bufLine = in.readLine();
      QStringList list = bufLine.split(";");

      std::string manufacturer = list[0].toStdString();

      std::string modelName = list[1].toStdString();

      QStringList speed = list[2].split(" ");
      std::pair<int, int> baseSpeed = std::make_pair(speed[0].toInt(), speed[1].toInt());

      int portCount = list[3].toInt();

      bool hasPoE = list[4].toInt();

      QStringList size = list[5].split(" ");
      double width  = size[0].toDouble(),
             length = size[1].toDouble(),
             high   = size[2].toDouble();

      int price = list[6].toInt();

      _switches->insertValue(Switch(manufacturer, modelName, baseSpeed, portCount, hasPoE, {width, length, high}, price));
    }

  QApplication::restoreOverrideCursor();

  proxyModel->setSourceModel(_switches);

  ui->tableView->resizeColumnsToContents();

  ui->actionSave->setEnabled(true);
  ui->actionClose->setEnabled(true);
  ui->menuEntry->setEnabled(true);
}

void MainWindow::actionSave_triggered()
{
  QString fileName = QFileDialog::getSaveFileName(this, tr("Save Document"),
                                                  QDir::currentPath(),
                                                  "Text Files (*.txt);;All Files (*.*)");
  if (!fileName.isEmpty()) {
      saveFile(fileName);
    }
}

void MainWindow::saveFile(const QString &fullFileName)
{
  QFile file(fullFileName);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
      QMessageBox::warning(this,
                           tr("Save Document"),
                           tr("Can not write file %1:\n%2")
                           .arg(QFileInfo(fullFileName).fileName(), file.errorString()));
      return;
    }

  QTextStream out(&file);
  QApplication::setOverrideCursor(Qt::WaitCursor);

  foreach (const auto& it, _switches->toQMap()) {
      out << it.getManufacturer().c_str() << ';'
          << it.getModelName().c_str()    << ';'
          << it.getBaseSpeed().first      << ' '
          << it.getBaseSpeed().second     << ';'
          << it.getPortCount()            << ';'
          << it.getHasPoE()               << ';'
          << it.getModelSize().__width    << ' '
          << it.getModelSize().__length   << ' '
          << it.getModelSize().__high     << ';'
          << it.getPrice()                << ';' << '\n';
    }

  QApplication::restoreOverrideCursor();
}

void MainWindow::aboutProgramm()
{
  auto aboutWin = new AboutProgramm(this);
  aboutWin->setWindowFlag(Qt::Window);
  aboutWin->setWindowTitle(tr("About programm"));
  aboutWin->setFixedSize(aboutWin->size());
  aboutWin->setAttribute(Qt::WA_DeleteOnClose);
  aboutWin->show();
}

void MainWindow::actionClose_triggered()
{
  proxyModel->setSourceModel(nullptr);
  _switches->clear();

  ui->actionSave->setEnabled(false);
  ui->actionClose->setEnabled(false);
  ui->menuEntry->setEnabled(false);
}

void MainWindow::customMenuRequested(QPoint pos)
{
  QMenu *menu = new QMenu(this);


  menu->addAction(ui->actionAdd);
  menu->addAction(ui->actionRemove);
  // Вызываем контекстное меню
  menu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

void MainWindow::actionAdd_triggered()
{
  if (!_switches->rowCount(QModelIndex())) {
      QMessageBox::warning(this,
                           tr("Error of appending"),
                           tr("Can not append entry. Probably, table is empty..."));
      return;
    }

  proxyModel->setSourceModel(nullptr);

  _switches->insertValue(Switch());

  proxyModel->setSourceModel(_switches);

  ui->tableView->resizeColumnsToContents();
}

void MainWindow::actionRemove_triggered()
{
  if (!_switches->rowCount(QModelIndex())) {
      QMessageBox::warning(this,
                           tr("Error of removing"),
                           tr("Can not removing entry. Probably, table is empty..."));
      return;
    }

  int tableID = ui->tableView->currentIndex().siblingAtColumn(0).data().toInt();

  proxyModel->setSourceModel(nullptr);

  _switches->removeValue(tableID);

  proxyModel->setSourceModel(_switches);

  ui->tableView->resizeColumnsToContents();
}
