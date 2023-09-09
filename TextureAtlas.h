#ifndef TEXTUREATLAS_H
#define TEXTUREATLAS_H
#include <string>
#include <map>
#include <pugixml.hpp>
#include <raylib.h>
#include <vector>

class TextureAtlas
{

public:
	bool FromFile(std::string path)
	{
		pugi::xml_document doc;
		std::string image_path = "";
		pugi::xml_parse_result result = doc.load_file(path.c_str());
		if (!result)
		{
			TraceLog(LOG_DEBUG, "Failed to load TextureAtlas file at path %s", path.c_str());
			return false;
		}
		image_path = "assets/" + std::string(doc.first_child().attribute("imagePath").value());
		spriteSheet = LoadTexture(image_path.c_str());

		for (pugi::xml_node node : doc.first_child().children())
		{
			float x = atof(node.attribute("x").value());
			float y = atof(node.attribute("y").value());
			float width = atof(node.attribute("width").value());
			float height = atof(node.attribute("height").value());
			std::string name = node.attribute("name").value();
			Rectangle subRect = { x,y,width, height };
			subRectMap[name] = subRect;
		}
		return true;
	}

	Rectangle GetSubRectangle(std::string name)
	{
		return subRectMap[name];
	}

	bool DrawTexture(std::string name, Vector2 Position = { -1,-1 }, Color color = WHITE)
	{
		if (subRectMap.find(name) != subRectMap.end())
		{
			Rectangle subRect = subRectMap[name];

			if (Position.x == -1 && Position.y == -1)
			{
				Position = { subRect.x, subRect.y };
			}

			DrawTextureRec(spriteSheet, subRect, Position, color);
			return true;
		}
		return false;
	}

	Texture2D Rect2Texture(std::string name)
	{

		Image cropped = ImageCopy(LoadImageFromTexture(spriteSheet));
		ImageCrop(&cropped, GetSubRectangle(name));
		return LoadTextureFromImage(cropped);
	}

	std::vector<std::string> GetAvaliableTextures()
	{
		std::vector<std::string> textureNames;
		for (const auto& pair : subRectMap)
		{
			textureNames.emplace_back(pair.first);
		}
	}


private:
	Texture2D spriteSheet;
	std::map<std::string, Rectangle> subRectMap; // holds all the textures inside the spritesheet
};


class TextureAtlasManager
{
public:
	static TextureAtlasManager* instance;

	static TextureAtlasManager* GetInstance()
	{
		if (!instance)
			instance = new TextureAtlasManager();
		return instance;
	}

	bool LoadAtlasTexture(std::string name, std::string path)
	{
		TextureAtlas atlas;
		atlas.FromFile(path);

		textureAtlasMap[name] = atlas;

		return true;

	}

	TextureAtlas GetTexureAtlas(std::string name)
	{
		return textureAtlasMap[name];
	}


private:
	std::map<std::string, TextureAtlas> textureAtlasMap; // keep trace of loaded texture atlases;
};

#endif // !TEXTUREATLAS_H
