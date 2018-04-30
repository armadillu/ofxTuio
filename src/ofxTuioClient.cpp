
#include "ofxTuioClient.h"

ofxTuioClient::ofxTuioClient(){
	currentFrame = lastFrame = maxFingerID = -1;
};

void ofxTuioClient::start(int _port){
	receiver.setup( _port );
};

void ofxTuioClient::start(){
	receiver.setup( PORT );
};

void ofxTuioClient::getMessage(){

	while( receiver.hasWaitingMessages() )
	{
		ofxOscMessage m;
		receiver.getNextMessage( &m );

		if ( m.getAddress() == "/tuio/2Dobj" )
		{

			if( m.getArgAsString( 0 ) == "set" ){
				if ((currentFrame<lastFrame) && (currentFrame>0)) return;

				long sid  = (long)(m.getArgAsInt32(1));
				int fiducial = m.getArgAsInt32(2);
				float xpos =  m.getArgAsFloat(3);
				float ypos =  m.getArgAsFloat(4);
				float angle =  m.getArgAsFloat(5);
				float xspeed =  m.getArgAsFloat(6);
				float yspeed =  m.getArgAsFloat(7);
				float rspeed =  m.getArgAsFloat(8);
				float maccel =  m.getArgAsFloat(9);
				float raccel =  m.getArgAsFloat(10);

				list<ofxTuioObject*>::iterator tobj;
				for (tobj=objectList.begin(); tobj != objectList.end(); tobj++)
					if((*tobj)->getSessionId()==sid) break;

				if (tobj == objectList.end()) {
					ofxTuioObject *addObject = new ofxTuioObject(sid, fiducial, xpos, ypos, angle);
					objectList.push_back(addObject);


					ofNotifyEvent(objectAdded, *(objectList.back()), this);

				}else if ( ((*tobj)->getX()!=xpos) || ((*tobj)->getY()!=ypos) || ((*tobj)->getAngle()!=angle) || ((*tobj)->getXSpeed()!=xspeed) || ((*tobj)->getYSpeed()!=yspeed) || ((*tobj)->getRotationSpeed()!=rspeed) || ((*tobj)->getMotionAccel()!=maccel) || ((*tobj)->getRotationAccel()!=raccel) ) {
					(*tobj)->update(xpos,ypos,angle,xspeed,yspeed,rspeed,maccel,raccel);

					ofNotifyEvent(objectUpdated, **tobj, this);
				}
			} else if( m.getArgAsString( 0 ) == "alive"  ){
				if ((currentFrame<lastFrame) && (currentFrame> 0)) return;
				for (int i=1;i<m.getNumArgs();i++) {

					long sid  = (long)(m.getArgAsInt32(i));;
					newObjectList.push_back((long)(sid));

					list<long>::iterator iter;
					iter = find(aliveObjectList.begin(), aliveObjectList.end(), (long)(sid));
					if (iter != aliveObjectList.end()) aliveObjectList.erase(iter);
				}
				list<long>::iterator alive_iter;
				for (alive_iter=aliveObjectList.begin(); alive_iter != aliveObjectList.end(); alive_iter++) {
					list<ofxTuioObject*>::iterator tobj;
					for (tobj=objectList.begin(); tobj!=objectList.end(); tobj++) {
						ofxTuioObject *deleteObject = (*tobj);
						if(deleteObject->getSessionId()==*alive_iter) {

							ofNotifyEvent(objectRemoved, **tobj, this);

							objectList.erase(tobj);

							delete deleteObject;
							break;
						}
					}
				}
				aliveObjectList = newObjectList;
				newObjectList.clear();
			} else if( m.getArgAsString( 0 ) == "fseq" ){

				if(currentFrame>0) lastFrame = currentFrame;
				currentFrame  = (int)(m.getArgAsInt32(1));
			}
		} else if ( m.getAddress() == "/tuio/2Dcur" )
		{
			if( m.getArgAsString( 0 ) == "set" ){
				if ((currentFrame<lastFrame) && (currentFrame>0)) return;
				int nArgs = m.getNumArgs();
				long sid = 0;
				float xpos = 0;
				float ypos = 0;
				float xspeed = 0;
				float yspeed = 0;
				float maccel = 0;

				if(nArgs > 1 ) sid = (long)(m.getArgAsInt32(1));
				if(nArgs > 2 ) xpos = m.getArgAsFloat(2);
				if(nArgs > 3 ) ypos =  m.getArgAsFloat(3);
				if(nArgs > 4 ) xspeed = m.getArgAsFloat(4);
				if(nArgs > 5 ) yspeed = m.getArgAsFloat(5);
				if(nArgs > 6 ) maccel = m.getArgAsFloat(6);

				if(xspeed != xspeed || !std::isfinite(xspeed)){
					xspeed = 0;
				}
				if(yspeed != yspeed || !std::isfinite(yspeed)){
					yspeed = 0;
				}
				if(maccel != maccel || !std::isfinite(maccel)){
					maccel = 0;
				}

				list<ofxTuioCursor*>::iterator tit;
				for (tit=cursorList.begin(); tit != cursorList.end(); tit++)
					if((*tit)->getSessionId()==sid) break;

				if (tit == cursorList.end()) {
					int fid = (int)(cursorList.size());

					if ((int)(cursorList.size())<=maxFingerID) {
						list<ofxTuioCursor*>::iterator closestCursor = freeCursorList.begin();

						for(list<ofxTuioCursor*>::iterator testCursor = freeCursorList.begin();testCursor!= freeCursorList.end(); testCursor++) {
							if((*testCursor)->getDistance(xpos,ypos)<(*closestCursor)->getDistance(xpos,ypos)) closestCursor = testCursor;
						}

						fid = (*closestCursor)->getFingerId();
						ofxTuioCursor *curToDelete = (*closestCursor);
						freeCursorList.erase(closestCursor);
						delete curToDelete;
					} else maxFingerID = fid;

					ofxTuioCursor *addCursor = new ofxTuioCursor(sid,fid,xpos,ypos);
					cursorList.push_back(addCursor);

					ofNotifyEvent(cursorAdded, *(cursorList.back()), this);

				} else if ( ((*tit)->getX()!=xpos) || ((*tit)->getY()!=ypos) || ((*tit)->getXSpeed()!=xspeed) || ((*tit)->getYSpeed()!=yspeed) || ((*tit)->getMotionAccel()!=maccel) ) {
					(*tit)->update(xpos,ypos,xspeed,yspeed,maccel);

					ofNotifyEvent(cursorUpdated, **tit, this);
				}
			} else if( m.getArgAsString( 0 ) == "alive" ){
				if ((currentFrame<lastFrame) && (currentFrame>0)) return;
				for (int i=1;i<m.getNumArgs();i++) {

					long sid  = (long)(m.getArgAsInt32(i));;
					newCursorList.push_back((long)(sid));

					list<long>::iterator iter;
					iter = find(aliveCursorList.begin(), aliveCursorList.end(), (long)(sid));
					if (iter != aliveCursorList.end()) aliveCursorList.erase(iter);
				}
				list<long>::iterator alive_iter;
				for (alive_iter=aliveCursorList.begin(); alive_iter != aliveCursorList.end(); alive_iter++) {
					list<ofxTuioCursor*>::iterator tit;
					for (tit=cursorList.begin(); tit != cursorList.end(); tit++) {
						ofxTuioCursor *deleteCursor = (*tit);
						if(deleteCursor->getSessionId()==*alive_iter) {

							ofNotifyEvent(cursorRemoved, **tit, this);

							cursorList.erase(tit);

							if (deleteCursor->getFingerId()==maxFingerID) {
								maxFingerID = -1;
								delete deleteCursor;

								if (cursorList.size()>0) {
									list<ofxTuioCursor*>::iterator clist;
									for (clist=cursorList.begin(); clist != cursorList.end(); clist++) {
										int fid = (*clist)->getFingerId();
										if (fid>maxFingerID) maxFingerID=fid;
									}

									list<ofxTuioCursor*>::iterator flist;
									for (flist=freeCursorList.begin(); flist != freeCursorList.end(); flist++) {
										ofxTuioCursor *freeCursor = (*flist);
										if (freeCursor->getFingerId()>maxFingerID) delete freeCursor;
										else freeCursorBuffer.push_back(freeCursor);
									}

									freeCursorList = freeCursorBuffer;
									freeCursorBuffer.clear();
								}
							} else if (deleteCursor->getFingerId()<maxFingerID) freeCursorList.push_back(deleteCursor);

							break;
						}
					}

				}
				aliveCursorList = newCursorList;
				newCursorList.clear();
			}
		} else if( m.getArgAsString( 0 ) == "fseq" ){

			if(currentFrame>0) lastFrame = currentFrame;
			currentFrame  = (int)(m.getArgAsInt32(1));
		}
	}
};

