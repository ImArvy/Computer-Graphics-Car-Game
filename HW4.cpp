
/*
Ryan Vales
10/19/21
S00339723
CSCI 4550 : Computer Graphics
Homework 4
*/

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <ctime>
#include <cmath>

#define MSEC_PER_FRAME_1 33.3 // 30 fps => 1000 / 30
#define MSEC_PER_FRAME_2 16.6 // 60 fps => 1000 / 60

using namespace std;

float newTruckFrontRed = 0.0;
float newTruckFrontGreen = 1.0;
float newTruckFrontBlue = 1.0;

float newTruckBackRed = 0.75;
float newTruckBackGreen = 0.75;
float newTruckBackBlue = 0.75;

float newTruckEdgeRed = 0.0;
float newTruckEdgeGreen = 0.0;
float newTruckEdgeBlue = 0.0;

float randomObstacleX[20];
float randomObstacleZ[20];
float obstacleX[20];
float obstacleY = 2.0;
float obstacleZ[20];
float obstacleDimension = 2.0;
float obstacles[20];
float obstacleRed = 0.0;
float obstacleGreen = 1.0;
float obstacleBlue = 1.0;

float randomPumpUpX[4];
float randomPumpUpZ[4];
float pumpUpX[4];
float pumpUpY = 2.0;
float pumpUpZ[4];
float pumpUpDimension = 2.0;
float pumpUps[4];
float pumpUpRed = 1.0;
float pumpUpGreen = 0.0;
float pumpUpBlue = 1.0;
float pumpUpTimer = 0.0;

float randomAntTruckX[2];
float randomAntTruckZ[2];
float antTruckX[2];
float antTruckY = 2.0;
float antTruckZ[2];
float antTruckDimension = 2.0;
float antTrucks[2];
float antTruckRed = 1.0;
float antTruckGreen = 0.5;
float antTruckBlue = 0.0;
float antTruckTimer = 0.0;

bool startGame = false;
bool pauseGame = false;
bool wonGame = false;
bool shouldMoveLeft = false;
bool shouldMoveRight = false;

float moveForward = 0.0;
float moveSideways = 0.0;

float newTruckX = 4.0;
float newTruckY = 4.0;
float newTruckZ = 0.0;

float newTruckWidth = 4.0;
float newTruckLength = 8.0;
float newTruckHeight = 4.0;

float cameraX = 4.0;
float cameraY = 20.0;
float cameraZ = 20.0;

float cameraFocusX = 4.0;
float cameraFocusY = 8.0;

int totalScore = 0;

bool truckHit = false;
bool pumpUpTheTruck = false;
bool antManTheTruck = false;
float truckCubeSize = 1.0;

// Class for truck object
class Truck {
private:
    float truckX;
    float truckY;
    float truckZ;

    float truckWidth;
    float truckLength;
    float truckHeight;
public:
    void setTruckCoordinates(float, float, float);
    void setTruckDimensions(float, float, float);
    void drawTruck();
};

// Function definitions for Truck class member functions.
void Truck::setTruckCoordinates(float xParameter, float yParameter, float zParameter) {
    truckX = xParameter;
    truckY = yParameter;
    truckZ = zParameter;
}

void Truck::setTruckDimensions(float widthParameter, float lengthParameter, float heightParameter) {
    truckWidth = widthParameter;
    truckLength = lengthParameter;
    truckHeight = heightParameter;
}

