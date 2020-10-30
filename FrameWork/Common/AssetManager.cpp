#include "AssetManager.h"
#include <algorithm>
#include "AssetLoader.h"
#include "TextureParser.h"
#include "ObjParser.h"
#include "Material.h"
#include "MaterialParser.h"
#include <mutex>

#include "UI/Font.h"

GameEngineBegin 

extern AssetLoader *g_pAssetLoader;
extern AssetManager *g_pAssetManager;

static std::map<std::string, SharedObject> g_cache;
static FT_Library ft;

int AssetManager::Initialize()
{
	// if (FT_Init_FreeType(&ft))
	// {
	// 	std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
	// return 1;
	// }
	return 0;
}

void AssetManager::Finalize()
{
	// FT_Done_FreeType(ft);
	g_cache.clear();
}

void AssetManager::Tick()
{
}

SharedGameObject AssetManager::LoadGameObject(const std::string &path)
{
	SharedGameObject obj;
	// if (g_pAssetLoader->FileExists(path.c_str()))
	// {

	// 	obj = ReadGameObject(ms, SharedGameObject());
	// }
	return obj;
}

SharedMaterial AssetManager::LoadMaterial(const std::string &path)
{
	SharedMaterial obj;
	if (g_cache.find(path) != g_cache.end())
	{
		return std::dynamic_pointer_cast<Material>(g_cache[path]);
	}
	obj = MaterialParser::Parse(path);
	if (obj)
		g_cache[path] = obj;
	return obj;
}

SharedMesh AssetManager::LoadMesh(const std::string &path)
{
	if (g_cache.find(path) != g_cache.end())
	{
		return std::dynamic_pointer_cast<Mesh>(g_cache[path]);
	}

	SharedMesh mesh = ObjParser::Parse(path);
	if (mesh)
		g_cache[path] = mesh;
	return mesh;
}

SharedTexture AssetManager::LoadTexture(const std::string &path)
{
	SharedTexture image;
	if (g_cache.find(path) != g_cache.end())
	{
		return std::dynamic_pointer_cast<Texture>(g_cache[path]);
	}
	Buffer buffer = g_pAssetLoader->SyncOpenAndReadBinary(path.c_str());
	if (buffer.m_szSize > 0)
	{
		image = TextureParser::Parse(buffer);
		image->Path = path;
		g_cache[path] = image;
	}
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
	image = TextureParser::bindTexture(0x1908, size, size, pixels);
	g_pAssetManager->AddTexture(path, image);
	return image;
}
GameEngineEnd