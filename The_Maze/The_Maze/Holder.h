#pragma once
#include <vector>
#include "Player.h"

struct Holder {
	Player* PL;

	const std::vector <Object*> ReadObjects() {
		return O;
	}

	Object* ReadObject(int index) {
		return O[index];
	}

	void FillObjects(std::vector<Object*> ObjectsVector){
		O = ObjectsVector;
	}
private:
	std::vector<Object*> O;
};