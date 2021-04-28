#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Component.h"
#include "Config.h"
#include "Frustum.h"
#include "ISerializable.h"
#include "Renderer.h"
#include "Transform.h"

namespace GameEngine
{
    class Camera : public Component
    {
        enum CameraType
        {
            Perspective = 0, //透视投影
            Orthographic = 1 //正交投影
        };

    public:
        Camera(glm::float32 width, glm::float32 height, glm::float32 m_Near = 0.1,
               glm::float32 m_Far = 20, glm::float32 fieldofView = 45, ClassIDType classID = ClassID(Camera));
        Camera(glm::float32 m_Near = 0.1, glm::float32 m_Far = 20,
               glm::float32 fieldofView = 45, ClassIDType classID = ClassID(Camera));

        glm::mat4 GetProjectionMatrix();
        void SetProjectionMatrix(glm::mat4 temp);

        virtual void Start();

        glm::mat4 GetProjectionMatrixOrthographic();

        //给定近远平面,构建视椎体
        Frustum CalculateFrustum(float fNear, float fFar);
        void CalculateSplitPositions(float *pDistances, int numSplits);

        virtual void OnSerialize(cJSON *root);
        virtual void OnDeserialize(cJSON *root);

        int GetSplitNum() { return i_SplitNums; }
        glm::float32 GetFieldofView() { return m_FieldofView; }
        glm::float32 GetWidth() { return m_ScreenWidth; }
        glm::float32 GetHeigth() { return m_ScreenHeight; }
        glm::float32 GetNear() { return m_Near; }
        glm::float32 GetFar() { return m_Far; }

    private:
        //			y
        //			|
        //			|
        //			|
        //			----------->x
        //		   /
        //		  /
        //		 /
        //		z

        glm::float32 m_Near;         //近摄像机平面距离
        glm::float32 m_Far;          //远摄像机平面距离
        glm::float32 m_FieldofView;  //摄像机夹角
        glm::float32 m_ScreenWidth;  //屏幕宽度
        glm::float32 m_ScreenHeight; //屏幕高度
        int i_SplitNums = 4;         //分割次数

        glm::mat4 m_ProjectionMatrix4_Perspective;
        glm::mat4 m_ProjectionMatrix4_Orthographic;
    };
} // namespace GameEngine