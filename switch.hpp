#ifndef SWITCH_HPP
#define SWITCH_HPP
#include "device.hpp"


class Switch : public Device{
public:
    Switch();

    Switch(const std::string         modelName,
           const std::pair<int, int> baseSpeed,
           const int                 portCount,
           const Size                modelSize);

    Switch(const Switch& rhs);

    Switch& operator=(const Switch& rhs);

    ~Switch();

    friend std::ostream& operator<<(std::ostream& stream, const Switch& item);

    void setBaseSpeed(const std::pair<int, int>& baseSpeed);
    std::pair<int, int> getBaseSpeed() const;

private:
    std::pair<int, int> _baseSpeed;
};


#endif //SWITCH_HPP
