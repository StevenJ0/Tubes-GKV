#ifndef TRUK_H_INCLUDED
#define TRUK_H_INCLUDED

#include <GL/glut.h> // For OpenGL types

void wheel(float x, float y, float z);
void container(int posisi, float x, float y, float z);
void wheelDepan(float x, float y, float z);
void collisionBox(float putaran, float tx, float ty, float tz);
void Truk(float putaran, float x, float y, float z);
void drawTruckShadow(float posX, float posZ, float rotation);

// Texture declarations
extern GLuint truckTexture; // Texture ID for truck
void loadTruckTexture(const char* filename); // Function to load texture

#endif // TRUK_H_INCLUDED
