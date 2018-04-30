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

#ifndef _TUIO_OBJECT
#define _TUIO_OBJECT

#include "ofxTuioContainer.h"

//--------------------------------------------------------
class ofxTuioObject : public ofxTuioContainer{
	
public:
	
	ofxTuioObject(long _sid, int _fid, float _xpos, float _ypos, float _angle);
	ofxTuioObject(ofxTuioObject * _tuioObject);
	
	~ofxTuioObject();
	
	void update (float _xpos, float _ypos, float _angle, float _xspeed, float _yspeed, float _rspeed, float _maccel, float _raccel) ;
	void update (ofxTuioObject * _tuioObject) ;
	
	int getFiducialId() ;
	float getAngle() ;
	float getAngleDegrees() ;
	float getRotationSpeed() ;
	float getRotationAccel() ;
	

protected:

	int fiducialId;
	float angle;
	float rotation_speed, rotation_accel;
};

#endif	
