#pragma once
#include <vector>
#include <string>
#include <fstream>

GLuint _textureID; // Inisialisasi
using namespace std;
GLuint LoadTGA_custom(const char* tgaPath) {
	struct PixelData {
		uint32_t color; // Menyimpan data warna per pixel
		struct 
		{
		uint8_t R, G, B, A;
		};
	};

	PixelData* pixelsData;
	vector<uint8_t> pixels; // Unsignedint supaya bisa menuju tepat ke 8 bit
	uint32_t width, height, size, bpp; // Unsignedint supaya bisa menuju tepat ke 32 bit
	fstream inFile(tgaPath, ios::in | ios::binary);
	if (!inFile.is_open()) {
		printf("File Not Found");
		return 0;
	}

	uint8_t header[18] = { 0 }; // Header file TGA

	vector<uint8_t> colorData;
	inFile.read(reinterpret_cast<char*>(&header), sizeof(header)); // Interpretasi dari byte ke char
	bpp = header[16];
	width = header[13] * 256 + header[12];
	height = header[15] * 256 + header[14];
	size = size = ((width * bpp + 31) / 32) * 4 * height;

	if ((bpp != 24) && (bpp != 32)) { // Error Handling
		inFile.close();
		printf("Not Correct TGA File");
		return 0;
	}

	colorData.resize(size);
	inFile.read(reinterpret_cast<char*>(colorData.data()), size); // Interpretasi dari byte ke char
	inFile.close();
	pixels = colorData;
	glGenTextures(1, &_textureID);
	glBindTexture(GL_TEXTURE_2D, _textureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pixels.data()); // Mengisi data tiap pixel
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}