void Truck::drawTruck() {
    if (!antManTheTruck && !pumpUpTheTruck) {
        glPushMatrix();
        glTranslatef(truckX, truckY, truckZ);
        glScalef(truckWidth, truckHeight, truckLength - 2.0);
        glColor3f(newTruckBackRed, newTruckBackGreen, newTruckBackBlue);
        glutSolidCube(truckCubeSize);
        glColor3f(newTruckEdgeRed, newTruckEdgeGreen, newTruckEdgeBlue);
        glutWireCube(truckCubeSize);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(truckX, truckY, truckZ - 4.0);
        glScalef(truckWidth, truckHeight - 2.0, truckLength - 6.0);
        glColor3f(newTruckFrontRed, newTruckFrontGreen, newTruckFrontBlue);
        glutSolidCube(truckCubeSize);
        glColor3f(newTruckEdgeRed, newTruckEdgeGreen, newTruckEdgeBlue);
        glutWireCube(truckCubeSize);
        glPopMatrix();
    } else if (pumpUpTheTruck && !antManTheTruck) {
        glPushMatrix();
        glTranslatef(truckX, truckY, truckZ);
        glScalef(truckWidth, truckHeight, truckLength - 2.0);
        glColor3f(newTruckBackRed, newTruckBackGreen, newTruckBackBlue);
        glutSolidCube(truckCubeSize);
        glColor3f(newTruckEdgeRed, newTruckEdgeGreen, newTruckEdgeBlue);
        glutWireCube(truckCubeSize);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(truckX, truckY, truckZ - 12.0);
        glScalef(truckWidth, truckHeight - 2.0, truckLength - 6.0);
        glColor3f(newTruckFrontRed, newTruckFrontGreen, newTruckFrontBlue);
        glutSolidCube(truckCubeSize);
        glColor3f(newTruckEdgeRed, newTruckEdgeGreen, newTruckEdgeBlue);
        glutWireCube(truckCubeSize);
        glPopMatrix();
    } else if (!pumpUpTheTruck && antManTheTruck) {
        glPushMatrix();
        glTranslatef(truckX, truckY, truckZ);
        glScalef(truckWidth, truckHeight, truckLength - 2.0);
        glColor3f(newTruckBackRed, newTruckBackGreen, newTruckBackBlue);
        glutSolidCube(truckCubeSize);
        glColor3f(newTruckEdgeRed, newTruckEdgeGreen, newTruckEdgeBlue);
        glutWireCube(truckCubeSize);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(truckX, truckY, truckZ - 2.0);
        glScalef(truckWidth, truckHeight - 2.0, truckLength - 6.0);
        glColor3f(newTruckFrontRed, newTruckFrontGreen, newTruckFrontBlue);
        glutSolidCube(truckCubeSize);
        glColor3f(newTruckEdgeRed, newTruckEdgeGreen, newTruckEdgeBlue);
        glutWireCube(truckCubeSize);
        glPopMatrix();
    }
}

// Function calculateDistance fidns difference between two points and
float calculateDistance(float xTwo, float xOne, float yTwo, float yOne, float zTwo, float zOne) {
    float xDiff = xTwo - xOne;
    float yDiff = yTwo - yOne;
    float zDiff = zTwo - zOne;

    float power = 2.0;
    float xDiffSquared = pow(xDiff, power);
    float yDiffSquared = pow(yDiff, power);
    float zDiffSquared = pow(zDiff, power);

    float distance = sqrt(xDiffSquared + yDiffSquared + zDiffSquared);
    return distance;
}

void checkObstacleCollision() {
    float x2;
    float x1;
    float y2;
    float y1;
    float z2;
    float z1;

    float distance;

    float truckRadius = truckCubeSize * 2.0;
    float obstacleRadius = obstacleDimension;

    for (int i = 0; i < 20; i++) {
        x2 = obstacleX[i];
        x1 = (moveSideways + 4.0);
        y2 = obstacleY;
        y1 = newTruckY;
        z2 = obstacleZ[i];
        z1 = moveForward;

        distance = calculateDistance(x2, x1, y2, y1, z2, z1);

        if (distance < truckRadius + obstacleRadius) {
            if (!pumpUpTheTruck) {
                truckHit = true;
            }
        }
    }
}

