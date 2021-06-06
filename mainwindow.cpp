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
  , contextTableMenu(new QMenu(this))
  , currentFileName(QString())
{
  ui->setupUi(this);

  // Задаем название главного окна
  setWindowTitle(tr("Switch"));
  // Задаеммодель для tableView
  ui->tableView->setModel(proxyModel);
  // Сортировка по manufacturer
  ui->tableView->sortByColumn(0, Qt::AscendingOrder);
  // Добавляем действия в контекстное меню таблицы
  contextTableMenu->addAction(ui->actionAdd);
  contextTableMenu->addAction(ui->actionRemove);
  // Установка переводчика
  qApp->installTranslator(&appTranslator);
  // Местоположение каталога с файлами перевода
  qmPath = qApp->applicationDirPath() + "/translations";
  // Вызов коннектов
  createConnections();
  // Создание языкового меню
  createLanguageMenu();
}

void MainWindow::createConnections()
{
  // Вызов "О программе"
  connect(ui->actionAboutProgramm, &QAction::triggered,  this, &MainWindow::aboutProgramm);
  // Вызов контекстного меню
  connect(ui->tableView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(customMenuRequested(QPoint)));
  // Вызов фильтрации (поиска) по всей таблице при изменении текста
  connect(ui->lineEditFind, &QLineEdit::textChanged, this, &MainWindow::lineEditFind_textChanged);
  // Вызов открытия файла
  connect(ui->actionOpen  , &QAction::triggered,  this, &MainWindow::actionOpen_triggered);
  // Вызов сохранения файла
  connect(ui->actionSave  , &QAction::triggered,  this, &MainWindow::actionSave_triggered);
  // Вызов сохранения файла как...
  connect(ui->actionSaveAs, &QAction::triggered,  this, &MainWindow::actionSaveAs_triggered);
  // Вызов закрытия файла
  connect(ui->actionClose , &QAction::triggered,  this, &MainWindow::actionClose_triggered);
  // Вызов добавления записи
  connect(ui->actionAdd   , &QAction::triggered,  this, &MainWindow::actionAdd_triggered);
  // Вызов удаления записи
  connect(ui->actionRemove, &QAction::triggered,  this, &MainWindow::actionRemove_triggered);
}

MainWindow::~MainWindow()
{
  delete contextTableMenu;
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
      if (QMessageBox::Yes == QMessageBox::question(this,
                     tr("Save and close"),
                     tr("Do you want to save and close "
                        "%1 before opening of "
                        "new file?").arg(QFileInfo(currentFileName).fileName()),
                      QMessageBox::Yes |
                      QMessageBox::Cancel)) {
          actionSave_triggered();
          actionClose_triggered();
        } else {
          return;
        }
    }

  currentFileName = QFileDialog::getOpenFileName(this, tr("Open Document"));

  if (!currentFileName.isEmpty()) {
      openFile(currentFileName);
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

  file.close();

  QApplication::restoreOverrideCursor();

  // Задаем модель для proxyModel
  proxyModel->setSourceModel(_switches);
  // Выравнивание колонок по содержимому таблицы
  ui->tableView->resizeColumnsToContents();
  // Растягивание последнего столбца
  ui->tableView->horizontalHeader()->setStretchLastSection(true);

  ui->actionSave->setEnabled(true);
  ui->actionSaveAs->setEnabled(true);
  ui->actionClose->setEnabled(true);
  ui->menuEntry->setEnabled(true);
  ui->lineEditFind->setEnabled(true);
}

void MainWindow::actionSave_triggered()
{
  saveFile(currentFileName);
}

void MainWindow::actionSaveAs_triggered()
{
  QString saveFileName = QFileDialog::getSaveFileName(this, tr("Save Document"),
                                                  QDir::currentPath(),
                                                  "Text Files (*.txt);;All Files (*.*)");
  if (!saveFileName.isEmpty()) {
      saveFile(saveFileName);
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

  foreach (const auto& it, _switches->toQList()) {
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

  file.close();

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
  currentFileName = QString();

  ui->actionSave->setEnabled(false);
  ui->actionSaveAs->setEnabled(false);
  ui->actionClose->setEnabled(false);
  ui->menuEntry->setEnabled(false);
  ui->lineEditFind->setEnabled(false);
}

void MainWindow::customMenuRequested(QPoint pos)
{
  // Вызываем контекстное меню для таблицы
  contextTableMenu->popup(ui->tableView->viewport()->mapToGlobal(pos));
}

void MainWindow::actionAdd_triggered()
{
  if (currentFileName.isEmpty()) {
      QMessageBox::warning(this,
                           tr("Error of appending"),
                           tr("Can not append entry. Probably, table is empty..."));
      return;
    }

  // Добавление записи
  _switches->insertRows(0, 1);

  for (int row = _switches->rowCount(); row >= 0 ; --row) {
       QModelIndex indexItem = proxyModel->index(row, 1);
       if (indexItem.data().toString() == "Unknown") {
           ui->tableView->selectRow(indexItem.row());
           break;
         }
    }
}

void MainWindow::actionRemove_triggered()
{
  if (!_switches->rowCount(QModelIndex())) {
      QMessageBox::warning(this,
                           tr("Error of removing"),
                           tr("Can not removing entry. Probably, table is empty..."));
      return;
    }

  // Удаление выделенной строки
  int row = proxyModel->mapToSource(ui->tableView->currentIndex()).row();
  _switches->removeRows(row, 1);
}

void MainWindow::lineEditFind_textChanged(const QString& text)
{
  //Устанавливаем регулярное выражения для фильтра
  QRegExp::PatternSyntax syntax = QRegExp::PatternSyntax(QRegExp::FixedString);
  QRegExp regExp(text, Qt::CaseInsensitive, syntax);

  //Устанавливаем все колонки фильтрации при поиске
  proxyModel->setFilterKeyColumn(-1);
  proxyModel->setFilterRegExp(regExp);
}
