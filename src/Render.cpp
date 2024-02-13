#include "Shader.h"
#include "Rectangle.h"
#include "Algebra.h"

bool moved = false;
bool rotated = false;
bool scaled = false;
enum box {Red = 0, Blue = 1, Green = 2, Yellow = 3};
sdds::Rectangle boxes[4];
int selectBox = -1;
//Screen Dimensions Variables
const unsigned int screen_width = 1024;
const unsigned int screen_height = 768;
float deltaFrame = 0.0;
float firstFrame = 0.0;
unsigned int count = 1;
unsigned int fps = 0;
auto transformBox = sdds::mat4(1.0f);

//cam
sdds::vec3 cam_pos = {-5.0f, 0.0f, 3.0f};
sdds::vec3 cam_target = {0.0f, 0.0f, 0.0f};
sdds::vec3 cam_f = normalize((cam_target - cam_pos));
sdds::vec3 cam_r = normalize(cam_f.cross({0.0f, 0.0f, 1.0f}));
sdds::vec3 cam_u = normalize(cam_r.cross(cam_f));

//basic functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void render();
void closeWindow(GLFWwindow* window);
void init(sdds::Shader &shader);
void reset(GLFWwindow* window);
void move(GLFWwindow* window);
void size(GLFWwindow* window);
void turn(GLFWwindow* window);
void translate(sdds::Shader &shader);
void scale(sdds::Shader &shader);
void rotate(sdds::Shader &shader);
void processInput(GLFWwindow *window);

