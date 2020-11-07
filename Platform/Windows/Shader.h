﻿#pragma once

#include <cstdint>
#include <string>

#include "glad/glad.h"

#include "Config.h"
#include "MyMath.h"
#include "ShaderData.h"
#include "glm/glm.hpp"

GameEngineBegin

struct Pass
{
    std::string vs;
    std::string fs;
};

class Shader
{
public:
    const char *COCOS2D_SHADER_UNIFORMS =
        "#version 330 core\n"
        "uniform mat4 CC_PMatrix;\n"
        "uniform mat4 CC_MultiViewPMatrix[4];\n"
        "uniform mat4 CC_MVMatrix;\n"
        "uniform mat4 CC_MVPMatrix;\n"
        "uniform mat4 CC_MultiViewMVPMatrix[4];\n"
        "uniform mat3 CC_NormalMatrix;\n"
        "uniform vec4 CC_Time;\n"
        "uniform vec4 CC_SinTime;\n"
        "uniform vec4 CC_CosTime;\n"
        "uniform vec4 CC_Random01;\n"
        "uniform sampler2D CC_Texture0;\n"
        "uniform sampler2D CC_Texture1;\n"
        "uniform sampler2D CC_Texture2;\n"
        "uniform sampler2D CC_Texture3;\n"
        "//CC INCLUDES END\n\n";
    unsigned int ID = 0;

    Shader() {}

    ~Shader()
    {
    }
    // constructor generates the shader on the fly
    // ------------------------------------------------------------------------
    Shader(std::string vertexCode, std::string fragmentCode, std::string geometryCode = "")
    {
        // 2. compile shaders
        unsigned int vertex, fragment;

        if (vertexCode.size()>0)
        {
            if (!compileShader(&vertex, GL_VERTEX_SHADER, vertexCode.c_str()))
            {
                checkCompileErrors(vertex, "VERTEX");
                return;
            }
        }

        if (fragmentCode.size()>0)
        {
            if (!compileShader(&fragment, GL_FRAGMENT_SHADER, fragmentCode.c_str()))
            {
                checkCompileErrors(fragment, "FRAGMENT");
                return;
            }
        }

        unsigned int geometry;
        if (geometryCode.size() > 0)
        {
            if (!compileShader(&geometry, GL_FRAGMENT_SHADER, geometryCode.c_str()))
            {
                checkCompileErrors(geometry, "GEOMETRY");
                return;
            }
        }
        // shader Program
        ID = glCreateProgram();
        glAttachShader(ID, vertex);
        glAttachShader(ID, fragment);
        if (geometryCode.size() > 0)
            glAttachShader(ID, geometry);
        bindPredefinedVertexAttribs();
        glLinkProgram(ID);
        checkCompileErrors(ID, "PROGRAM");
        // delete the shaders as they're linked into our program now and no longer necessery
        glDeleteShader(vertex);
        glDeleteShader(fragment);
        if (geometryCode.size() > 0)
            glDeleteShader(geometry);
    }

    void bindPredefinedVertexAttribs()
    {
        static const struct
        {
            const char *attributeName;
            int location;
        } attribute_locations[] =
            {
                {"a_position", MeshValueType::VERTEX_ATTRIB_POSITION},
                {"a_color", MeshValueType::VERTEX_ATTRIB_COLOR},
                {"a_texCoord", MeshValueType::VERTEX_ATTRIB_TEX_COORD},
                {"a_texCoord1", MeshValueType::VERTEX_ATTRIB_TEX_COORD1},
                {"a_texCoord2", MeshValueType::VERTEX_ATTRIB_TEX_COORD2},
                {"a_texCoord3", MeshValueType::VERTEX_ATTRIB_TEX_COORD3},
                {"a_normal", MeshValueType::VERTEX_ATTRIB_NORMAL},
            };

        const int size = sizeof(attribute_locations) / sizeof(attribute_locations[0]);

        for (int i = 0; i < size; i++)
        {
            glBindAttribLocation(ID, attribute_locations[i].location, attribute_locations[i].attributeName);
        }
    }

    // activate the shader
    // ------------------------------------------------------------------------

    bool compileShader(GLuint *shader, GLenum type, const GLchar *source)
    {
        GLint status;

        if (!source)
        {
            return false;
        }

        const GLchar *sources[] = {
            COCOS2D_SHADER_UNIFORMS,
            source};

        *shader = glCreateShader(type);
        glShaderSource(*shader, sizeof(sources) / sizeof(*sources), sources, nullptr);
        glCompileShader(*shader);

        glGetShaderiv(*shader, GL_COMPILE_STATUS, &status);

        if (!status)
        {
            GLsizei length;
            glGetShaderiv(*shader, GL_SHADER_SOURCE_LENGTH, &length);
            GLchar *src = (GLchar *)malloc(sizeof(GLchar) * length);

            glGetShaderSource(*shader, length, nullptr, src);
            free(src);

            return false;
        }
        return (status == GL_TRUE);
    }

    void use()
    {
        glUseProgram(ID);
    }
    // utility uniform functions
    // ------------------------------------------------------------------------
    void setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    {
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
    }
    void setVec4(const std::string &name, float x, float y, float z, float w)
    {
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const float *value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, value);
    }

private:
    // utility function for checking shader compilation/linking errors.
    // ------------------------------------------------------------------------
    void checkCompileErrors(GLuint shader, std::string type)
    {
        GLint success;
        GLchar infoLog[1024];
        if (type != "PROGRAM")
        {
            glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
            if (!success)
            {
                glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            }
        }
        else
        {
            glGetProgramiv(shader, GL_LINK_STATUS, &success);
            if (!success)
            {
                glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            }
        }
        if (!success)
            printf(infoLog);
    }
};

GameEngineEnd