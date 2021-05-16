#include "mainwindow.hpp"

#include <QApplication>
#include <QIcon>

int main(int argc, char *argv[])
{
  QApplication a(argc, argv);
  MainWindow w;
  w.setWindowIcon(QIcon(":/img/images/iconMainWindow.jpg"));
  w.show();
  return a.exec();
}
