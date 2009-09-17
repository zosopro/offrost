
#include "PluginController.h"
#include "PluginIncludes.h"



MoonDust::MoonDust(){
	type = OUTPUT;
	
	for(int i=0;i<100;i++){
		particles.push_back(DustParticle(0.5+ofRandom(-0.1,0.1),ofRandom(0, 1),0));
	}
	
	force = 1;
	damp = 0.999;
	
	min = 0.2;
	max = 0.5;
}

void MoonDust::setup(){
	particleImg.loadImage("MoonDustParticle30.png");
	particleTrack.loadImage("MoonDustTrack.png");
}

void MoonDust::update(){
    vector<DustParticle>::iterator it;
    it = particles.begin();
	for(int i=0; i<particles.size();i++){
		particles[i].update(force, damp, min, max);
	}
}

void MoonDust::draw(){
	float size = 0.01;
	ofSetColor(255, 255, 255);

	applyFloorProjection();
	
	glBlendFunc (GL_SRC_COLOR, GL_ONE);	
    vector<DustParticle>::iterator it;
    it = particles.begin();
    while( it != particles.end() ) {
		particleTrack.draw((*it).x, (*it).y, -(*it).v.x*3000.0*size, size);
		particleImg.draw((*it).x-size/2.0-(*it).v.x*100.0*size, (*it).y,size,size);
		float a = 100;
		/*for(int i=(*it).history.size()-1;i>=0;i--){
			a -= 100.0/(*it).history.size();
			ofSetColor(255, 255, 255,a);
//			particleImg.draw((*it).history[i].x*ofGetWidth(), (*it).history[i].y*ofGetHeight(),size,size);			
			ofEllipse((*it).history[i].x*ofGetWidth(), (*it).history[i].y*ofGetHeight(), size, size);

		}*/

		++it;
    }
	float middleX = (max - min)/2.0+min;
	ofSetColor(255, 255, 255);
	ofLine(min, 0, min, 1);
	ofLine(max, 0, max, 1);
//	ofLine(middleX*ofGetWidth(), 0, middleX*ofGetWidth(), ofGetHeight());
	glPopMatrix();
}


DustParticle::DustParticle(float _x, float _y, float _z){
	x = _x;
	y = _y;
	z = _z;
	v.x = ofRandom(-0.01, 0.01);
//	v.y = ofRandom(-0.4, 0.4);
	vEffect = ofRandom(0.8, 1.2);
//	vEffect = 1.0;
	goingMax = false;
}

void DustParticle::update(float force, float damp, float min, float max){
	history.push_back(pos());
	if(history.size() > 40){
		history.erase(history.begin());
	}

	float a = vEffect*0.0001*100.0/ofGetFrameRate(); 
	if(!goingMax){
		a *= -1;
	}	

	float timeToStop = fabs(v.x)/fabs(a);
	float p = 0.5*-a*timeToStop*timeToStop+v.x*timeToStop+x;
	
	if(p < min){
		goingMax = true;
	} else if(p > max){
		goingMax = false;
	}
	
	v.x += a ;//(max - x)*0.01*force*60.0/ofGetFrameRate();		
	x += v.x;//*100.0/ofGetFrameRate();
}



ofxVec3f DustParticle::pos(){
	return ofxVec3f(x,y,z);
}