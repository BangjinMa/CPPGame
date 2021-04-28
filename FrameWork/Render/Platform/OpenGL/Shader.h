#pragma once

#include <vector>

#include "Config.h"
#include "Object.h"
#include "ShaderBase.h"
#include "glm/glm.hpp"

namespace GameEngine
{
    class Shader : public ShaderBase
    {
    public:
        Shader(ShaderType type) : ShaderBase(type) {}
        ~Shader() override;
        virtual bool CompileSourceCode(const char *source) override;
    };

    class ShaderProgram : public ShaderProgramBase
    {
    public:
        ShaderProgram();

        virtual bool AddShaderFromSourceCode(ShaderType type, const char *source) override;
        virtual bool AddShaderFromFilePath(ShaderType type, const char *path) override;

        virtual bool Link() override;

        virtual bool Use() override;

        // utility uniform functions
        // ------------------------------------------------------------------------
        virtual void setBool(const std::string &name, bool value) const override;
        // ------------------------------------------------------------------------
        virtual void setInt(const std::string &name, int value) const override;
        // ------------------------------------------------------------------------
        virtual void setFloat(const std::string &name, float value) const override;
        // ------------------------------------------------------------------------
        virtual void setVec2(const std::string &name, const glm::vec2 &value) const override;
        virtual void setVec2(const std::string &name, float x, float y) const override;
        // ------------------------------------------------------------------------
        virtual void setVec3(const std::string &name, const glm::vec3 &value) const override;
        virtual void setVec3(const std::string &name, float x, float y, float z) const override;
        // ------------------------------------------------------------------------
        virtual void setVec4(const std::string &name, const glm::vec4 &value) const override;
        virtual void setVec4(const std::string &name, float x, float y, float z, float w) const override;
        // ------------------------------------------------------------------------
        virtual void setMat2(const std::string &name, const glm::mat2 &mat) const override;
        // ------------------------------------------------------------------------
        virtual void setMat3(const std::string &name, const glm::mat3 &mat) const override;
        // ------------------------------------------------------------------------
        virtual void setMat4(const std::string &name, const float *value) const override;
        virtual void setMat4(const std::string &name, const glm::mat4 &mat) const override;

        virtual void SetVoid(const std::string &name, const void *value) const override;
        
        void BindPredefinedVertexAttribs();
    };

} // namespace GameEngine