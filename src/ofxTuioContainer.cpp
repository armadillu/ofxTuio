
#include "ofxTuioContainer.h"
#include <math.h>
#

ofxTuioContainer::ofxTuioContainer(long _sid, float _xpos, float _ypos) : ofxTuioPoint(xpos,  ypos){
	sessionId = _sid;
	xspeed = 0.0f;
	yspeed = 0.0f;
	motion_speed = 0.0f;
	motion_accel = 0.0f;
	xpos = _xpos;
	ypos = _ypos;
};

ofxTuioContainer::ofxTuioContainer(ofxTuioContainer * _tuioContainer) : ofxTuioPoint(_tuioContainer){
	sessionId = _tuioContainer->getSessionId();
	xspeed = _tuioContainer->getXSpeed();
	yspeed = _tuioContainer->getYSpeed();
	motion_speed = _tuioContainer->getMotionSpeed();
	motion_accel = _tuioContainer->getMotionAccel();
	xpos = _tuioContainer->getX();
	ypos = _tuioContainer->getY();
};

ofxTuioContainer::~ofxTuioContainer(){};

void ofxTuioContainer::update (float _xpos, float _ypos, float _xspeed, float _yspeed, float _maccel) {
	ofxTuioPoint::update(_xpos, _ypos);
	xspeed = _xspeed;
	yspeed = _yspeed;
	motion_speed = (float)sqrt(_xspeed*_xspeed+_yspeed*_yspeed);
	motion_accel = _maccel;
};

void ofxTuioContainer::update (ofxTuioContainer * _tuioContainer) {
	ofxTuioPoint::update(_tuioContainer);
	xspeed = _tuioContainer->getXSpeed();
	yspeed = _tuioContainer->getYSpeed();
	motion_speed = _tuioContainer->getMotionSpeed();
	motion_accel = _tuioContainer->getMotionAccel();
};

long ofxTuioContainer::getSessionId() {
	return sessionId; 
};

ofxTuioPoint ofxTuioContainer::getPosition() {
	ofxTuioPoint p(xpos,ypos);
	return p;
};

float ofxTuioContainer::getXSpeed(){
	return xspeed;
};

float ofxTuioContainer::getYSpeed(){
	return yspeed;
};

float ofxTuioContainer::getMotionSpeed(){
	return motion_speed;
};

float ofxTuioContainer::getMotionAccel(){
	return motion_accel;
};
