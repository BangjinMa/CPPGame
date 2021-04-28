#pragma once

#include <ft2build.h>

#include <functional>
#include <list>
#include <map>
#include <memory>

#include "Config.h"
#include "GameObject.h"
#include "IRuntimeModule.h"
#include "Mesh.h"
#include "Texture.h"
#include FT_FREETYPE_H

namespace GameEngine
{
#define UIMESHDATA "_UIMESH"

    class AssetManager : public IRuntimeModule
    {
    private:
    public:
        virtual int Initialize();
        virtual void Finalize();
        virtual void Tick(float deltaTime);

        static SharedGameObject LoadGameObject(const std::string &path);
        static SharedMesh LoadMesh(const std::string &path);
        static SharedMesh GetUIMesh();
        static SharedTexture LoadTexture(const std::string &path);

        // static SharePtr<Font> GetFont(const std::string &path);

        static SharedTexture GetTexture(const std::string &path);
        static void AddTexture(const std::string &path, SharedTexture image);

        static SharedTexture getWhiteTexture();
    };

}  // namespace GameEngine
