#include "AssetManager.h"

#include <algorithm>
#include <mutex>

#include "AssetLoader.h"
#include "Parser/ParserManager.h"

namespace GameEngine
{
    extern AssetLoader *g_pAssetLoader;
    extern AssetManager *g_pAssetManager;

    static std::map<std::string, SharedObject> g_cache;
    static FT_Library ft;

    int AssetManager::Initialize()
    {
        // if (FT_Init_FreeType(&ft))
        // {
        // 	std::cout << "ERROR::FREETYPE: Could not init FreeType Library" <<
        // std::endl; return 1;
        // }
        return 0;
    }

    void AssetManager::Finalize()
    {
        // FT_Done_FreeType(ft);
        g_cache.clear();
    }

    void AssetManager::Tick(float deltaTime) {}

    SharedGameObject AssetManager::LoadGameObject(const std::string &path)
    {
        SharedGameObject obj;
        // if (g_pAssetLoader->FileExists(path.c_str()))
        // {

        // 	obj = ReadGameObject(ms, SharedGameObject());
        // }
        return obj;
    }

    SharedMesh AssetManager::LoadMesh(const std::string &path)
    {
        if (g_cache.find(path) != g_cache.end())
        {
            return std::dynamic_pointer_cast<Mesh>(g_cache[path]);
        }

        SharedMesh mesh =
            std::dynamic_pointer_cast<Mesh>(ObjectParser(
                ParserExtType::OBJ, path));
        if (mesh)
            g_cache[path] = mesh;
        return mesh;
    }

    SharedMesh AssetManager::GetUIMesh()
    {
        if (g_cache.find(UIMESHDATA) != g_cache.end())
        {
            return std::dynamic_pointer_cast<Mesh>(g_cache[UIMESHDATA]);
        }

        SharedMesh mesh = std::make_shared<Mesh>();
        VecterFloat3 position[4];
        VecterFloat2 textcoord[4];
        position[0] = VecterFloat3(0.5f, 0.5f, 0.0f);
        position[1] = VecterFloat3(0.5f, -0.5f, 0.0f);
        position[2] = VecterFloat3(-0.5f, -0.5f, 0.0f);
        position[3] = VecterFloat3(-0.5f, 0.5f, 0.0f);

        textcoord[0] = VecterFloat2(1.0f, 1.0f);
        textcoord[1] = VecterFloat2(1.0f, 0.0f);
        textcoord[2] = VecterFloat2(0.0f, 0.0f);
        textcoord[3] = VecterFloat2(0.0f, 1.0f);

        MeshData meshData;
        meshData.indices = {
            0, 1, 2,  // first triangle
            0, 2, 3   // second triangle
        };

        MeshVertexAttrib attrib;
        attrib.size = 3;
        attrib.type = 0x1406;

        attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_POSITION;
        attrib.attribSizeBytes = attrib.size * sizeof(float);
        meshData.attribs.push_back(attrib);
        meshData.vertexSizeInFloat += 3;

        // attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_COLOR;
        // attrib.attribSizeBytes = attrib.size * sizeof(float);
        // meshData.attribs.push_back(attrib);
        // meshData.vertexSizeInFloat += 3;

        attrib.size = 2;
        attrib.vertexAttrib = MeshValueType::VERTEX_ATTRIB_TEX_COORD;
        attrib.attribSizeBytes = attrib.size * sizeof(float);
        meshData.attribs.push_back(attrib);
        meshData.vertexSizeInFloat += 2;

        std::vector<float> vertices;
        for (size_t i = 0; i < 4; i++)
        {
            meshData.vertex.push_back(position[i][0]);
            meshData.vertex.push_back(position[i][1]);
            meshData.vertex.push_back(position[i][2]);

            // meshData.vertex.push_back(color[i][0]);
            // meshData.vertex.push_back(color[i][1]);
            // meshData.vertex.push_back(color[i][2]);

            meshData.vertex.push_back(textcoord[i][0]);
            meshData.vertex.push_back(textcoord[i][1]);
        }
        mesh->PushMeshData(meshData);
        g_cache[UIMESHDATA] = mesh;
        return mesh;
    }

    SharedTexture AssetManager::LoadTexture(const std::string &path)
    {
        SharedTexture image;
        if (g_cache.find(path) != g_cache.end())
        {
            return std::dynamic_pointer_cast<Texture>(g_cache[path]);
        }

        image = std::dynamic_pointer_cast<Texture>(ObjectParser(
            ParserExtType::IMAGE, path));
        image->Path = path;
        if (image)
            g_cache[path] = image;
        return image;
    }
    // SharePtr<Font> AssetManager::GetFont(const std::string &path)
    // {
    // 	SharePtr<Font> font;
    // 	if (g_cache.find(path) != g_cache.end())
    // 	{
    // 		return std::dynamic_pointer_cast<Font>(g_cache[path]);
    // 	}
    // 	Buffer buffer = g_pAssetLoader->SyncOpenAndReadBinary(path.c_str());
    // 	if (buffer.m_szSize > 0)
    // 	{
    // 		FT_Face face;
    // 		if (FT_New_Memory_Face(ft, buffer.m_pData, buffer.m_szSize, 0, &face))
    // 		{
    // 			std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    // 		}

    // 		font = SharePtr<Font>(new Font());
    // 		font->setFace(face);
    // 		font->setPath(path);

    // 		g_cache[path] = font;
    // 	}
    // 	return font;
    // }
    SharedTexture AssetManager::GetTexture(const std::string &path)
    {
        SharedTexture image;
        if (g_cache.find(path) != g_cache.end())
        {
            return std::dynamic_pointer_cast<Texture>(g_cache[path]);
        }
        return image;
    }

    void AssetManager::AddTexture(const std::string &path, SharedTexture image)
    {
        if (g_cache.find(path) != g_cache.end() || !image)
        {
            return;
        }
        g_cache[path] = image;
    }
    const int size = 4;
    SharedTexture AssetManager::getWhiteTexture()
    {
        const std::string path = "default/white.png";
        auto image = g_pAssetManager->GetTexture(path);
        if (image)
            return image;
        uint8_t *pixels = reinterpret_cast<uint8_t *>(malloc(size * size * 4));
        for (int i = 0; i < size * size; ++i)
        {
            pixels[i * 4 + 0] = 255;
            pixels[i * 4 + 1] = 255;
            pixels[i * 4 + 2] = 255;
            pixels[i * 4 + 3] = 255;
        }
        pixels += '\0';
        image = std::make_shared<Texture>();
        image->formate = 3;
        image->Width = size;
        image->Height = size;
        image->data = pixels;
        g_pAssetManager->AddTexture(path, image);
        return image;
    }
}  // namespace GameEngine