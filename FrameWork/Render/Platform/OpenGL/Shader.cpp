#include "Shader.h"

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "easylogging++.h"


namespace GameEngine
{
    Shader::~Shader()
    {
        if (m_CompileID <= 0)
            return;
        GLsizei length;
        glGetShaderiv(m_CompileID, GL_SHADER_SOURCE_LENGTH, &length);
        GLchar *src = (GLchar *)malloc(sizeof(GLchar) * length);
        glGetShaderSource(m_CompileID, length, nullptr, src);
        free(src);
    }

    bool Shader::CompileSourceCode(const char *source)
    {
        el::Loggers::getLogger("logger")->info(source);
        const char *COCOS2D_VERTEX_SHADER_UNIFORMS =
            "";
        GLint status;
        GLenum shaderType = GL_VERTEX_SHADER;
        const GLchar *sources[] = {COCOS2D_VERTEX_SHADER_UNIFORMS, source};
        if (m_ShaerType == ShaderType::Vertex)
        {
            shaderType = GL_VERTEX_SHADER;
        }
        else if (m_ShaerType == ShaderType::Fragment)
        {
            shaderType = GL_FRAGMENT_SHADER;
        }
        else if (m_ShaerType == ShaderType::Geometry)
        {
            shaderType = GL_GEOMETRY_SHADER;
        }
        m_CompileID = glCreateShader(shaderType);

        glShaderSource(m_CompileID, sizeof(sources) / sizeof(*sources), sources,
                       nullptr);

        glCompileShader(m_CompileID);

        glGetShaderiv(m_CompileID, GL_COMPILE_STATUS, &status);

        if (!status)
        {
            GLsizei length;
            glGetShaderiv(m_CompileID, GL_SHADER_SOURCE_LENGTH, &length);
            GLchar *src = (GLchar *)malloc(sizeof(GLchar) * length);

            glGetShaderSource(m_CompileID, length, nullptr, src);
            free(src);

            return false;
        }
        return (status == GL_TRUE);
    }

    ShaderProgram::ShaderProgram() { RemoveAllShaders(); }

    bool ShaderProgram::AddShaderFromSourceCode(ShaderType type,
                                                const char *source)
    {
        Shader *shader = new Shader(type);
        bool flag = shader->CompileSourceCode(source);
        m_Shaders.push_back(shader);
        return flag;
    }
    bool ShaderProgram::AddShaderFromFilePath(ShaderType type,
                                              const char *path)
    {
        return true;
    }

    bool ShaderProgram::Link()
    {
        m_ProgramID = glCreateProgram();
        for (unsigned int i = 0; i < m_Shaders.size(); i++)
        {
            glAttachShader(m_ProgramID, m_Shaders[i]->m_CompileID);
        }
        BindPredefinedVertexAttribs();
        glLinkProgram(m_ProgramID);

        GLint attrMaxLength = 0;
        GLint attrCount = 0;
        glGetProgramiv(m_ProgramID, GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &attrMaxLength);
        glGetProgramiv(m_ProgramID, GL_ACTIVE_ATTRIBUTES, &attrCount);

        GLchar glName[256];
        GLsizei glLength;
        GLsizei glSize;
        GLenum glType;

        // gpuShader->glInputs.resize(attrCount);
        for (GLint i = 0; i < attrCount; ++i)
        {
            // GLES3GPUInput &gpuInput = gpuShader->glInputs[i];

            memset(glName, 0, sizeof(glName));
            glGetActiveAttrib(m_ProgramID, i, attrMaxLength, &glLength, &glSize, &glType, glName);
            char *offset = strchr(glName, '[');
            if (offset)
            {
                glName[offset - glName] = '\0';
            }

            // GL_CHECK(gpuInput.glLoc = glGetAttribLocation(gpuShader->glProgram, glName));
            // gpuInput.binding = gpuInput.glLoc;
            // gpuInput.name = glName;
            // gpuInput.type = MapType(glType);
            // gpuInput.stride = GLTypeSize(glType);
            // gpuInput.count = glSize;
            // gpuInput.size = gpuInput.stride * gpuInput.count;
            // gpuInput.glType = glType;
        }

        return true;
    }

    bool ShaderProgram::Use()
    {
        glUseProgram(m_ProgramID);
        return true;
    }

    void ShaderProgram::BindPredefinedVertexAttribs()
    {
        static const struct
        {
            const char *attributeName;
            int location;
        } attribute_locations[] = {
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
            glBindAttribLocation(m_ProgramID, attribute_locations[i].location,
                                 attribute_locations[i].attributeName);
        }
    }

    // utility uniform functions
    // ------------------------------------------------------------------------
    void ShaderProgram::setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), (int)value);
    }
    // ------------------------------------------------------------------------
    void ShaderProgram::setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(m_ProgramID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void ShaderProgram::setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(m_ProgramID, name.c_str()), value);
    }
    // ------------------------------------------------------------------------
    void ShaderProgram::setVec2(const std::string &name,
                                const glm::vec2 &value) const
    {
        glUniform2fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);
    }
    void ShaderProgram::setVec2(const std::string &name, float x, float y) const
    {
        glUniform2f(glGetUniformLocation(m_ProgramID, name.c_str()), x, y);
    }
    // ------------------------------------------------------------------------
    void ShaderProgram::setVec3(const std::string &name,
                                const glm::vec3 &value) const
    {
        glUniform3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);
    }
    void ShaderProgram::setVec3(const std::string &name, float x, float y,
                                float z) const
    {
        glUniform3f(glGetUniformLocation(m_ProgramID, name.c_str()), x, y, z);
    }
    // ------------------------------------------------------------------------
    void ShaderProgram::setVec4(const std::string &name,
                                const glm::vec4 &value) const
    {
        glUniform4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1, &value[0]);
    }
    void ShaderProgram::setVec4(const std::string &name, float x, float y, float z,
                                float w) const
    {
        glUniform4f(glGetUniformLocation(m_ProgramID, name.c_str()), x, y, z, w);
    }
    // ------------------------------------------------------------------------
    void ShaderProgram::setMat2(const std::string &name,
                                const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1,
                           GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void ShaderProgram::setMat3(const std::string &name,
                                const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1,
                           GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void ShaderProgram::setMat4(const std::string &name,
                                const float *value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1,
                           GL_FALSE, value);
    }

    void ShaderProgram::setMat4(const std::string &name,
                                const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1,
                           GL_FALSE, &mat[0][0]);
    }

    void ShaderProgram::SetVoid(const std::string &name,
                                const void *value) const
    {
        glUniformMatrix4fv(glGetUniformLocation(m_ProgramID, name.c_str()), 1,
                           GL_FALSE, (float *)value);
    }

} // namespace GameEngine