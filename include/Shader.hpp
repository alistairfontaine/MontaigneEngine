#ifndef SHADER_HPP
#define SHADER_HPP
#include <GL/glew.h>
#include <string>

class Shader {
public:
    GLuint ID;
    Shader(const char* vSource, const char* fSource) {
        GLuint vShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vShader, 1, &vSource, NULL);
        glCompileShader(vShader);
        GLuint fShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fShader, 1, &fSource, NULL);
        glCompileShader(fShader);
        ID = glCreateProgram();
        glAttachShader(ID, vShader);
        glAttachShader(ID, fShader);
        glLinkProgram(ID);
    }
    void use() { glUseProgram(ID); }
    void setMat4(const std::string &name, const float* matrix) const {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, matrix);
    }
    void setInt(const std::string &name, int value) const {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
};
#endif