void checkPumpUpCollision() {
    float x2;
    float x1;
    float y2;
    float y1;
    float z2;
    float z1;

    float distance;

    float truckRadius;
    float powerUpRadius;

    for (int i = 0; i < 4; i++) {
        x2 = pumpUpX[i];
        x1 = (moveSideways + 4.0);
        y2 = pumpUpY;
        y1 = newTruckY;
        z2 = pumpUpZ[i];
        z1 = moveForward;

        truckRadius = truckCubeSize * 2.0;
        powerUpRadius = pumpUpDimension;

        distance = calculateDistance(x2, x1, y2, y1, z2, z1);

        if (distance < truckRadius + powerUpRadius) {
            pumpUpTimer = 0.0;
            pumpUpTheTruck = true;
            antManTheTruck = false;
        }
    }
}

void checkAntTruckCollision() {
    float x2;
    float x1;
    float y2;
    float y1;
    float z2;
    float z1;

    float distance;

    float truckRadius;
    float powerUpRadius; 

    for (int i = 0; i < 2; i++) {
        x2 = antTruckX[i];
        x1 = (moveSideways + 4.0);
        y2 = antTruckY;
        y1 = newTruckY;
        z2 = antTruckZ[i];
        z1 = moveForward;

        truckRadius = truckCubeSize * 2.0;
        powerUpRadius = antTruckDimension;

        distance = calculateDistance(x2, x1, y2, y1, z2, z1);

        if (distance < truckRadius + powerUpRadius) {
            antTruckTimer = 0.0;
            antManTheTruck = true;
            pumpUpTheTruck = false;
        }
    }
}

// Function to handle creation of text.
void writeBitmapString(void* font, const char* string) {
    for (const char* c = string; *c != '\0'; c++)
        glutBitmapCharacter(font, *c);
}

void drawGameText() {
    if (!startGame) {
        glColor3f(0.0, 0.0, 1.0);
        glRasterPos3f(-8.0, 10.0, moveForward);
        writeBitmapString(GLUT_BITMAP_8_BY_13, "Dodge Cyan blocks while aiming for Purple and Orange blocks!");

        glRasterPos3f(0.0, 9.0, moveForward);
        writeBitmapString(GLUT_BITMAP_8_BY_13, "Press 'ENTER' to play!");
    }
    
    if (startGame && !truckHit && !pauseGame && moveForward != (-1000.0 + (newTruckLength - 2.0))) {
        glColor3f(0.0, 0.0, 0.0);
        if (!shouldMoveLeft && !shouldMoveRight) {
            glRasterPos3f(-8.0, 12.0, moveForward);
        } else if (shouldMoveLeft && !shouldMoveRight) {
            glRasterPos3f(moveSideways - 8.0, 12.0, moveForward);
        } else if (!shouldMoveLeft && shouldMoveRight) {
            glRasterPos3f(moveSideways - 8.0, 12.0, moveForward);
        }

        switch (totalScore){
            case 0:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 0");
                break;
            case 1:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 1");
                break;
            case 2:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 2");
                break;
            case 3:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 3");
                break;
            case 4:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 4");
                break;
            case 5:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 5");
                break;
            case 6:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 6");
                break;
            case 7:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 7");
                break;
            case 8:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 8");
                break;
            case 9:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 9");
                break;
            case 10:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 10");
                break;
            case 11:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 11");
                break;
            case 12:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 12");
                break;
            case 13:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 13");
                break;
            case 14:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 14");
                break;
            case 15:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 15");
                break;
            case 16:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 16");
                break;
            case 17:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 17");
                break;
            case 18:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 18");
                break;
            case 19:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 19");
                break;
            case 20:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "Score : 20");
                break;
            default:
                writeBitmapString(GLUT_BITMAP_8_BY_13, "ERROR : INVALID SCORE");
                break;
        }
    } else if (startGame && truckHit) {
        glColor3f(0.0, 0.0, 1.0);
        if (!shouldMoveLeft && !shouldMoveRight) {
            glRasterPos3f(-6.0, 10.0, moveForward);
        } else if (shouldMoveLeft && !shouldMoveRight) {
            glRasterPos3f(moveSideways - 6.0, 10.0, moveForward);
        } else if (!shouldMoveLeft && shouldMoveRight) {
            glRasterPos3f(moveSideways - 6.0, 10.0, moveForward);
        }
        writeBitmapString(GLUT_BITMAP_8_BY_13, "You hit an obstacle, press 'ESC' to exit game!");
    } else if (startGame && pauseGame) {
        glColor3f(0.0, 0.0, 1.0);
        if (!shouldMoveLeft && !shouldMoveRight) {
            glRasterPos3f(-4.0, 10.0, moveForward);
        } else if (shouldMoveLeft && !shouldMoveRight) {
            glRasterPos3f(moveSideways - 4.0, 10.0, moveForward);
        } else if (!shouldMoveLeft && shouldMoveRight) {
            glRasterPos3f(moveSideways - 4.0, 10.0, moveForward);
        }
        writeBitmapString(GLUT_BITMAP_8_BY_13, "Game is paused, press 'SPACE' to resume!");
    } else if (startGame && !truckHit && moveForward == -1000.0 + (newTruckLength - 2.0)) {
        glColor3f(0.0, 0.0, 0.0);
        if (!shouldMoveLeft && !shouldMoveRight) {
            glRasterPos3f(-5.0, 12.0, moveForward + 5.0);
        } else if (shouldMoveLeft && !shouldMoveRight) {
            glRasterPos3f(moveSideways - 5.0, 12.0, moveForward + 5.0);
        } else if (!shouldMoveLeft && shouldMoveRight) {
            glRasterPos3f(moveSideways - 5.0, 12.0, moveForward + 5.0);
        }
        writeBitmapString(GLUT_BITMAP_8_BY_13, "You made it to the finish line, press 'ESC' to exit game!");
    }
}

