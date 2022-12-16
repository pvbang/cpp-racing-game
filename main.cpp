#include <windows.h>
#include <GL/glut.h>

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <math.h>
#include <cmath>

int start = 0;

int score = 0;
int speed = 30;
int level = 0;

float may1 = 0;
float may2 = 0;
float may3 = 0;

float vachDuongTren = 0;
float vachDuongGiua = 0;
float vachDuongDuoi = 0;

float carLocation = 0;

float xcar1 = 0;
float xcar2 = 0;
float xcar3 = 0;
float xcar4 = 0;
float xcar5 = 0;

float ycar1 = 0;
float ycar2 = 0;
float ycar3 = 0;
float ycar4 = 0;
float ycar5 = 0;

void showCurve (float x, float y, float goc, float chieuDai, float banKinh, float chieuRong) {
    const float outer = banKinh + chieuRong;
    glBegin( GL_QUAD_STRIP );
    for (unsigned int i = 0; i <= 50; i++) {
        float a = goc + ( i / (float)30 ) * chieuDai;
        glVertex2f(banKinh * cos(a) + x, banKinh * sin(a) + y);
        glVertex2f(outer * cos(a) + x, outer * sin(a) + y);
    }
    glEnd();
}

void showString (float x, float y, void *font, const char *string) {
    const char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

float float_rand (float min, float max) {
    float scale = rand() / (float) RAND_MAX; 
    return min + scale * ( max - min );     
}

float checkRandom (float xcar1, float xcar2) {
	xcar2 = float_rand(-0.6, 0.6);
	while (fabs(xcar2 - xcar1) < 0.09) {
    	xcar2 = float_rand(-0.6, 0.6);
    	checkRandom (xcar2, xcar1);
	}
	return xcar2;
}

void firstScreen() {
	// bau troi
	glColor3ub(30, 146, 235);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glColor3ub(83, 170, 237);
    glVertex2f(1, 0.3);
    glVertex2f(-1, 0.3);
    glEnd();
    
    // co
    glColor3ub(79, 125, 50);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 0.3);
    glVertex2f(1, 0.3);
    glColor3ub(72, 168, 12);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glEnd();

	// duong dua
	glColor3ub(143, 148, 142);
    glBegin(GL_POLYGON);
    glVertex2f(0, 0.3);
    glVertex2f(0.2, 0.3);
    glColor3ub(180, 186, 179);
    glVertex2f(0.8, -1);
    glVertex2f(-0.9, -1);
    glEnd();
    
    // vach vang
    glColor3ub(211, 214, 4);
    glBegin(GL_POLYGON);
    glVertex2f(0.095, 0.3);
    glVertex2f(0.105, 0.3);
    glColor3ub(243, 247, 0);
    glVertex2f(-0, -1);
    glVertex2f(-0.1, -1);
    glEnd();
    
    // vach trang
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2f(-0.015, 0.3);
    glVertex2f(0, 0.3);
    glColor3ub(240, 240, 240);
    glVertex2f(-0.9, -1);
    glVertex2f(-1, -1);
    glEnd();
    
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2f(0.2, 0.3);
    glVertex2f(0.215, 0.3);
    glColor3ub(240, 240, 240);
    glVertex2f(0.9, -1);
    glVertex2f(0.8, -1);
    glEnd();
    
    // bang huong dan
	glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2f(may1 + 1, 0.75);
    glVertex2f(may1 + 1, 0.65);
    glVertex2f(may1 + 0.6, 0.65);
    glVertex2f(may1 + 0.6, 0.75);
    glEnd();
  
    char huongdan[50];
    sprintf(huongdan, "Nhan SPACE de Bat dau");
    glColor3f(0, 0, 0);
    showString(may1 + 0.63, 0.69, (void *)GLUT_BITMAP_8_BY_13, huongdan);
    
	may1 -= 0.001f;
    if (may1 < -2) {
        may1 = 0.5;
    }
    
    // may 2
	glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2f(may2 + 0, 0.9);
    glVertex2f(may2 + 0, 0.85);
    glVertex2f(may2 + -0.2, 0.85);
    glVertex2f(may2 + -0.2, 0.9);
    glEnd();
    
    may2 -= 0.001f;
    if (may2 < -1) {
        may2 = 1.3;
    }
    
    // may 3
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2f(may3 + -0.8, 0.6);
    glVertex2f(may3 + -0.8, 0.5);
    glVertex2f(may3 + -0.95, 0.5);
    glVertex2f(may3 + -0.95, 0.6);
    glEnd();
    
    may3 -= 0.001f;
    if (may3 < -0.5) {
        may3 = 2;
    }

}

