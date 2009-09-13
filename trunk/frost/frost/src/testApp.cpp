#include "testApp.h"
#include "CustomGLViewDelegate.h"

//#include "OFGuiController.h"


//--------------------------------------------------------------
void testApp::setup(){	
	cout<<"Testapp setup"<<endl;
	ofBackground(255,0,255);	
	ofSetFrameRate(60);
	
	vidGrabber = new ofVideoGrabber();
	vidGrabber->initGrabber(640, 480);
	printf("Setup!\n");
	
/*	if( otherWindow != NULL ){
		otherWindow->setup((&testApp::drawCameraView));

		
	} else {
	}*/
}

void testApp::setReferenceToOtherWindow( CustomGLViewDelegate* delegate )
{
	otherWindow = delegate;
	otherWindow->setup((&testApp::drawCameraView));

}


//--------------------------------------------------------------
void testApp::update()
{
	vidGrabber->grabFrame();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofBackground(255,0,255);	
	
	vidGrabber->draw(10,0,100,100);
}

void testApp::drawCameraView(){
	cout<<"draw"<<endl;
	vidGrabber->draw(0,0,otherWindow->getWidth(),otherWindow->getHeight());
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
	
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	
}

//------------- -------------------------------------------------
void testApp::mouseMoved(int x, int y ){
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){
	
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){
	/*for (int i = 0; i < nCurveVertexes; i++){
	 float diffx = x - curveVertices[i].x;
	 float diffy = y - curveVertices[i].y;
	 float dist = sqrt(diffx*diffx + diffy*diffy);
	 if (dist < curveVertices[i].radius){
	 curveVertices[i].bBeingDragged = true;
	 } else {
	 curveVertices[i].bBeingDragged = false;
	 }	
	 }
	 
	 printf("mouseX is %i mouseY is %i \n", x, y);
	 
	 */
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){
	/*
	 for (int i = 0; i < nCurveVertexes; i++){
	 curveVertices[i].bBeingDragged = false;	
	 }*/
}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){
	
}