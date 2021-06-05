#pragma once

#include "Scene.h"

class CTitleScene : CScene {

public:

	virtual void init();
	virtual void update() ;
	virtual void render() ;

	CTitleScene();

private:

	int menuIdx;

};