int main(int argc, char * argv[]){

    sdds::Window window = sdds::Window(screen_width, screen_height, "Simple Window With Colour Square");
    if (window.getWindow() == NULL) {
        fprintf(stderr, "Failed to open GLFW window\n");
        return -1;
    }
    // Load all OpenGL function pointers and check if GLAD works�
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    sdds::Shader shader = sdds::Shader::create("Vertex.txt", "Fragment.txt");

    boxes[Blue] = sdds::Rectangle(window, screen_height/4, screen_height/4, 'B');
    boxes[Yellow] = sdds::Rectangle(window, screen_height/4, screen_height/4, 'Y');
    boxes[Green] = sdds::Rectangle(window, screen_height/4, screen_height/4, 'G');
    boxes[Red] = sdds::Rectangle(window, screen_height/4, screen_height/4, 'R');


    for (int i = 0; i < 4; ++i) {
       boxes[i].mesh();
    }

    auto view = sdds::createLookAt(cam_pos, cam_target);
    auto loc_view = glGetUniformLocation(shader.getID(), "view");
    auto proj = //sdds::mat4(1.0f);
            sdds::createPerspectiveProjection((float)screen_width/(float)screen_height, 45.0f, 0.1f, 10.0f);
    auto loc_proj = glGetUniformLocation(shader.getID(), "projection");

    while(!glfwWindowShouldClose(window.getWindow())){
        float currentFrame = (float)glfwGetTime();
        deltaFrame = currentFrame - firstFrame;
        firstFrame = currentFrame;

        processInput(window.getWindow());

        size(window.getWindow());
        move(window.getWindow());
        turn(window.getWindow());
        reset(window.getWindow());

        render();
        shader.use();

        view = sdds::createLookAt(cam_pos, cam_target);
        init(shader);
        scale(shader);
        rotate(shader);
        translate(shader);

        glUniformMatrix4fv(loc_proj,1, GL_FALSE, proj.columns);
        glUniformMatrix4fv(loc_view,1, GL_FALSE, view.columns);

        if(selectBox > -1) boxes[selectBox].draw();

        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
        closeWindow(window.getWindow());
    }
    return 0;
}
//close the Window with esc
void closeWindow(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS || glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
    }
}
//render 
void render(){
    static const float colour[] = { 0.5f, 0.0f, 0.5f, 0.0f };
    glClearBufferfv(GL_COLOR, 0, colour);
    glClear(GL_COLOR_BUFFER_BIT);
}
void init(sdds::Shader &shader){
    auto loc_model = glGetUniformLocation(shader.getID(), "model");

    transformBox = sdds::translate({0.5f, -0.5f, 0.0f});
    glUniformMatrix4fv(loc_model,1, GL_FALSE, transformBox.columns);
    if(selectBox != Green)  boxes[Green].draw();

    transformBox = sdds::translate({-0.5f, -0.5f, 0.0f});
    glUniformMatrix4fv(loc_model,1, GL_FALSE, transformBox.columns);
    if(selectBox != Yellow )  boxes[Yellow].draw();

    transformBox = sdds::translate({-0.5f, 0.5f, 0.0f});
    glUniformMatrix4fv(loc_model,1, GL_FALSE, transformBox.columns);
    if(selectBox != Red )  boxes[Red].draw();

    transformBox = sdds::translate({0.5f, 0.5f, 0.0f});
    glUniformMatrix4fv(loc_model,1, GL_FALSE, transformBox.columns);
    if(selectBox != Blue )  boxes[Blue].draw();
}
void reset(GLFWwindow* window){
    if(glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS ) {
        selectBox = -1;
        moved = scaled = rotated = false;
    }
}
void move(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS && rotated) {
        moved = true;
    }
}
void turn(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS && !rotated) {
        selectBox = std::rand() / ((RAND_MAX + 1u) / 4);
        rotated = true;
    }
}
void size(GLFWwindow* window) {
     if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS && rotated){
         scaled = true;
     }
}
void translate(sdds::Shader &shader){
    auto loc_model = glGetUniformLocation(shader.getID(), "model");
    if(moved){
        transformBox = sdds::translate(transformBox, {0.0f, 0.0f, 0.0f});
        glUniformMatrix4fv(loc_model,1, GL_FALSE, transformBox.columns);
    } else {
        switch (selectBox) {
            case Green: transformBox = sdds::translate(transformBox,{0.5f, -0.5f, 0.0f}); break;
            case Yellow: transformBox = sdds::translate(transformBox,{-0.5f, -0.5f, 0.0f}); break;
            case Red: transformBox = sdds::translate(transformBox,{-0.5f, 0.5f, 0.0f}); break;
            case Blue: transformBox = sdds::translate(transformBox,{0.5f, 0.5f, 0.0f}); break;
            default:  break;
        }
        glUniformMatrix4fv(loc_model,1, GL_FALSE, transformBox.columns);
    }
}
void scale(sdds::Shader &shader){
    if(scaled){
        auto loc_model = glGetUniformLocation(shader.getID(), "model");
        transformBox = sdds::scale(transformBox,2.0f);
        glUniformMatrix4fv(loc_model,1, GL_FALSE, transformBox.columns);
    }
}
void rotate(sdds::Shader &shader){
    if(rotated){
        auto loc_model = glGetUniformLocation(shader.getID(), "model");
        transformBox = sdds::rotor3(45.0f, sdds::vec3(0.0f, 0.0f, -1.0f)).rotate();
        glUniformMatrix4fv(loc_model,1, GL_FALSE, transformBox.columns);
    }
}
void processInput(GLFWwindow *window){

    const float cameraSpeed = 5.05f * deltaFrame; // adjust accordingly
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cam_pos += (cam_f * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cam_pos -= (cam_f * cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cam_pos -= sdds::normalize(cam_f.cross(cam_u)).scale(cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cam_pos += sdds::normalize(cam_f.cross(cam_u)).scale(cameraSpeed);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        cam_target.y += 3.0f * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        cam_target.y -= 3.0f * cameraSpeed;    
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cam_target.x += cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cam_target.x -= cameraSpeed;
}
        /*fps++;
        if( ((float)fps)/(deltaFrame * 10000000 * 4) > 1){
            count++; fps = 0;
        }*/
