#ifndef SWITCH_HPP
#define SWITCH_HPP
#include "device.hpp"


class Switch : public Device {
public:
    Switch();

    Switch(const std::string         manafacturer,
           const std::string         modelName,
           const std::pair<int, int> baseSpeed,
           const int                 portCount,
           const bool                hasPoE,
           const Size                modelSize,
           const int                 price);

    Switch(const Switch& rhs);

    Switch& operator=(const Switch& rhs);

    ~Switch();

    friend std::ostream& operator<<(std::ostream& stream, const Switch& item);

    void setBaseSpeed(const std::pair<int, int>& hasPoE);
    std::pair<int, int> getBaseSpeed() const;

    void setHasPoE(const bool& baseSpeed);
    bool getHasPoE() const;

private:
    std::pair<int, int> _baseSpeed;
    bool _hasPoE;
};


#endif //SWITCH_HPP