// Function drawRaceTrack() draws track for truck to drive on
void drawRaceTrack() {
    // Left Side of race track
    glColor3f(0.25, 0.25, 0.25);

    glBegin(GL_POLYGON);

    glVertex3f(-8.0, 0.0, 1000.0); // Close left point of track
    glVertex3f(-8.0, 0.0, -1000.0); // Far left point of track
    glVertex3f(-0.5, 0.0, -1000.0); // Far right point of track
    glVertex3f(-0.5, 0.0, 1000.0); // Close right point of track

    glEnd();

    // Right Side of race track
    glBegin(GL_POLYGON);

    glVertex3f(0.5, 0.0, 1000.0); // Close left point of track
    glVertex3f(0.5, 0.0, -1000.0); // Far left point of track
    glVertex3f(8.0, 0.0, -1000.0); // Far right point of track
    glVertex3f(8.0, 0.0, 1000.0); // Close right point of track

    glEnd();

    // White line in middle of race track
    glColor3f(1.0, 1.0, 1.0);

    glBegin(GL_POLYGON);

    glVertex3f(-0.5, 0.0, 1000.0); // Close left point of white line
    glVertex3f(-0.5, 0.0, -1000.0); // Far left point of white line
    glVertex3f(0.5, 0.0, -1000.0); // Far right point of white line
    glVertex3f(0.5, 0.0, 1000.0); // close right point of white line

    glEnd();

    // Yellow line on left of race track
    glColor3f(1.0, 1.0, 0.0);

    glBegin(GL_POLYGON);

    glVertex3f(-8.0, 0.0, 1000.0); // Close right point of yellow line
    glVertex3f(-8.0, 0.0, -1000.0); // Far right point of yellow line
    glVertex3f(-9.0, 0.0, -1000.0); // Far left point of yellow line
    glVertex3f(-9.0, 0.0, 1000.0); // Close left point of yellow line

    glEnd();

    // Yellow line on right of race track
    glBegin(GL_POLYGON);

    glVertex3f(8.0, 0.0, 1000.0); // Close left point of yellow line
    glVertex3f(8.0, 0.0, -1000.0); // Far left point of yellow line
    glVertex3f(9.0, 0.0, -1000.0); // Far right point of yellow line
    glVertex3f(9.0, 0.0, 1000.0); // Close right point of yellow line

    glEnd();
}

