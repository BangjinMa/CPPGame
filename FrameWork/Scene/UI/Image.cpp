#include "Image.h"
#include "Material.h"

GameEngineBegin

Image::Image()
{
}

Image::~Image()
{
}

void Image::setTexture(SharedTexture texture)
{
	m_Texture = texture;
}

void Image::Start()
{
	Widget::Start();
	auto material = GetMaterial();
	if (!material)
		return;
	material->AddProperty(m_Texture->Path.c_str(), "MainTextures", m_Texture->Path.size(), MaterialType::T_Texture);
}
GameEngineEnd