#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
}

MainWindow::~MainWindow()
{
  delete ui;
}


void MainWindow::on_actionOpen_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Open Document");

  if (!fileName.isEmpty()) {
      openFile(fileName);
    }
}

void MainWindow::openFile(const QString& fullFileName)
{
  QFile file(fullFileName);
  if (!file.open(QFile::ReadOnly | QFile::Text)) {
      QMessageBox::warning(this,
                           "Open Document",
                           QString("Can not read file &1:\n%2")
                           .arg(QFileInfo(fullFileName).fileName(), file.errorString()));
      return;
    }
  QTextStream in(&file);
  QApplication::setOverrideCursor(Qt::WaitCursor);

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

      _switches.push_back(Switch(manufacturer, modelName, baseSpeed, portCount, hasPoE, {width, length, high}, price));
    }

  QApplication::restoreOverrideCursor();

  ui->actionSave->setEnabled(true);
  ui->actionShow->setEnabled(true);
  ui->actionClose->setEnabled(true);
  ui->menuEntry->setEnabled(true);
}


void MainWindow::on_actionSave_triggered()
{
  QString fileName = QFileDialog::getOpenFileName(this, "Save Document");
  if (!fileName.isEmpty()) {
      saveFile(fileName);
    }
}

void MainWindow::saveFile(const QString &fullFileName)
{
  QFile file(fullFileName);
  if (!file.open(QFile::WriteOnly | QFile::Text)) {
      QMessageBox::warning(this,
                           "Save Document",
                           QString("Can not write file &1:\n%2")
                           .arg(QFileInfo(fullFileName).fileName(), file.errorString()));
      return;
    }

  QTextStream out(&file);
  QApplication::setOverrideCursor(Qt::WaitCursor);

  foreach (const auto& it, _switches) {
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
