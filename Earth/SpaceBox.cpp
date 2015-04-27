#include "SpaceBox.hpp"


SpaceBox::SpaceBox()
{	
	return;
}

GLuint SpaceBox::LoadTexture( string  file)
{	
	const char * filename = file.c_str();
	GLuint texture_id;
	int width, height;
	
	unsigned char* data=SOIL_load_image(filename, &width, &height, 0, SOIL_LOAD_RGB);
	if(!data)
	{
		fprintf (stderr, "ERROR: could not load %s\n", filename);
		exit(0);
	}
	// non-power-of-2 dimensions check
	if ((width & (width - 1)) != 0 || (height & (height - 1)) != 0)
	{
		fprintf (stderr, "WARNING: image %s is not power-of-2 dimensions\n", filename);
	}

	// copy image data into 'target' side of cube map
	
	texture_id= SOIL_load_OGL_texture(
     	   filename,
     	   SOIL_LOAD_AUTO,
    	    SOIL_CREATE_NEW_ID,
     	   SOIL_FLAG_POWER_OF_TWO
     	   | SOIL_FLAG_MIPMAPS
     	   | SOIL_FLAG_MULTIPLY_ALPHA
     	   | SOIL_FLAG_COMPRESS_TO_DXT
     	   | SOIL_FLAG_DDS_LOAD_DIRECT| SOIL_FLAG_INVERT_Y
     	   );
	
  	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
  	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  	glTexParameteri (GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if(texture_id>0)
	{	
		free (data);
		return texture_id;
	}
	else
		return 0;
}

void SpaceBox::render(float x, float y, float z, float width, float height, float length,GLuint SpaceSide)
{

	glPushMatrix();
	// Center the Skybox around the given x,y,z position
	x = x - width  / 2;
	y = y - height / 2;
	z = z - length / 2;

	
	glEnable(GL_TEXTURE_2D);
	// Draw Front side

	glBindTexture(GL_TEXTURE_2D,SpaceSide);
	glBegin(GL_QUADS);	
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height, z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z+length);
	glEnd();

	// Draw Back side
	glBindTexture(GL_TEXTURE_2D, SpaceSide);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height, z); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
	glEnd();

	// Draw Left side
	glBindTexture(GL_TEXTURE_2D, SpaceSide);
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z);	
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z+length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z);		
	glEnd();

	// Draw Right side
	glBindTexture(GL_TEXTURE_2D,SpaceSide);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y+height,	z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y+height,	z);
	glEnd();

	// Draw Up side
	glBindTexture(GL_TEXTURE_2D,SpaceSide);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x+width, y+height, z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x+width, y+height, z+length); 
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,		  y+height,	z+length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x,		  y+height,	z);
	glEnd();

	// Draw Down side
	glBindTexture(GL_TEXTURE_2D, SpaceSide);
	glBegin(GL_QUADS);		
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x,		  y,		z);
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,		  y,		z+length);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x+width, y,		z+length); 
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x+width, y,		z);
	glEnd();
  	glPopMatrix();

}
