#include "device.hpp"
#include <iostream>


Device::Device() : Device("Unknown",
                          "Unknown",
                          0,
                          {0, 0, 0},
                          0)
{ }

Device::Device(const std::string   manufacturer,
               const std::string   modelName,
               const int           portCount,
               const Device::Size  modelSize,
               const int           price) :
      _manufacturer(manufacturer)
    , _modelName(modelName)
    , _portCount(portCount)
    , _modelSize(modelSize)
    , _price(price)
{ }

Device::Device(const Device& rhs) :
      _manufacturer(rhs._manufacturer)
    , _modelName(rhs._modelName)
    , _portCount(rhs._portCount)
    , _modelSize(rhs._modelSize)
    , _price(rhs._price)
{ }

Device &Device::operator=(const Device& rhs) {
    if (this == &rhs) return *this;

    _manufacturer = rhs._manufacturer;
    _modelName    = rhs._modelName;
    _portCount    = rhs._portCount;
    _modelSize    = rhs._modelSize;
    _price        = rhs._price;
    return *this;
}

Device::~Device()
{ }


std::ostream& operator<<(std::ostream& stream, const Device& item) {
    stream << " Device's manufacturer: "   << item.getManufacturer()   << '\n'
           << " Device's model: "          << item._modelName          << '\n'
           << " Number of ports: "         << item._portCount          << '\n'
           << " Dimensions:\n\t width  - " << item._modelSize.__width  << " mm"
           <<             "\n\t length - " << item._modelSize.__length << " mm"
           <<             "\n\t high   - " << item._modelSize.__high   << " mm"
           << " Price: "                   << item._price              << " ₽" << std::endl;
    return stream;
}

void Device::setManufacturer(const std::string& manufacturer)
{
    _manufacturer = manufacturer;
}

std::string Device::getManufacturer() const
{
    return _manufacturer;
}

void Device::setModelName(const std::string& modelName) {
    _modelName = modelName;
}

std::string Device::getModelName() const {
    return _modelName;
}

void Device::setPortCount(const int& portCount) {
    _portCount = portCount;
}

int Device::getPortCount() const {
    return _portCount;
}

void Device::setModelSize(const Device::Size& modelSize) {
    _modelSize = modelSize;
}

Device::Size Device::getModelSize() const {
    return _modelSize;
}

void Device::setPrice(const int& price) {
    _price = price;
}

int Device::getPrice() const {
    return _price;
}