// Function drawCube draws a cube
void drawCube(float leftX, float rightX, float bottomY, float topY, float closeZ, float farZ) {
    // Bottom face
    glBegin(GL_POLYGON);

    glVertex3f(leftX, bottomY, closeZ); // Close left of face
    glVertex3f(leftX, bottomY, farZ); // Far left of face
    glVertex3f(rightX, bottomY, farZ); // Far right of face
    glVertex3f(rightX, bottomY, closeZ); // Close right of face

    glEnd();

    // Top face
    glBegin(GL_POLYGON);

    glVertex3f(leftX, topY, closeZ); // Close left of face
    glVertex3f(leftX, topY, farZ); // Far left of face
    glVertex3f(rightX, topY, farZ); // Far right of face
    glVertex3f(rightX, topY, closeZ); // Close right of face

    glEnd();

    // Front face
    glBegin(GL_POLYGON);

    glVertex3f(leftX, bottomY, closeZ); // Bottom left of face
    glVertex3f(leftX, topY, closeZ); // Top left of face
    glVertex3f(rightX, topY, closeZ); // Top right of face
    glVertex3f(rightX, bottomY, closeZ); // Bottom right of face

    glEnd();

    // Back face
    glBegin(GL_POLYGON);

    glVertex3f(leftX, bottomY, farZ); // Bottom left of face
    glVertex3f(leftX, topY, farZ); // Top left of face
    glVertex3f(rightX, topY, farZ); // Top right of face
    glVertex3f(rightX, bottomY, farZ); // Bottom right of face

    glEnd();

    // Left face
    glBegin(GL_POLYGON);

    glVertex3f(leftX, bottomY, closeZ); // Close bottom of face
    glVertex3f(leftX, bottomY, farZ); // Far bottom of face
    glVertex3f(leftX, topY, farZ); // Far top of face
    glVertex3f(leftX, topY, closeZ); // Close top of face

    glEnd();

    // Right face
    glBegin(GL_POLYGON);

    glVertex3f(rightX, bottomY, closeZ); // Close bottom of face
    glVertex3f(rightX, bottomY, farZ); // Far bottom of face
    glVertex3f(rightX, topY, farZ); // Far top of face
    glVertex3f(rightX, topY, closeZ); // Close top of face

    glEnd();
}

// Function drawFinishLine draws the finish line with help from drawCube
void drawFinishLine() {
    // Left pole of finish line
    glColor3f(0.0, 0.0, 0.0);
    drawCube(-12.0, -10.0, 0.0, 12.0, -980.0, -982.0);

    // Right pole of finish line
    glColor3f(0.0, 0.0, 0.0);
    drawCube(10.0, 12.0, 0.0, 12.0, -980.0, -982.0);

    // Row one, column one
    glColor3f(1.0, 1.0, 1.0);
    drawCube(-10.0, -6.0, 10.0, 12.0, -980.0, -982.0);
    
    // Row one, column two
    glColor3f(0.0, 0.0, 0.0);
    drawCube(-6.0, -2.0, 10.0, 12.0, -980.0, -982.0);

    // Row one, column three
    glColor3f(1.0, 1.0, 1.0);
    drawCube(-2.0, 2.0, 10.0, 12.0, -980.0, -982.0);

    // Row one, column four
    glColor3f(0.0, 0.0, 0.0);
    drawCube(2.0, 6.0, 10.0, 12.0, -980.0, -982.0);

    // Row one, column five
    glColor3f(1.0, 1.0, 1.0);
    drawCube(6.0, 10.0, 10.0, 12.0, -980.0, -982.0);

    // Row two, column one
    glColor3f(0.0, 0.0, 0.0);
    drawCube(-10.0, -6.0, 8.0, 10.0, -980.0, -982.0);

    // Row two, column two
    glColor3f(1.0, 1.0, 1.0);
    drawCube(-6.0, -2.0, 8.0, 10.0, -980.0, -982.0);

    // Row two, column three
    glColor3f(0.0, 0.0, 0.0);
    drawCube(-2.0, 2.0, 8.0, 10.0, -980.0, -982.0);

    // Row two, column four
    glColor3f(1.0, 1.0, 1.0);
    drawCube(2.0, 6.0, 8.0, 10.0, -980.0, -982.0);

    // Row two, column five
    glColor3f(0.0, 0.0, 0.0);
    drawCube(6.0, 10.0, 8.0, 10.0, -980.0, -982.0);
}

