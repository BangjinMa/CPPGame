#pragma once

struct Frame
{
    int m_uboLightInfo = -1;
    int m_uboCameraInfo = -1;
    int m_uboModelInfo = -1;
    int m_uboLightModelInfo = -1;
    int m_uboShadowInfos = -1;

    unsigned int shadowMap = 0;
    unsigned int sumShadowCount = 0;
    unsigned int sumShadowSTA = 0;
    unsigned int shadowFBO = 0;
};
