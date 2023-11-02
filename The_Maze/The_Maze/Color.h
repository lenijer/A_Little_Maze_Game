#pragma once
class Color
{
public:
	Color() {};
	Color(int red, int green, int blue) { rgba[0] = red; rgba[1] = blue; rgba[2] = green; rgba[3] = 255; }
	Color(int red, int green, int blue, int alpha) { rgba[0] = red; rgba[1] = blue; rgba[2] = green; rgba[3] = alpha; }
	~Color() {};
private:
	int rgba[4];
};

