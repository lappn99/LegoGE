#include "ShaderProgram.h"
namespace LGE {
    int ShaderProgram::CompileShader(unsigned int type, const std::string& text)
    {
        unsigned int id = glCreateShader(type);
        const char* src = text.c_str();
        glShaderSource(id, 1, &src, nullptr);
        glCompileShader(id);

        int result;
        glGetShaderiv(id, GL_COMPILE_STATUS, &result);
        if (result == GL_FALSE) {
            int length;
            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
            char* message = (char*)_malloca(length * sizeof(char));
            glGetShaderInfoLog(id, length, &length, message);
            std::cout << message;

            return  LGE_SHADER_COMPILE_FAILED;

        }

        return id;
    }



    int ShaderProgram::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
    {
        unsigned int program = glCreateProgram();
        int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
        if (vs < 0) {
            std::cout << "Error compiling vertex shader: " << vs << std::endl;
            return vs;
        }
        int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
        if (fs < 0) {
            std::cout << "Error compiling fragment shader: " << fs << std::endl;
            return fs;
        }

        glAttachShader(program, vs);
        glAttachShader(program, fs);
        glLinkProgram(program);
        glValidateProgram(program);
        glDeleteShader(vs);
        glDeleteShader(fs);
        return program;
    }
    ShaderProgram::ShaderProgram(const std::string& path)
    {
        std::string shader = "";
        ReadFile(path, &shader);
        std::string line;
        std::stringstream stream(shader);
        std::stringstream ss[2];
        m_shaderProgram = LGE_SHADER_NOTCOMPILED;
        ShaderType shaderType = ShaderType::NONE;
        while (std::getline(stream, line)) {
            if (line.find("#shader") != std::string::npos)
            {
                if (line.find("vertex") != std::string::npos)
                {
                    shaderType = ShaderType::VERTEX;
                }
                else if (line.find("fragment") != std::string::npos)
                {
                    shaderType = ShaderType::FRAGMENT;
                }
            }
            else
            {
                ss[(int)shaderType] << line << "\n";
            }


        }
        this->m_fragmentSrc = ss[(int)ShaderType::FRAGMENT].str();
        this->m_vertexSrc = ss[(int)ShaderType::VERTEX].str();
    }

    LGE_RESULT ShaderProgram::Compile()
    {
        int result = CreateShader(this->m_vertexSrc, this->m_fragmentSrc);
        if (result < 0) {
            return result;
        }
        m_shaderProgram = result;

        return LGE_OK;
    }

}
