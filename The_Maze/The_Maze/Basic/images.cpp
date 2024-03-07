/*
*       Made by: Lenita Njærheim
*           Created On: 01/12-2023
*           Completed: 04/03-2024
*       Project Name: The Maze
*/
#include "images.h"

#include <iostream>
#include <fstream>
#include <vector>

//This ONLY works for bitmaps on windows (probably also only with bitdepth of 4) and width has to be a multiple of 4
//NOTE: width and height har to be 16 for it do display corretly
std::vector <pixel*> bitmapread(std::string filepath) {

	//best Documentation for bitmaps: https://en.wikipedia.org/wiki/BMP_file_format
	unsigned char Headder_uchar[14]; //Main headder is always size 14
	FILE* f;
	fopen_s(&f, filepath.c_str(), "rb");
	fread(Headder_uchar, sizeof(unsigned char), 14, f);

	unsigned char filesize_uchar[4];
	unsigned char offsetdata[4];

	filesize_uchar[0] = Headder_uchar[0 + 2];
	filesize_uchar[1] = Headder_uchar[1 + 2];
	filesize_uchar[2] = Headder_uchar[2 + 2];
	filesize_uchar[3] = Headder_uchar[3 + 2];

	for (int i = 0; i < 4; i++) { //4 is since it is 4 bytes of data
		offsetdata[i] = Headder_uchar[i + 10];
	}

	int offset_int = (int)offsetdata[3] + (int)offsetdata[2] + (int)offsetdata[1] + (int)offsetdata[0];
	int size_int = (int)filesize_uchar[3] + (int)filesize_uchar[2] + (((int)filesize_uchar[1] / 4) * 1024) /*this might be wrong???*/ + (int)filesize_uchar[0];

	rewind(f);

	//this file uses BITMAPINFOHEADDER (BM, seems windows specific)
	std::vector <unsigned char> wholefile_vec;
	wholefile_vec.resize(size_int);
	fread(&wholefile_vec[0], sizeof(unsigned char), size_int, f);

	unsigned char btspix[2];

	btspix[0] = wholefile_vec[14 + 14 + 0];
	btspix[1] = wholefile_vec[14 + 14 + 1];

	int btspix_int = (int)btspix[0] + (int)btspix[1]; //is the colour depth of the image

	unsigned char sizeofDIB_uchar[4];
	unsigned char width_uchar[4];
	unsigned char height_uchar[4];
	unsigned char compression_uchar[4];

	for (int i = 0; i < 4; i++) {
		sizeofDIB_uchar[i] = wholefile_vec[14 + i];
		width_uchar[i] = wholefile_vec[14 + 4 + i];
		height_uchar[i] = wholefile_vec[14 + 8 + i];
		compression_uchar[i] = wholefile_vec[14 + 16 + i];
	}

	int sizeofDIB_int = (int)sizeofDIB_uchar[0] + (int)sizeofDIB_uchar[1] + (int)sizeofDIB_uchar[2] + (int)sizeofDIB_uchar[3];
	int width_int = (int)width_uchar[0] + (int)width_uchar[1] + (int)width_uchar[2] + (int)width_uchar[3];
	int height_int = (int)height_uchar[0] + (int)height_uchar[1] + (int)height_uchar[2] + (int)height_uchar[3];
	int compression_int = (int)compression_uchar[0] + (int)compression_uchar[1] + (int)compression_uchar[2] + (int)compression_uchar[3];
		
	int rowsize = ((btspix_int * width_int) / 32) * 4;
	if (height_int < 0) {
		height_int *= (-1);
	}
	int PixelArraySize = rowsize * height_int;

	std::vector <pixel*> pix;
	int start;
	std::vector <std::vector <unsigned char>> rgb_vec;
	int x_int{ 0 };
	int y_int = height_int - 1;
	int j{ 0 };
	switch (compression_int) {
	case 0: //BI_RGB
		//REMEMBER Padding
		//these has no padding since width is a multiple of 4
		start = 14 + sizeofDIB_int;

		for (int i = start; i < offset_int; i += 4) {
			rgb_vec.push_back({ wholefile_vec[i + 2], wholefile_vec[i + 1], wholefile_vec[i + 0], wholefile_vec[i + 3]});
			j++;
		}

		int read;
		int ind[2];

		for (int i = offset_int; i < size_int; i++) {
			read = (int)wholefile_vec[i];

			ind[1] = read % 16;
			read = read / 16;
			ind[0] = read % 16;

			std::vector <unsigned char> rgb = rgb_vec[ind[0]];
			pix.push_back(new pixel(colour((int)rgb[0], (int)rgb[1], (int)rgb[2], 255), x_int, y_int));
			x_int++;
			if (x_int >= width_int) {
				x_int = 0;
				y_int--;
			}

			rgb = rgb_vec[ind[1]];
			pix.push_back(new pixel(colour((int)rgb[0], (int)rgb[1], (int)rgb[2], 255), x_int, y_int));
			x_int++;
			if (x_int >= width_int) {
				x_int = 0;
				y_int--;
			}
		}
		break;
	case 3: //BI_BITFIELDS (supposedly uses Huffman 1D compression method)
		//seems to just store colour by colour
		//REMEMBER padding
		//Current file should work fine without padding
		start = offset_int;
		for (int i = start; i < wholefile_vec.size(); i += 4) {
			pix.push_back(new pixel(colour((int)wholefile_vec[i + 2], (int)wholefile_vec[i + 1], (int)wholefile_vec[i], (int)wholefile_vec[i + 3]), x_int, y_int));
			x_int++;
			if (x_int >= width_int) {
				x_int = 0;
				y_int--;
			}
		}
		break;
	}
	return pix;
}

