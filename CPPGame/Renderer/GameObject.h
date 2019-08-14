#ifndef SRC_RENDERER_GAMEOBJECT_H
#define SRC_RENDERER_GAMEOBJECT_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <list>

#include "Texture2D.h"
#include "SpriteRenderer.h"
#include "Component.h"
#include "Node.h"
#include "ClassIDs.h"

#include "ResourceManager.h"
#include "Transform.h"
#include "CubeRenderer.h"
#include "Camera.h"

class GameObject;

typedef std::list<Node<GameObject> *> GameObjectList;
class GameObjectManager
{
public:
	GameObjectList m_ActiveNodes;

	static GameObjectManager* s_Instance;
};
GameObjectManager& GetGameObjectManager();

class Object
{
public:
	template<class T> inline
	T* getComponent(int classID);
	void addComponent(int id, Component* component);

private:
	Component* queryComponentImplementation(int classID);

private:
	typedef std::pair<int, Component*> ComponentPair;
	std::list<ComponentPair> m_compenents;
};

class GameObject :public Object {
public:
	void Renderer();
};

class CubeObject :public Object
{
public:
	void Renderer(Object *cameraObject);
};

#endif