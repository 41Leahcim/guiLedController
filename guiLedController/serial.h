#ifndef SERIAL_H
#define SERIAL_H

#include <string>

class Serial{
public:
    Serial(const std::string&, const uint32_t);
    Serial(const std::string&, const uint32_t, const uint8_t);
    void sendChar(const char) const;
    void sendString(const std::string&) const;
    char receiveChar() const;
    const std::string receiveString() const;
    ~Serial();
private:
    void openPort(const char*);
    void retrieveSettings(struct termios *tty);
    void setSettings(struct termios*, const uint32_t, const uint8_t);
    void storeSettings(struct termios*);

    int port;
};

#endif // SERIAL_H
