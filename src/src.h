#ifndef SRC_H
#define SRC_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iterator>
#include <algorithm>
#include <functional>


// auto errorCheck = [](unsigned int &s, bool linker){   
//         int pass = 1;
//         char errorLog[1024];
//         if(linker){
//             glGetProgramiv(s, GL_LINK_STATUS, &pass);
//             if (!pass) {
//                 glGetProgramInfoLog(s, 1024, NULL, errorLog);
//                 std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << errorLog << std::endl;
//             }
//         }else{
//             glGetShaderiv(s,  GL_COMPILE_STATUS, &pass);
//             if (!pass) {
//                 glGetShaderInfoLog(s,  1024, NULL, errorLog);
//                 std::cerr << "Shader Module compilation error:\n" << errorLog << std::endl;
//             } 
//         }
// };

#endif //SRC_H
