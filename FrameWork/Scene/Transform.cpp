﻿#include "Transform.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Utils/SerializableHelper.h"
#include "easylogging++.h"
namespace GameEngine
{
    Transform::Transform()
    {
        m_ClassID = ClassID(Transform);
        m_V3ParentPosition = VecterFloat3(0);
        m_Position = VecterFloat3(0, 0, 0);
        m_Scale = VecterFloat3(1, 1, 1);
        m_Rotation = VecterFloat3(0, 0, 0);
        m_Matrix = GlmMat4(1.0f);
        m_Front = VecterFloat3(0, 0, -1);
        SetMatrix(m_Position, m_Scale, m_Rotation);
    }

    void Transform::SetPosition(VecterFloat3 position)
    {
        m_Position = position;
        SetMatrix(m_Position, m_Scale, m_Rotation);
    }
    void Transform::SetScale(VecterFloat3 scale)
    {
        m_Scale = scale;
        SetMatrix(m_Position, m_Scale, m_Rotation);
    }
    void Transform::SetRotation(VecterFloat3 rotation)
    {
        m_Rotation = rotation;
        SetMatrix(m_Position, m_Scale, m_Rotation);
    }
    void Transform::SetMatrix(VecterFloat3 position, VecterFloat3 scale, VecterFloat3 rotation)
    {
        m_Matrix = GlmMat4(1.0f);
        MatrixCompose(m_Matrix, position, scale, rotation);
        m_InverseMatrix = glm::inverse(m_Matrix);

        m_Right = glm::normalize(m_Matrix * VecterFloat4(1, 0, 0, 0));
        m_Up = glm::normalize(m_Matrix * VecterFloat4(0, 1, 0, 0));
        m_Front = glm::normalize(m_Matrix * VecterFloat4(0, 0, -1, 0));
    }
    void Transform::SetParentPosition(VecterFloat3 pos)
    {
        m_V3ParentPosition = std::move(pos);
        SetMatrix(m_Position, m_Scale, m_Rotation);
    }
    void Transform::OnSerialize(cJSON *root)
    {
        SerializableHelper::Seserialize(root, "rotation", m_Rotation);
        SerializableHelper::Seserialize(root, "position", m_Position);
        SerializableHelper::Seserialize(root, "scale", m_Scale);
        Component::OnSerialize(root);
    }

    void Transform::OnDeserialize(cJSON *root)
    {
        SetRotation(SerializableHelper::DeserializeVecterFloat3(root, "rotation"));
        SetPosition(SerializableHelper::DeserializeVecterFloat3(root, "position"));
        SetScale(SerializableHelper::DeserializeVecterFloat3(root, "scale"));
        Component::OnDeserialize(root);
    }

}  // namespace GameEngine
