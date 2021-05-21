#ifndef ABOUTPROGRAMM_HPP
#define ABOUTPROGRAMM_HPP

#include <QDialog>

namespace Ui {
  class AboutProgramm;
}

class AboutProgramm : public QDialog
{
  Q_OBJECT

public:
  explicit AboutProgramm(QWidget *parent = nullptr);
  ~AboutProgramm();

private:
  Ui::AboutProgramm *ui;
};

#endif // ABOUTPROGRAMM_HPP
