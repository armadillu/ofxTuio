
#include "ofxTuioCursor.h"

ofxTuioCursor::ofxTuioCursor(long _sid, int _fid, float _xpos, float _ypos) : ofxTuioContainer( _sid,  _xpos,  _ypos){
	fingerId = _fid;
	xpos = _xpos;
	ypos = _ypos;
};

ofxTuioCursor::ofxTuioCursor(ofxTuioCursor * _tuioCursor) : ofxTuioContainer(_tuioCursor){
	fingerId = _tuioCursor->getFingerId();
};

ofxTuioCursor::~ofxTuioCursor(){};

int ofxTuioCursor::getFingerId(){
	return fingerId;
};
