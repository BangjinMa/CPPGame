#include "ParserManager.h"

#include "MaterialParser.h"
#include "ObjParser.h"
#include "TextureParser.h"
#include "easylogging++.h"
namespace GameEngine
{
    ParserManager* ParserManager::_instance = nullptr;
    ParserManager::ParserManager()
    {
        AddParser(ParserExtType::IMAGE, new TextureParser());
        AddParser(ParserExtType::OBJ, new ObjParser());
    }

    ParserManager::~ParserManager()
    {
        ParserMap::iterator iter = m_ParserMaps.begin();

        while (iter != m_ParserMaps.end())
        {
            delete iter->second;
            iter->second = nullptr;
            delete iter->second;
        }

        m_ParserMaps.clear();
    }

    ParserManager* ParserManager::GetInstance()
    {
        if (!_instance)
        {
            _instance = new ParserManager();
        }
        return _instance;
    }

    void ParserManager::AddParser(ParserExtType type, IParser* parser)
    {
        m_ParserMaps[type] = parser;
    }

    void ParserManager::RemoveParser(ParserExtType type)
    {
        auto pf = m_ParserMaps.find(type);
        if (pf != m_ParserMaps.end())
        {
            delete pf->second;
            m_ParserMaps.erase(type);
            return;
        }
        return;
    }

    SharedObject ParserManager::ExecuteParser(ParserExtType type, std::string path)
    {
        LOG(INFO) << "ExecuteParser   type:" << type << "      path:" << path;
        auto pf = m_ParserMaps.find(type);
        if (pf == m_ParserMaps.end())
            return nullptr;
        return pf->second->Parser(path);
    }

}  // namespace GameEngine
