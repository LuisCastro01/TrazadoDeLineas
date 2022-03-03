#include <iostream>
#include <math.h>
#include <GLFW/glfw3.h>
using namespace std;


//inicializacion de la libreria OpenGL
void show(float xarray[], float yarray[], int length) {
bool init = true;
   if (!glfwInit()) {
         cout << "Initialization failed" << endl;
         init = false;
         //return?

	}

	 //creacion de la ventana OpenGL 
     GLFWwindow * window1 = glfwCreateWindow(640, 640, "Trazado de lineas", NULL, NULL);

	 //si existe un fallo al abrir la ventana con OpenGL
	 /*if (!window1) {
		 cout << "Window or OpenGL context creation failed" << endl;
		 glfwTerminate();
		 //return?
		 
	 }*/

 if (init && window1) {
	        // creamos la venta principal */
			       glfwMakeContextCurrent(window1);
		
			        while (!glfwWindowShouldClose(window1)) {
			            // mantendra ejecutandose
			             glBegin(GL_POINTS);
		
						//agregamos el color
			             glColor3f(1, 0.52, 0.0);    // Naranja
			            for (int i = 0;i < length;i++) {
			                 glVertex2f(xarray[i], yarray[i]);
			
			}
			
			             glEnd();
							
						 //cuando se procesa cambia ed buffer
				            glfwSwapBuffers(window1);
			
				            /* eventos */
				             glfwPollEvents();
			
		}
		
			       if (glfwWindowShouldClose(window1))
			            glfwDestroyWindow(window1);
		
			         //terminado
			         glfwTerminate();
		
	}
	
}


 float normalize(int input) {
	     return float(input) / 500;
	
}
void bresenham(int array[], int p, int i, int length, int dx, int dy) {
     if (i == length - 1)
	         return;
	     int pnext;
	     if (p <= 0) {
		        array[i + 1] = array[i];
	         pnext = p + 2 * dy;
	
	}
     else {
	         array[i + 1] = array[i] + 1;
		         pnext = p + 2 * dy - 2 * dx;
	
	}
	     bresenham(array, pnext, i + 1, length, dx, dy);
	
}

 int main() {
	    int x0, x1, y0, y1;
	
	     cout << "Digite el valor de X y Y del primer punto" << endl;
	     cin >> x0 >> y0;
	     cout << "Digite la coordenada del primer punto: (" << x0 << ", " << y0 << ")." << endl;
	
		     cout << "Digite el valor de X y Y del segundo punto" << endl;
	     cin >> x1 >> y1;
	   cout << "Digite la coordenada del segundo punto (" << x1 << ", " << y1 << ")." << endl;
	
		     int length;
	     int xarray[1001], yarray[1001];
	     int dx;
	     int dy;

		     if (x0 == x1) {
		         if (y0 > y1) {
			            int tempy = y0;
			             y0 = y1;
			             y1 = tempy;
			
		}
		         length = y1 - y0 + 1;
		         for (int i = 0;i < length;i++) {
			             xarray[i] = x0;
			             yarray[i] = y0 + i;
		
		}
		
	}
		else {
		         //|m|<=1,el punto 1 esta a la derecha del punto 0
			        float m = float(y1 - y0) / float(x1 - x0);
		        if (fabs(m) <= 1 && x0 > x1) {
		             int tempx = x0;
			             int tempy = y0;
			             x0 = x1;
			             y0 = y1;
			             x1 = tempx;
			           y1 = tempy;
			
		}
		         //|m|>1, el punto 1 esta arriba del punto 0
			        if (fabs(m) > 1 && y0 > y1) {
		             int tempy = y0;
			             int tempx = x0;
			            y0 = y1;
			             x0 = x1;
			             y1 = tempy;
			             x1 = tempx;
			
		}
		         dx = x1 - x0;
		         dy = y1 - y0;
		        m = float(dy) / float(dx);
		
		         if (fabs(m) <= 1) {
			           length = x1 - x0 + 1;
			             for (int i = 0;i < length;i++)
				                 xarray[i] = x0 + i;
			             //0<m<=1
				             if (dy >= 0) {
				                 yarray[0] = y0;
			                 yarray[length - 1] = y1;
				                 int p0 = 2 * dy - dx;
				                 bresenham(yarray, p0, 0, length, dx, dy);
				
			}
				else {
				                 //-1<=m<0
					                 yarray[0] = -y0;
				                 yarray[length - 1] = -y1;
				                 int p0 = 2 * (-dy) - dx;
				                 bresenham(yarray, p0, 0, length, dx, -dy);
				                 for (int i = 0;i < length;i++)
					                     yarray[i] = -yarray[i];
				
			}
			
		}
			else {
			             length = y1 - y0 + 1;
			             for (int i = 0;i < length;i++)
				                 yarray[i] = y0 + i;
			             if (dx >= 0) {
				                 //m>1
					                 xarray[0] = x0;
				                 xarray[length - 1] = x1;
				                 int p0 = 2 * dx - dy;
				                 bresenham(xarray, p0, 0, length, dy, dx);
				
			}
			else {
				                 //m<-1
					                 xarray[0] = -x0;
				                 xarray[length - 1] = -x1;
				                 int p0 = 2 * (-dx) - dy;
				                 bresenham(xarray, p0, 0, length, dy, -dx);
				                 for (int i = 0;i < length;i++)
					                     xarray[i] = -xarray[i];
				
			}
			
		}
		
	}
	
		     float fxarray[1001];
	     float fyarray[1001];
	     for (int i = 0;i < length;i++) {
		         fxarray[i] = normalize(xarray[i]);
		         fyarray[i] = normalize(yarray[i]);
		
	}
	
		     show(fxarray, fyarray, length);
	
		
		
		     return 0;
	
}