void xe (int car, float xcar, float ycar, int red, int green, float blue, int redTop, int greenTop, float blueTop) {
	// dau xe
	glColor3ub(red, green, blue);
    showCurve(xcar + 0, ycar + 2 + -0.78, 1.57, 5, 0, 0.04);
	glColor3f(red, green, blue);
    showCurve (xcar + 0, ycar + 2 + -0.78, 0, 5, 0, 0.04); 
    
    // duoi xe
    glColor3ub(red, green, blue);
    showCurve(xcar + 0, ycar + 2 + -0.94, 2, 5, 0, 0.04);
	glColor3f(red, green, blue);
    showCurve (xcar + 0, ycar + 2 + -0.94, 2.5, 5, 0, 0.04); 
    
    // than xe (vuong)
    glColor3ub(redTop, greenTop, blueTop);
    glBegin(GL_POLYGON);
    glVertex2f(xcar + -0.04, ycar + 2 + -0.78);
    glVertex2f(xcar + 0.04, ycar + 2 + -0.78);
    glVertex2f(xcar + 0.04, ycar + 2 + -0.94);
    glVertex2f(xcar + -0.04, ycar + 2 + -0.94);
    glEnd();
    
    // than xe tren (vuong)
    glColor3ub(red, green, blue);
	glBegin(GL_POLYGON);
    glVertex2f(xcar + -0.028, ycar + 2 + -0.81);
    glVertex2f(xcar + 0.028, ycar + 2 + -0.81);
    glVertex2f(xcar + 0.028, ycar + 2 + -0.89);
    glVertex2f(xcar + -0.028, ycar + 2 + -0.89);
    glEnd();
    
    // 4 duong vach
	glColor3ub(red, green, blue);
    glBegin(GL_POLYGON);
    glVertex2f(xcar + -0.04, ycar + 2 + -0.78);
    glVertex2f(xcar + -0.04, ycar + 2 + -0.79);
    glVertex2f(xcar + -0.02, ycar + 2 + -0.85);
    glVertex2f(xcar + -0.02, ycar + 2 + -0.84);
    glEnd();
    
    glColor3ub(red, green, blue);
    glBegin(GL_POLYGON);
    glVertex2f(xcar + 0.04, ycar + 2 + -0.78);
    glVertex2f(xcar + 0.04, ycar + 2 + -0.79);
    glVertex2f(xcar + 0.02, ycar + 2 + -0.85);
    glVertex2f(xcar + 0.02, ycar + 2 + -0.84);
    glEnd();
    
    glColor3ub(red, green, blue);
    glBegin(GL_POLYGON);
    glVertex2f(xcar + 0.02, ycar + 2 + -0.85);
    glVertex2f(xcar + 0.02, ycar + 2 + -0.84);
    glVertex2f(xcar + 0.04, ycar + 2 + -0.92);
    glVertex2f(xcar + 0.04, ycar + 2 + -0.91);
    glEnd();
    
    glColor3ub(red, green, blue);
    glBegin(GL_POLYGON);
    glVertex2f(xcar + -0.02, ycar + 2 + -0.85);
    glVertex2f(xcar + -0.02, ycar + 2 + -0.84);
    glVertex2f(xcar + -0.04, ycar + 2 + -0.92);
    glVertex2f(xcar + -0.04, ycar + 2 + -0.91);
    glEnd();
    
    // lop xe
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(xcar + -0.05, ycar + 2 + -0.79);
    glVertex2f(xcar + -0.04, ycar + 2 + -0.79);
    glVertex2f(xcar + -0.04, ycar + 2 + -0.83);
    glVertex2f(xcar + -0.05, ycar + 2 + -0.83);
    glEnd();
    
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(xcar + -0.05, ycar + 2 + -0.88);
    glVertex2f(xcar + -0.04, ycar + 2 + -0.88);
    glVertex2f(xcar + -0.04, ycar + 2 + -0.92);
    glVertex2f(xcar + -0.05, ycar + 2 + -0.92);
    glEnd();
    
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(xcar + 0.05, ycar + 2 + -0.79);
    glVertex2f(xcar + 0.04, ycar + 2 + -0.79);
    glVertex2f(xcar + 0.04, ycar + 2 + -0.83);
    glVertex2f(xcar + 0.05, ycar + 2 + -0.83);
    glEnd();
    
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(xcar + 0.05, ycar + 2 + -0.88);
    glVertex2f(xcar + 0.04, ycar + 2 + -0.88);
    glVertex2f(xcar + 0.04, ycar + 2 + -0.92);
    glVertex2f(xcar + 0.05, ycar + 2 + -0.92);
    glEnd();
    
    switch (car) {
    	case 1:
    		ycar1 -= 0.02f;
		    if (ycar1 < -2.2) {
		        ycar1 = 0;
		        xcar1 = checkRandom(xcar5, xcar1);
		    }
		    if ((fabs(carLocation - xcar1) < 0.09) && (ycar1 < -1.75)) {
		        start = 0;
		    }
		    break;
		case 2:
    		ycar2 -= 0.02f;
		    if (ycar2 < -2.2 -0.5) {
		        ycar2 = 0 -0.5;
		        xcar2 = checkRandom(xcar1, xcar2);
		    }
		    if ((fabs(carLocation - xcar2) < 0.09) && (ycar2 < -1.75 -0.5)) {
		        start = 0;
		    }
		    break;
		case 3:
    		ycar3 -= 0.02f;
		    if (ycar3 < -2.2 -1) {
		        ycar3 = 0 -1;
		        xcar3 = checkRandom(xcar2, xcar3);
		    }
		    if ((fabs(carLocation - xcar3) < 0.09) && (ycar3 < -1.75 -1)) {
		        start = 0;
		    }
		    break;
		case 4:
    		ycar4 -= 0.02f;
		    if (ycar4 < -2.2 -1.5) {
		        ycar4 = 0 -1.5;
		        xcar4 = checkRandom(xcar3, xcar4);
		    }
		    if ((fabs(carLocation - xcar4) < 0.09) && (ycar4 < -1.75 -1.5)) {
		        start = 0;
		    }
		    break;
		case 5:
    		ycar5 -= 0.02f;
		    if (ycar5 < -2.2 -2) {
		        ycar5 = 0 -2;
		        xcar5 = checkRandom(xcar4, xcar5);
		    }
		    if ((fabs(carLocation - xcar5) < 0.09) && (ycar5 < -1.75 -2)) {
		        start = 0;
		    }
		    break;
		default:
			break;
	}
    
}


