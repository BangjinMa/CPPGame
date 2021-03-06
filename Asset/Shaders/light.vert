#version 420 core
in vec3 a_position;

layout(std140) uniform ModelInfos{ 
    mat4 u_model_matrix;
} modelInfos;

layout(std140) uniform ViewInfos
{
    /////////////////////////////////
    // 摄像机坐标
    /////////////////////////////////
    vec3 u_camera_pos;
    /////////////////////////////////
    // 摄像机投影矩阵
    /////////////////////////////////
    mat4 u_projection_matrix;
    /////////////////////////////////
    // 摄像机观察矩阵
    /////////////////////////////////
    mat4 u_view_matrix;
} viewInfos;

void main()
{
    gl_Position = viewInfos.u_projection_matrix * viewInfos.u_view_matrix * modelInfos.u_model_matrix * vec4(a_position, 1.0);
}