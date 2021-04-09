#include "switch.hpp"
#include <iostream>

Switch::Switch() : Device()
{
    _baseSpeed = std::make_pair(0, 0);
}

Switch::Switch(const std::string         modelName,
               const std::pair<int, int> baseSpeed,
               const int                 portCount,
               const Switch::Size        modelSize) :
      Device(modelName, portCount, modelSize)
    , _baseSpeed(baseSpeed)
{ }

Switch::Switch(const Switch &rhs) :
      Device(rhs)
    , _baseSpeed(rhs._baseSpeed)
{ }

Switch &Switch::operator=(const Switch &rhs) {
    if (this == &rhs) return *this;

    Device::operator=(rhs);
    _baseSpeed = rhs._baseSpeed;
    return *this;
}

Switch::~Switch()
{ }

std::ostream& operator<<(std::ostream& stream, const Switch& item) {
    stream << " Device's model: "           << item.getModelName()          << '\n'
           << " Base baud rate: " << item._baseSpeed.first << " Mbps , " << item._baseSpeed.second << " Mbps \n"
           << " Number of ports: "          << item.getPortCount()          << '\n'
           << " Dimensions:\n\t width  - "  << item.getModelSize().__width  << " mm"
           <<             "\n\t length - "  << item.getModelSize().__length << " mm"
           <<             "\n\t high   - "  << item.getModelSize().__high   << " mm" << std::endl;
    return stream;
}

void Switch::setBaseSpeed(const std::pair<int, int>& baseSpeed) {
    _baseSpeed = baseSpeed;
}

std::pair<int, int> Switch::getBaseSpeed() const {
    return _baseSpeed;
}
