#pragma once


#include "BaseObject.h"

class CScene :CBaseObject {

private:

	virtual void update() = 0;
	virtual void render() = 0;

public:



};