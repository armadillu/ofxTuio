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

#ifndef _TUIO_CLIENT
#define _TUIO_CLIENT

#include "ofMain.h"
#include "ofxOscReceiver.h"
#include "ofxTuioCursor.h"
#include "ofxTuioObject.h"


#define PORT 12345

//--------------------------------------------------------
class ofxTuioClient{

public:
	ofxTuioClient();

	void start(int _port);
	void start();
	void getMessage();

	void drawCursors();
	void drawObjects();

	list<ofxTuioObject*> getTuioObjects();
	list<ofxTuioCursor*> getTuioCursors();

	ofEvent<ofxTuioCursor> cursorRemoved;
	ofEvent<ofxTuioCursor> cursorAdded;
	ofEvent<ofxTuioCursor> cursorUpdated;

	ofEvent<ofxTuioObject> objectAdded;
	ofEvent<ofxTuioObject> objectRemoved;
	ofEvent<ofxTuioObject> objectUpdated;

private:

	ofxOscReceiver	receiver;
	list<ofxTuioCursor*> cursorList;
	list<ofxTuioCursor*> freeCursorList;
	list<ofxTuioCursor*> freeCursorBuffer;
	list<ofxTuioObject*> objectList;
	list<long> aliveObjectList;
	list<long> newObjectList;
	list<long> aliveCursorList;
	list<long> newCursorList;

	int currentFrame, lastFrame, maxFingerID;
};

#endif
