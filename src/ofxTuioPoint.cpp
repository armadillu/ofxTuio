#include "ofxTuioPoint.h"
#include "ofMain.h"
#include <math.h>

ofxTuioPoint::ofxTuioPoint(float _xpos, float _ypos){
	xpos = _xpos;
	ypos = _ypos;
};

ofxTuioPoint::ofxTuioPoint(ofxTuioPoint * _tuioPoint){
	xpos = _tuioPoint->getX();
	ypos = _tuioPoint->getY();
};

ofxTuioPoint::~ofxTuioPoint(){};

void ofxTuioPoint::update (float _xpos, float _ypos) {
	xpos = _xpos;
	ypos = _ypos;
};

void ofxTuioPoint::update (ofxTuioPoint * _tuioPoint) {
	xpos = _tuioPoint->getX();
	ypos = _tuioPoint->getY();
};

float ofxTuioPoint::getX(){
	return xpos;
};

float ofxTuioPoint::getY(){
	return ypos;
};

float ofxTuioPoint::getDistance(float _x, float _y) {
	float dx = xpos-_x;
	float dy = ypos-_y;
	return sqrtf(dx*dx+dy*dy);
};

float ofxTuioPoint::getDistance(ofxTuioPoint * _tuioPoint) {
	float dx = xpos-_tuioPoint->getX();
	float dy = ypos-_tuioPoint->getY();
	return sqrtf(dx*dx+dy*dy);
};

float ofxTuioPoint::getAngle(ofxTuioPoint * _tuioPoint) {

	float side = _tuioPoint->getX()-xpos;
	float height = _tuioPoint->getY()-ypos;
	float distance = _tuioPoint->getDistance(xpos,ypos);

	float angle = (float)(asin(side/distance)+PI/2);
	if (height<0) angle = 2.0f*(float)PI-angle;

	return angle;
};

float ofxTuioPoint::getAngleDegrees(ofxTuioPoint * _tuioPoint) {
	return ((getAngle(_tuioPoint)/(float)PI)*180.0f);
};