void drawGrass() {
    glColor3f(0.0, 1.0, 0.0);

    // Grass left of race track
    glBegin(GL_POLYGON);

    glVertex3f(-9.0, 0.0, 1000.0); // Close right point of grass
    glVertex3f(-9.0, 0.0, -1000.0); // Far right point of grass
    glVertex3f(-100.0, 0.0, -1000.0); // Far left point of grass
    glVertex3f(-100.0, 0.0, 1000.0); // Close left point of grass

    glEnd();

    // Grass right of race track
    glBegin(GL_POLYGON);

    glVertex3f(9.0, 0.0, 1000.0); // Close left point of grass
    glVertex3f(9.0, 0.0, -1000.0); // Far left point of grass
    glVertex3f(100.0, 0.0, -1000.0); // Far right point of grass
    glVertex3f(100.0, 0.0, 1000.0); // Close right point of grass

    glEnd();
}

void drawSkyBox() {
    glColor3f(0.0, 0.0, 1.0);

    // Left side of sky box
    glBegin(GL_POLYGON);

    glVertex3f(-100.0, 0.0, 1000.0); // Bottom left of sky
    glVertex3f(-100.0, 100.0, 1000.0); // Top left of sky
    glVertex3f(-100.0, 100.0, -1000.0); // Top right of sky
    glVertex3f(-100.0, 0.0, -1000.0); // Bottom right of sky

    glEnd();

    // Right side of sky box
    glBegin(GL_POLYGON);

    glVertex3f(100.0, 0.0, 1000.0); // Bottom right of sky
    glVertex3f(100.0, 100.0, 1000.0); // Top right of sky
    glVertex3f(100.0, 100.0, -1000.0); // Top left of sky
    glVertex3f(100.0, 0.0, -1000.0); // Bottom left of sky

    glEnd();

    // Back of sky box
    glBegin(GL_POLYGON);

    glVertex3f(-100.0, 0.0, -1000.0); // Bottom left of sky
    glVertex3f(-100.0, 100.0, -1000.0); // Top left of sky
    glVertex3f(100.0, 100.0, -1000.0); // Top right of sky
    glVertex3f(100.0, 0.0, -1000.0); // Bottom right of sky

    glEnd();

    // Front of sky box
    glBegin(GL_POLYGON);

    glVertex3f(-100.0, 0.0, 1000.0); // Bottom left of sky
    glVertex3f(-100.0, 100.0, 1000.0); // Top left of sky
    glVertex3f(100.0, 100.0, 1000.0); // Top right of sky
    glVertex3f(100.0, 0.0, 1000.0); // Bottom right of sky

    glEnd();

    // Top of sky box
    glBegin(GL_POLYGON);

    glVertex3f(-100.0, 100.0, 1000.0); // Close left of sky
    glVertex3f(-100.0, 100.0, -1000.0); // Back left of sky
    glVertex3f(100.0, 100.0, -1000.0); // Back right of sky
    glVertex3f(100.0, 100.0, 1000.0); // Close right of sky

    glEnd();
}

void randomlySpawnObstacles() {
    for (int i = 0; i < 20; i++) {
        randomObstacleX[i] = rand() % 100;
        if (randomObstacleX[i] <= 49.0) {
            obstacleX[i] = -4.0;
        } else if (randomObstacleX[i] >= 50.0) {
            obstacleX[i] = 4.0;
        }
    }

    for (int j = 0; j < 20; j++) {
        randomObstacleZ[j] = rand() % 1000;
        obstacleZ[j] = randomObstacleZ[j] * -1.0;
    }
}

