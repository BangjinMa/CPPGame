﻿#include <iostream>
#include "GraphicsManager.h"
#include "glad/glad.h"
#include "Scene.h"
#include <GLFW/glfw3.h>
#include "SceneManager.h"
#include "AssetManager.h"
#include "ParserManager.h"
#include "ShaderManager.h"
#include <algorithm>

#include "Shader.h"
#include "Material.h"
#include "Mesh.h"


#include <string>
using namespace std;

GameEngineBegin
extern AssetManager *g_pAssetManager;
extern GameEngineParser::ParserManager *g_pParserManager;
extern ShaderManager *g_pShaderManager;

int GraphicsManager::Initialize()
{
	int result;
	result = gladLoadGL();
	if (!result)
	{
		cerr << "OpenGL load failed!" << endl;
		result = -1;
	}
	else
	{
		result = 0;
		cout << "OpenGL Version " << GLVersion.major << "." << GLVersion.minor << " loaded" << endl;

		glClearDepth(1.0f);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);

		SharePtr<Scene> m_Scene;
		m_Scene = std::dynamic_pointer_cast<Scene>(g_pParserManager->ExecuteParser(GameEngineParser::ParserExtType::SCENE, "Scene/defaultEx.scene"));
		SceneManager::GetInstance()->SetNextScene(m_Scene);
		result = 0;
	}

	return result;
}

void GraphicsManager::Finalize()
{
}

void GraphicsManager::Tick()
{
	auto window = glfwGetCurrentContext();
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	m_RendererCommands.clear();
	BaseGraphicsManager::Tick();
	glfwSwapBuffers(window);
}

void GraphicsManager::Clear()
{
}

void GraphicsManager::Draw()
{
	for (auto renderer = m_RendererCommands.begin(); renderer != m_RendererCommands.end(); renderer++)
	{
		PrepareMaterial(renderer->material);
		PrepareMesh(renderer->mesh, renderer->index);
	}
}

void GraphicsManager::PrepareMaterial(Material &material)
{
	int textureID = 0;
	auto shader = g_pShaderManager->GetShaderProgram(material.shaderID);
	shader->Use();
	for (size_t i = 0; i < material.m_MaterialDatas.size(); i++)
	{
		auto data = material.m_MaterialDatas[i];

		switch (data.m_Type)
		{
		case MaterialType::T_Mat4:
		{
			auto property = (float *)data.m_Buffer;
			shader->setMat4(data.m_Name, &property[0]);
			break;
		}
		case MaterialType::T_Texture:
		{
			auto property = (char *)data.m_Buffer;
			int location;
			location = glGetUniformLocation(shader->m_ProgramID, data.m_Name.c_str());
			if (location != -1)
			{
				SharedTexture image = g_pAssetManager->LoadTexture(property);
				if (!image)
					image = g_pAssetManager->getWhiteTexture();
				shader->setInt(data.m_Name, textureID);
				if (image->id <= 0)
				{
					BindTexture(image);
				}
				glActiveTexture(GL_TEXTURE0 + textureID);
				glBindTexture(GL_TEXTURE_2D, image->id);
				textureID++;
			}
			break;
		}
		default:
			break;
		}
	}
}

void GraphicsManager::BindTexture(SharedTexture texture)
{
	GLenum format;
	if (texture->formate == 1)
		format = GL_RED;
	else if (texture->formate == 3)
		format = GL_RGB;
	else if (texture->formate == 4)
		format = GL_RGBA;

	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, format, texture->Width, texture->Height, 0, format, GL_UNSIGNED_BYTE, texture->data);
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	texture->id = textureID;
}

void GraphicsManager::PrepareMesh(SharedMesh mesh, int index)
{
	if (mesh->isPrepare)
	{
		glBindVertexArray(mesh->m_MeshDatas[index].VAO);
		glDrawElements(GL_TRIANGLES, mesh->m_MeshDatas[index].indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
		return;
	}
	for (size_t iMesh = 0; iMesh < mesh->m_MeshDatas.size(); iMesh++)
	{
		glGenVertexArrays(1, &mesh->m_MeshDatas[iMesh].VAO);
		glGenBuffers(1, &mesh->m_MeshDatas[iMesh].VBO);
		glGenBuffers(1, &mesh->m_MeshDatas[iMesh].EBO);

		glBindVertexArray(mesh->m_MeshDatas[iMesh].VAO);
		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, mesh->m_MeshDatas[iMesh].VBO);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
		// again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, mesh->m_MeshDatas[iMesh].vertex.size() * sizeof(float), &mesh->m_MeshDatas[iMesh].vertex[0], GL_STATIC_DRAW);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->m_MeshDatas[iMesh].EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->m_MeshDatas[iMesh].indices.size() * sizeof(unsigned int), &mesh->m_MeshDatas[iMesh].indices[0], GL_STATIC_DRAW);
		int offest = 0;
		for (size_t i = 0; i < mesh->m_MeshDatas[iMesh].attribs.size(); i++)
		{
			auto data = mesh->m_MeshDatas[iMesh].attribs[i];
			glEnableVertexAttribArray(data.vertexAttrib);
			glVertexAttribPointer(data.vertexAttrib, data.size, GL_FLOAT, GL_FALSE, mesh->m_MeshDatas[iMesh].vertexSizeInFloat * sizeof(float), (void *)offest);
			offest += data.attribSizeBytes;
		}
		glBindVertexArray(0);
	}
	mesh->isPrepare = true;
	PrepareMesh(mesh, index);
}

GameEngineEnd