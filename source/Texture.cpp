#include "Texture.h"

Texture::Texture(std::string path)
{
	unsigned char* image;
	int textureWidth = 0;
	int textureHeight = 0;
	image = SOIL_load_image(path.c_str(), &textureWidth, &textureHeight, NULL, SOIL_LOAD_RGB);
	glGenTextures(1, &this->texture);
	glBindTexture(GL_TEXTURE_2D, this->texture);

	//wczytawanie jpga
	if (image)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);;
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	}
	else
	{
		std::cout << "Error loading texture" << std::endl;
	}

	glActiveTexture(0);
	glBindTexture(GL_TEXTURE_2D, 0);
	SOIL_free_image_data(image);
}

void Texture::use()
{
	glActiveTexture(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->texture);
}

void Texture::unuse()
{
	glBindTexture(GL_TEXTURE_2D, 0);
	glActiveTexture(0);
}
