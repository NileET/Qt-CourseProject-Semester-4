#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "switch.hpp"

#include <QWidget>


namespace Ui {
  class Graphics;
}

class Graphics : public QWidget
{
  Q_OBJECT

  /**
   * @brief The Properties enum - свойства
   */
  enum class Properties { price,
                          portCount,
                          volume };

  /**
   * @brief setChart - задание графика
   * @param prop - выбранное свойство
   */
  void setChart(Properties prop);

public:
  /**
   * @brief Graphics - конструктор класса
   */
  explicit Graphics(QList<Switch> switches, QWidget *parent = nullptr);

  ~Graphics();

  /**
   * @brief Price - график цены
   */
  void Price();

  /**
   * @brief PortCount - график количества портов
   */
  void PortCount();

  /**
   * @brief Volume - график объема
   */
  void Volume();


private:
  /**
   * @brief ui - указатель на поля, созданные в Qt Designer
   */
  Ui::Graphics *ui;
  /**
   * @brief _switches - хранилище данных
   */
  QList<Switch> _switches;
};

#endif // GRAPHICS_HPP
