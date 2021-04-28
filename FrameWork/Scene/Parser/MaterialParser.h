//
// Copyright 2012-2015, Syoyo Fujita.
//
// Licensed under 2-clause BSD license.
//
//https://github.com/syoyo/tinyobjloader
#pragma once

#include <map>
#include <string>
#include <vector>

#include "AssetLoader.h"
#include "Config.h"
#include "IParser.h"
#include "cjson/cJSON.h"

namespace GameEngine
{
    extern AssetLoader *g_pAssetLoader;
}  // namespace GameEngine

using namespace GameEngine;
namespace GameEngine
{
    class MaterialParser : public IParser
    {
    public:
        virtual SharedObject Parser(const std::string path) override
        {
        //    SharedMaterial material = std::make_shared<Material>();
        //    std::string mstr = g_pAssetLoader->SyncOpenAndReadTextFileToString(path.c_str());
        //    auto json = cJSON_Parse(mstr.c_str());

        //    auto frag = cJSON_GetObjectItem(json, "frag");
        //    auto vert = cJSON_GetObjectItem(json, "vert");
        //    material->AddShaderPath(ShaderType::Vertex, vert->valuestring);
        //    material->AddShaderPath(ShaderType::Fragment, frag->valuestring);

        //    auto paramsNode = cJSON_GetObjectItem(json, "params");
        //    if (paramsNode)
        //    {
        //        auto count = cJSON_GetArraySize(paramsNode);
        //        for (int i = 0; i < count; i++)
        //        {
        //            cJSON *item = cJSON_GetArrayItem(paramsNode, i);
        //            std::string name = item->string;
        //            std::string type = cJSON_GetObjectItem(item, "type")->valuestring;
        //            if (type.compare("texture") == 0)
        //            {
        //                std::string pathStr = cJSON_GetObjectItem(item, "path")->valuestring;
        //                material->AddProperty(pathStr.c_str(), name, pathStr.size(), MaterialType::T_Texture);
        //            }
        //            else if (type.compare("vec4") == 0)
        //            {
        //            }
        //        }
        //    }
        //    delete json;
        //    return material;
        }
    };
}  // namespace GameEngine
