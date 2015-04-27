#ifndef _PLANET_ 
#define _PLANET_
#include <iostream>
#include <GL/glut.h>
#include <GL/glu.h>
#include <GL/gl.h>
#include <SOIL.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <assert.h>
#include <GL/glext.h>
using namespace std;



class Planet{

	public:
		Planet();
		GLuint GetTexture(string,int);
		void BackGroundTexture(GLuint);
		void LongLat(float);
		void Orbit(float,float);
		void Earth(float,GLuint,GLUquadricObj*);
		void Moon(float,float,GLuint,GLUquadricObj*);
		void SunLight(float);
		
};
#endif