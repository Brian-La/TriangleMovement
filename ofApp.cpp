#include "ofApp.h"

//Global Var & Def----------------------------------------------
#define WIDTH 1024
#define HEIGHT 768
#define PI 3.14159

glm::vec3 mouPos, diffPos, dragPos;			//mouse, difference, and drag position vectors
bool moveTriangle = false;			//boolean switch to denote triangle movement

ofColor triColor(255, 0, 0);			//default color of triangle: set to red

float deg;				//declare degrees var
float origX[3];			//store original x vertices of triangle
float origY[3];			//original y...
//constructor---------------------------------------------------
Triangle::Triangle() {
	pos = glm::vec3(WIDTH/2, HEIGHT/2, 0);			//center position
	
	//push element to end of dynamic array:
	verts.clear();			//pre-check new list
	verts.push_back(glm::vec3(-b, h, 0));			//push first pt
	verts.push_back(glm::vec3(0, -h, 0));			//second...
	verts.push_back(glm::vec3(b, h, 0));			//third...
}

//draw class override-------------------------------------------
//draws triangle
void Triangle::draw() {
	ofSetColor(triColor);			//set triangle color

	//convert vector into array: display shape
	ofBeginShape();
	for (int i = 0; i < verts.size(); i++) {
		ofVertex(pos + verts[i]);			//draw center position w/ verts
	}
	ofEndShape();
}


//inside class (provided)---------------------------------------
//checks if position within triangle (vec3 p)
bool Triangle::inside(const glm::vec3 p) {

	//create new vectors based on normalization of triangle points
	glm::vec3 v1 = glm::normalize(verts[0] + pos - p);
	glm::vec3 v2 = glm::normalize(verts[1] + pos - p);
	glm::vec3 v3 = glm::normalize(verts[2] + pos - p);
	//cout << "v1: " << v1 << " v2: " << v2 << " v3: " << v3 << endl;
	
	//get float values based on angle orientation
	float a1 = glm::orientedAngle(v1, v2, glm::vec3(0, 0, 1));
	float a2 = glm::orientedAngle(v2, v3, glm::vec3(0, 0, 1));
	float a3 = glm::orientedAngle(v3, v1, glm::vec3(0, 0, 1));

	//cout << "a1: " << a1 << " a2: " << a2 << " a3: " << a3 << endl;

	//clock-wise enabled; return t if values are positive, otherwise f
	if (signbit(a1) == signbit(a2) && signbit(a1) == signbit(a3)) return true;
	else return false;
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetBackgroundColor(ofColor::black);			//BG color: black
}

//--------------------------------------------------------------
void ofApp::update(){
	//empty
}

//--------------------------------------------------------------
void ofApp::draw() {
	tri.draw();			//draw triangle
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == ofKey::OF_KEY_CONTROL && moveTriangle == true) 
		triColor = ofColor::blue;			//if CTRL pressed, triangle: blue	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	//if move switch on and key released...
	if (moveTriangle == true && key == ofKey::OF_KEY_CONTROL) {
		//if dragPos inside triangle...
		if (tri.inside(dragPos)) {
			diffPos = dragPos - tri.pos;		//update diffPos

			//save vertices (as though mouse pressd)
			for (int i = 0; i < tri.verts.size(); i++) {
				origX[i] = tri.verts[i].x;
				origY[i] = tri.verts[i].y;
			}

			triColor = ofColor::green;		//triangle: green
		}
		//else outside triangle...
		else {
			moveTriangle = false;		//turn of move switch	
			triColor = ofColor::red;	//triangle: red
		}
			//assign color after rotation depending on where mouse is
			//triColor = (tri.inside(dragPos)) ? ofColor::yellow : ofColor::red;
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
	glm::vec3 mov = glm::vec3(x, y, 0);			//temporary vec point
	triColor = (tri.inside(mov)) ? ofColor::yellow : ofColor::red;	//check if mouse enters triangle
																	//if t, triangle: yellow; else, triangle: red
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	//if move switch is on...
	if (moveTriangle == true) {
		dragPos = glm::vec3(x, y, 0);			//get drag mouse position

		//if CTRL is pressed...
		if (ofGetKeyPressed(ofKey::OF_KEY_CONTROL)) {
			mouPos = tri.pos + diffPos;				//update mouse pos if translated first
			deg = (dragPos.x - mouPos.x) / 2;		//get degrees by subt. drag and mouse x coordinate
															//divide by # to proportionately slow rotate speed 
			//cout << deg << endl;

			//going through vertices...
			for (int i = 0; i < tri.verts.size(); i++) {			
				//clock-wiserotation matrix using saved vertices...
				tri.verts[i].x = origX[i] * cos(deg * PI / 180) - origY[i] * sin(deg * PI / 180);		//rotate using pos + new values
				tri.verts[i].y = origX[i] * sin(deg * PI / 180) + origY[i] * cos(deg * PI / 180);
			}
		}
		else 
			tri.pos = dragPos - diffPos;			//update triangle position if CTRL not pressed
	}
	
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	mouPos = glm::vec3(x, y, 0);			//save mouseclick position

	//if mouseclick within triangle boundaries...
	if (tri.inside(mouPos) == true) {
		diffPos = mouPos - tri.pos;			//save dist. btwn mclick and current tri. pos.
		
		moveTriangle = true;				//turn on move switch 
		triColor = ofColor::green;			//set triangle: green

		//save original vertices of triangle before drag
		for (int i = 0; i < tri.verts.size(); i++) {
			origX[i] = tri.verts[i].x;
			origY[i] = tri.verts[i].y;
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	moveTriangle = false;			//turn off switch when mouse release
	glm::vec3 release = glm::vec3(x, y, 0);

	triColor = (tri.inside(release)) ? ofColor::yellow : ofColor::red;
}
