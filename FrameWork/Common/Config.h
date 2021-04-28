#pragma once

#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <vector>

#include "MyMath.h"
namespace GameEngine
{
#define MAX_LIGHT_COUNT 100

    class Object;
    class GameObject;
    class ShaderProgramBase;
    class Mesh;
    class Texture;
    class GameObject;
    class ShaderProgramBase;
    class Mesh;
    class Texture;
    class Widget;
    class Renderer;
    class Scene;
    class Cube;

#define SharePtr std::shared_ptr
#define SharedObject SharePtr<Object>
#define SharedGameObject SharePtr<GameObject>
#define SharedMesh SharePtr<Mesh>
#define SharedTexture SharePtr<Texture>
#define SharedShaderProgramBase SharePtr<ShaderProgramBase>
#define SharedScene SharePtr<Scene>
#define SharedComponent SharePtr<Component>
#define SharedCube SharePtr<Cube>
#define SharedCamera SharePtr<Camera>

    enum MeshValueType
    {
        /**Index 0 will be used as Position.*/
        VERTEX_ATTRIB_POSITION,
        /**Index 1 will be used as Color.*/
        VERTEX_ATTRIB_COLOR,
        /**Index 2 will be used as Tex coord unit 0.*/
        VERTEX_ATTRIB_TEX_COORD,
        /**Index 3 will be used as Tex coord unit 1.*/
        VERTEX_ATTRIB_TEX_COORD1,
        /**Index 4 will be used as Tex coord unit 2.*/
        VERTEX_ATTRIB_TEX_COORD2,
        /**Index 5 will be used as Tex coord unit 3.*/
        VERTEX_ATTRIB_TEX_COORD3,
        /**Index 6 will be used as Normal.*/
        VERTEX_ATTRIB_NORMAL,
        /**Index 7 will be used as Blend weight for hardware skin.*/
        VERTEX_ATTRIB_BLEND_WEIGHT,
        /**Index 8 will be used as Blend index.*/
        VERTEX_ATTRIB_BLEND_INDEX,
        /**Index 9 will be used as tangent.*/
        VERTEX_ATTRIB_TANGENT,
        /**Index 10 will be used as Binormal.*/
        VERTEX_ATTRIB_BINORMAL,
        VERTEX_ATTRIB_MAX,

        // backward compatibility
        VERTEX_ATTRIB_TEX_COORDS = VERTEX_ATTRIB_TEX_COORD,
    };

    /////////////////////////////////
    // 摄像机信息
    /////////////////////////////////
    volatile struct ViewInfos
    {
        /////////////////////////////////
        // 摄像机坐标
        /////////////////////////////////
        float u_camera_pos[4];
        /////////////////////////////////
        // 摄像机投影矩阵
        /////////////////////////////////
        float u_projection_matrix[16];
        /////////////////////////////////
        // 摄像机观察矩阵
        /////////////////////////////////
        float u_view_matrix[16];
    };

    volatile struct ShadowInfos{
        float aFragPosLightSpace[16*4];
        float afarBounds[4];
    };

    /////////////////////////////////
    // 模型信息
    /////////////////////////////////
    volatile struct ModelInfos
    {
        /////////////////////////////////
        // 模型坐标,平移矩阵
        /////////////////////////////////
        float modelMat4[16];
    };

    struct ModelRenderConfig
    {
        SharedMesh mesh;
        ModelInfos modelInfos;
        int index;
    };

    struct RendererCammand
    {
        std::vector<ModelRenderConfig> modelConfigs;
    };
    /////////////////////////////////
    // 立方体贴图方向枚举
    /////////////////////////////////
    enum CubeDir
    {
        RIGHT = 1,
        LEFT,
        TOP,
        BOTTOM,
        BACK,
        FRONT
    };
    /////////////////////////////////
    // 立方体贴图
    // path 贴图路径
    // dir 方向
    /////////////////////////////////
    struct CubeValue
    {
        std::string path;
        CubeDir dir;
    };

    /////////////////////////////////
    // 光照 属性参照light类 总长度 = 120
    /////////////////////////////////
    // #pragma pack(push, 16)
    volatile struct LightProperty
    {
        int type;

        float constant;
        float linear;
        float quadratic;

        float cutOff;
        float outerCutOff;

        float i[2]; // 手动对齐.....我太菜了

        float position[4];
        float direction[4];

        float color[4];

        float ambient[4];
        float diffuse[4];
        float specular[4];
    };

    volatile struct LightMatrix
    {
        float m_projection[16 * 4];
        float m_view[16];
        float f_farbounds[4];
        float i_count = 0;
    };

    volatile struct LightInfo
    {
        LightProperty lights[MAX_LIGHT_COUNT];
        int numsLight;
        float nums[3];
    };
    // #pragma pack(pop)

    enum ShaderType
    {
        Vertex = 1 << 1,
        Fragment = 1 << 2,
        Geometry = 1 << 3,
    };

#ifndef ALIGN
#define ALIGN(x, a) (((x) + ((a)-1)) & ~((a)-1))
#endif
    const size_t kSizeLightInfo = sizeof(LightInfo); // CB size is required to be 256-byte aligned.
} // namespace GameEngine