//This ONLY works for bitmaps on windows (probably also only with bitdepth of 4) and width has to be a multiple of 4
//NOTE: width and height har to be 16 for it do display corretly
std::vector <pixel*> bitmapread(std::string filepath, images* img) {

	//best Documentation for bitmaps: https://en.wikipedia.org/wiki/BMP_file_format
	unsigned char Headder_uchar[14]; //Main headder is always size 14
	FILE* f;
	fopen_s(&f, filepath.c_str(), "rb");
	fread(Headder_uchar, sizeof(unsigned char), 14, f);

	unsigned char filesize_uchar[4];
	unsigned char offsetdata[4];

	filesize_uchar[0] = Headder_uchar[0 + 2];
	filesize_uchar[1] = Headder_uchar[1 + 2];
	filesize_uchar[2] = Headder_uchar[2 + 2];
	filesize_uchar[3] = Headder_uchar[3 + 2];

	for (int i = 0; i < 4; i++) { //4 is since it is 4 bytes of data
		offsetdata[i] = Headder_uchar[i + 10];
	}

	int offset_int = (int)offsetdata[3] + (int)offsetdata[2] + (int)offsetdata[1] + (int)offsetdata[0];
	int size_int = (int)filesize_uchar[3] + (int)filesize_uchar[2] + (((int)filesize_uchar[1] / 4) * 1024) /*this might be wrong???*/ + (int)filesize_uchar[0];

	rewind(f);

	//this file uses BITMAPINFOHEADDER (BM, seems windows specific)
	std::vector <unsigned char> wholefile_vec;
	wholefile_vec.resize(size_int);
	fread(&wholefile_vec[0], sizeof(unsigned char), size_int, f);

	unsigned char btspix[2];

	btspix[0] = wholefile_vec[14 + 14 + 0];
	btspix[1] = wholefile_vec[14 + 14 + 1];

	int btspix_int = (int)btspix[0] + (int)btspix[1]; //is the colour depth of the image

	unsigned char sizeofDIB_uchar[4];
	unsigned char width_uchar[4];
	unsigned char height_uchar[4];
	unsigned char compression_uchar[4];

	for (int i = 0; i < 4; i++) {
		sizeofDIB_uchar[i] = wholefile_vec[14 + i];
		width_uchar[i] = wholefile_vec[14 + 4 + i];
		height_uchar[i] = wholefile_vec[14 + 8 + i];
		compression_uchar[i] = wholefile_vec[14 + 16 + i];
	}

	int sizeofDIB_int = (int)sizeofDIB_uchar[0] + (int)sizeofDIB_uchar[1] + (int)sizeofDIB_uchar[2] + (int)sizeofDIB_uchar[3];
	int width_int = (int)width_uchar[0] + (int)width_uchar[1] + (int)width_uchar[2] + (int)width_uchar[3];
	int height_int = (int)height_uchar[0] + (int)height_uchar[1] + (int)height_uchar[2] + (int)height_uchar[3];
	int compression_int = (int)compression_uchar[0] + (int)compression_uchar[1] + (int)compression_uchar[2] + (int)compression_uchar[3];

	img->height = height_int;
	img->width = width_int;

	int rowsize = ((btspix_int * width_int) / 32) * 4;
	if (height_int < 0) {
		height_int *= (-1);
	}
	int PixelArraySize = rowsize * height_int;

	std::vector <pixel*> pix;
	int start;
	std::vector <std::vector <unsigned char>> rgb_vec;
	int x_int{ 0 };
	int y_int = height_int - 1;
	int j{ 0 };
	switch (compression_int) {
	case 0: //BI_RGB
		//REMEMBER Padding
		//these has no padding since width is a multiple of 4
		start = 14 + sizeofDIB_int;

		for (int i = start; i < offset_int; i += 4) {
			rgb_vec.push_back({ wholefile_vec[i + 2], wholefile_vec[i + 1], wholefile_vec[i + 0], wholefile_vec[i + 3] });
			j++;
		}

		int read;
		int ind[2];

		for (int i = offset_int; i < size_int; i++) {
			read = (int)wholefile_vec[i];

			ind[1] = read % 16;
			read = read / 16;
			ind[0] = read % 16;

			std::vector <unsigned char> rgb = rgb_vec[ind[0]];
			pix.push_back(new pixel(colour((int)rgb[0], (int)rgb[1], (int)rgb[2], 255), x_int, y_int));
			x_int++;
			if (x_int >= width_int) {
				x_int = 0;
				y_int--;
			}

			rgb = rgb_vec[ind[1]];
			pix.push_back(new pixel(colour((int)rgb[0], (int)rgb[1], (int)rgb[2], 255), x_int, y_int));
			x_int++;
			if (x_int >= width_int) {
				x_int = 0;
				y_int--;
			}
		}
		break;
	case 3: //BI_BITFIELDS (supposedly uses Huffman 1D compression method)
		//seems to just store colour by colour
		//REMEMBER padding
		//Current file should work fine without padding
		img->transparentpixels(true);
		start = offset_int;
		for (int i = start; i < wholefile_vec.size(); i += 4) {
			pix.push_back(new pixel(colour((int)wholefile_vec[i + 2], (int)wholefile_vec[i + 1], (int)wholefile_vec[i], (int)wholefile_vec[i + 3]), x_int, y_int));
			x_int++;
			if (x_int >= width_int) {
				x_int = 0;
				y_int--;
			}
		}
		break;
	}
	return pix;
}

