#version 420 core
in vec3 a_position;
in vec3 a_normal;
in vec2 a_texCoord;

layout(std140) uniform ModelInfos{ 
    mat4 u_model_matrix;
} modelInfos;

layout(std140) uniform ViewInfos
{
    vec3 u_camera_pos;
    mat4 u_projection_matrix;
    mat4 u_view_matrix;
} viewInfos;

out Value  
{  
    vec2 texCoord;
    vec4 worldPosition;
    vec4 position;
    vec3 noraml;
}value; 

void main() {
    value.worldPosition = modelInfos.u_model_matrix * vec4(a_position, 1);
    value.position = viewInfos.u_projection_matrix * viewInfos.u_view_matrix *  value.worldPosition;
    gl_Position = value.position;
    value.texCoord = a_texCoord;
    value.noraml = mat3(modelInfos.u_model_matrix) * a_normal;
}
