#include <iostream>
#include <ctime>
#include <array>
#define GLEW_STATIC
#include <GL\glew.h>
#include <GLFW\glfw3.h>

bool const FULLSCREEN = false;
bool const ENABLE_VSYNC = false;

class Vector3 {
    std::array<double, 3> e;
public:
    //Vector3(double x = 0, double y = 0, double z = 0) : e[0] = x, e[1](b), e[2](c) { }
    Vector3(double x = 0, double y = 0, double z = 0) {
        e[0] = x;
        e[1] = y;
        e[2] = z;
    }

    double& operator[](int i) { return e[i]; }
    double  operator[](int i) const { return e[i]; }

    double X() { return e[0]; }
    void X(double x_) { e[0] = x_; }

    double Y() { return e[1]; }
    void Y(double y_) { e[1] = y_; }

    double Z() { return e[2]; }
    void Z(double z_) { e[2] = z_; }

    static int const size;
    /* repeat for -, * and / -- same pattern */
    Vector3& operator += (Vector3 const& b) {
        e[0] += b[0]; e[1] += b[1]; e[2] += b[2];
        return *this;
    }

    Vector3& operator *= (double b) {
        e[0] *= b; e[1] *= b; e[2] *= b;
        return *this;
    }
};

Vector3 const operator + (Vector3 const& a, Vector3 const& b) {
    return Vector3(a) += b;
}

Vector3 const operator * (Vector3 const& a, double b) {
    return Vector3(a) += b;
}

template<typename T>
float sum(T a) {
    float s = 0;
    for (int i = 0; i < a.size; ++i) s += a[i];
    return s;
}

template<typename T>
float dot(T a, T b) {
    return sum(a * b);
}

template<typename T>
float length(T a) {
    return sqrt(dot(a, a));
}

Vector3 Update(double timestep, Vector3 position, Vector3 velocity = Vector3(), Vector3 acceleration = Vector3()) {
    auto newPos = position + velocity * timestep;
    return newPos;
}

// Buffer to average fps count
//class CircularBuffer

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main() {
    
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window;

    // Make the window
    if (FULLSCREEN) {
        window = glfwCreateWindow(2560, 1440, "LearnOpenGL", glfwGetPrimaryMonitor(), nullptr);
    }
    else {
        window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
    }
    if (window == nullptr)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);

    glViewport(0, 0, width, height);

    glfwSetKeyCallback(window, key_callback);

    if (ENABLE_VSYNC) {
        glfwSwapInterval(1);
    }
    else {
        glfwSwapInterval(0);
    }

    bool alternator = true;
    int fpsCounter = 0;
    clock_t clockLastRefresh = clock();
    int FPS_AVERAGE = 100;



    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        
        clock_t clocks = clock();

        if (fpsCounter == FPS_AVERAGE-1) {

            double elapsedSeconds = double(clocks - clockLastRefresh) / double(CLOCKS_PER_SEC);
            std::cout << 1.0 / elapsedSeconds << " fps" << std::endl;
            alternator = !alternator;
            fpsCounter = 0;
        }

        fpsCounter++;
        clockLastRefresh = clocks;

        if (alternator) {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }
        else {
            glClearColor(0.0f, 0.3f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);
        }

        glfwSwapBuffers(window);
    }

    glfwTerminate();

    return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, 
    // closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);

    // Change colour of background
    /*if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        glfwSetW
    }*/
}