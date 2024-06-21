#include "defs.h"
#include <iostream>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Razterizer.h"
#include "Matrix44.h"
#include "GenMath.h"

int main(void){
	initscr();
	raw();
	noecho();
    
    Razterizer razterizer(WW, WH);

    float angle = 0;
    int presentidx = 25;
    Matrix44 transformation;
    transformation.scale(Vector3(4, 2, 1));
    transformation.rotate(Vector3(0, 0, 1), GenMath::toRadians(10)); // 20
    // these are coordinates from top left of the screen, in line column
    // in Tuto7, see video, the coordinates are referenced from center of the screen
    Vector4 v1(10, 10, 1, 1);
    Vector4 v2(20, 20, 1, 1);
    Vector4 v3(15, 30, 1, 1);
    //       below is what we'll have in Tuto7
 //       Vector4 v1(-1, 1, 0, 1);
 //       Vector4 v2(1, 1, 0, 1);
 //       Vector4 v3(0, -1, 0, 1);

    v1 = transformation * v1;
    v2 = transformation * v2;
    v3 = transformation * v3;

    razterizer.clearFrame();
    razterizer.razterizeTriangle(Vector2(v1.x, v1.y), Vector2(v2.x, v2.y), Vector2(v3.x, v3.y));
    razterizer.presentFrame(presentidx, presentidx);
    //razterizer.presentFrame(7, 7);
    //razterizer.presentFrame(30, 30);
    getch();
    clear();

    endwin();

    return 0;
}
