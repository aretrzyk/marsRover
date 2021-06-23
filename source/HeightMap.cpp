#include "HeightMap.h"

HeightMap::HeightMap(std::string path, glm::vec3 min, glm::vec3 max)
{
	std::ifstream file(path, std::ios::binary);

	std::string format;
	file >> format;

	file >> this->pixelsWidth >> this->pixelsHeight;

	this->map = new unsigned int* [this->pixelsWidth];
	for (int i = 0; i < this->pixelsWidth; i++)
		this->map[i] = new unsigned int[this->pixelsHeight];

	int read1, read2, read3;
	file >> read1;
	bool firstRead = true;

	//std::ofstream save("dane.txt", std::ios::app);

	for (int i = 0; i < this->pixelsHeight; i++)
	{
		for (int j = 0; j < this->pixelsWidth; j++)
		{
			file >> read1;
			file >> read2;
			file >> read3;
			this->map[j][i] = (read1 + read2 + read3) / 3;
			//save << i << " " << j << " " << this->map[i][j] << std::endl;
			//if (this->map[i][j] > 0) std::cout << "1";
			//else std::cout << "0";
			if (firstRead)
			{
				this->minBright = this->map[j][i];
				this->maxBright = this->map[j][i];
				firstRead = false;
			}
			else
			{
				if (this->minBright > this->map[j][i]) this->minBright = this->map[j][i];
				else if (this->maxBright < this->map[j][i]) this->maxBright = this->map[j][i];
			}
		}
		//std::cout << std::endl;
	}

	this->minHeight = min.y;
	this->maxHeight = max.y;

	this->minXZ = glm::vec2(min.x, min.z);
	this->maxXZ = glm::vec2(max.x, max.z);

	this->sizeX = this->maxXZ.x - this->minXZ.x;
	this->sizeZ = this->maxXZ.y - this->minXZ.y;


}

float HeightMap::getHeight(float x, float z)
{
	glm::vec2 pos = glm::vec2(-this->minXZ.x, this->maxXZ.y) - glm::vec2(x,z);

	//std::cout << pos.x << " " << pos.y << std::endl;

	std::cout << pos.x * this->pixelsWidth / this->sizeX << " " << pos.y * this->pixelsHeight / this->sizeZ << std::endl;

	float mapValue = (float)(map[(int)round(pos.x * this->pixelsWidth / this->sizeX)][(int)round(pos.y * this->pixelsHeight / this->sizeZ)] + this->minBright) / (float)(this->maxBright - this->minBright);

	//std::cout << mapValue * (this->maxHeight - this->minHeight) + this->minHeight << std::endl;

	return mapValue * (this->maxHeight - this->minHeight) + this->minHeight;

}