void randomlySpawnPumpUpBlocks() {
    for (int i = 0; i < 4; i++) {
        randomPumpUpX[i] = rand() % 100;
        if (randomPumpUpX[i] <= 49.0) {
            pumpUpX[i] = -4.0;
        } else if (randomPumpUpX[i] >= 50.0) {
            pumpUpX[i] = 4.0;
        }
    }

    for (int j = 0; j < 4; j++) {
        randomPumpUpZ[j] = rand() % 1000;
        pumpUpZ[j] = randomPumpUpZ[j] * -1.0;
    }
}

void randomlySpawnAntTruckBlocks() {
    for (int i = 0; i < 2; i++) {
        randomAntTruckX[i] = rand() % 100;
        if (randomAntTruckX[i] <= 49.0) {
            antTruckX[i] = -4.0;
        } else if (randomAntTruckX[i] >= 50.0) {
            antTruckX[i] = 4.0;
        }
    }

    for (int j = 0; j < 2; j++) {
        randomAntTruckZ[j] = rand() % 1000;
        antTruckZ[j] = randomAntTruckZ[j] * -1.0;
    }
}

void drawObstacles() {
    for (int i = 0; i < 20; i++) {
        glPushMatrix();
            glTranslatef(obstacleX[i], obstacleY, obstacleZ[i]);
            glScalef(obstacleDimension, obstacleDimension, obstacleDimension);
            glColor3f(obstacleRed, obstacleGreen, obstacleBlue);
            glutSolidCube(1);
            glColor3f(0.0, 0.0, 0.0);
            glutWireCube(1);
        glPopMatrix();
    }
}

void drawPumpUpBlocks() {
    for (int i = 0; i < 4; i++) {
        glPushMatrix();
            glTranslatef(pumpUpX[i], pumpUpY, pumpUpZ[i]);
            glScalef(pumpUpDimension, pumpUpDimension, pumpUpDimension);
            glColor3f(pumpUpRed, pumpUpGreen, pumpUpBlue);
            glutSolidCube(1);
            glColor3f(0.0, 0.0, 0.0);
            glutWireCube(1);
        glPopMatrix();
    }
}

void drawAntTruckBlocks() {
    for (int i = 0; i < 2; i++) {
        glPushMatrix();
        glTranslatef(antTruckX[i], antTruckY, antTruckZ[i]);
        glScalef(antTruckDimension, antTruckDimension, antTruckDimension);
        glColor3f(antTruckRed, antTruckGreen, antTruckBlue);
        glutSolidCube(1);
        glColor3f(0.0, 0.0, 0.0);
        glutWireCube(1);
        glPopMatrix();
    }
}

// Create Truck object using default class constructor
Truck newTruck;

void drawScene(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Call Truck member functions to assign values to data members of the class
    newTruck.setTruckCoordinates(newTruckX, newTruckY, newTruckZ);
    newTruck.setTruckDimensions(newTruckWidth, newTruckLength, newTruckHeight);

    gluLookAt(cameraX, cameraY, cameraZ, cameraFocusX, cameraFocusY, moveForward, 0.0, 1.0, 0.0);

    checkObstacleCollision();
    checkPumpUpCollision();
    checkAntTruckCollision();
    drawGameText();
    drawRaceTrack();
    drawFinishLine();
    drawGrass();
    drawSkyBox();
    drawObstacles();
    drawPumpUpBlocks();
    drawAntTruckBlocks();

    // Call Truck class member function drawTruck to draw the object.
    if (!shouldMoveLeft && !shouldMoveRight) {
        glTranslatef(0.0, 0.0, moveForward);
        newTruck.drawTruck();
        glLoadIdentity();
    } else if (shouldMoveLeft || shouldMoveRight) {
        glTranslatef(moveSideways, 0.0, moveForward);
        newTruck.drawTruck();
        glLoadIdentity();
    }

    glDisable(GL_DEPTH_TEST);
    glutSwapBuffers();
}

