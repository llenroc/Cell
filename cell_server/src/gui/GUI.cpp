//
//  gui->cpp
//  emptyExample
//
//  Created by James Alliban on 25/06/2013.
//
//

#include "GUI.h"
#include "SceneManager.h"
#include "Field.h"
#include "testApp.h"


void GUI::setup()
{
    app = (testApp*)ofGetAppPtr();
    GUIManager::setup();
    
    dim = 8;

	skelOffsetRange = 500;
    
    addKeyboardShortcutsGUI();
    addCameraGUI();
    addTagShaderGUI();
    addLineAppearanceGUI();
    addTagAnimationGUI();
    addTagBoundariesGUI();
    addMotionFields1GUI();
    addMotionFields2GUI();
    addColourFieldsGUI();
    addKinectGlobalGUI();
    addKinectCalibration0and1GlobalGUI();
    addKinectCalibration2and3GlobalGUI();
//    addDuplicatesGUI();
    addKinectUserDegugGUI();
    addVariousGUI();
    
    setGUIColour();
}


bool GUI::getVisible()
{
    return GUIManager::getVisible();
}

void GUI::addKeyboardShortcutsGUI()
{
    string title = "KEYBOARD SHORTCUTS";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("KEY", OFX_UI_FONT_MEDIUM);
    gui->addLabel("SPACE - SHOW/HIDE GUI", OFX_UI_FONT_SMALL);
    gui->addLabel("'[' - PREVIOUS GUI", OFX_UI_FONT_SMALL);
    gui->addLabel("']' - NEXT GUI", OFX_UI_FONT_SMALL);
    gui->addLabel("'0-9' - GO TO GUI PAGE", OFX_UI_FONT_SMALL);
    gui->addLabel("'g' - TOGGLE GRID VISIBLE", OFX_UI_FONT_SMALL);
    gui->addLabel("'a' - TOGGLE FIELD LINES VISIBLE", OFX_UI_FONT_SMALL);
    gui->addLabel("'m' - MAIN CAMERA POSITION", OFX_UI_FONT_SMALL);
    gui->addLabel("'p' - PAUSE FREE CAM", OFX_UI_FONT_SMALL);
    gui->addLabel("'u' - UPDATE VARS - REFRESH CLOUD", OFX_UI_FONT_SMALL);
    gui->addLabel("'f' - TOGGLE FULLSCREEN ", OFX_UI_FONT_SMALL);
    gui->addLabel("'t' - TOGGLE TAG VISIBILITY", OFX_UI_FONT_SMALL);
    gui->addLabel("'l' - TOGGLE LINE VISIBILITY", OFX_UI_FONT_SMALL);
    gui->addLabel("'z' - CLEAR CLIENT SKELETONS", OFX_UI_FONT_SMALL);
    gui->addLabel("'o' - PAUSE DEBUG SKELETON", OFX_UI_FONT_SMALL);
    gui->addLabel("'z' - CLEAR CLIENT SKELETONS", OFX_UI_FONT_SMALL);
    gui->addLabel("'R' - RECORD SKELETONS", OFX_UI_FONT_SMALL);
    gui->addLabel("'S' - STOP SKELETON RECORDING", OFX_UI_FONT_SMALL);
    gui->addLabel("'E' - EXPORT SKELETON RECORDING", OFX_UI_FONT_SMALL);
    gui->addLabel("'P' - PLAYBACK LAST SKELETON RECORDING", OFX_UI_FONT_SMALL);
//    gui->addLabel("'p' - PAUSE CLIENTS", OFX_UI_FONT_SMALL);
//    gui->addLabel("'x' - CLOSE CLIENTS", OFX_UI_FONT_SMALL);
    
    gui->addLabel("GRID");
    gui->addToggle("GRID VISIBLE", &app->sceneManager.isGridVisible, toggleDim, toggleDim);
    gui->addSlider("GRID ALPHA", 0, 255, &app->sceneManager.gridAlpha, length, dim);
    
    gui->addLabel("GUI DESIGN");
    gui->addSlider("RED", 0, 255, 255, length, dim);
    gui->addSlider("GREEN", 0, 255, 1, length, dim);
    gui->addSlider("BLUE", 0, 255, 1, length, dim);
    gui->addSlider("ALPHA", 0, 255, 255, length, dim);
    
    gui->addLabel("GUI DESIGN");
    gui->addSlider("height", 1, 200, &app->topBlockHeight, length, dim);
    gui->addSlider("bottom", 1, 200, &app->topBlockBot, length, dim);
    gui->addSlider("left", 1, 100, &app->leftBlockW, length, dim);
    gui->addSlider("right", 1, 100, &app->rightBlockW, length, dim);
    
	ofAddListener(gui->newGUIEvent, this, &GUI::variousGUIEvent);
    finaliseCanvas(gui, true);
}



