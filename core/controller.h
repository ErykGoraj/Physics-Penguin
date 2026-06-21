#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <asio.hpp>
#include <iostream>
#include <string>
#include <future>
#include "camera.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Structs from kontroler.ino
struct JoystickData
{
    int16_t xVal;
    int16_t yVal;
    bool swVal;
};

struct SendData
{
    JoystickData left;
    JoystickData right;
    uint8_t irCode;
};


class Controller
{
public:
    asio::io_service io;
    std::unique_ptr<asio::serial_port> serial_port;

    Controller();
    ~Controller();
    void init();
    SendData getData();
    void movement(Camera &camera, GLFWwindow *window, float deltaTime);

private:
    SendData sendData;
    bool isConnected = false;
    unsigned int BAUD_RATE = 9600;
    std::string DEVICE_PORT = "/dev/ttyACM0";
    float SENSITIVITY = 1.5f;
    std::future<std::string> future_data;

    void configureSerialPort();
    std::string readLineFromSerialPort();
    void dataStrip(std::string data);
    std::string getElement(std::string &data);
};

#endif // CONTROLLER_H
