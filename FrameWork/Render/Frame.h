#pragma once

struct Frame
{
    int m_uboLightInfo = -1;
    int m_uboCameraInfo = -1;
    int m_uboModelInfo = -1;
    int m_uboLightModelInfo = -1;

    unsigned int shadowMap = 0;
    unsigned int shadowFBO = 0;
};
