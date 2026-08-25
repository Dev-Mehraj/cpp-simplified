//
// Created by Dev-Mehraj on 8/12/2026.
// @Copyright Dev-Mehraj CPPEASY_H 2026-2027
// This OPENSOURCE library is for those  developers who have habit of
// OG english code writing syntax and are having problems with famlilirazing with Cpp syntax!
// AIM IS TO MAKE CPP SYNTAX AS CLOSE TO READABLE AS POSSIBLE
// ALSO WITHOUT USING TEMPLATES!!! AVIOD TEMPLATES AND HIGH LEVEL ADVANCED PROGRAMMING!
// IMPORTANT: Use class after declaring every class so in the main.cpp or any other cpp file, the user doesnt have to declare the class again
//

#ifndef CPPEASY_CPPEASY_H
#define CPPEASY_CPPEASY_H
#define GLEW_STATIC
#include <iostream>
#include <string>

#include <algorithm>
#include <array>
#include <fstream>
#include <vector>
using namespace std;
#define function auto
#define null nullptr
#define let auto
#define finish return 0;

#define structure struct
#define OR ||
#define AND &&
#define NOT !
#define EQUAL_TO ==
#define NOT_EQUAL_TO !=
#define SUB -
#define MUL *
#define DIV /
#define repeat(n) for (int repeat_i_ = 0; repeat_i_ < (n); repeat_i_++)
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define RESET   "\033[0m"
namespace jsk {

    class Console {
    public:

        auto log(auto... args) {
            ((cout<<args <<" "), ...);
        }
        auto nlog(auto... args) {
            ((cout <<endl <<args <<" "), ...);
        }
        auto prompt(auto& input, string messageTheyWantTodisplay) {
            cout <<messageTheyWantTodisplay << endl;
            cin >> input;
            return input;
        }
        auto error(auto... args) {
            ((cerr <<args <<" "), ...);
        }
        auto warn(auto... args) {
            ((cout  <<YELLOW <<"WARNING: " <<args <<" " <<endl <<RESET), ...);
        }
        auto log_table(auto& rowArray, auto& columnArray, string rowLabel = "ROW", string columnLabel = "COLUMN") {
            int rows = rowArray.size();
            int cols = columnArray.size();
            int maxRows = rows > cols ? rows : cols;

            cout << rowLabel << "\t\t" << columnLabel << endl;
            cout << "---------------------------" << endl;

            for (int i = 0; i < maxRows; i++) {
                if (i < rows) {
                    cout << rowArray[i];
                } else {
                    cout << "-";
                }
                cout << "\t\t";
                if (i < cols) {
                    cout << columnArray[i];
                } else {
                    cout << "-";
                }
                cout << endl;
            }
        }
    };
    inline Console console;
class Array {
public:
    void arrayCopierforINT(int array[], int toCopyToArray[], int size) {

        for (int i = 0; i <size; i++) {
            toCopyToArray[i] = array[i];
        }
    }
    void arrayCopierforSTRING(string array[], string toCopyToArray[], int size) {

        for (int i = 0; i <size; i++) {
            toCopyToArray[i] = array[i];
        }
    }
    void arrayCopierforCHAR(char array[], char toCopyToArray[], int size) {

        for (int i = 0; i <size; i++) {
            toCopyToArray[i] = array[i];
        }
    }
    void arrayCopierforDOUBLE(double array[], double toCopyToArray[], int size) {

        for (int i = 0; i <size; i++) {
            toCopyToArray[i] = array[i];
        }
    }
    void arrayCopierforSIZE_T(size_t array[], size_t toCopyToArray[], int size) {

        for (int i = 0; i <size; i++) {
            toCopyToArray[i] = array[i];
        }
    }
    void arrayCopierforSHORT(short array[], short toCopyToArray[], int size) {

        for (int i = 0; i <size; i++) {
            toCopyToArray[i] = array[i];
        }
    }
    void arrayCopierforLONG(long array[], long toCopyToArray[], int size) {

        for (int i = 0; i <size; i++) {
            toCopyToArray[i] = array[i];
        }
    }
    void arrayCopierforLONG_LONG(long long array[], long long toCopyToArray[], int size) {

        for (int i = 0; i <size; i++) {
            toCopyToArray[i] = array[i];
        }
    }
    void arrayCopierforBOOLEAN(bool array[], bool toCopyToArray[], int size) {

        for (int i = 0; i <size; i++) {
            toCopyToArray[i] = array[i];
        }
    }
};
inline Array arrayReworked;
    template<typename T>
class List {
    public:
        vector<T> data;

        List() {}
        List(initializer_list<T> values) : data(values) {}

        void push(T value) { data.push_back(value); }
        void pop() { if (!data.empty()) data.pop_back(); }
        int size() { return (int)data.size(); }

        bool includes(T value) {
            for (int i = 0; i < (int)data.size(); i++) {
                if (data[i] EQUAL_TO value) return true;
            }
            return false;
        }
        int indexOf(T value) {
            for (int i = 0; i < (int)data.size(); i++) {
                if (data[i] EQUAL_TO value) return i;
            }
            return -1;
        }
        void remove(T value) {
            for (int i = 0; i < (int)data.size(); i++) {
                if (data[i] EQUAL_TO value) {
                    data.erase(data.begin() + i);
                    return;
                }
            }
        }
        void clear() { data.clear(); }

        void print() {
            cout << "[";
            for (int i = 0; i < (int)data.size(); i++) {
                cout << data[i];
                if (i < (int)data.size() - 1) cout << ", ";
            }
            cout << "]" << endl;
        }

        T& operator[](int i) { return data[i]; }
    };

