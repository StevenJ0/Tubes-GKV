#include "common.h"
#include "truk.h"

//berisi render buat seluruh bagian truk
//saat ini truk masih jadi satu objek,
//kalau sempet tolong dipisah
//jgn lupa untuk semua bagian truk dimasukin
//ke fungsi display() di main.cpp juga

//redefinition variable collision point
float cpDepanX, cpDepanZ, cpBelakangX, cpBelakangZ;

void wheel(float x, float y, float z)
{
    glPushMatrix();
    glTranslatef(x, y, z);
    glPushMatrix();
    for (int j = 0; j <= 360; j += 10) // Finer spokes for detailed wheel
    {
        glPushMatrix();
        glTranslatef(0, 0, -0.5);
        glRotated(90, 1, 0, 0);
        glRotated(j, 0, 1, 0);
        glTranslatef(0, 3, 1);
        glColor3f(0.2, 0.2, 0.2); // Dark gray tire
        glBegin(GL_QUADS);
        glVertex3f(0, 0, 0);
        glVertex3f(0.4, 0, 0);
        glVertex3f(0.4, 0.8, 0);
        glVertex3f(0, 0.8, 0);
        glEnd();
        glPopMatrix();
    }
    glPopMatrix();

    //pelek ban
    float th;
    glPushMatrix();
    glTranslatef(0, 0, 3.1);
    glColor3f(0.7, 0.7, 0.7); // Light gray rim
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=8) // Detailed rim pattern
    {
        th = i * M_PI / 180;
        float radius = (i % 16 == 0) ? 0.75 : 1.0; // More pronounced star pattern
        glVertex3f(radius * cos(th), radius * sin(th), 0);
    }
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(0, 0, 2.5);
    glColor3f(0.7, 0.7, 0.7);
    glBegin(GL_POLYGON);
    for(int i=0; i<360; i+=8)
    {
        th = i * M_PI / 180;
        float radius = (i % 16 == 0) ? 0.75 : 1.0;
        glVertex3f(radius * cos(th), radius * sin(th), 0);
    }
    glEnd();
    glPopMatrix();

    glPopMatrix();
}

/*posisi 0 = container paling depan (pertama)
ukuran container pertama lebih pendek dibanding container dibelakangnya*/
void container(int posisi, float x, float y, float z) {
    glPushMatrix();
        glTranslatef(x, y, z);
        glPushMatrix();
        glTranslatef(0, 2.0, 0.0);
        if(posisi == 0){
            glScalef(2.2, 1.1, 1.1);
        }else{
            glScalef(2.7, 1.1, 1.1);
        }
        glColor3f(0.1, 0.2, 0.6); // Deep blue container
        glutSolidCube(3.0f);
        // Edge highlight
        glColor3f(0.7, 0.7, 0.7); // Gray for edges
        glLineWidth(2.0);
        glBegin(GL_LINE_LOOP);
        glVertex3f(-1.5, -1.5, -1.5);
        glVertex3f(1.5, -1.5, -1.5);
        glVertex3f(1.5, 1.5, -1.5);
        glVertex3f(-1.5, 1.5, -1.5);
        glEnd();
        glBegin(GL_LINE_LOOP);
        glVertex3f(-1.5, -1.5, 1.5);
        glVertex3f(1.5, -1.5, 1.5);
        glVertex3f(1.5, 1.5, 1.5);
        glVertex3f(-1.5, 1.5, 1.5);
        glEnd();
        glPopMatrix();

        //atur roda buat container
        glScalef(0.65,0.65,0.65);
        if(posisi == 0){
            wheel(-2.5,0.75,-0.75); //kanan
            wheel(-2.5,0.75,-4.85); //kiri
        }
        else{
            wheel(4.0,0.75,-0.75); //depan kanan
            wheel(4.0,0.75,-4.85); //depan kiri
            wheel(-3.5,0.75,-0.75); //belakang kanan
            wheel(-3.5,0.75,-4.85); //belakang kiri
        }
    glPopMatrix();
}

void wheelDepan(float x, float y, float z) {
    glPushMatrix();
        glScalef(0.65,0.65,0.65);
        wheel(x,y,-0.75+z); //wheel kanan
        wheel(x,y,-4.85+z); //wheel kiri
    glPopMatrix();
}

void collisionBox(float putaran, float tx, float ty, float tz) {
    putaran = putaran - 90;
    cpDepanX = tx + -10.0*sin(putaran*M_PI/180);
    cpDepanZ = tz + -10.0*cos(putaran*M_PI/180);

    cpBelakangX = tx + 5.0*sin(putaran*M_PI/180);
    cpBelakangZ = tz + 5.0*cos(putaran*M_PI/180);
}

