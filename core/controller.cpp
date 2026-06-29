#include "controller.h"

Controller::Controller()
{
}

Controller::~Controller()
{
    // Close the serial port
    serial_port->close();
}

void Controller::init()
{
    serial_port = std::make_unique<asio::serial_port>(io);

    try
    {
        configureSerialPort();
        // Async data read on begin of program
        future_data = std::async(std::launch::async, &Controller::readLineFromSerialPort, this);
        isConnected = true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error configuring serial port: " << e.what() << std::endl;
    }
}

void Controller::configureSerialPort()
{
    // Setup serial port and baud rate
    serial_port->open(DEVICE_PORT);
    serial_port->set_option(asio::serial_port_base::baud_rate(BAUD_RATE));
}

SendData Controller::getData()
{
    // If data is avaliable and future data status is ready
    if (future_data.valid() && future_data.wait_for(std::chrono::seconds(0)) == std::future_status::ready)
    {
        std::string response = future_data.get();
        // Async data read (only one line at every loop)
        future_data = std::async(std::launch::async, &Controller::readLineFromSerialPort, this);
        dataStrip(response);
    }
    return sendData;
}

void Controller::movement(Camera &camera, GLFWwindow *window, float deltaTime)
{
    if (isConnected) {
        int joystick_x = sendData.right.xVal;
        int joystick_y = sendData.right.yVal;

        float xoffset = 0.0f;
        float yoffset = 0.0f;

        if (joystick_x <= 400.0f )
        {
            xoffset = static_cast<float>(joystick_x - 512) * SENSITIVITY;
        } else if (joystick_x >= 800) {
            xoffset = static_cast<float>(joystick_x - 512) * SENSITIVITY;
        }

        if (joystick_y >= 800)
        {
            yoffset = static_cast<float>(joystick_y - 512) * SENSITIVITY;
        } else if (joystick_y <= 400) {
            yoffset = static_cast<float>(joystick_y - 512) * SENSITIVITY;
        }

        xoffset *= deltaTime;
        yoffset *= deltaTime;
        camera.processMouseMovement(-xoffset, -yoffset);

        if (sendData.left.xVal >= 800)
            camera.processKeyboard(LEFT, deltaTime);
        if (sendData.left.xVal <= 400)
            camera.processKeyboard(RIGHT, deltaTime);
        if (sendData.left.yVal >= 800)
            camera.processKeyboard(BACKWARD, deltaTime);
        if (sendData.left.yVal <= 400)
            camera.processKeyboard(FORWARD, deltaTime);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.processKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.processKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.processKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.processKeyboard(RIGHT, deltaTime);
}

std::string Controller::readLineFromSerialPort()
{
    asio::streambuf input_buffer; // Bucket of data
    asio::error_code ec;
    asio::read_until(*serial_port, input_buffer, '\n', ec); // Read until new line achive

    if (ec)
    {
        std::cerr << "Error reading from serial port: " << ec.message() << std::endl;
        return "";
    }
    std::string line;
    std::istream is(&input_buffer); // Stream reading from buffer
    std::getline(is, line); // We get a line of data and write to line
    return line;
}

void Controller::dataStrip(std::string data)
{
    if (data.substr(0,2) == "$S")
    {
        data.erase(0,3);
        sendData.irCode = std::stoi(getElement(data));
        sendData.left.swVal = std::stoi(getElement(data));
        sendData.left.xVal = std::stoi(getElement(data));
        sendData.left.yVal = std::stoi(getElement(data));
        sendData.right.swVal = std::stoi(getElement(data));
        sendData.right.xVal = std::stoi(getElement(data));
        sendData.right.yVal = std::stoi(getElement(data));

        if (data.substr(0, 2) != "$E") // End
        {
            std::cerr << "Broken data frame!";
        }
    }
    else
    {
        std::cout << "Failed buffer!" << std::endl;
    }
}

std::string Controller::getElement(std::string &data)
{
    std::string result;
    while (!data.empty() && data[0] != ',')
    {
        result += data[0];
        data.erase(0,1);
    }
    if (!data.empty()) data.erase(0,1);
    return result;
}
