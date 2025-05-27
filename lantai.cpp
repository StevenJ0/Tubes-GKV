#include "common.h"

// Ground with varied terrain
void ground() {
    // Grass base
    glPushMatrix();
    glColor3f(0.1, 0.5, 0.1); // Darker green for grass
    glBegin(GL_QUADS);
    glVertex3f(-1000, 0, 1000);
    glVertex3f(-1000, 0, -1000);
    glVertex3f(1000, 0, -1000);
    glVertex3f(1000, 0, 1000);
    glEnd();
    glPopMatrix();

    // Dirt patches for texture
    glPushMatrix();
    glColor3f(0.4, 0.3, 0.2); // Brown dirt
    for (float x = -900; x <= 900; x += 200) {
        for (float z = -900; z <= 900; z += 200) {
            glPushMatrix();
            glTranslatef(x, 0.01, z);
            glBegin(GL_QUADS);
            glVertex3f(-50, 0, 50);
            glVertex3f(-50, 0, -50);
            glVertex3f(50, 0, -50);
            glVertex3f(50, 0, 50);
            glEnd();
            glPopMatrix();
        }
    }
    glPopMatrix();
}

// Road with realistic texture and markings
void road(float x, float width, float elevation) {
    glPushMatrix();
    glTranslatef(0.0, elevation, 0.0);

    // Asphalt surface
    glColor3f(0.2, 0.2, 0.2); // Dark asphalt
    glBegin(GL_QUADS);
    glVertex3f(-x, 0, width);
    glVertex3f(-x, 0, -width);
    glVertex3f(x, 0, -width);
    glVertex3f(x, 0, width);
    glEnd();

    // Lane markings (white dashed lines)
    glColor3f(1.0, 1.0, 1.0); // White
    for (float i = -x + 10; i < x - 50; i += 50) {
        glBegin(GL_QUADS);
        glVertex3f(i, 0.01, 2);
        glVertex3f(i, 0.01, -2);
        glVertex3f(i + 40, 0.01, -2);
        glVertex3f(i + 40, 0.01, 2);
        glEnd();
    }
    // Last shorter dash
    glBegin(GL_QUADS);
    glVertex3f(x - 50, 0.01, 2);
    glVertex3f(x - 50, 0.01, -2);
    glVertex3f(x - 10, 0.01, -2);
    glVertex3f(x - 10, 0.01, 2);
    glEnd();

    // Yellow center line for two-way roads
    glColor3f(1.0, 1.0, 0.0); // Yellow
    glBegin(GL_QUADS);
    glVertex3f(-x, 0.01, 0.2);
    glVertex3f(-x, 0.01, -0.2);
    glVertex3f(x, 0.01, -0.2);
    glVertex3f(x, 0.01, 0.2);
    glEnd();

    glPopMatrix();
}