void gameScreen() {
	// co
	glColor3ub(79, 125, 50);
    glBegin(GL_POLYGON);
    glVertex2f(-1, 1);
    glVertex2f(1, 1);
    glVertex2f(1, -1);
    glVertex2f(-1, -1);
    glEnd();
    
    // duong dua
	glColor3ub(143, 148, 142);
    glBegin(GL_POLYGON);
    glVertex2f(-0.7, 1);
    glVertex2f(0.7, 1);
    glVertex2f(0.7, -1);
    glVertex2f(-0.7, -1);
    glEnd();
    
    // vach trang
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2f(-0.79, 1);
    glVertex2f(-0.7, 1);
    glColor3ub(240, 240, 240);
    glVertex2f(-0.7, -1);
    glVertex2f(-0.79, -1);
    glEnd();
    
    glColor3ub(255, 255, 255);
    glBegin(GL_POLYGON);
    glVertex2f(0.7, 1);
    glVertex2f(0.79, 1);
    glColor3ub(240, 240, 240);
    glVertex2f(0.79, -1);
    glVertex2f(0.7, -1);
    glEnd();
    
    // vach duong tren
    glColor3ub(211, 214, 4);
    glBegin(GL_POLYGON);
    glVertex2f(-0.035, vachDuongTren + 1);
    glVertex2f(0.035, vachDuongTren + 1);
    glVertex2f(0.035, vachDuongTren + 0.6);
    glVertex2f(-0.035, vachDuongTren + 0.6);
    glEnd(); 
    
    vachDuongTren -= 0.02f;
    if (vachDuongTren < -2) {
        vachDuongTren = 0.4;
        score++;
    }
    
    // vach duong giua
    glColor3ub(211, 214, 4);
    glBegin(GL_POLYGON);
    glVertex2f(-0.035, vachDuongGiua + 0.2);
    glVertex2f(0.035, vachDuongGiua + 0.2);
    glVertex2f(0.035, vachDuongGiua + -0.2);
    glVertex2f(-0.035, vachDuongGiua + -0.2);
    glEnd(); 
    
    vachDuongGiua -= 0.02f;
    if (vachDuongGiua < -1.2) {
        vachDuongGiua = 1.2;
        score++;
    }
    
    // vach duong duoi
    glColor3ub(211, 214, 4);
    glBegin(GL_POLYGON);
    glVertex2f(-0.035, vachDuongDuoi + -0.6);
    glVertex2f(0.035, vachDuongDuoi + -0.6);
    glVertex2f(0.035, vachDuongDuoi + -1);
    glVertex2f(-0.035, vachDuongDuoi + -1);
    glEnd(); 
    
    vachDuongDuoi -= 0.02f;
    if (vachDuongDuoi < -0.4) {
        vachDuongDuoi = 2;
        score++;
    }

	// bang diem
	glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(-1, -0.72);
    glVertex2f(-0.7, -0.72);
    glVertex2f(-0.7, -1);
    glVertex2f(-1, -1);
    glEnd();
    
    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2f(-1, -0.72);
    glVertex2f(-0.79, -0.72);
    glVertex2f(-0.79, -0.7);
    glVertex2f(-1, -0.7);
    glEnd();
    
    // diem
    char diem[50];
    sprintf(diem, "Diem   : %d", score);
    glColor3f(0, 1, 0);
    showString(-0.98, -0.79, (void *)GLUT_BITMAP_8_BY_13, diem);
    
    // toc do
    char tocDo[50];
    sprintf(tocDo, "Toc do : %d km/h", speed);
    glColor3f(0, 1, 0);
    showString(-0.98, -0.87, (void *)GLUT_BITMAP_8_BY_13, tocDo);
    
    // muc do
    if (score % 10 == 0) {
        int last = score / 10;
        if (last != level) {
            level = score / 10;
            speed = speed + 2;
        }
    }
    
    char mucDo[50];
    sprintf(mucDo, "Muc do : %d", level);
    glColor3f(0, 1, 0);
    showString(-0.98, -0.95, (void *)GLUT_BITMAP_8_BY_13, mucDo);
    
    
    // XE CHINH
    // dau xe
	glColor3f(0, 0, 1);
    showCurve(carLocation + 0, -0.76, 1.57, 5, 0, 0.04);
	glColor3f(0, 0, 1);
    showCurve (carLocation + 0, -0.76, 0, 5, 0, 0.04); 
    
    // duoi xe
    glColor3f(0, 0, 1);
    showCurve(carLocation + 0, -0.92, 2, 5, 0, 0.04);
	glColor3f(0, 0, 1);
    showCurve (carLocation + 0, -0.92, 2.5, 5, 0, 0.04); 
    
    // than xe (vuong)
    glColor3ub(0, 50, 255);
    glBegin(GL_POLYGON);
    glVertex2f(carLocation + -0.04, -0.76);
    glVertex2f(carLocation + 0.04, -0.76);
    glVertex2f(carLocation + 0.04, -0.92);
    glVertex2f(carLocation + -0.04, -0.92);
    glEnd();
    
    // than xe tren (vuong)
    glColor3ub(0, 0, 255);
	glBegin(GL_POLYGON);
    glVertex2f(carLocation + -0.028, -0.81);
    glVertex2f(carLocation + 0.028, -0.81);
    glVertex2f(carLocation + 0.028, -0.89);
    glVertex2f(carLocation + -0.028, -0.89);
    glEnd();
    
    // 4 duong vach
	glColor3ub(0, 0, 255);
    glBegin(GL_POLYGON);
    glVertex2f(carLocation + -0.04, -0.78);
    glVertex2f(carLocation + -0.04, -0.79);
    glVertex2f(carLocation + -0.02, -0.85);
    glVertex2f(carLocation + -0.02, -0.84);
    glEnd();
    
    glColor3ub(0, 0, 255);
    glBegin(GL_POLYGON);
    glVertex2f(carLocation + 0.04, -0.78);
    glVertex2f(carLocation + 0.04, -0.79);
    glVertex2f(carLocation + 0.02, -0.85);
    glVertex2f(carLocation + 0.02, -0.84);
    glEnd();
    
    glColor3ub(0, 0, 255);
    glBegin(GL_POLYGON);
    glVertex2f(carLocation + 0.02, -0.85);
    glVertex2f(carLocation + 0.02, -0.84);
    glVertex2f(carLocation + 0.04, -0.92);
    glVertex2f(carLocation + 0.04, -0.91);
    glEnd();
    
    glColor3ub(0, 0, 255);
    glBegin(GL_POLYGON);
    glVertex2f(carLocation + -0.02, -0.85);
    glVertex2f(carLocation + -0.02, -0.84);
    glVertex2f(carLocation + -0.04, -0.92);
    glVertex2f(carLocation + -0.04, -0.91);
    glEnd();
    
    // lop xe
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(carLocation + -0.05, -0.79);
    glVertex2f(carLocation + -0.04, -0.79);
    glVertex2f(carLocation + -0.04, -0.83);
    glVertex2f(carLocation + -0.05, -0.83);
    glEnd();
    
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(carLocation + -0.05, -0.88);
    glVertex2f(carLocation + -0.04, -0.88);
    glVertex2f(carLocation + -0.04, -0.92);
    glVertex2f(carLocation + -0.05, -0.92);
    glEnd();
    
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(carLocation + 0.05, -0.79);
    glVertex2f(carLocation + 0.04, -0.79);
    glVertex2f(carLocation + 0.04, -0.83);
    glVertex2f(carLocation + 0.05, -0.83);
    glEnd();
    
    glColor3f(0, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(carLocation + 0.05, -0.88);
    glVertex2f(carLocation + 0.04, -0.88);
    glVertex2f(carLocation + 0.04, -0.92);
    glVertex2f(carLocation + 0.05, -0.92);
    glEnd();

	xe(1, xcar1, ycar1, 255, 0, 0, 255, 70, 70);
	
	xe(2, xcar2, ycar2 + 0.5, 0, 255, 0, 100, 255, 100);
	
	xe(3, xcar3, ycar3 + 1, 255, 255, 0, 255, 255, 130);
	
	xe(4, xcar4, ycar4 + 1.5, 255, 0, 255, 255, 80, 255);
	
	xe(5, xcar5, ycar5 + 2, 0, 255, 255, 130, 255, 255);

}

void timer (int) {
    glutPostRedisplay();
    glutTimerFunc(1000 / speed, timer, 0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (start == 1) {
    	glClearColor(1, 1, 1, 1);
		gameScreen();
    }
    else {
    	start = 0;
        firstScreen();
    }

    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    glFlush();
    glutSwapBuffers();
}

void specialKey (int key, int x, int y) {
    switch (key) {
	    case GLUT_KEY_DOWN:
	    	if (speed != 1) {
	    		speed--;
			}
	        break;
	        
	    case GLUT_KEY_UP:
	    	speed++;
	        break;
	
	    case GLUT_KEY_LEFT:
	    	if (carLocation > -0.60) {
	    		carLocation -= 0.03f;
			}
			break;
	
	    case GLUT_KEY_RIGHT:
	    	if (carLocation < 0.60) {
	        	carLocation += 0.03f;
	    	}
	        break;
	
	    default:
	        break;
    }
}


void keyboard (unsigned char key, int x, int y) {
    switch (key) {
	    case ' ':
	        if (start == 0) {
	            start = 1;

				score = 0;
				speed = 30;
				level = 0;
				
				may1 = 0;
				may2 = 0;
				may3 = 0;
				
				vachDuongTren = 0;
				vachDuongGiua = 0;
				vachDuongDuoi = 0;
				
				carLocation = 0;
				
				xcar1 = checkRandom(xcar5, xcar1);
				xcar2 = checkRandom(xcar1, xcar2);
				xcar3 = checkRandom(xcar2, xcar3);
				xcar4 = checkRandom(xcar3, xcar4);
				xcar5 = checkRandom(xcar4, xcar5);
				
				ycar1 = 0;
				ycar2 = 0;
				ycar3 = 0;
				ycar4 = 0;
				ycar5 = 0;
	        }
	        break;
	
	    case 27:
	        exit(0);
	        break;
	        
	    default:
	        break;
	}
}

int main (int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    int POS_X = (glutGet(GLUT_SCREEN_WIDTH) - 1000) >> 1;
    int POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - 700) >> 1;
    glutInitWindowSize(1000, 650);
    glutInitWindowPosition(POS_X, POS_Y);
    glutCreateWindow("Racing Game");

    glutDisplayFunc(display);
    
    glutSpecialFunc(specialKey);
    glutKeyboardFunc(keyboard);

    glClearColor(1, 1, 1, 1);

    glutTimerFunc(1000, timer, 0);
    glutMainLoop();

    return 0;
}
