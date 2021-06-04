#include <stdio.h>

#include "Scene.h"
#include "TitleScene.h"

CScene* scene;

void init() {

	scene = new CTitleScene();


}

int main() {

	init();

	return 0;
}