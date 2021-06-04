#pragma once

#include "Character.h"

class CUser : CCharacter {

public:

	virtual void update() = 0;
	virtual void render() = 0;

private:

};