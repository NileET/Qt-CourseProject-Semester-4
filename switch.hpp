#ifndef SWITCH_HPP
#define SWITCH_HPP
#include "device.hpp"


class Switch : public Device {
public:
    /**
     * @brief Switch - конструктор по умолчанию
     */
    Switch();

    /**
     * @brief Switch - конструктор с параметрами
     * @param manufacturer - производитель
     * @param modelName - модель
     * @param baseSpeed - базовая скорость передачи данных
     * @param portCount - количество портов
     * @param hasPoE - поддержка PoE
     * @param modelSize - размеры
     * @param price - цена
     */
    Switch(const std::string         manufacturer,
           const std::string         modelName,
           const std::pair<int, int> baseSpeed,
           const int                 portCount,
           const bool                hasPoE,
           const Size                modelSize,
           const int                 price);

    /**
     * @brief Switch - конструктор копирования
     * @param rhs - копируемый экземпляр
     */
    Switch(const Switch& rhs);

    /**
     * @brief operator= - перегруженная операция присваивания
     * @param rhs - присваемый экземпляр
     * @return
     */
    Switch& operator=(const Switch& rhs);

    ~Switch();

    /**
     * @brief operator<< - перегруженная операция вывода в поток
     * @param stream - принимаемый поток
     * @param item - принимаемый экземпляр
     */
    friend std::ostream& operator<<(std::ostream& stream, const Switch& item);

    /**
     * @brief setBaseSpeed - задает новое значение _baseSpeed
     * @param hasPoE - принимаемое новое значение
     */
    void setBaseSpeed(const std::pair<int, int>& hasPoE);

    /**
     * @brief getBaseSpeed - возращает _baseSpeed
     * @return
     */
    std::pair<int, int> getBaseSpeed() const;

    /**
     * @brief setHasPoE - задает новое значение _hasPoE
     * @param baseSpeed - принимаемое новое значение
     */
    void setHasPoE(const bool& baseSpeed);

    /**
     * @brief getHasPoE - возращает _hasPoE
     * @return
     */
    bool getHasPoE() const;

private:
    /**
     * @brief _baseSpeed - базовая скорость передачи данных
     */
    std::pair<int, int> _baseSpeed;

    /**
     * @brief _hasPoE - поддержка PoE
     */
    bool _hasPoE;
};


#endif //SWITCH_HPP