images::images(std::string filepath)
{
	int period = 0;
	for (int i = filepath.length(); i > 0; i--) {
		if (filepath[i] == '.') {
			period = i;
			break;
		}
	}
	std::string filetype = "";
	for (int i = period; i < filepath.length(); i++) {//will be used to check the filetype, different files have different structure
		filetype += filepath[i];
	}
	if (filetype == ".bmp") {
		pixels = bitmapread(filepath, this);
	}
}

images::images(std::string filepath, int x, int y, int image_size)
{
	loc[0] = x;
	loc[1] = y;
	size = image_size;

	int period = 0;
	for (int i = filepath.length(); i > 0; i--) {
		if (filepath[i] == '.') {
			period = i;
			break;
		}
	}
	std::string filetype = "";
	for (int i = period; i < filepath.length(); i++) {//will be used to check the filetype, different files have different structure
		filetype += filepath[i];
	}
	if (filetype == ".bmp") {
		pixels = bitmapread(filepath);
	}
	for (int i = 0; i < pixels.size(); i++) {
		//NOTE: with the draw on location funktion I will not need to move the pixels
		pixels[i]->move(pixels[i]->get_x() + loc[0] - size/2, pixels[i]->get_y() + loc[1] - size / 2); //moves the image to the location and centers it
		if (pixels[i]->GetColour().GetAlpha() < 255 && hastransparentpixels != true) {
			hastransparentpixels = true;
		}
	}
}

images::images(int Location_x, int Location_y, colour unicolour, int image_size)
{
	loc[0] = Location_x;
	loc[1] = Location_y;
	size = image_size;

	int max_x = Location_x + image_size / 2;
	int max_y = Location_y + image_size / 2;
	int min_x = Location_x - image_size / 2;
	int min_y = Location_y - image_size / 2;


	for (int x = min_x; x < max_x; x ++) {
		for (int y = min_y; y < max_y; y ++) {
			pixels.push_back(new pixel(unicolour, x, y));
		}
	}
}

pixel images::GetPixel(int x, int y)
{
	pixel p;
	for (int i = 0; i < pixels.size(); i++) {
		if (pixels[i]->get_x() == x && pixels[i]->get_y() == y) {
			p = *pixels[i];
			break;
		}
	}
	return p;
}

void images::move(int new_x, int new_y)
{
	int changed_x = new_x - loc[0];
	int changed_y = new_y - loc[1];
	loc[0] = new_x;
	loc[1] = new_y;

	for (int i = 0; i < pixels.size(); i++) {
		pixels[i]->move(pixels[i]->get_x() + changed_x, pixels[i]->get_y() + changed_y);
	}
}

void images::draw(HDC hdc)
{
	for (int i = 0; i < pixels.size(); i++) {
		pixels[i]->drawpixel(hdc);
	}
}

void images::draw_on_location(HDC hdc, int x, int y)
{
	int relative_x = x - width / 2;
	int relative_y = y - height / 2;
	for (int i = 0; i < pixels.size(); i++) {
		pixels[i]->draw_in_location(hdc, pixels[i]->get_x() + relative_x, pixels[i]->get_y() + relative_y);
	}
}