/*
	TUIO C++ Library for OpenFrameworks
    http://www.openframeworks.cc
	
	Copyright (c) 2008 by Matthias Dörfelt based on the Classes by Martin Kaltenbrunner
	which can be found at http://reactivision.sourceforge.net/
	
    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef _TUIO_CONTAINER
#define _TUIO_CONTAINER

#include "ofxTuioPoint.h"

//--------------------------------------------------------
class ofxTuioContainer : public ofxTuioPoint{
	
public:
	
	ofxTuioContainer(long _sid, float _xpos, float _ypos);
	ofxTuioContainer(ofxTuioContainer * _tuioContainer);
	virtual ~ofxTuioContainer();
	
	virtual void update (float _xpos, float _ypos, float _xspeed, float _yspeed, float _maccel);
	virtual void update (ofxTuioContainer * _tuioContainer) ;
	
	virtual long getSessionId() ;
    virtual ofxTuioPoint getPosition() ;
	virtual float getXSpeed();
	virtual float getYSpeed();
	virtual float getMotionSpeed();
	virtual float getMotionAccel();
	
protected:
	long sessionId;
    float xspeed, yspeed;
	float motion_speed, motion_accel;
};

#endif	