    using IntArray      = List<int>;
    using StringArray   = List<string>;
    using CharArray     = List<char>;
    using DoubleArray   = List<double>;
    using SizeTArray    = List<size_t>;
    using ShortArray    = List<short>;
    using LongArray     = List<long>;
    using LongLongArray = List<long long>;
    using BooleanArray  = List<bool>;
    using Size_tArray = List<size_t>;

    class FileReader {
    public:
        ifstream file;

        FileReader(string path) {
            file.open(path);
        }

        bool exists() {
            return file.is_open();
        }

        string readAll() {
            string content, line;
            while (getline(file, line)) {
                content += line + "\n";
            }
            return content;
        }

        StringArray readLines() {
            StringArray lines;
            string line;
            while (getline(file, line)) {
                lines.push(line);
            }
            return lines;
        }

        void close() {
            file.close();
        }
    };


    class FileWriter {
    public:
        ofstream file;

        FileWriter(string path, bool append = false) {
            if (append) {
                file.open(path, ios::app);
            } else {
                file.open(path);
            }
        }

        bool exists() {
            return file.is_open();
        }

        auto write(auto value) {
            file << value;
        }

        auto writeLine(auto value) {
            file << value << endl;
        }

        void close() {
            file.close();
        }
    };
    class STRING {
    public:
        string reverseString(const string& input) {
            string reversedString = input;
            reverse(reversedString.begin(), reversedString.end());
            return reversedString;
        }

        bool isPalindrome(const string& input) {
            return input EQUAL_TO reverseString(input);
        }

        string palindromeMessage(const string& input) {
            if (isPalindrome(input)) {
                return "The word/statement '" + input + "', is a palindrome!";
            } else {
                return "The word/statement '" + input + "', is NOT a palindrome!";
            }
        }
        CharArray convertStringToCharArray(const string& input) {
            CharArray result;
            for (int i = 0; i < (int)input.size(); i++) {
                result.push(input[i]);
            }
            return result;
        }
    };
     inline STRING strings;
    class Window {
    public:
        GLFWwindow* handle;

        Window(int width, int height, string title) {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            handle = glfwCreateWindow(width, height, title.c_str(), null, null);
            glfwMakeContextCurrent(handle);

            glfwSwapInterval(1); // Enforces VSync (prevents 100% CPU/GPU usage)

            glewExperimental = true;
            glewInit();
        }

        bool isOpen() {
            return !glfwWindowShouldClose(handle);
        }

        void clear(float r = 0.1f, float g = 0.1f, float b = 0.1f) {
            glClearColor(r, g, b, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void update() {
            glfwSwapBuffers(handle);
            glfwPollEvents();
        }

        void close() {
            glfwDestroyWindow(handle);
            glfwTerminate();
        }
    };class Camera {
    public:
        glm::vec3 position;
        glm::vec3 front;
        glm::vec3 up;
        glm::vec3 right;
        glm::vec3 worldUp;

        float yaw;
        float pitch;
        float moveSpeed;
        float mouseSensitivity;

        bool firstMouse;
        float lastX, lastY;

        Camera(float posX = 0.0f, float posY = 2.0f, float posZ = 8.0f) {
            position = glm::vec3(posX, posY, posZ);
            worldUp = glm::vec3(0.0f, 1.0f, 0.0f);
            front = glm::vec3(0.0f, 0.0f, -1.0f);

            yaw = -90.0f;
            pitch = 0.0f;
            moveSpeed = 6.0f;
            mouseSensitivity = 0.1f;

            firstMouse = true;
            lastX = 400.0f;
            lastY = 300.0f;

            updateCameraVectors();
        }

        void moveTo(float x, float y, float z) {
            position = glm::vec3(x, y, z);
        }

        void lookAt(float x, float y, float z) {
            front = glm::normalize(glm::vec3(x, y, z) - position);
            pitch = glm::degrees(asin(front.y));
            yaw = glm::degrees(atan2(front.z, front.x));
            updateCameraVectors();
        }

        void setSpeed(float speed) {
            moveSpeed = speed;
        }

        void setSensitivity(float sensitivity) {
            mouseSensitivity = sensitivity;
        }

        // Handles WASD, Space (Up), and Left-Shift (Down) movement
        void processKeyboard(GLFWwindow* window, float deltaTime) {
            float velocity = moveSpeed * deltaTime;

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
                position += front * velocity;
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
                position -= front * velocity;
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
                position -= right * velocity;
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
                position += right * velocity;
            if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
                position += worldUp * velocity;
            if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
                position -= worldUp * velocity;
        }

        // Rotates camera based on mouse movement coordinates
        void processMouse(float xpos, float ypos, bool constrainPitch = true) {
            if (firstMouse) {
                lastX = xpos;
                lastY = ypos;
                firstMouse = false;
            }

            float xoffset = (xpos - lastX) * mouseSensitivity;
            float yoffset = (lastY - ypos) * mouseSensitivity;

            lastX = xpos;
            lastY = ypos;

            yaw += xoffset;
            pitch += yoffset;

            if (constrainPitch) {
                if (pitch > 89.0f) pitch = 89.0f;
                if (pitch < -89.0f) pitch = -89.0f;
            }

            updateCameraVectors();
        }

        glm::mat4 viewMatrix() {
            return glm::lookAt(position, position + front, up);
        }

    private:
        void updateCameraVectors() {
            glm::vec3 newFront;
            newFront.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            newFront.y = sin(glm::radians(pitch));
            newFront.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            front = glm::normalize(newFront);

            right = glm::normalize(glm::cross(front, worldUp));
            up = glm::normalize(glm::cross(right, front));
        }
    };





#endif //CPPEASY_CPPEASY_H
