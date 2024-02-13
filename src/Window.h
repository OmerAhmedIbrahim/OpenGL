#ifndef SDDS_WINDOW_H
#define SDDS_WINDOW_H
#include "src.h"
namespace sdds{

    class Window {
        GLFWwindow *window{};
        const unsigned int m_screen_width{};
        const unsigned int m_screen_height{};
        const char* m_name{};
        static void framebuffer_size_callback(GLFWwindow* window, int width, int height){
            glViewport(0, 0, width, height);
        }
    public:
        explicit Window(const unsigned int &width, const unsigned int &height, const char* name):
                m_screen_width(width), m_screen_height(height), m_name(name){
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
                        //Apple compatibility
            #ifdef __APPLE__
                        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            #endif
            window = glfwCreateWindow(width, height, name, NULL, NULL);
            glfwMakeContextCurrent(window); // Set the windows to render
            glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

        }
        GLFWwindow* getWindow() {
            return window;
        }
        unsigned int getWidth() const{
            return m_screen_width;
        }
        unsigned int getHeight() const{
            return m_screen_height;
        }
        ~Window(){
            glfwTerminate();
        }

    };
};

#endif //SRC_WINDOW_H
