#include "pch.h"
#include "backend.h"

player::player() {
	points = 0;
	p_rem = 0;
	hp = 3;
	finished = 0;
}

void player::decHP() {
	this->hp -= 1;
}