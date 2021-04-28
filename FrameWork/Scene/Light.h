#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <memory>

#include "Camera.h"
#include "Component.h"
#include "Config.h"
#include "Frustum.h"
#include "GameObject.h"
#include "MyMath.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Transform.h"

namespace GameEngine
{
    extern SceneManager* g_pSceneManager;
    enum LightType
    {
        Type_PointLight = 1,
        Type_AreaLight,
        Type_SpotLight,
        Type_DirectionalLight
    };
    class Light : public Component
    {
    public:
        virtual void Start() override
        {
            Component::Start();
            auto light = GetParent()->GetComponent<Light>();
            if (!light)
                return;
            auto scene = g_pSceneManager->GetScene();
            scene->AddLight(std::dynamic_pointer_cast<Light>(light));
        }

        virtual void Update() override
        {
            Component::Update();
        }
        virtual void Destory() override
        {
            Component::Destory();
        }

        Light()
        {
            m_Color = ColorRGBA(1, 1, 1, 1);
            m_ClassID = ClassID(Light);
        }

        virtual void OnSerialize(cJSON* root) override
        {
            SerializableHelper::Seserialize(root, "color", m_Color);
            Component::OnSerialize(root);
        }
        virtual void OnDeserialize(cJSON* root) override
        {
            m_Color = SerializableHelper::DeserializeVecterFloat4(root, "color");
            Component::OnDeserialize(root);
        }

        int GetLightType() { return m_LightType; }

        ColorRGBA GetColor() { return m_Color; }

        std::map<int, RendererCammand> FindCasters(std::map<int, RendererCammand> origins, Frustum frustum)
        {
        }

        // helper function for computing AABB in clip space
        inline BoundingBox CreateClipSpaceAABB(const BoundingBox& bb, const glm::mat4& mViewProj)
        {
            glm::vec3 vTransformed[8];
            for (int i = 0; i < 8; i++)
            {
                // transform to projection space
                glm::vec4 temp = mViewProj * glm::vec4(bb.m_pPoints[i], 1);
                // compute clip-space coordinates

                temp.x /= temp.w;
                temp.y /= temp.w;
                temp.z /= temp.w;
                vTransformed[i] = temp;
            }

            // find boundaries in light�s clip space
            return BoundingBox(vTransformed, 8, sizeof(glm::vec3));
        }

        glm::mat4 CalculateCropMatrix(const Frustum& frustum)
        {
            glm::mat4 m_mView = GetParent()->GetComponent<Transform>()->GetViewMatrix();
            glm::mat4 m_mProj = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);

            //获得VP
            glm::mat4 mViewProj = m_mProj * m_mView;
            BoundingBox cropBB;
            //将AABB顶点转到裁剪空间,并获得新的包围盒
            cropBB = CreateClipSpaceAABB(frustum.m_AABB, mViewProj);

            // 构建投影矩阵的变化矩阵 返回新的VP
            return BuildCropMatrix(cropBB.m_vMin, cropBB.m_vMax) * m_mProj * m_mView;
        }

        //////////////////////////////////////////////////////////////
        //构建变换矩阵
        /////////////////////////////////////////////////////////////
        glm::mat4 BuildCropMatrix(const glm::vec3& vMin, const glm::vec3& vMax)
        {
            float fScaleX, fScaleY, fScaleZ;
            float fOffsetX, fOffsetY, fOffsetZ;

            fScaleX = 2.0f / (vMax.x - vMin.x);
            fScaleY = 2.0f / (vMax.y - vMin.y);

            fOffsetX = -0.5f * (vMax.x + vMin.x) * fScaleX;
            fOffsetY = -0.5f * (vMax.y + vMin.y) * fScaleY;

            fScaleZ = 1.0f / (vMax.z - vMin.z);
            fOffsetZ = -vMin.z * fScaleZ;

            glm::mat4 m(1);
            m[0][0] = fScaleX;
            m[1][1] = fScaleY;
            m[2][2] = fScaleZ;

            m[3][0] = fOffsetX;
            m[3][1] = fOffsetY;
            m[3][2] = fOffsetZ;

            return m;
        }

