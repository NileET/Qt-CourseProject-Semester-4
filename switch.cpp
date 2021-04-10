#include "switch.hpp"
#include <iostream>

Switch::Switch() :
      Device()
    , _baseSpeed(std::make_pair(0, 0))
    , _hasPoE(false)
{ }

Switch::Switch(const std::string         manufacturer,
               const std::string         modelName,
               const std::pair<int, int> baseSpeed,
               const int                 portCount,
               const bool                hasPoE,
               const Switch::Size        modelSize,
               const int                 price) :
      Device(manufacturer, modelName, portCount, modelSize, price)
    , _baseSpeed(baseSpeed)
    , _hasPoE(hasPoE)
{ }

Switch::Switch(const Switch &rhs) :
      Device(rhs)
    , _baseSpeed(rhs._baseSpeed)
    , _hasPoE(rhs._hasPoE)
{ }

Switch &Switch::operator=(const Switch &rhs) {
    if (this == &rhs) return *this;

    Device::operator=(rhs);
    _baseSpeed = rhs._baseSpeed;
    _hasPoE = rhs._hasPoE;
    return *this;
}

Switch::~Switch()
{ }

std::ostream& operator<<(std::ostream& stream, const Switch& item) {
    stream << " Device's manufacturer: "    << item.getManufacturer()       << '\n'
           << " Device's model: "           << item.getModelName()          << '\n'
           << " Base baud rate: " << item._baseSpeed.first << " Mbps , " << item._baseSpeed.second << " Mbps \n"
           << " Number of ports: "          << item.getPortCount()          << '\n'
           << " PoE support: "    << std::boolalpha << item._hasPoE         << '\n'
           << " Dimensions:\n\t width  - "  << item.getModelSize().__width  << " mm"
           <<             "\n\t length - "  << item.getModelSize().__length << " mm"
           <<             "\n\t high   - "  << item.getModelSize().__high   << " mm"
           << " Price: "                    << item.getPrice()              << std::endl;
    return stream;
}

void Switch::setBaseSpeed(const std::pair<int, int>& baseSpeed) {
    _baseSpeed = baseSpeed;
}

std::pair<int, int> Switch::getBaseSpeed() const {
    return _baseSpeed;
}

void Switch::setHasPoE(const bool& hasPoE) {
    _hasPoE = hasPoE;
}

bool Switch::getHasPoE() const {
    return _hasPoE;
}