void GUI::addCameraGUI()
{
    string title = "CAMERA";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("POSITION/ROTATION", OFX_UI_FONT_MEDIUM);
    gui->addSlider("X", -150, 150, &app->sceneManager.camX, length, dim);
    gui->addSlider("Y", -150, 150, &app->sceneManager.camY, length, dim);
    gui->addSlider("Z", -150, 150, &app->sceneManager.camZ, length, dim);
	gui->addSlider("Distance Multiplier", 0, 5, &app->sceneManager.camDistanceMultiplier, length, dim);
    gui->addSlider("LookAt node X", -50, 50, &app->sceneManager.camDirectionX, length, dim);
    gui->addSlider("LookAt node Y", -50, 50, &app->sceneManager.camDirectionY, length, dim);
    gui->addSlider("LookAt node Z", -50, 50, &app->sceneManager.camDirectionZ, length, dim);
    gui->addSlider("FOV", 0, 50, &app->sceneManager.fov, length, dim);
    gui->addLabel("MOUSE", OFX_UI_FONT_SMALL);
    gui->addToggle("Toggle mouse input", &app->sceneManager.isCamMouseInput, toggleDim, toggleDim);
    gui->addSlider("Mouse input smooth", 0.01, 0.3, &app->sceneManager.mouseSmoothAmount, length, dim);
    
    finaliseCanvas(gui, true);
}


void GUI::addTagShaderGUI()
{
    string title = "TAG SHADER";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addSlider("Contrast min", -1.0, 1.0, &app->sceneManager.cloudTagMan.shadeContrastMin, length, dim);
    gui->addSlider("Contrast max", -1.0, 1.0, &app->sceneManager.cloudTagMan.shadeContrastMax, length, dim);
    gui->addSlider("Brightness min", -1.0, 1.0, &app->sceneManager.cloudTagMan.shadeBrightnessMin, length, dim);
    gui->addSlider("Brightness max", -1.0, 1.0, &app->sceneManager.cloudTagMan.shadeBrightnessMax, length, dim);
    gui->addSlider("Alpha min", 0.0, 1.0, &app->sceneManager.cloudTagMan.shadeAlphaMin, length, dim);
    gui->addSlider("Alpha max", 0.0, 1.0, &app->sceneManager.cloudTagMan.shadeAlphaMax, length, dim);
    gui->addSlider("Blend mix", 0.0, 1.0, &app->sceneManager.cloudTagMan.shadeBlendMix, length, dim);
    gui->addSlider("Blend mode", 0, 10, &app->sceneManager.cloudTagMan.shadeBlendMode, length, dim);
    //gui->addToggle("Apply", &app->sceneManager.isUpdateVars, toggleDim, toggleDim);
    gui->addWidgetDown(new ofxUILabelButton(false, "Apply"));
    
    
//	ofAddListener(gui->newGUIEvent, this, &GUI::addTagShaderGUIEvent);
    finaliseCanvas(gui, true);
}

void GUI::addTagShaderGUIEvent(ofxUIEventArgs &e){
	if (e.widget->getName() == "Apply")	SceneManager::isUpdateVars = true;
}


