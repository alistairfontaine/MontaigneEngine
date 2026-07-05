#ifndef MONTAIGNE_SHADER_HPP
#define MONTAIGNE_SHADER_HPP

#include <GL/glew.h>
#include <string>
#include <iostream>

class Shader {
public:
    GLuint ID;
    Shader(const char* v, const char* f) {
        GLint success;
        GLchar infoLog[512];

        // Vertex Shader Compilation
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &v, NULL);
        glCompileShader(vs);
        glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(vs, 512, NULL, infoLog);
            std::cerr << "[Shader Error] Vertex compilation failed:\n" << infoLog << "\n";
        }

        // Fragment Shader Compilation
        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &f, NULL);
        glCompileShader(fs);
        glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(fs, 512, NULL, infoLog);
            std::cerr << "[Shader Error] Fragment compilation failed:\n" << infoLog << "\n";
        }

        // Program Linking
        ID = glCreateProgram();
        glAttachShader(ID, vs);
        glAttachShader(ID, fs);
        glLinkProgram(ID);
        glGetProgramiv(ID, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(ID, 512, NULL, infoLog);
            std::cerr << "[Shader Error] Program linking failed:\n" << infoLog << "\n";
        }

        glDeleteShader(vs);
        glDeleteShader(fs);
    }

    void use() { glUseProgram(ID); }

    void setMat4(const std::string& name, const float* val) {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, val);
    }
    void setInt(const std::string& name, int val) {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), val);
    }
    void setVec3(const std::string& name, float x, float y, float z) {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
};

#endif
