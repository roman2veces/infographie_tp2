#include "model.h"

#include "obj_loader.h"
#include <iostream>

Model::Model(const char* path)
{
	// TODO: Initalisation du modèle et des attibuts de la classe
	std::vector<GLfloat> pos; 
	std::vector<GLuint> indices;
	this->loadObj(path, pos, indices);
	this->m_shape = BasicShapeElements(pos.data(), pos.size(), indices.data(), indices.size());
	this->m_shape.enableAttribute(0, 3, 6 * sizeof(float), 0);
	this->m_count = sizeof(indices) / sizeof(GLuint);
}

void Model::loadObj(const char* path, std::vector<GLfloat>& pos, std::vector<GLuint>& indices)
{
	objl::Loader loader;
	bool loadout = loader.LoadFile(path);
	if (!loadout)
	{
		std::cout << "Unable to load model " << path << std::endl;
		return;
	}

	for (size_t i = 0; i < loader.LoadedVertices.size(); i++)
	{
		objl::Vector3 p = loader.LoadedVertices[i].Position;
		pos.push_back(p.X);
		pos.push_back(p.Y);
		pos.push_back(p.Z);
		// TODO: Décommenter lors de la partie 2
		//objl::Vector2 t = loader.LoadedVertices[i].TextureCoordinate;
		//vertexData.push_back(t.X);
		//vertexData.push_back(t.Y);
	}
	indices = loader.LoadedIndices;
}

void Model::draw()
{
	// TODO: Dessine le modèle en triangle
	this->m_shape.draw(GL_TRIANGLES, this->m_count);
}