// Initialization routine.
void setup(void) {
    glClearColor(1.0, 1.0, 1.0, 0.0);

    randomlySpawnObstacles();
    randomlySpawnPumpUpBlocks();
    randomlySpawnAntTruckBlocks();
}

// OpenGL window reshape routine.
void resize(int w, int h) {
    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, w / h, 10.0, 1000.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyInput(unsigned char key, int x, int y) {
    switch (key) {
    case 13:
        startGame = true;
        break;
    case 27:
         exit(0);
         break;
    case ' ':
         if (!pauseGame) {
             pauseGame = true;
         } else {
             pauseGame = false;
         }
         break;
    default:
         break;
    }
}

void SpecialInput(int key, int x, int y) {
    if (startGame && !truckHit && !pauseGame && !wonGame) {
        switch (key) {
        case GLUT_KEY_LEFT:
            shouldMoveLeft = true;
            shouldMoveRight = false;
            break;
        case GLUT_KEY_RIGHT:
            shouldMoveRight = true;
            shouldMoveLeft = false;
            break;
        default:
            break;
        }
    }
}

void timerFunc(int value) {
    if (startGame && !pauseGame && !truckHit) {
        if (moveForward > -1000.0 + (newTruckLength - 2.0)) {
            moveForward -= 1.0;
            cameraZ -= 1.0;
        } else if (moveForward == -1000.0 + (newTruckLength - 2.0)) {
            wonGame = true;
        }
    } else if (truckHit) {
        moveForward -= 0.0;
        cameraZ -= 0.0;
    }

    for (int i = 0; i < 20; i++) {
        if (moveForward == obstacleZ[i]) {
            totalScore += 1;
        }
    }

    if (shouldMoveLeft && !shouldMoveRight) {
        if (moveSideways > -8.0) {
            moveSideways -= 0.5;
            cameraX -= 0.5;
            cameraFocusX -= 0.5;
        } else if (moveSideways == -8.0) {
             moveSideways -= 0.0;
             cameraX -= 0.0;
             cameraFocusX -= 0.0;
        }    
    } else if (shouldMoveRight && !shouldMoveLeft) {
        if (moveSideways < 0.0) {
            moveSideways += 0.5;
            cameraX += 0.5;
            cameraFocusX += 0.5;
        } else if (moveSideways == 0.0) {
            moveSideways += 0.0;
            cameraX += 0.0;
            cameraFocusX += 0.0;
        }
    }

    if (pumpUpTheTruck) {
        pumpUpTimer += 1.0;
        if (truckCubeSize < 2.0) {
            truckCubeSize += 0.1;
        } else if (pumpUpTimer == 180.0) {
            pumpUpTheTruck = false;
            pumpUpTimer = 0.0;
        }
    } else if (!pumpUpTheTruck) {
        if (truckCubeSize > 1.0) {
            truckCubeSize -= 0.1;
        }
    }

    if (antManTheTruck) {
        antTruckTimer += 1.0;
        if (truckCubeSize > 0.5) {
            truckCubeSize -= 0.1;
        } else if (antTruckTimer == 360.0) {
            antManTheTruck = false;
            antTruckTimer = 0.0;
        }
    } else if (!antManTheTruck) {
        if (truckCubeSize < 1.0) {
            truckCubeSize += 0.1;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(MSEC_PER_FRAME_2, timerFunc, value);
}

// Main function of program.
int main(int argc, char** argv) {
    srand(time(NULL));

    glutInit(&argc, argv);

    glutInitContextVersion(4, 3); // OpenGL version 4.3
    glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE); // Allows use of older versions.

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

    glutInitWindowSize(500, 500); // Window 500px x 500px
    glutInitWindowPosition(100, 100);
    glutCreateWindow("HW4.cpp");

    glutDisplayFunc(drawScene);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutSpecialFunc(SpecialInput);

    glutTimerFunc(MSEC_PER_FRAME_2, timerFunc, 1);

    glewExperimental = GL_TRUE;
    glewInit();

    setup();

    glutMainLoop();
}