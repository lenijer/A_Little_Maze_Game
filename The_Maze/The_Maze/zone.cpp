#include "zone.h"
#include "Basic/images.h"
#include "Basic/pixel.h"
#include "Basic/colour.h"

images* blend_images(images* i1, images* i2) {
    std::vector <pixel*> pix_arr;
    int r1, g1, b1, r2, b2, g2, a;
    float r, g, b;
    for (int k = 0; k < i1->Vector_Length(); k++) {
        r1 = i1->GetPixel(k).GetColour().GetRed();
        g1 = i1->GetPixel(k).GetColour().GetGreen();
        b1 = i1->GetPixel(k).GetColour().GetBlue();
        a = i1->GetPixel(k).GetColour().GetAlpha();

        r2 = i2->GetPixel(i1->GetPixel(k).get_x(), i1->GetPixel(k).get_y()).GetColour().GetRed();
        g2 = i2->GetPixel(i1->GetPixel(k).get_x(), i1->GetPixel(k).get_y()).GetColour().GetGreen();
        b2 = i2->GetPixel(i1->GetPixel(k).get_x(), i1->GetPixel(k).get_y()).GetColour().GetBlue();

        r = r1 * ((float)a / 255) + r2 * ((255 - (float)a) / 255);
        g = g1 * ((float)a / 255) + g2 * ((255 - (float)a) / 255);
        b = b1 * ((float)a / 255) + b2 * ((255 - (float)a) / 255);

        colour c = colour((int)r, (int)g, (int)b, 255);
        pixel* p = new pixel(c, i1->GetPixel(k).get_x(), i1->GetPixel(k).get_y());
        pix_arr.push_back(p);
    }
    return new images(pix_arr);
}

zone::zone(int top, int bottom, int left, int right)
{
	area[2] = top; //y_0
	area[3] = bottom; //y_1
	area[0] = right; //x_0
	area[1] = left; //x_1
}

void zone::addObject(Object* Object)
{
    O.push_back(Object);
}

void zone::addPlayer(Object* Player)
{
	O.push_back(Player);
}

void zone::Remove_Player()
{
	O.pop_back();
}

void zone::Draw(HDC hdc)
{
    Object* tmp;
    std::vector <Object*> obj;
    bool weird = false;

    for (int i = 0; i < O.size(); i++) {
        tmp = O[i];
        if (obj.size() > 0) {
            for (int j = 0; j < obj.size(); j++) {
                if (tmp->x() == obj[j]->x() && tmp->y() == obj[j]->y()) {
                    weird = true;
                    if (tmp->layer > obj[j]->layer) {
                        if (tmp->image()->HasTransparentPixels()) {
                            tmp->add_temp_image(blend_images(tmp->image(), obj[j]->image()));
                        }
                        obj[j] = tmp;
                    }
                    else
                    {
                        if (obj[j]->image()->HasTransparentPixels()) {
                            obj[j]->add_temp_image(blend_images(obj[j]->image(), tmp->image()));
                        }
                    }
                }
            }
        }
        if (!weird) {
            obj.push_back(tmp);
        }
        weird = false;
    }
    for (int i = 0; i < obj.size(); i++) {
        obj[i]->draw_Object(hdc);
    }
}

void zone::Delete()
{
    O.clear();
}

bool zone::Is_in_zone(Object* Checker)
{
	if ((Checker->x() >= area[0] && Checker->x() < area[1]) && (Checker->y() >= area[2] && Checker->y() < area[3])) {
		return true;
	}
	return false;
}

const bool zone::Has_Max_Objects(int max_objects)
{
    if (O.size() >= max_objects) {
        return true;
    }
    return false;
}

bool zone::find_Player(Object* Player)
{
    for (int i = 0; i < O.size(); i++) {
        if (O[i] == Player) {
            return true;
        }
    }
    return false;
}
