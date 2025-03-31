/*

Spinning Cube and Triangle

you can change the shape by remove and add annotation symbols in the main fucntion

*/
#include <bits/stdc++.h>
#include <unistd.h>
#include <windows.h>
using namespace::std;
#define too 1.15473
#define trans 0.01745
#define hrootof3 0.86602
//cube
const int width=40,length=20;   //fast //40 20
int cubewidth=15;   //15
//tetradron
float TY,TX,TZ;
float rx,ry,rz;
int telength=40;    //40
float hal_teheight=telength*0.43301;
float forword=hal_teheight*0.35;

char buffer[length*width];
float tBuffer[length*width];
char backgroundasciicode=' ';

float Camd=100;
int csize=70;
float A=0,B=0,C=0;
float incrementspeed=0.6;
float cubeX,cubeY;
float x,y,z;
int xp,yp;

int horizon;
float calculateX(int i, int j, int k, float A, float B, float C) {
  return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
         j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calculateY(int i, int j, int k, float A, float B, float C) {
  return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
         j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
         i * cos(B) * sin(C);
}

float calculateZ(int i, int j, int k, float A, float B, float C) {
  return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}

void SpinCalculate(float cubeA,float cubeB,float cubeC,int ch){ //parameter is the surface
    x=calculateX(cubeA,cubeB,cubeC,A,B,C);
    y=calculateY(cubeA,cubeB,cubeC,A,B,C);
    z=calculateZ(cubeA,cubeB,cubeC,A,B,C)+Camd+1;

    float ooz=1/z;
    x*=ooz*csize;
    y*=ooz*csize;

    xp=(int)(x+horizon/2);
    yp=(int)(y/2+length/2);

    int idx=(xp+(width*(yp)));
    if(idx>=0 && idx<width*length){
        if(ooz>tBuffer[idx]){
            tBuffer[idx]=ooz;
            buffer[idx]=ch;
        }
    }

}
int main(){
    printf("\x1b[2J");
    while(1){
        memset(buffer,backgroundasciicode,length*width);    //each element is 1 byte
        memset(tBuffer,-100,length*width*4);  //each element is 4 bytes
        //Spinning Cube
        horizon=40;
        for(cubeX=-cubewidth; cubeX<cubewidth; cubeX+=incrementspeed){  //cube
            for(cubeY=-cubewidth; cubeY<cubewidth; cubeY+=incrementspeed){
                SpinCalculate(cubeX,cubeY,-cubewidth,'1');
                SpinCalculate(cubewidth,cubeY,cubeX,'/');
                SpinCalculate(-cubewidth,cubeY,-cubeX,'.');
                SpinCalculate(-cubeX,cubeY,cubewidth,'*');
                SpinCalculate(cubeX,-cubewidth,-cubeY,'x');
                SpinCalculate(cubeX,cubewidth,cubeY,'o');
            }
        }

        //Spinning Triangle
        /* horizon=40;
        for(TY=-hal_teheight; TY<hal_teheight;TY+=incrementspeed){  //tetradron
            for(TX=-((hal_teheight-TY)*too/2); TX<((hal_teheight-TY)*too/2); TX+=incrementspeed){
                ry=calculateY(TX,TY,0,19.48*trans,0,0);
                rx=calculateX(TX,TY,0,19.48*trans,0,0);
                rz=calculateZ(TX,TY,0,19.48*trans,0,0)+forword;
                SpinCalculate(rx,ry,rz,'$');
                SpinCalculate(-hrootof3*rz-rx/2,ry,-rz/2+rx*hrootof3,'~');
                SpinCalculate(hrootof3*rz-rx/2,ry,-rz/2-rx*hrootof3,'*');
                ry=calculateY(TX,TY,0,90*trans,0,0);
                rx=calculateX(TX,TY,0,90*trans,0,0);
                rz=calculateZ(TX,TY,0,90*trans,0,0);
                SpinCalculate(rx,ry-telength*0.4,rz-telength*0.15,'o');
            }
        } */

        printf("\x1b[H");
        for(int i=0; i<width*length ;i++){
            putchar( i % width ? buffer[i] : 10);
        }
        usleep(1000);  //0
        A+=0.05;
        B+=0.05;
        C+=0.05;
    }
}
