#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include "Transform.h"
#include "Projector.h"
#include <sstream>
#include <string>
#define LGE_OK 1
#define LGE_EXIT -1
#define LGE_INIT_FAILED -2
#define LGE_SHADER_COMPILE_FAILED -3
#define LGE_IO_ERROR -4
#define LGE_SHADER_NOTCOMPILED -5
#define LGE_NULL_VERTEX -7

#define LGE_2DVERTEX_SIZE 4



namespace LGE {
	typedef int LGE_RESULT;

	

	struct LGEColor {
		float r;
		float g;
		float b;
		float a;
		LGEColor() {
			r = 1.0f;
			g = 1.0f;
			b = 1.0f;
			a = 1.0f;
		}
		LGEColor(float _r, float _g, float _b, float _a) : r(_r),b(_b),g(_g),a(_a) {

		}

	};

    struct Vector2
    {
        float x;
        float y;
        
        

        Vector2() {
            x = 0;
            y = 0;
        }

        Vector2(float _x, float _y) : x(_x),y(_y)
        {
            
        }

        static Vector2 zero()
        {
            return Vector2(0, 0);

        }

        static Vector2 one()
        {
            return Vector2(1, 1);
        }

    };
    

#define RED LGEColor(1.0f,0.0f,0.0f,1.0f)
#define WHITE LGEColor(1.0f,1.0f,1.0f,1.0f)

	struct Vertex {
		
		float x;
		float y;
		float z;
        float w;

		Vertex(float _x, float _y, float _z, float _w) : x(_x), y(_y), z(_z),w(_w) {

		}
		Vertex(){}

	};

	inline LGE_RESULT ReadFile(const std::string& path, std::string* out) {
		std::ifstream in(path);
		
		if (!in) {
			return LGE_IO_ERROR;
		}
		else {
			
			std::stringstream buf("");
			buf << in.rdbuf();
			std::string text(buf.str());
			*out = text;
			return LGE_OK;
		}


	}

    enum DebugMessageStrictness
    {
        LOW,
        MEDIUM,
        HIGH

    };

	inline void APIENTRY OpenGLDebugMessage(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* param)
	{

        std::string _source;
        std::string _type;
        std::string _severity;
        int strictness = (int)param;
        

        switch (source) {
        case GL_DEBUG_SOURCE_API:
            _source = "API";
            break;

        case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
            _source = "WINDOW SYSTEM";
            break;

        case GL_DEBUG_SOURCE_SHADER_COMPILER:
            _source = "SHADER COMPILER";
            break;

        case GL_DEBUG_SOURCE_THIRD_PARTY:
            _source = "THIRD PARTY";
            break;

        case GL_DEBUG_SOURCE_APPLICATION:
            _source = "APPLICATION";
            break;

        case GL_DEBUG_SOURCE_OTHER:
            _source = "UNKNOWN";
            break;

        default:
            _source = "UNKNOWN";
            break;
        }

        switch (type) {
        case GL_DEBUG_TYPE_ERROR:
            _type = "ERROR";
            break;

        case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
            _type = "DEPRECATED BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
            _type = "UDEFINED BEHAVIOR";
            break;

        case GL_DEBUG_TYPE_PORTABILITY:
            _type = "PORTABILITY";
            break;

        case GL_DEBUG_TYPE_PERFORMANCE:
            _type = "PERFORMANCE";
            break;

        case GL_DEBUG_TYPE_OTHER:
            _type = "OTHER";
            break;

        case GL_DEBUG_TYPE_MARKER:
            _type = "MARKER";
            break;

        default:
            _type = "UNKNOWN";
            break;
        }

        switch (severity) {
        case GL_DEBUG_SEVERITY_HIGH:
            _severity = "HIGH";
            break;

        case GL_DEBUG_SEVERITY_MEDIUM:
            _severity = "MEDIUM";
            break;

        case GL_DEBUG_SEVERITY_LOW:
            _severity = "LOW";
            break;

        case GL_DEBUG_SEVERITY_NOTIFICATION:
            _severity = "NOTIFICATION";
            break;

        default:
            _severity = "UNKNOWN";
            break;
        }

        if (strictness == (int)DebugMessageStrictness::LOW)
        {
            if (severity <= GL_DEBUG_SEVERITY_HIGH && severity != GL_DEBUG_SEVERITY_NOTIFICATION)
            {
                std::cout << "[" << _severity << "] " << _type << ": " << message << std::endl;

            }

        }
        else if (strictness == (int)DebugMessageStrictness::MEDIUM)
        {
            if (severity <= GL_DEBUG_SEVERITY_LOW && severity != GL_DEBUG_SEVERITY_NOTIFICATION)
            {
                std::cout << "[" << _severity << "] " << _type << ": " << message << std::endl;
            }
        }

        else
        {
            std::cout << "[" << _severity << "] " << _type << ": " << message << std::endl;
        }


        

        

	}
}