void Truk(float putaran, float x, float y, float z){
    collisionBox(putaran, x, y, z);
    glTranslatef(x, y, z);

    glPushMatrix();
    glRotated(putaran, 0.0f, 1.0f, 0.0f);

    glColor3f(0.1, 0.2, 0.6); // Deep blue container
    container(0,4,0,0); //depan
    
    //Depan
    glPushMatrix();
    //Hiasan 1
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7); // Gray decoration
    glTranslatef(1.5,2,1.51);
    glRectf(5.5, 0.6, -0.6, -0.6);
    glPopMatrix();
    
    //hiasan 2
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(1.5,2,-1.51);
    glRectf(5.5, 0.6, -0.6, -0.6);
    glPopMatrix();
    glPopMatrix();
    
    //belakang
    glPushMatrix();
    glTranslatef(-6.2, 0, 0);
    //Hiasan 1
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(1.5,2,1.51);
    glRectf(5.5, 0.6, -2.0, -0.6);
    glPopMatrix();
    
    //hiasan 2
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(1.5,2,-1.51);
    glRectf(5.5, 0.6, -2.0, -0.6);
    glPopMatrix();
    glPopMatrix();
    
    //hiasan biru belakang
    glPushMatrix();
    glTranslatef(-8.3, 0, -1.5);
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glTranslatef(1.5,2,1.51);
    glRotatef(90, 0, 1, 0);
    glRectf(1.6, 0.6, -1.6, -0.6);
    glPopMatrix();
    glPopMatrix();
    
    //lampu kiri kuning
    glPushMatrix();
    glTranslatef(-8.3, -1.2, -2.55);
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.0); // Amber light
    glTranslatef(1.5,2,1.51);
    glRotatef(90, 0, 1, 0);
    glRectf(0.25, 0.12, -0.25, -0.12); // Slightly smaller for proportionality
    glPopMatrix();
    glPopMatrix();
    
    //lampu kiri kuning
    glPushMatrix();
    glTranslatef(-8.3, -1.2, -2.1);
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.0);
    glTranslatef(1.5,2,1.51);
    glRotatef(90, 0, 1, 0);
    glRectf(0.25, 0.12, -0.25, -0.12);
    glPopMatrix();
    glPopMatrix();
    
    //lampu kanan kuning
    glPushMatrix();
    glTranslatef(-8.3, -1.2, -0.9);
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.0);
    glTranslatef(1.5,2,1.51);
    glRotatef(90, 0, 1, 0);
    glRectf(0.25, 0.12, -0.25, -0.12);
    glPopMatrix();
    glPopMatrix();
    
    //lampu kanan kuning
    glPushMatrix();
    glTranslatef(-8.3, -1.2, -0.5);
    glPushMatrix();
    glColor3f(1.0, 0.6, 0.0);
    glTranslatef(1.5,2,1.51);
    glRotatef(90, 0, 1, 0);
    glRectf(0.25, 0.12, -0.25, -0.12);
    glPopMatrix();
    glPopMatrix();
    
    glColor3f(0.1, 0.2, 0.6); // Deep blue container
    container(1,-3,0,0); //belakang

    //truck depan
    glPushMatrix();
    glTranslatef(8.75,1.7,1.5);
    glColor3f(0.1, 0.2, 0.6); // Deep blue cabin
    glBegin(GL_POLYGON);
    glVertex3f(-1.6f,-1.3f,0.0f); //kiri bawah
    glVertex3f(1.6f,-1.3f,0.0f); //kanan bawah
    glVertex3f(1.6f,0.4f,0.0f); //kanan atas
    glVertex3f(0.3f,0.8f,0.0f); //tengah kanan atas
    glVertex3f(-0.1f,1.4f,0.0f); //tengah kiri atas
    glVertex3f(-1.6f,1.6f,0.0f); //kiri atas
    glEnd();
    glPopMatrix();

    //belakang
    glPushMatrix();
    glTranslatef(8.75,1.7,1.5);
    glColor3f(0.1, 0.2, 0.6);
    glBegin(GL_POLYGON);
    glVertex3f(-1.6f,-1.3f,-3.0f); //kiri bawah
    glVertex3f(1.6f,-1.3f,-3.0f); //kanan bawah
    glVertex3f(1.6f,0.4f,-3.0f); //kanan atas
    glVertex3f(0.3f,0.8f,-3.0f); //tengah kanan atas
    glVertex3f(-0.1f,1.4f,-3.0f); //tengah kiri atas
    glVertex3f(-1.6f,1.6f,-3.0f); //kiri atas
    glEnd();
    glPopMatrix();

    //tutup kiri
    glPushMatrix();
    glTranslatef(8.75,1.7,1.5);
    glColor3f(0.1, 0.2, 0.6);
    glBegin(GL_QUADS);
    glVertex3f(-1.6f,-1.3f,-3.0f);
    glVertex3f(-1.6f,1.6f,-3.0f);
    glVertex3f(-1.6f,1.6f,0.0f);
    glVertex3f(-1.6f,-1.3f,0.0f);
    glEnd();
    glPopMatrix();

    //tutup bawah
    glPushMatrix();
    glTranslatef(8.75,1.7,1.5);
    glColor3f(0.1, 0.2, 0.6);
    glBegin(GL_QUADS);
    glVertex3f(-1.6f,-1.3f,0.0f);
    glVertex3f(1.6f,-1.3f,0.0f);
    glVertex3f(1.6f,-1.3f,-3.0f);
    glVertex3f(-1.6f,-1.3f,-3.0f);
    glEnd();
    glPopMatrix();

    //tutup depan
    glPushMatrix();
    glTranslatef(8.75,1.7,1.5);
    glColor3f(0.1, 0.2, 0.6);
    glBegin(GL_QUADS);
    glVertex3f(1.6f,0.4f,-3.0f);
    glVertex3f(1.6f,-1.3f,-3.0f);
    glVertex3f(1.6f,-1.3f,0.0f);
    glVertex3f(1.6f,0.4f,0.0f);
    glEnd();
    glPopMatrix();

    //cerobong kanan
    glPushMatrix();
    GLUquadricObj *pObj;
    pObj = gluNewQuadric();
    gluQuadricNormals(pObj, GLU_SMOOTH);
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7); // Gray exhaust
    glRotated(270, 1, 0, 0);
    glTranslatef(7, 1.2, 0.6);
    gluCylinder(pObj, 0.25, 0.25, 4.2, 12, 12);
    glPopMatrix();
    glPopMatrix();

    //cerobong kiri
    glPushMatrix();
    glColor3f(0.7, 0.7, 0.7);
    glRotated(270, 1, 0, 0);
    glTranslatef(7, -1.2, 0.5);
    gluCylinder(pObj, 0.25, 0.25, 4.2, 12, 12);
    glPopMatrix();

    //plat
    glPushMatrix();
    glTranslatef(10.4,1,0);
    glRotatef(90,0,1,0);
    glColor3f(0.7, 0.7, 0.7); // Gray plate
    glRectf(0.6,0.3,-0.6,-0.3);
    glPopMatrix();

    //lampu kiri kuning
    glPushMatrix();
    glTranslatef(10.32, 1.8, 1.0);
    glRotatef(90,0,1,0);
    glColor3f(1.0, 0.6, 0.0); // Amber light
    glRectf(0.25,0.12,-0.25,-0.12);
    glPopMatrix();

    //lampu kiri putih
    glPushMatrix();
    glTranslatef(10.3, 1.8, 1.1);
    glRotatef(90,0,1,0);
    glColor3f(1.0, 1.0, 1.0); // Bright white light
    glRectf(0.35,0.17,-0.35,-0.17);
    glPopMatrix();

    //lampu kanan kuning
    glPushMatrix();
    glTranslatef(10.32, 1.8, -1.0);
    glRotatef(90,0,1,0);
    glColor3f(1.0, 0.6, 0.0);
    glRectf(0.25,0.12,-0.25,-0.12);
    glPopMatrix();

    //lampu kanan putih
    glPushMatrix();
    glTranslatef(10.3, 1.8, -1.0);
    glRotatef(90,0,1,0);
    glColor3f(1.0, 1.0, 1.0);
    glRectf(0.35,0.17,-0.35,-0.17);
    glPopMatrix();

    //tutup atas
    glPushMatrix();
    glTranslatef(8.75,1.7,1.5);
    glColor3f(0.1, 0.2, 0.6);
    glBegin(GL_QUADS);
    glVertex3f(1.6f,0.4f,-3.0f);
    glVertex3f(1.6f,0.4f,0.0f);
    glVertex3f(0.3f,0.8f,0.0f);
    glVertex3f(0.3f,0.8f,-3.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.75,1.7,1.5);
    glColor3f(0.1, 0.2, 0.6);
    glBegin(GL_QUADS);
    glVertex3f(-0.1f,1.4f,-3.0f);
    glVertex3f(-0.1f,1.4f,0.0f);
    glVertex3f(-1.6f,1.6f,0.0f);
    glVertex3f(-1.6f,1.6f,-3.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glTranslatef(8.75,1.7,1.5);
    glColor3f(0.7, 0.7, 0.7); // Gray roof panel
    glBegin(GL_QUADS);
    glVertex3f(0.3f,0.8f,0.0f);
    glVertex3f(-0.1f,1.4f,0.0f);
    glVertex3f(-0.1f,1.4f,-3.0f);
    glVertex3f(0.3f,0.8f,-3.0f);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    wheelDepan(13.5,0.75,0);
    glEnd();
    glPopMatrix();

    glPopMatrix();
}
