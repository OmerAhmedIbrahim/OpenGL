#ifndef SHADER_H
#define SHADER_H
#include "src.h"
namespace sdds {

    class ShaderBinary {
        unsigned int binary;
        explicit ShaderBinary(int m): binary(m){}
    public:
        ShaderBinary(ShaderBinary &&sb) noexcept:binary(sb.binary){}
        static ShaderBinary create(const char* filepath, GLenum shaderType){
            std::ifstream file;
            std::stringstream ss;
            file.open(filepath);
            ss << file.rdbuf();
            file.close();  
            std::string str = ss.str();
            const char * src = str.c_str();
#ifdef DEBUG
            std::cout << "Filepath: " << filepath << std::endl;
            std::cout << "Shader: " << src << std::endl;
#endif
            unsigned int shader = glCreateShader(shaderType);
            glShaderSource(shader, 1, &src, NULL);
            glCompileShader(shader);
            checkCompileError(shader);
            return  ShaderBinary(shader);
        }
        static void checkCompileError(unsigned int &s){
            int pass = 1;
            char errorLog[1024];
            glGetShaderiv(s,  GL_COMPILE_STATUS, &pass);
            if (!pass) {
                glGetShaderInfoLog(s,  1024, NULL, errorLog);
                std::cerr << "Shader Module compilation error:\n" << errorLog << std::endl;
            } 
        }
        ~ShaderBinary() {
            glDeleteShader(binary);
        }
        ShaderBinary(const ShaderBinary &sb) = delete;
        unsigned int getBinary() {
            return binary;
        }
    };

    class Shader {
        unsigned int program;
        explicit Shader(unsigned int m): program(m){}
    public:
        Shader(Shader &&s) noexcept:program(s.program){}
        static Shader create(const char* filepathV, const char* filepathF) {
            ShaderBinary vShader = ShaderBinary::create(filepathV, GL_VERTEX_SHADER);
            ShaderBinary fShader = ShaderBinary::create(filepathF, GL_FRAGMENT_SHADER);

            unsigned int shaderProgram = glCreateProgram();
            glAttachShader(shaderProgram, vShader.getBinary());
            glAttachShader(shaderProgram, fShader.getBinary());
            glLinkProgram(shaderProgram);
            checkProgramError(shaderProgram);
                      
            return  Shader(shaderProgram);
            
        }
        void use() {
            glUseProgram(program);
        }
        static void checkProgramError(unsigned int &s){
            int pass = 1;
            char errorLog[1024];
            glGetProgramiv(s, GL_LINK_STATUS, &pass);
            if (!pass) {
                glGetProgramInfoLog(s, 1024, NULL, errorLog);
                std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << errorLog << std::endl;
            }
        }
        unsigned int getID() {
            return program;
        }
        ~Shader() {
            glDeleteProgram(program);
        }
    };

}

#endif //SHADER_H
