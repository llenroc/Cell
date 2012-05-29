/*
 *  SceneManager.h
 *  cell
 *
 *  Created by James Alliban on 16/08/2011.
 *  Copyright 2011 Augmatic. All rights reserved.
 *
 */

#ifndef _SCENE_MANAGER
#define _SCENE_MANAGER

#include "ofMain.h"
#include "CloudTagManager.h"
#include "Grid.h"
#include "LightManager.h"
#include "UserManager.h"
#include "FieldManager.h"

class SceneManager
{
public:
	SceneManager();
	~SceneManager();

	void init();
	void update();
	void draw();
	void setupViewports();
	void keyPressed(int key);

	CloudTagManager			cloudTagMan;

	FieldManager            fieldMan;

	// 3D
	ofEasyCam				camEasyCam;
	ofRectangle				viewPort;
	Grid					nodeGrid;

    // texturing
	LightManager light;
	ofShader shader;

	// user
	UserManager userManager;

	// camera properties
	float camX, camY, camZ;
	float camDirectionX, camDirectionY, camDirectionZ;
	float smoothMouseX, smoothMouseY, mouseSmoothAmount;
	float camRotX, camRotY, camRotZ;

	bool isCamMouseInput;		// allows the camera to be controlled by the mouse
	bool isCamMouseInputPaused; // pauses camera movement while it is controllable by the mouse
	bool isUpdateVars;			// toggle - updates all variables that do not require rebuilding objects


protected:

};


#endif
