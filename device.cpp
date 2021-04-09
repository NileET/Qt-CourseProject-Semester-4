#include "device.hpp"
#include <iostream>

Device::Device() : Device("Unknown",
                          0,
                          {0, 0, 0})
{ }

Device::Device(const std::string   modelName,
               const int           portCount,
               const Device::Size  modelSize) :
      _modelName(modelName)
    , _portCount(portCount)
    , _modelSize(modelSize)
{ }

Device::Device(const Device& rhs) :
      _modelName(rhs._modelName)
    , _portCount(rhs._portCount)
    , _modelSize(rhs._modelSize)
{ }

Device &Device::operator=(const Device& rhs) {
    if (this == &rhs) return *this;

    _modelName = rhs._modelName;
    _portCount = rhs._portCount;
    _modelSize = rhs._modelSize;
    return *this;
}

Device::~Device()
{ }

std::ostream& operator<<(std::ostream& stream, const Device& item) {
    stream << " Device's model: "          << item._modelName          << '\n'
           << " Number of ports: "         << item._portCount          << '\n'
           << " Dimensions:\n\t width  - " << item._modelSize.__width  << " mm"
           <<             "\n\t length - " << item._modelSize.__length << " mm"
           <<             "\n\t high   - " << item._modelSize.__high   << " mm" << std::endl;
    return stream;
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
