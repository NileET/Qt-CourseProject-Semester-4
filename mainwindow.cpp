#include "mainwindow.hpp"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QString>
#include <sstream>

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
                             "Application",
                             QString("Can not read file &1:\n%2")
                             .arg(QFileInfo(fullFileName).fileName(), file.errorString()));
        return;
      }
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);

    while (!in.atEnd()) {
        QString bufLine = in.readLine();
        std::istringstream ss(bufLine.toStdString());

        std::string manufacturer; std::getline(ss, manufacturer, ';');

        std::string modelName; std::getline(ss, modelName, ';');

        std::pair<int, int> baseSpeed; ss >> baseSpeed.first >> baseSpeed.second;
        ss.ignore(1);

        int portCount; ss >> portCount;
        ss.ignore(1);

        bool hasPoE; ss >> hasPoE;
        ss.ignore(1);

        double width, length, high; ss >> width >> length >> high;
        ss.ignore(1);

        int price; ss >> price;

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
    QString fileName = QFileDialog::getOpenFileName(this, "Open Document");
    if (!fileName.isEmpty()) {

      }
}
