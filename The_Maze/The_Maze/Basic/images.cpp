/*
*       Made by: Lenita Njærheim
*           Created On: 01/12-2023
*           Completed:
*       Project Name: The Maze
*/
#include "images.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

struct BMPFileHeader { //https://solarianprogrammer.com/2018/11/19/cpp-reading-writing-bmp-images/
	uint16_t file_type{ 0x4D42 };
	uint32_t file_size{ 0 };
	uint16_t reserved1{ 0 };
	uint16_t reserved2{ 0 };
	uint32_t offset_data{ 0 };
};

struct BMPInfoHeader {
	uint32_t size{ 0 };
	int32_t width{ 0 };
	int32_t height{ 0 };

	uint16_t planes{ 1 };
	uint16_t bit_count{ 0 };
	uint32_t compression{ 0 };
	uint32_t size_image{ 0 };
	int32_t x_pixel_per_meter{ 0 };
	int32_t y_pixel_per_meter{ 0 };
	uint32_t colors_used{ 0 };
	uint32_t colors_important{ 0 };
};

struct BMPColorHeader {
	uint32_t red_mask{ 0x00ff0000 };
	uint32_t green_mask{ 0x0000ff00 };
	uint32_t blue_mask{ 0x000000ff };
	uint32_t alpha_mask{ 0xff000000 };
	uint32_t color_space_type{ 0x73524742 };
	uint32_t unused[16]{ 0 };
};

struct BMP {
	BMPFileHeader file_header;
	BMPInfoHeader bmp_info_header;
	BMPColorHeader bmp_color_header;
	std::vector<uint8_t> data;

	BMP(const char* fname) {
		read(fname);
	}

	void read(const char* fname) {
		std::ifstream inp{ fname, std::ios_base::binary };
		if (inp) {
			inp.read((char*)&file_header, sizeof(file_header));
			if (file_header.file_type != 0x4D42) {

			}
			inp.read((char*)&bmp_info_header, sizeof(bmp_info_header));

			if (bmp_info_header.bit_count == 32) {
				if (bmp_info_header.size >= (sizeof(BMPInfoHeader) + sizeof(BMPColorHeader))) {
					inp.read((char*)&bmp_color_header, sizeof(bmp_color_header));
					check_color_header(bmp_color_header);
				}
				else {

				}
			}
			inp.seekg(file_header.offset_data, inp.beg);
			
			if (bmp_info_header.bit_count == 32) {
				bmp_info_header.size = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
				file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
			}
			else {
				bmp_info_header.size = sizeof(BMPInfoHeader);
				file_header.offset_data = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);
			}
			file_header.file_size = file_header.offset_data;
			
			if (bmp_info_header.height < 0) {

			}
			
			data.resize(bmp_info_header.width * bmp_info_header.height * bmp_info_header.bit_count / 8);
			
			if (bmp_info_header.width % 4 == 0) {
				inp.read((char*)data.data(), data.size());
				file_header.file_size += data.size();
			}
			else {
				row_stride = bmp_info_header.width * bmp_info_header.bit_count / 8;
				uint32_t new_stride = make_stride_aligned(4);
				std::vector<uint8_t> padding_row(new_stride - row_stride);
				
				for (int y = 0; y < bmp_info_header.height; ++y) {
					inp.read((char*)(data.data() + row_stride * y), row_stride);
					inp.read((char*)padding_row.data(), padding_row.size());
				}
				file_header.file_size += data.size() + bmp_info_header.height * padding_row.size();
			}
		}
		else {

		}
	}

	BMP(int32_t width, int32_t height, bool has_alpha = true) {

	}

	void write(const char* fname) {

	}

private:
	uint32_t row_stride{ 0 };

	void check_color_header(BMPColorHeader & bmp_color_header) {
		BMPColorHeader expected_color_header;
		if (expected_color_header.red_mask != bmp_color_header.red_mask || expected_color_header.blue_mask != bmp_color_header.blue_mask || expected_color_header.green_mask != bmp_color_header.green_mask || expected_color_header.alpha_mask != bmp_color_header.alpha_mask) {

		}
		if (expected_color_header.color_space_type != bmp_color_header.color_space_type) {

		}
	}

	uint32_t make_stride_aligned(uint32_t align_stride) {
		uint32_t new_stride = row_stride;
		while (new_stride % align_stride != 0) {
			new_stride++;
		}
		return new_stride;
	}
};

