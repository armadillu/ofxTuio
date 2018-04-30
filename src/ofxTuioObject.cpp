
#include "ofxTuioObject.h"
#include "ofMain.h"

ofxTuioObject::ofxTuioObject(long _sid, int _fid, float _xpos, float _ypos, float _angle) : ofxTuioContainer( _sid,  _xpos,  _ypos){
	fiducialId = _fid;
	angle = _angle;
	rotation_speed = 0.0f;
	rotation_accel = 0.0f;
	xpos = _xpos;
	ypos = _ypos;
	
};

ofxTuioObject::ofxTuioObject(ofxTuioObject * _tuioObject) : ofxTuioContainer(_tuioObject){
	fiducialId = _tuioObject->getFiducialId();
	angle = _tuioObject->getAngle();
	rotation_speed = _tuioObject->getRotationSpeed();
	rotation_accel = _tuioObject->getRotationAccel();
	xpos = _tuioObject->getX();
	ypos = _tuioObject->getY();
};

ofxTuioObject::~ofxTuioObject(){};

void ofxTuioObject::update (float _xpos, float _ypos, float _angle, float _xspeed, float _yspeed, float _rspeed, float _maccel, float _raccel) {
	ofxTuioContainer::update(_xpos,_ypos,_xspeed,_yspeed,_maccel);
	angle = _angle;
	rotation_speed = _rspeed;
	rotation_accel = _raccel;
};

void ofxTuioObject::update (ofxTuioObject * _tuioObject) {
	ofxTuioContainer::update(_tuioObject);
	angle = _tuioObject->getAngle();
	rotation_speed = _tuioObject->getRotationSpeed();
	rotation_accel = _tuioObject->getRotationAccel();
};

int ofxTuioObject::getFiducialId() {
	return fiducialId; 
};

float ofxTuioObject::getAngle() {
	return angle; 
};

float ofxTuioObject::getAngleDegrees() {
	return (float)(angle/PI*180); 
};

float ofxTuioObject::getRotationSpeed() {
	return rotation_speed; 
};

float ofxTuioObject::getRotationAccel() {
	return rotation_accel; 
};