void GUI::addLineAppearanceGUI()
{
    string title = "LINE APPEARANCE";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addToggle("Lines enabled", &app->sceneManager.cloudTagMan.areLinesEnabled, toggleDim, toggleDim);
    gui->addLabel("SHADER", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Line Contrast min", -1.0, 1.0, &app->sceneManager.cloudTagMan.lineContrastMin, length, dim);
    gui->addSlider("Line Contrast max", -1.0, 1.0, &app->sceneManager.cloudTagMan.lineContrastMax, length, dim);
    gui->addSlider("Line Brightness min", -1.0, 1.0, &app->sceneManager.cloudTagMan.lineBrightnessMin, length, dim);
    gui->addSlider("Line Brightness max", -1.0, 1.0, &app->sceneManager.cloudTagMan.lineBrightnessMax, length, dim);
    gui->addSlider("Line Alpha min", -1.0, 1.0, &app->sceneManager.cloudTagMan.lineAlphaMin, length, dim);
    gui->addSlider("Line Alpha max", -1.0, 1.0, &app->sceneManager.cloudTagMan.lineAlphaMax, length, dim);
    gui->addLabel("PROPS", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Line Length Squared Min", 500.0, 10000.0, &app->sceneManager.cloudTagMan.lineLengthSquaredMin, length, dim);
    gui->addSlider("Map Line Distance Min", 500, 10000.0, &app->sceneManager.cloudTagMan.mapLineDistanceMin, length, dim);
    gui->addSlider("Map Line Distance Max", 500, 10000.0, &app->sceneManager.cloudTagMan.mapLineDistanceMax, length, dim);
    gui->addSlider("Map Z Area Min", -100, 10.0, &app->sceneManager.cloudTagMan.lineZAreaMin, length, dim);
    gui->addSlider("Map Z Area Max", 10, 100.0, &app->sceneManager.cloudTagMan.lineZAreaMax, length, dim);
    gui->addSlider("Line Thickness", 0.0, 10.0, &app->sceneManager.cloudTagMan.lineThickness, length, dim);
    gui->addLabel("LINE ANIMATION", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Init line fade", 0.0, 5.0, &app->sceneManager.cloudTagMan.lineFadeTime, length, dim);
    
    finaliseCanvas(gui, true);
}


void GUI::addTagAnimationGUI()
{
    string title = "TAG ANIMATION";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addToggle("Tags enabled", &app->sceneManager.cloudTagMan.areTagsEnabled, toggleDim, toggleDim);
    gui->addLabel("DEFAULT ANIMATION", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Perlin Input offset multiplier", 0.0000, 10, &app->sceneManager.cloudTagMan.perlinInputOffsetMultiplier, length, dim);
    gui->addSlider("Speed", 0.0001, 0.05, &app->sceneManager.cloudTagMan.speed, length, dim);
    gui->addSlider("Frame multiplier", 0.00001, 0.01, &app->sceneManager.cloudTagMan.frameMultiplier, length, dim);
    gui->addSlider("Noise multiplier", 0.001, 0.5, &app->sceneManager.cloudTagMan.noiseMultiplier, length, dim);
    
    gui->addLabel("BOUNDARIES", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Out of Bounds Angle Add", 0.001, 1, &app->sceneManager.cloudTagMan.angleAdd, length, dim);
    gui->addSlider("Out of Bounds Pos Add Max", 0.001, 1, &app->sceneManager.cloudTagMan.outOfBoundsPosAddMax, length, dim);
    gui->addSlider("Out of Bounds Pos Add Min", 0.0001, 0.01, &app->sceneManager.cloudTagMan.outOfBoundsPosAddMin, length, dim);
    gui->addSlider("Out of Bounds Pos Add Decay", 1, 5, &app->sceneManager.cloudTagMan.outOfBoundsPosAddDecay, length, dim);

    gui->addLabel("TAG ATTRACTION ANIMATION", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Attraction speed Min", 0.00001, 0.1, &app->sceneManager.cloudTagMan.attractionSpeedMin, length, dim);
    gui->addSlider("Attraction speed Max", 0.5, 0.99, &app->sceneManager.cloudTagMan.attractionSpeedMax, length, dim);
    gui->addSlider("Attraction speed Pow", 1, 30, &app->sceneManager.cloudTagMan.attractionSpeedPow, length, dim);
    
    gui->addLabel("SCALING TO Y POS", OFX_UI_FONT_MEDIUM);
    gui->addToggle("y Scale Only On Attraction", &app->sceneManager.cloudTagMan.yScaleOnlyOnAttraction, toggleDim, toggleDim);
    gui->addSlider("Y Min", 0, 20, &app->sceneManager.cloudTagMan.yMin, length, dim);
    gui->addSlider("Y Max", 10, 60, &app->sceneManager.cloudTagMan.yMax, length, dim);
    gui->addSlider("Scale Min", 0.01, 1, &app->sceneManager.cloudTagMan.scaleMin, length, dim);
    gui->addSlider("Scale Max", 0.01, 2, &app->sceneManager.cloudTagMan.scaleMax, length, dim);
    gui->addWidgetDown(new ofxUILabelButton(false, "Apply"));
    
	ofAddListener(gui->newGUIEvent, this, &GUI::variousGUIEvent);
    finaliseCanvas(gui, true);
}

void GUI::addTagAnimationGUIEvent(ofxUIEventArgs &e){
	if (e.widget->getName() == "Apply")	SceneManager::isUpdateVars = true;
}


void GUI::addTagBoundariesGUI()
{
    string title = "TAG BOUNDARIES";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addSlider("Boundary Width", 0.30, 500.0, &app->sceneManager.cloudTagMan.boundaryW, length, dim);
    gui->addSlider("Boundary Width Front", 0.30, 500.0, &app->sceneManager.cloudTagMan.boundaryWFront, length, dim);
    gui->addSlider("Boundary Depth", 0.30, 500.0, &app->sceneManager.cloudTagMan.boundaryD, length, dim);
    gui->addSlider("Boundary Height", 0.30, 100.0, &app->sceneManager.cloudTagMan.boundaryH, length, dim);
    gui->addLabel("HEIGHT OFFSET", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Boundary Centre Height", 0.0, 100.0, &app->sceneManager.cloudTagMan.boundaryCentreH, length, dim);
    
    finaliseCanvas(gui, true);
}




void GUI::addMotionFields1GUI()
{
    string title = "MOTION FIELDS 1";
    ofxUICanvas* gui = getNewGUI(title);
    
    
    gui->addLabel("GLOBAL", OFX_UI_FONT_MEDIUM);
    gui->addToggle("Enabled all", &Field::isAllEnabled, toggleDim, toggleDim);
    gui->addToggle("Field Lines Visible", &app->sceneManager.fieldMan.isFieldLineVisible, toggleDim, toggleDim);
    gui->addSlider("Frame Multiplier", 0.0, 1.0, &app->sceneManager.fieldMan.fieldEnergy.frameMultiplier, length, dim);
    gui->addSlider("Noise Multiplier", 0.0, 1.0, &app->sceneManager.fieldMan.fieldEnergy.noiseMultiplier, length, dim);
    
    gui->addLabel("ENERGY FIELD - RED", OFX_UI_FONT_MEDIUM);
    gui->addToggle("Enabled energy", &app->sceneManager.fieldMan.fieldEnergy.isEnabled, toggleDim, toggleDim);
    gui->addSlider("Play Area energy", 20, 150.0, &app->sceneManager.fieldMan.fieldEnergy.playArea, length, dim);
    gui->addSlider("Speed energy", 0.01, 0.1, &app->sceneManager.fieldMan.fieldEnergy.movementSpeed, length, dim);
    gui->addSlider("Radius energy", 100, 500.0, &app->sceneManager.fieldMan.fieldEnergy.lengthSquaredMin, length, dim);
    
    gui->addLabel("REPEL FIELD - GREEN", OFX_UI_FONT_MEDIUM);
    gui->addToggle("Enabled repel", &app->sceneManager.fieldMan.fieldRepel.isEnabled, toggleDim, toggleDim);
    gui->addSlider("Play Area repel", 20, 150.0, &app->sceneManager.fieldMan.fieldRepel.playArea, length, dim);
    gui->addSlider("Speed repel", 0.01, 0.1, &app->sceneManager.fieldMan.fieldRepel.movementSpeed, length, dim);
    gui->addSlider("Radius repel", 100, 500.0, &app->sceneManager.fieldMan.fieldRepel.lengthSquaredMin, length, dim);
    gui->addSlider("Strength repel", 0.001, 0.03, &app->sceneManager.fieldMan.fieldRepel.repelStrength, length, dim);
    
    gui->addLabel("SCALE UP FIELD - YELLOW", OFX_UI_FONT_MEDIUM);
    gui->addToggle("Enabled scale", &app->sceneManager.fieldMan.fieldScaleUp.isEnabled, toggleDim, toggleDim);
    gui->addSlider("Play Area", 20, 150.0, &app->sceneManager.fieldMan.fieldScaleUp.playArea, length, dim);
    gui->addSlider("Speed", 0.01, 0.1, &app->sceneManager.fieldMan.fieldScaleUp.movementSpeed, length, dim);
    gui->addSlider("Area size", 100, 500.0, &app->sceneManager.fieldMan.fieldScaleUp.lengthSquaredMin, length, dim);
    gui->addSlider("Scale Strength", 0.5, 3.0, &app->sceneManager.fieldMan.fieldScaleUp.scaleUpStrength, length, dim);
    
    finaliseCanvas(gui, true);
}



void GUI::addMotionFields2GUI()
{
    string title = "MOTION FIELDS 2";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("HEIGHT DOWN FIELD - BLUE", OFX_UI_FONT_MEDIUM);
    gui->addToggle("Enabled yd", &app->sceneManager.fieldMan.fieldHeightDown.isEnabled, toggleDim, toggleDim);
    gui->addSlider("Play Area yd", 20, 150.0, &app->sceneManager.fieldMan.fieldHeightDown.playArea, length, dim);
    gui->addSlider("Speed yd", 0.01, 0.1, &app->sceneManager.fieldMan.fieldHeightDown.movementSpeed, length, dim);
    gui->addSlider("Area size yd", 100, 500.0, &app->sceneManager.fieldMan.fieldHeightDown.lengthSquaredMin, length, dim);
    gui->addSlider("Height Adjust yd", 0.001, 0.5, &app->sceneManager.fieldMan.fieldHeightDown.heightAdjust, length, dim);
    
    gui->addLabel("HEIGHT UP FIELD - PINK", OFX_UI_FONT_MEDIUM);
    gui->addToggle("Enabled yu", &app->sceneManager.fieldMan.fieldHeightUp.isEnabled, toggleDim, toggleDim);
    gui->addSlider("Play Area yu", 20, 150.0, &app->sceneManager.fieldMan.fieldHeightUp.playArea, length, dim);
    gui->addSlider("Speed yu", 0.01, 0.1, &app->sceneManager.fieldMan.fieldHeightUp.movementSpeed, length, dim);
    gui->addSlider("Area size yu", 100, 500.0, &app->sceneManager.fieldMan.fieldHeightUp.lengthSquaredMin, length, dim);
    gui->addSlider("Height Adjust yu", 0.001, 0.5, &app->sceneManager.fieldMan.fieldHeightUp.heightAdjust, length, dim);

    finaliseCanvas(gui, true);
}



void GUI::addColourFieldsGUI()
{
    string title = "COLOUR FIELDS";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("COLOUR 1 FIELD - DOUBLE RED", OFX_UI_FONT_MEDIUM);
    gui->addToggle("Enabled 1", &app->sceneManager.fieldMan.fieldColour1.isEnabled, toggleDim, toggleDim);
    gui->addSlider("Play Area 1", 20, 150.0, &app->sceneManager.fieldMan.fieldColour1.playArea, length, dim);
    gui->addSlider("Speed 1", 0.01, 0.1, &app->sceneManager.fieldMan.fieldColour1.movementSpeed, length, dim);
    gui->addSlider("Area size 1", 100, 1000.0, &app->sceneManager.fieldMan.fieldColour1.lengthSquaredMin, length, dim);
    gui->addSlider("Colours 1 Red", 0, 1, &app->sceneManager.fieldMan.fieldColour1.colours[0], length, dim);
    gui->addSlider("Colours 1 Green", 0, 1, &app->sceneManager.fieldMan.fieldColour1.colours[1], length, dim);
    gui->addSlider("Colours 1 Blue", 0, 1, &app->sceneManager.fieldMan.fieldColour1.colours[2], length, dim);
    
    gui->addLabel("COLOUR 2 FIELD - DOUBLE GREEN", OFX_UI_FONT_MEDIUM);
    gui->addToggle("Enabled 2", &app->sceneManager.fieldMan.fieldColour2.isEnabled, toggleDim, toggleDim);
    gui->addSlider("Play Area 2", 20, 150.0, &app->sceneManager.fieldMan.fieldColour2.playArea, length, dim);
    gui->addSlider("Speed 2", 0.01, 0.1, &app->sceneManager.fieldMan.fieldColour2.movementSpeed, length, dim);
    gui->addSlider("Area size 2", 100, 1000.0, &app->sceneManager.fieldMan.fieldColour2.lengthSquaredMin, length, dim);
    gui->addSlider("Colours 2 Red", 0, 1, &app->sceneManager.fieldMan.fieldColour2.colours[0], length, dim);
    gui->addSlider("Colours 2 Green", 0, 1, &app->sceneManager.fieldMan.fieldColour2.colours[1], length, dim);
    gui->addSlider("Colours 2 Blue", 0, 1, &app->sceneManager.fieldMan.fieldColour2.colours[2], length, dim);
    
    gui->addLabel("COLOUR 3 FIELD - DOUBLE BLUE", OFX_UI_FONT_MEDIUM);
    gui->addToggle("Enabled 3", &app->sceneManager.fieldMan.fieldColour3.isEnabled, toggleDim, toggleDim);
    gui->addSlider("Play Area 3", 20, 150.0, &app->sceneManager.fieldMan.fieldColour3.playArea, length, dim);
    gui->addSlider("Speed 3", 0.01, 0.1, &app->sceneManager.fieldMan.fieldColour3.movementSpeed, length, dim);
    gui->addSlider("Area size 3", 100, 1000.0, &app->sceneManager.fieldMan.fieldColour3.lengthSquaredMin, length, dim);
    gui->addSlider("Colours 3 Red", 0, 1, &app->sceneManager.fieldMan.fieldColour3.colours[0], length, dim);
    gui->addSlider("Colours 3 Green", 0, 1, &app->sceneManager.fieldMan.fieldColour3.colours[1], length, dim);
    gui->addSlider("Colours 3 Blue", 0, 1, &app->sceneManager.fieldMan.fieldColour3.colours[2], length, dim);
    
    finaliseCanvas(gui, true);
}



void GUI::addKinectGlobalGUI()
{
    string title = "KINECT GLOBAL";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("CALIBRATION", OFX_UI_FONT_MEDIUM);
    gui->addLabel("PERSPECTIVE OFFSET", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Range Min", -300, 0, &app->sceneManager.userManager.xCorrectionOffsetRangeMin, length, dim);
    gui->addSlider("Range Max", 0, 300, &app->sceneManager.userManager.xCorrectionOffsetRangeMax, length, dim);
    gui->addSlider("Offset Min", -350, 350, &app->sceneManager.userManager.xCorrectionOffsetMin, length, dim);
    gui->addSlider("Offset Max", -350, 350, &app->sceneManager.userManager.xCorrectionOffsetMax, length, dim);
    gui->addSlider("Offset Modifier", 0, 500, &app->sceneManager.userManager.xCorrectionOffsetModifier, length, dim);
	
    gui->addLabel("KINECT Z REDUCTION", OFX_UI_FONT_MEDIUM);
	gui->addSlider("Z Reduction Multiplier", 0, 0.02, &User::skeletonZReductionMultiplier, length, dim);
	
    gui->addLabel("KINECT Z SCALING FIX", OFX_UI_FONT_MEDIUM);
	gui->addSlider("Z Position input min", -300, 300, &User::zScaleFixMin, length, dim);
	gui->addSlider("Z Position input max", -300, 300, &User::zScaleFixMax, length, dim);
	gui->addSlider("Z Multiplier min", 0.01, 1, &User::zScaleFixMultMin, length, dim);
	gui->addSlider("Z Multiplier max", 0.01, 1, &User::zScaleFixMultMax, length, dim);
    
    finaliseCanvas(gui, true);
}



void GUI::addKinectCalibration0and1GlobalGUI()
{
    string title = "KINECT CALIBRATION 0 & 1";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("SKELETON CALIBRATION CLIENT 0", OFX_UI_FONT_MEDIUM);
    gui->addLabel("SCALE", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Scale (0)", 0.01, 0.5,&app->sceneManager.userManager.skeletonScale[0], length, dim);
    gui->addLabel("ROTATION", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Degrees (0)", -50, 50,&app->sceneManager.userManager.skeletonRotDegrees[0], length, dim);
    gui->addSlider("Rotation X (0)", 0.0, 1.0,&app->sceneManager.userManager.skeletonRotX[0], length, dim);
    gui->addSlider("Rotation Y (0)", 0.0, 1.0,&app->sceneManager.userManager.skeletonRotY[0], length, dim);
    gui->addSlider("Rotation Z (0)", 0.0, 1.0,&app->sceneManager.userManager.skeletonRotZ[0], length, dim);
    gui->addLabel("POSITION OFFSET", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Pos offset X (0)", -skelOffsetRange, skelOffsetRange,&app->sceneManager.userManager.skeletonPosOffsetX[0], length, dim);
    gui->addSlider("Pos offset Y (0)", -skelOffsetRange, skelOffsetRange,&app->sceneManager.userManager.skeletonPosOffsetY[0], length, dim);
    gui->addSlider("Pos offset Z (0)", -skelOffsetRange, skelOffsetRange,&app->sceneManager.userManager.skeletonPosOffsetZ[0], length, dim);
    
    gui->addLabel("SKELETON CALIBRATION CLIENT 1", OFX_UI_FONT_MEDIUM);
    gui->addLabel("SCALE", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Scale (1)", 0.01, 0.5,&app->sceneManager.userManager.skeletonScale[1], length, dim);
    gui->addLabel("ROTATION", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Degrees (1)", -50, 50,&app->sceneManager.userManager.skeletonRotDegrees[1], length, dim);
    gui->addSlider("Rotation X (1)", 0.0, 1.0,&app->sceneManager.userManager.skeletonRotX[1], length, dim);
    gui->addSlider("Rotation Y (1)", 0.0, 1.0,&app->sceneManager.userManager.skeletonRotY[1], length, dim);
    gui->addSlider("Rotation Z (1)", 0.0, 1.0,&app->sceneManager.userManager.skeletonRotZ[1], length, dim);
    gui->addLabel("POSITION OFFSET", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Pos offset X (1)", -skelOffsetRange, skelOffsetRange,&app->sceneManager.userManager.skeletonPosOffsetX[1], length, dim);
    gui->addSlider("Pos offset Y (1)", -skelOffsetRange, skelOffsetRange,&app->sceneManager.userManager.skeletonPosOffsetY[1], length, dim);
    gui->addSlider("Pos offset Z (1)", -skelOffsetRange, skelOffsetRange,&app->sceneManager.userManager.skeletonPosOffsetZ[1], length, dim);
    
    finaliseCanvas(gui, true);
}


void GUI::addKinectCalibration2and3GlobalGUI()
{
    string title = "KINECT CALIBRATION 2 & 3";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("SKELETON CALIBRATION CLIENT 2", OFX_UI_FONT_MEDIUM);
    gui->addLabel("SCALE", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Scale (2)", 0.01, 0.5,&app->sceneManager.userManager.skeletonScale[2], length, dim);
    gui->addLabel("ROTATION", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Degrees (2)", -50, 50,&app->sceneManager.userManager.skeletonRotDegrees[2], length, dim);
    gui->addSlider("Rotation X (2)", 0.0, 1.0,&app->sceneManager.userManager.skeletonRotX[2], length, dim);
    gui->addSlider("Rotation Y (2)", 0.0, 1.0,&app->sceneManager.userManager.skeletonRotY[2], length, dim);
    gui->addSlider("Rotation Z (2)", 0.0, 1.0,&app->sceneManager.userManager.skeletonRotZ[2], length, dim);
    gui->addLabel("POSITION OFFSET", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Pos offset X (2)", -skelOffsetRange, skelOffsetRange,&app->sceneManager.userManager.skeletonPosOffsetX[2], length, dim);
    gui->addSlider("Pos offset Y (2)", -skelOffsetRange, skelOffsetRange,&app->sceneManager.userManager.skeletonPosOffsetY[2], length, dim);
    gui->addSlider("Pos offset Z (2)", -skelOffsetRange, skelOffsetRange,&app->sceneManager.userManager.skeletonPosOffsetZ[2], length, dim);
    
    gui->addLabel("SKELETON CALIBRATION CLIENT 3", OFX_UI_FONT_MEDIUM);
    gui->addLabel("SCALE", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Scale (3)", 0.01, 0.5,&app->sceneManager.userManager.skeletonScale[3], length, dim);
    gui->addLabel("ROTATION", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Degrees (3)", -50, 50,&app->sceneManager.userManager.skeletonRotDegrees[3], length, dim);
    gui->addSlider("Rotation X (3)", 0.0, 1.0,&app->sceneManager.userManager.skeletonRotX[3], length, dim);
    gui->addSlider("Rotation Y (3)", 0.0, 1.0,&app->sceneManager.userManager.skeletonRotY[3], length, dim);
    gui->addSlider("Rotation Z (3)", 0.0, 1.0,&app->sceneManager.userManager.skeletonRotZ[3], length, dim);
    gui->addLabel("POSITION OFFSET", OFX_UI_FONT_MEDIUM);
    gui->addSlider("Pos offset X (3)", -skelOffsetRange, skelOffsetRange,&app->sceneManager.userManager.skeletonPosOffsetX[3], length, dim);
    gui->addSlider("Pos offset Y (3)", -skelOffsetRange, skelOffsetRange,&app->sceneManager.userManager.skeletonPosOffsetY[3], length, dim);
    gui->addSlider("Pos offset Z (3)", -skelOffsetRange, skelOffsetRange,&app->sceneManager.userManager.skeletonPosOffsetZ[3], length, dim);
    
    finaliseCanvas(gui, true);
}


void GUI::addKinectUserDegugGUI()
{
    string title = "KINECT USER DEBUG";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("USER", OFX_UI_FONT_MEDIUM);
    gui->addToggle("Pause User",&app->sceneManager.userManager.isNonKinectUserPaused, toggleDim, toggleDim);
    gui->addLabel("CLOUD", OFX_UI_FONT_MEDIUM);
    gui->addToggle("Pause Cloud Tag Attraction",&app->sceneManager.cloudTagMan.isTagAttractionPaused, toggleDim, toggleDim);
    
    gui->addLabel("DEBUG", OFX_UI_FONT_MEDIUM);
    gui->addToggle("Show Joint Spheres", &app->sceneManager.userManager.isJointSpheres, toggleDim, toggleDim);
    gui->addToggle("Show Joint Lines", &app->sceneManager.userManager.isJointLines, toggleDim, toggleDim);
    gui->addToggle("Show Joint Pos Data", &app->sceneManager.userManager.isPositionDataDisplayed, toggleDim, toggleDim);
    gui->addToggle("Show User Data", &app->sceneManager.userManager.isUserDataDisplayed, toggleDim, toggleDim);
    
    gui->addLabel("RECORDED", OFX_UI_FONT_MEDIUM);

	ofDirectory dir;
	dir.listDir("images/recorded/");
	dir.allowExt(".png");
	for (int i = 0; i < dir.size(); i++)
		gui->addWidgetDown(new ofxUILabelButton(false, dir.getPath(i)));
	
	gui->addSlider("Recorded image alpha", 0, 255, &app->kinectManager.recordedImageAlpha, length, dim);
    
    
	ofAddListener(gui->newGUIEvent, this, &GUI::addKinectUserDegugGUIEvent);

    finaliseCanvas(gui, true);
}


void GUI::addVariousGUI()
{
    string title = "VARIOUS";
    ofxUICanvas* gui = getNewGUI(title);
    
    gui->addLabel("GRID");
    gui->addToggle("GRID VISIBLE", &app->sceneManager.isGridVisible, toggleDim, toggleDim);
    gui->addSlider("GRID ALPHA", 0, 255, &app->sceneManager.gridAlpha, length, dim);
    
    gui->addLabel("GUI DESIGN");
    gui->addSlider("RED", 0, 255, 255, length, dim);
    gui->addSlider("GREEN", 0, 255, 1, length, dim);
    gui->addSlider("BLUE", 0, 255, 1, length, dim);
    gui->addSlider("ALPHA", 0, 255, 255, length, dim);
    
    gui->addLabel("GUI DESIGN");
    gui->addSlider("height", 1, 200, &app->topBlockHeight, length, dim);
    gui->addSlider("bottom", 1, 200, &app->topBlockBot, length, dim);
    gui->addSlider("left", 1, 100, &app->leftBlockW, length, dim);
    gui->addSlider("right", 1, 100, &app->rightBlockW, length, dim);
    
	ofAddListener(gui->newGUIEvent, this, &GUI::variousGUIEvent);
    finaliseCanvas(gui, true);
}




void GUI::update()
{
    
}


void GUI::draw()
{
}


void GUI::variousGUIEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
    
    if (name == "RED")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        color.r = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "GREEN")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        color.g = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "BLUE")
    {
     	ofxUISlider *slider = (ofxUISlider *) e.widget;
        color.b = slider->getScaledValue();
        setGUIColour();
    }
    else if (name == "ALPHA")
    {
		ofxUISlider *slider = (ofxUISlider *) e.widget;
        color.a = slider->getScaledValue();
        setGUIColour();
    }
}


void GUI::addKinectUserDegugGUIEvent(ofxUIEventArgs &e)
{
    string name = e.widget->getName();
	
	if (name.substr(0, 6) == "images")
		app->kinectManager.startPlayback(name);
}