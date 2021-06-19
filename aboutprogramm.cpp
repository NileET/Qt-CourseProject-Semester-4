#include "aboutprogramm.hpp"
#include "ui_aboutprogramm.h"


AboutProgramm::AboutProgramm(QWidget *parent) :
  QDialog(parent),
  ui(new Ui::AboutProgramm)
{
  ui->setupUi(this);

  connect(ui->pushButtonOK, &QPushButton::clicked, this, &QDialog::close);
}

AboutProgramm::~AboutProgramm()
{
  delete ui;
}
