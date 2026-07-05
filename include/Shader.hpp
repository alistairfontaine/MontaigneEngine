#ifndef SHADER_HPP
#define SHADER_HPP
#include <GL/glew.h>
#include <string>

class Shader {
public:
    GLuint ID;
    Shader(const char* v, const char* f) {
        GLuint vs = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vs, 1, &v, NULL);
        glCompileShader(vs);

        GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fs, 1, &f, NULL);
        glCompileShader(fs);

        ID = glCreateProgram();
        glAttachShader(ID, vs);
        glAttachShader(ID, fs);
        glLinkProgram(ID);

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
};
#endif