std::vector <pixel*> bitmapread(std::string filepath) {

	//best Documentation for bitmaps: https://en.wikipedia.org/wiki/BMP_file_format
	unsigned char Headder_uchar[14];
	FILE* f;
	fopen_s(&f, filepath.c_str(), "rb");
	fread(Headder_uchar, sizeof(unsigned char), 14, f);

	unsigned char filesize_uchar[4];
	unsigned char offsetdata[4];

	filesize_uchar[3] = Headder_uchar[3 + 2];
	filesize_uchar[2] = Headder_uchar[2 + 2];
	filesize_uchar[1] = Headder_uchar[1 + 2];
	filesize_uchar[0] = Headder_uchar[0 + 2]; //easy to make into Loop

	offsetdata[3] = Headder_uchar[3 + 10];
	offsetdata[2] = Headder_uchar[2 + 10];
	offsetdata[1] = Headder_uchar[1 + 10];
	offsetdata[0] = Headder_uchar[0 + 10]; //easy to make into Loop

	int offset_int = (int)offsetdata[3] + (int)offsetdata[2] + (int)offsetdata[1] + (int)offsetdata[0];
	int size_int = (int)filesize_uchar[3] + (int)filesize_uchar[2] + (int)filesize_uchar[1] + (int)filesize_uchar[0];

	int infoheadder_size = offset_int - 14;

	rewind(f);

	//this uses specifically the Test.bmp file
	//this file uses BITMAPINFOHEADDER 
	unsigned char whole_file[198]; //need some way of having adaptive size for it
	fread(whole_file, sizeof(unsigned char), size_int, f);

	unsigned char sizeofDIB_uchar[4];

	sizeofDIB_uchar[0] = whole_file[14 + 0];
	sizeofDIB_uchar[1] = whole_file[14 + 1];
	sizeofDIB_uchar[2] = whole_file[14 + 2];
	sizeofDIB_uchar[3] = whole_file[14 + 3];

	int sizeofDIB_int = (int)sizeofDIB_uchar[0] + (int)sizeofDIB_uchar[1] + (int)sizeofDIB_uchar[2] + (int)sizeofDIB_uchar[3];

	unsigned char width_uchar[4];
	unsigned char height_uchar[4];

	width_uchar[0] = whole_file[14 + 4 + 0];
	width_uchar[1] = whole_file[14 + 4 + 1];
	width_uchar[2] = whole_file[14 + 4 + 2];
	width_uchar[3] = whole_file[14 + 4 + 3];

	height_uchar[0] = whole_file[14 + 8 + 0];
	height_uchar[1] = whole_file[14 + 8 + 1];
	height_uchar[2] = whole_file[14 + 8 + 2];
	height_uchar[3] = whole_file[14 + 8 + 3];

	int width_int = (int)width_uchar[0] + (int)width_uchar[1] + (int)width_uchar[2] + (int)width_uchar[3];
	int height_int = (int)height_uchar[0] + (int)height_uchar[1] + (int)height_uchar[2] + (int)height_uchar[3];

	unsigned char btspix[2];

	btspix[0] = whole_file[14 + 14 + 0];
	btspix[1] = whole_file[14 + 14 + 1];

	int btspix_int = (int)btspix[0] + (int)btspix[1]; //is the colour depth of the image

	unsigned char compression_uchar[4];

	compression_uchar[0] = whole_file[14 + 16 + 0];
	compression_uchar[1] = whole_file[14 + 16 + 1];
	compression_uchar[2] = whole_file[14 + 16 + 2];
	compression_uchar[3] = whole_file[14 + 16 + 3];

	int compression_int = (int)compression_uchar[0] + (int)compression_uchar[1] + (int)compression_uchar[2] + (int)compression_uchar[3];
	
	int rowsize = ((btspix_int * width_int) / 32) * 4;
	if (height_int < 0) {
		height_int *= (-1);
	}
	int PixelArraySize = rowsize * height_int;
	//Do something for padding

	std::vector <pixel*> pix; //This ONLY works for Test.bmp
	switch (compression_int) {
	case 0: //BI_RGB
		int start = 14 + sizeofDIB_int;
		unsigned char rgb[3][4]; //since i know it is 4 colours for this image
		int x_int{ 0 };
		int y_int{ 0 };

		int j{ 0 };
		for (int i = start; i < offset_int; i += 4) {
			rgb[2][j] = whole_file[i + 0];
			rgb[1][j] = whole_file[i + 1];
			rgb[0][j] = whole_file[i + 2];
			j++;
		}

		for (int i = offset_int; i < size_int; i++) {
			if ((int)whole_file[i] == 1) {
				pix.push_back(new pixel(colour((int)rgb[0][2], (int)rgb[1][2], (int)rgb[2][2], 255), x_int, y_int));
				x_int++;
				if (x_int >= width_int) {
					x_int = 0;
					y_int++;
				}
				pix.push_back(new pixel(colour((int)rgb[0][3], (int)rgb[1][3], (int)rgb[2][3], 255), x_int, y_int));
				x_int++;
				if (x_int >= width_int) {
					x_int = 0;
					y_int++;
				}
			}
			if ((int)whole_file[i] == 35) {
				pix.push_back(new pixel(colour((int)rgb[0][0], (int)rgb[1][0], (int)rgb[2][0], 255), x_int, y_int));
				x_int++;
				if (x_int >= width_int) {
					x_int = 0;
					y_int++;
				}
				pix.push_back(new pixel(colour((int)rgb[0][1], (int)rgb[1][1], (int)rgb[2][1], 255), x_int, y_int));
				x_int++;
				if (x_int >= width_int) {
					x_int = 0;
					y_int++;
				}
			}

		}
		break;
	}
	return pix;
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
	for (int i = period; i < filepath.length(); i++) {
		filetype += filepath[i];
	}
	if (filetype == ".bmp") {
		pixels = bitmapread(filepath);
	}
	for (int i = 0; i < pixels.size(); i++) {
		pixels[i]->move(pixels[i]->get_x() + loc[0] - size/2, pixels[i]->get_y() + loc[1] - size / 2);
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