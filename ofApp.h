#pragma once

#include "ofMain.h"

//Base Class----------------------------------------------------
class Shape {
public:
	//constructor: default--------------------------------------
	Shape() {}
	//functions-------------------------------------------------
	virtual void draw() {}								//overrided draw() method
	virtual bool inside(glm::vec3 p) { return false; }			//return t if p is inside Shape 		


	//data------------------------------------------------------
	vector<glm::vec3> verts;					//dynamic array to hold vertices
	glm::vec3 pos;								//position vec
	ofColor color;							//color of shape
};

//Derived Shape: Triangle------------------- 
class Triangle : public Shape {
public:
	//constructor: default------------------
	Triangle();

	//functions-----------------------------
	void draw();
	bool inside(glm::vec3 p);

	//data----------------------------------
	float h = 300 / 2;			//height divided by 2
	float b = 200 / 2;			//base divided by 2
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);

		Triangle tri;
		//Triangle tri2 = Triangle(100, 100, 0);

};
