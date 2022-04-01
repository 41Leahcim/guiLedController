#include "serial.h"

// linux only
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

Serial::Serial(const std::string& device, const uint32_t baudRate){
    struct termios tty;
    openPort(device.c_str());
    retrieveSettings(&tty);
    setSettings(&tty, baudRate, 8);
    storeSettings(&tty);
}

Serial::Serial(const std::string& device, const uint32_t baudRate, const uint8_t charSize){
    struct termios tty;
    openPort(device.c_str());
    retrieveSettings(&tty);
    setSettings(&tty, baudRate, charSize);
    storeSettings(&tty);
}

void Serial::sendChar(const char c) const{
    const char string[] = {c, '\0'};
    write(port, string, sizeof(string));
}

void Serial::sendString(const std::string& string) const{
    write(port, string.c_str(), string.length());
}

char Serial::receiveChar() const{
    int64_t messageLength = 0;
    char buffer[2];
    while(messageLength == 0){
        messageLength = read(port, buffer, 1);
        if(messageLength < 0){
            throw "ERROR: Failed to receive char!";
        }
    }
    return buffer[0];
}

const std::string Serial::receiveString() const{
    int64_t messageLength = 0;
    char buffer[2048];
    while(messageLength == 0){
        messageLength = read(port, buffer, 2048);
        if(messageLength < 0){
            throw "ERROR: Failed to receive char!";
        }
    }
    return buffer;
}

Serial::~Serial(){
    close(port);
}

// port initialization functions
void Serial::openPort(const char *device){
    port = open(device, O_RDWR);
    if(port < 0){
        throw "ERROR: Failed to open device!";
    }
}

void Serial::retrieveSettings(struct termios *tty){
    if(tcgetattr(port, tty)){
        close(port);
        throw "ERROR: Failed to load attributes of port!";
    }
}

void Serial::setSettings(struct termios *tty, const uint32_t baudRate, const uint8_t charSize){
    tty->c_cflag = (tty->c_cflag & ~(PARENB | CSTOPB | CRTSCTS)) | CLOCAL | CREAD;
    switch(charSize){
        case 5:
            tty->c_cflag |= CS5;
            break;
        case 6:
            tty->c_cflag |= CS6;
            break;
        case 7:
            tty->c_cflag |= CS7;
            break;
        default:
            tty->c_cflag |= CS8;
            break;
    }
    tty->c_lflag &= ~(ICANON | ECHO | ECHOE | ECHONL);
    tty->c_iflag &= ~(IXON | IXOFF | IXANY | IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL);
    tty->c_oflag &= ~(OPOST | ONLCR);
    tty->c_cc[VTIME] = 0;
    tty->c_cc[VMIN] = 0;
    cfsetspeed(tty, baudRate);
}

void Serial::storeSettings(struct termios *tty){
    if(tcsetattr(port, TCSANOW, tty)){
        close(port);
        throw "ERROR: Failed to save settings!";
    }
}