    protected:
        /////////////////////////////////
        //光颜色
        /////////////////////////////////
        ColorRGBA m_Color;
        /////////////////////////////////
        // 光类型
        /////////////////////////////////
        LightType m_LightType;
    };

    class AreaLight : public Light
    {
    public:
        virtual void OnSerialize(cJSON* root) override
        {
            Light::OnSerialize(root);
        }
        virtual void OnDeserialize(cJSON* root) override
        {
            Light::OnDeserialize(root);
        }
        AreaLight()
        {
            m_ClassID = ClassID(AreaLight);
            m_LightType = LightType::Type_AreaLight;
        }
    };
    /////////////////////////////////
    //方向光
    /////////////////////////////////
    class DirectionalLight : public Light
    {
    public:
        DirectionalLight()
        {
            m_ClassID = ClassID(DirectionalLight);
            m_LightType = LightType::Type_DirectionalLight;
        }
        virtual void OnSerialize(cJSON* root) override
        {
            SerializableHelper::Seserialize(root, "Ambient", m_Ambient);
            SerializableHelper::Seserialize(root, "Diffuse", m_Diffuse);
            SerializableHelper::Seserialize(root, "Specular", m_Specular);
            Light::OnSerialize(root);
        }
        virtual void OnDeserialize(cJSON* root) override
        {
            Light::OnDeserialize(root);
            m_Ambient = SerializableHelper::DeserializeVecterFloat3(root, "Ambient");
            m_Diffuse = SerializableHelper::DeserializeVecterFloat3(root, "Diffuse");
            m_Specular = SerializableHelper::DeserializeVecterFloat3(root, "Specular");
        }

        VecterFloat3 GetAmbient() { return m_Ambient; }
        VecterFloat3 GetDiffuse() { return m_Diffuse; }
        VecterFloat3 GetSpecular() { return m_Specular; }

        /////////////////////////////////
        //环境(Ambient)
        /////////////////////////////////
        VecterFloat3 m_Ambient;

        /////////////////////////////////
        //漫反射(Diffuse)
        /////////////////////////////////
        VecterFloat3 m_Diffuse;

        /////////////////////////////////
        //镜面(Specular)光照
        /////////////////////////////////
        VecterFloat3 m_Specular;
    };

    /////////////////////////////////
    //点光源  Fatt=1.0/(Kc+Kl∗d+Kq∗d^2)
    /////////////////////////////////
    class PointLight : public DirectionalLight
    {
    public:
        virtual void OnSerialize(cJSON* root) override
        {
            SerializableHelper::Seserialize(root, "constant", constant);
            SerializableHelper::Seserialize(root, "linear", linear);
            SerializableHelper::Seserialize(root, "quadratic", quadratic);
            DirectionalLight::OnSerialize(root);
        }
        virtual void OnDeserialize(cJSON* root) override
        {
            constant = SerializableHelper::DeserializeFloat(root, "constant");
            linear = SerializableHelper::DeserializeFloat(root, "linear");
            quadratic = SerializableHelper::DeserializeFloat(root, "quadratic");
            DirectionalLight::OnDeserialize(root);
        }
        PointLight()
        {
            m_ClassID = ClassID(PointLight);
            m_LightType = LightType::Type_PointLight;
        }

        float GetConstant() { return constant; }
        float GetLinear() { return linear; }
        float GetQuadratic() { return quadratic; }

    private:
        /////////////////////////////////
        // Kc 常数项
        /////////////////////////////////
        float constant;

        /////////////////////////////////
        // d 一次方项
        /////////////////////////////////
        float linear;

        /////////////////////////////////
        // d^2 二次方项
        /////////////////////////////////
        float quadratic;
    };
    /////////////////////////////////
    // 聚光灯
    /////////////////////////////////
    class SpotLight : public PointLight
    {
    public:
        virtual void OnSerialize(cJSON* root) override
        {
            SerializableHelper::Seserialize(root, "cutOff", cutOff);
            SerializableHelper::Seserialize(root, "outerCutOff", outerCutOff);
            PointLight::OnSerialize(root);
        }
        virtual void OnDeserialize(cJSON* root) override
        {
            cutOff = SerializableHelper::DeserializeFloat(root, "cutOff");
            outerCutOff = SerializableHelper::DeserializeFloat(root, "outerCutOff");
            PointLight::OnDeserialize(root);
        }
        SpotLight()
        {
            m_ClassID = ClassID(SpotLight);
            m_LightType = LightType::Type_SpotLight;
        }

        float GetCutOff() { return cutOff; }
        float GetOuterCutOff() { return outerCutOff; }

    private:
        /////////////////////////////////
        //内圆锥
        /////////////////////////////////
        float cutOff;
        /////////////////////////////////
        // 外圆锥
        /////////////////////////////////
        float outerCutOff;
    };

}  // namespace GameEngine