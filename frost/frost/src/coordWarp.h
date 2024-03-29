#ifndef _COORD_WARPING_H
#define _COORD_WARPING_H

#define OF_ADDON_USING_OFXOPENCV
#define OF_ADDON_USING_OFXVECTORMATH

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxVectorMath.h"
//we use openCV to calculate our transform matrix
#include "ofxCvConstants.h"
#include "ofxCvContourFinder.h"

class coordWarping{
	
	
public:
	
	//---------------------------
	coordWarping();
	~coordWarping();

	void calculateMatrix(ofxPoint2f src[4], ofxPoint2f dst[4]);
	
	ofxPoint2f transform(float xIn, float yIn);
	ofxPoint2f inversetransform(float xIn, float yIn);
	
	CvMat *translate;
	CvMat *itranslate;
protected:
	
	CvPoint2D32f cvsrc[4];
	CvPoint2D32f cvdst[4];
	
};

#endif