#pragma once

#include "Scene.h"

extern CScene* nextScene;

class CTitleScene : CScene {

public:

	virtual void init();
	virtual void update() ;
	virtual void render() ;

	CTitleScene();

private:

	int _menuIdx;

};