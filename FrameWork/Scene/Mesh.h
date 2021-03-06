﻿
#pragma once

#include <vector>

#include "BoundingBox.h"
#include "Config.h"
#include "Object.h"

namespace GameEngine
{
    struct MeshVertexAttrib
    {
        //attribute size
        unsigned int size;
        //GL_FLOAT
        unsigned int type;
        //VERTEX_ATTRIB_POSITION,VERTEX_ATTRIB_COLOR,VERTEX_ATTRIB_TEX_COORD,VERTEX_ATTRIB_NORMAL, VERTEX_ATTRIB_BLEND_WEIGHT, VERTEX_ATTRIB_BLEND_INDEX, GLProgram for detail
        int vertexAttrib;
        //size in bytes
        int attribSizeBytes;
    };

    class MeshData
    {
    public:
        std::vector<float> vertex;
        std::vector<int> indices;
        int vertexSizeInFloat;
        int numIndex;
        std::vector<MeshVertexAttrib> attribs;
        int attribCount;
        /*  渲染数据  */
        unsigned int VAO, VBO, EBO;

    public:
        //////////////////////////////
        //  * Get per vertex size
        //  * @return return the sum of each vertex's all attribute size.
        //////////////////////////////
        int getPerVertexSize() const
        {
            int vertexsize = 0;
            for (const auto& attrib : attribs)
            {
                vertexsize += attrib.attribSizeBytes;
            }
            return vertexsize;
        }
        //////////////////////////////
        //  * Reset the data
        ///////////////////////////////
        void ResetData()
        {
            vertex.clear();
            attribs.clear();
            vertexSizeInFloat = 0;
            numIndex = 0;
            attribCount = 0;
        }

        MeshData() : vertexSizeInFloat(0), numIndex(0), attribCount(0)
        {
            ResetData();
        }

        ~MeshData()
        {
            ResetData();
        }
    };

    class Mesh : public Object
    {
    public:
        //////////////////////////////////
        // * 渲染数据
        // * @param meshData 数据
        //////////////////////////////////
        void PushMeshData(MeshData& meshData)
        {
            m_MeshDatas.push_back(meshData);
        }

        void SetBoundingBox(BoundingBox oobb)
        {
            m_OOBB = oobb;
        }

    public:
        //////////////////////////////////
        // * 渲染数据
        //////////////////////////////////
        std::vector<MeshData> m_MeshDatas;
        BoundingBox m_OOBB;
        bool isPrepare = false;
    };

}  // namespace GameEngine