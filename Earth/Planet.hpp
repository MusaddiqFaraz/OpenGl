#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <SOIL.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
using namespace std;

class Planet{

	public:
		Planet();
		GLuint GetTexture(string);
		void BackGroundTexture();
		void LongLat(float);
		void Orbit(float,float);
		void Earth(float,GLuint,GLUquadricObj*);
		void Moon(float,float,GLuint,GLUquadricObj*);
		void SunLight(float);
		
};