// Roadside with curbs, guardrails, and vegetation
void roadsideRight(float x, float width, float elevation) {
    glPushMatrix();
    glTranslatef(0.0, elevation, width);

    // Curb (bottom)
    glColor3f(0.7, 0.7, 0.7); // Light gray
    glBegin(GL_QUADS);
    glVertex3f(-x, 0, 1);
    glVertex3f(-x, 0, -1);
    glVertex3f(x, 0, -1);
    glVertex3f(x, 0, 1);
    glEnd();

    // Curb (top)
    glPushMatrix();
    glTranslatef(0.0, 0.3, 0.0);
    glColor3f(0.6, 0.6, 0.6); // Slightly darker gray
    glBegin(GL_QUADS);
    glVertex3f(-x, 0, 1);
    glVertex3f(-x, 0, -1);
    glVertex3f(x, 0, -1);
    glVertex3f(x, 0, 1);
    glEnd();
    glPopMatrix();

    // Side faces of curb
    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
    glTranslatef(0.0, 0.15, -1.0);
    glBegin(GL_QUADS);
    glVertex3f(-x, -0.15, 0);
    glVertex3f(-x, 0.15, 0);
    glVertex3f(x, 0.15, 0);
    glVertex3f(x, -0.15, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.15, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(-x, -0.15, 0);
    glVertex3f(-x, 0.15, 0);
    glVertex3f(x, 0.15, 0);
    glVertex3f(x, -0.15, 0);
    glEnd();
    glPopMatrix();

    // Guardrail
    glPushMatrix();
    glTranslatef(0.0, 0.5, 1.5);
    glColor3f(0.8, 0.8, 0.8); // Metallic silver
    for (float i = -x + 5; i < x; i += 10) {
        glPushMatrix();
        glTranslatef(i, 0, 0);
        glBegin(GL_QUADS);
        glVertex3f(-2, 0, 0.1);
        glVertex3f(-2, 0.5, 0.1);
        glVertex3f(2, 0.5, 0.1);
        glVertex3f(2, 0, 0.1);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();

    // Vegetation (simple grass patches)
    glPushMatrix();
    glTranslatef(0.0, 0.0, 3.0);
    glColor3f(0.2, 0.6, 0.2);
    for (float i = -x + 10; i < x; i += 20) {
        glPushMatrix();
        glTranslatef(i, 0.01, 0);
        glBegin(GL_QUADS);
        glVertex3f(-5, 0, 2);
        glVertex3f(-5, 0, -2);
        glVertex3f(5, 0, -2);
        glVertex3f(5, 0, 2);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();

    glPopMatrix();
}

void roadsideLeft(float x, float width, float elevation) {
    glPushMatrix();
    glTranslatef(0.0, elevation, -width - 20);

    // Curb (bottom)
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_QUADS);
    glVertex3f(-x, 0, 1);
    glVertex3f(-x, 0, -1);
    glVertex3f(x, 0, -1);
    glVertex3f(x, 0, 1);
    glEnd();

    // Curb (top)
    glPushMatrix();
    glTranslatef(0.0, 0.3, 0.0);
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_QUADS);
    glVertex3f(-x, 0, 1);
    glVertex3f(-x, 0, -1);
    glVertex3f(x, 0, -1);
    glVertex3f(x, 0, 1);
    glEnd();
    glPopMatrix();

    // Side faces of curb
    glColor3f(0.5, 0.5, 0.5);
    glPushMatrix();
    glTranslatef(0.0, 0.15, -1.0);
    glBegin(GL_QUADS);
    glVertex3f(-x, -0.15, 0);
    glVertex3f(-x, 0.15, 0);
    glVertex3f(x, 0.15, 0);
    glVertex3f(x, -0.15, 0);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0.0, 0.15, 1.0);
    glBegin(GL_QUADS);
    glVertex3f(-x, -0.15, 0);
    glVertex3f(-x, 0.15, 0);
    glVertex3f(x, 0.15, 0);
    glVertex3f(x, -0.15, 0);
    glEnd();
    glPopMatrix();

    // Guardrail
    glPushMatrix();
    glTranslatef(0.0, 0.5, -1.5);
    glColor3f(0.8, 0.8, 0.8);
    for (float i = -x + 5; i < x; i += 10) {
        glPushMatrix();
        glTranslatef(i, 0, 0);
        glBegin(GL_QUADS);
        glVertex3f(-2, 0, 0.1);
        glVertex3f(-2, 0.5, 0.1);
        glVertex3f(2, 0.5, 0.1);
        glVertex3f(2, 0, 0.1);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();

    // Vegetation
    glPushMatrix();
    glTranslatef(0.0, 0.0, -3.0);
    glColor3f(0.2, 0.6, 0.2);
    for (float i = -x + 10; i < x; i += 20) {
        glPushMatrix();
        glTranslatef(i, 0.01, 0);
        glBegin(GL_QUADS);
        glVertex3f(-5, 0, 2);
        glVertex3f(-5, 0, -2);
        glVertex3f(5, 0, -2);
        glVertex3f(5, 0, 2);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();

    glPopMatrix();
}

// Streetlight
void streetlight(float x, float z) {
    glPushMatrix();
    glTranslatef(x, 0, z);

    // Pole
    glColor3f(0.3, 0.3, 0.3); // Dark gray
    glPushMatrix();
    glTranslatef(0, 5, 0);
    glScalef(0.2, 10, 0.2);
    glutSolidCube(1.0);
    glPopMatrix();

    // Light
    glPushMatrix();
    glTranslatef(0, 10, 0);
    glColor3f(1.0, 1.0, 0.8); // Warm light
    glutSolidSphere(0.5, 10, 10);
    glPopMatrix();

    glPopMatrix();
}

void Jalan() {
    // Ground
    glPushMatrix();
    glTranslatef(0.0, -0.5, 0.0);
    ground();
    glPopMatrix();

    // Roads with varied widths and slight elevation
    glPushMatrix();
    glTranslatef(-680.0, 0.0, -400.0);
    road(320, 20, 0.1);
    roadsideRight(320, 20, 0.1);
    roadsideLeft(320, 20, 0.1);
    streetlight(-300, 25);
    streetlight(300, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-680.0, 0.0, 400.0);
    road(320, 20, 0.1);
    roadsideRight(320, 20, 0.1);
    roadsideLeft(320, 20, 0.1);
    streetlight(-300, 25);
    streetlight(300, 25);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0.0, 0.0, -340.0);
    road(1000, 20, 0.1);
    roadsideRight(1000, 20, 0.1);
    roadsideLeft(1000, 20, 0.1);
    streetlight(-900, 25);
    streetlight(900, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-170.0, 0.0, -200.0);
    road(150, 15, 0.05);
    roadsideRight(150, 15, 0.05);
    roadsideLeft(150, 15, 0.05);
    streetlight(-140, 20);
    streetlight(140, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-170.0, 0.0, 400.0);
    road(150, 15, 0.05);
    roadsideRight(150, 15, 0.05);
    roadsideLeft(150, 15, 0.05);
    streetlight(-140, 20);
    streetlight(140, 20);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0.0, 0.0, 0.0);
    road(1000, 20, 0.1);
    roadsideRight(1000, 20, 0.1);
    roadsideLeft(1000, 20, 0.1);
    streetlight(-900, 25);
    streetlight(900, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(170.0, 0.0, -300.0);
    road(150, 15, 0.05);
    roadsideRight(150, 15, 0.05);
    roadsideLeft(150, 15, 0.05);
    streetlight(-140, 20);
    streetlight(140, 20);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(170.0, 0.0, 300.0);
    road(150, 15, 0.05);
    roadsideRight(150, 15, 0.05);
    roadsideLeft(150, 15, 0.05);
    streetlight(-140, 20);
    streetlight(140, 20);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0.0, 0.0, 340.0);
    road(1000, 20, 0.1);
    roadsideRight(1000, 20, 0.1);
    roadsideLeft(1000, 20, 0.1);
    streetlight(-900, 25);
    streetlight(900, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(610.0, 0.0, -400.0);
    road(250, 20, 0.1);
    roadsideRight(250, 20, 0.1);
    roadsideLeft(250, 20, 0.1);
    streetlight(-240, 25);
    streetlight(240, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(610.0, 0.0, 400.0);
    road(250, 20, 0.1);
    roadsideRight(250, 20, 0.1);
    roadsideLeft(250, 20, 0.1);
    streetlight(-240, 25);
    streetlight(240, 25);
    glPopMatrix();

    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(0.0, 0.0, 880.0);
    road(1000, 20, 0.1);
    roadsideRight(1000, 20, 0.1);
    roadsideLeft(1000, 20, 0.1);
    streetlight(-900, 25);
    streetlight(900, 25);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(950.0, 0.0, -200.0);
    road(50, 10, 0.05);
    roadsideRight(50, 10, 0.05);
    roadsideLeft(50, 10, 0.05);
    streetlight(-40, 15);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(950.0, 0.0, 200.0);
    road(50, 10, 0.05);
    roadsideRight(50, 10, 0.05);
    roadsideLeft(50, 10, 0.05);
    streetlight(40, 15);
    glPopMatrix();
}
