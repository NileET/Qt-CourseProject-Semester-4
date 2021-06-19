#ifndef DEVICE_HPP
#define DEVICE_HPP
#include <string>


class Device {
public:
    /**
     * @brief The Size struct - хранит размеры девайса (ширина, глубина, высота)
     */
    struct Size {
        double  __width,
                __length,
                __high;
    };

protected:
    /**
     * @brief Device - конструктор по умолчанию
     */
    Device();

    /**
     * @brief Device - конструктор с параметрами
     * @param manufacturer - производитель
     * @param modelName - модель
     * @param portCount - количество портов
     * @param modelSize - размеры
     * @param price - цена
     */
    Device(const std::string   manufacturer,
           const std::string   modelName,
           const int           portCount,
           const Size          modelSize,
           const int           price);

    /**
     * @brief Device - конструктор копирования
     * @param rhs - копируемый экземпляр
     */
    Device(const Device& rhs);

public:
    /**
     * @brief operator= - перегруженная операция присваивания
     * @param rhs - присваемый экземпляр
     */
    Device& operator=(const Device& rhs);

    /**
     * @brief ~Device - деструктор класса
     */
    virtual ~Device();

    /**
     * @brief operator<< - перегруженная операция вывода в поток
     * @param stream - принимаемый поток
     * @param item - принимаемый экземпляр
     */
    friend std::ostream& operator<<(std::ostream& stream, const Device& item);

    /**
     * @brief setManufacturer - задает новое значение _manufacturer
     * @param manufacturer - принимаемое новое значение
     */
    void setManufacturer(const std::string& manufacturer);

    /**
     * @brief getManufacturer - возращает _manufacturer
     */
    std::string getManufacturer() const;

    /**
     * @brief setModelName - задает новое значение _modelName
     * @param modelName - принимаемое новое значение
     */
    void setModelName(const std::string& modelName);

    /**
     * @brief getModelName - возращает _modelName
     */
    std::string getModelName() const;

    /**
     * @brief setPortCount - задает новое значение _portCount
     * @param portCount - принимаемое новое значение
     */
    void setPortCount(const int& portCount);

    /**
     * @brief getPortCount - возращает _portCount
     */
    int getPortCount() const;

    /**
     * @brief setModelSize - задает новое значение _modelSize
     * @param modelSize - принимаемое новое значение
     */
    void setModelSize(const Size& modelSize);

    /**
     * @brief getModelSize - возращает _modelSize
     */
    Size getModelSize() const;

    /**
     * @brief setPrice - задает новое значение _price
     * @param price - принимаемое новое значение
     */
    void setPrice(const int& price);

    /**
     * @brief getPrice - возращает _price
     */
    int getPrice() const;

private:
    /**
     * @brief _manufacturer - производитель
     */
    std::string _manufacturer;

    /**
     * @brief _modelName - модель
     */
    std::string _modelName;

    /**
     * @brief _portCount - количество портов
     */
    int _portCount;

    /**
     * @brief _modelSize - размеры
     */
    Size _modelSize;

    /**
     * @brief _price - цена
     */
    int _price;
};


#endif //DEVICE_HPP