void ofxTuioClient::drawCursors(){
	list<ofxTuioCursor*>::iterator tit;
	for (tit=cursorList.begin(); tit != cursorList.end(); tit++) {
		ofxTuioCursor *blob = (*tit);

		ofSetColor(255,255,255);
		ofEllipse(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight(), 10.0, 10.0);
		string str = "SessionId: "+ofToString((int)(blob->getSessionId()));
		ofDrawBitmapString(str, blob->getX()*ofGetWidth()-10.0, blob->getY()*ofGetHeight()+25.0);
	}
};

void ofxTuioClient::drawObjects(){

	list<ofxTuioObject*>::iterator tobj;
	for (tobj=objectList.begin(); tobj != objectList.end(); tobj++) {
		ofxTuioObject *blob = (*tobj);
		//glColor3f(1.0,0.0,0.0);
		ofSetColor(255,0,0);
		glPushMatrix();
		glTranslatef(blob->getX()*ofGetWidth(), blob->getY()*ofGetHeight(), 0.0);
		glRotatef(blob->getAngleDegrees(), 0.0, 0.0, 1.0);
		ofRect(-10.0, -10.0, 20.0, 20.0);
		ofSetColor(255,255,255);
		//glColor3f(1.0,1.0,1.0);
		ofLine(0, 0, 0, 10);
		glPopMatrix();
		string str = "FiducialId: "+ofToString((int)(blob->getFiducialId()));
		ofDrawBitmapString(str, blob->getX()*ofGetWidth()-10.0, blob->getY()*ofGetHeight()+25.0);
		str = "SessionId: "+ofToString((int)(blob->getSessionId()));
		ofDrawBitmapString(str, blob->getX()*ofGetWidth()-10.0, blob->getY()*ofGetHeight()+40.0);
	}
};

list<ofxTuioObject*> ofxTuioClient::getTuioObjects() {
	return objectList;
};

list<ofxTuioCursor*> ofxTuioClient::getTuioCursors() {
	return cursorList;
};
