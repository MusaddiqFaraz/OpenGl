#ifndef _SPACEBOX_
#define _SPACEBOX_

#include "Planet.hpp"



class SpaceBox{

	public:
		SpaceBox();

		GLuint LoadTexture(string);
		void render(float,float,float,float,float,float,GLuint);
};

#endif