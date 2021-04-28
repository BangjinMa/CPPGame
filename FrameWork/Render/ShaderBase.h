#pragma once

#include <vector>

#include "Config.h"
#include "Object.h"
#include "glm/glm.hpp"

namespace GameEngine
{
    class ShaderBase : public Object
    {
    public:
        ShaderBase(ShaderType type) : m_ShaerType(type) {}

        ~ShaderBase()
        {
            if (m_SourceCode)
                delete m_SourceCode;
        }

        ShaderType GetShaderType() const { return m_ShaerType; }

        virtual bool CompileSourceCode(const char *source) { return true; }

        char *m_SourceCode;
        ShaderType m_ShaerType;
        int m_CompileID;
    };

    class ShaderProgramBase : public Object
    {
    public:
        ShaderProgramBase() {}

        virtual bool AddShaderFromSourceCode(ShaderType type,
                                             const char *source)
        {
            return true;
        }
        virtual bool AddShaderFromFilePath(ShaderType type,
                                           const char *path)
        {
            return true;
        }

        virtual bool Link() { return true; }

        virtual bool Use() { return true; }

        // utility uniform functions
        // ------------------------------------------------------------------------
        virtual void setBool(const std::string &name, bool value) const {}
        // ------------------------------------------------------------------------
        virtual void setInt(const std::string &name, int value) const {}
        // ------------------------------------------------------------------------
        virtual void setFloat(const std::string &name, float value) const {}
        // ------------------------------------------------------------------------
        virtual void setVec2(const std::string &name,
                             const glm::vec2 &value) const {}
        virtual void setVec2(const std::string &name, float x, float y) const {}
        // ------------------------------------------------------------------------
        virtual void setVec3(const std::string &name,
                             const glm::vec3 &value) const {}
        virtual void setVec3(const std::string &name, float x, float y,
                             float z) const {}
        // ------------------------------------------------------------------------
        virtual void setVec4(const std::string &name,
                             const glm::vec4 &value) const {}
        virtual void setVec4(const std::string &name, float x, float y, float z,
                             float w) const {}
        // ------------------------------------------------------------------------
        virtual void setMat2(const std::string &name, const glm::mat2 &mat) const {}
        // ------------------------------------------------------------------------
        virtual void setMat3(const std::string &name, const glm::mat3 &mat) const {}
        // ------------------------------------------------------------------------
        virtual void setMat4(const std::string &name, const float *value) const {}
        virtual void setMat4(const std::string &name, const glm::mat4 &mat) const {}

        virtual void SetVoid(const std::string &name, const void *value) const {}

        virtual bool IsLinked() const { return true; }
        void RemoveAllShaders()
        {
            for (size_t i = 0; i < m_Shaders.size(); i++)
            {
                delete m_Shaders[i];
            }
            m_Shaders.clear();
        }

        int ProgramId() const { return m_ProgramID; }

        std::vector<ShaderBase *> m_Shaders;

        int m_ProgramID;
    };

} // namespace GameEngine