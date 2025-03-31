/*
Spinning Donut
*/
#include <bits/stdc++.h>
#include <unistd.h>
#include <windows.h>
using namespace::std;

const int width=60,length=25;
char buffer[length*width];
float tBuffer[length*width];
char backgroundasciicode=' ';
float x,y,z;

int K1=40,K2=60;
int R2=20,R1=10;
float ox,oy,oz;
float vx,vy,vz;
char ins;
int lightx=0,lighty=-30,lightz=0,lightd=30;
float dotproduct;
float fincos;
float incrementspeed=0.05;
float cA,cB,sA,sB,sDx,sDy,cDx,cDy;

float calculateX(int R1,int R2) {
  return (R2+R1*cDx)*(cB*cDy+sA*sB*sDy)
         -R1*cA*sB*sDx;
}

float calculateY(int R1,int R2) {
  return (R2+R1*cDx)*(cDy*sB-cB*sA*sDy)
         +R1*cA*cB*sDx;
}

float calculateZ(int R1,int R2) {
  return cA*(R2+R1*cDx)*sDy+R1*sA*sDx;
}
void picCalculate(float x,float y,float z,int ch){
    float ooz=K1/(K2+z);
    
    x*=ooz;
    y*=ooz;

    int screenX=(int)(x+width/2);
    int screenY=(int)(y/2.2+length/2);
    int idx=(screenX+screenY*width);
    if(idx>=0 && idx<width*length){
        if(ooz>tBuffer[idx]){
            tBuffer[idx]=ooz;
            buffer[idx]=ch;
        }
    }
}
void Pointcalculate(float A,float B){
    cA=cos(A);
    cB=cos(B);
    sA=sin(A);
    sB=sin(B);
    for(float Dy=0 ; Dy<=6.28 ; Dy+=incrementspeed){
        sDy=sin(Dy);
        cDy=cos(Dy);
        ox=calculateX(0,R2);
        oy=calculateY(0,R2);
        oz=calculateZ(0,R2);
        for(float Dx=0 ; Dx<=6.28 ; Dx+=incrementspeed){
            sDx=sin(Dx);
            cDx=cos(Dx);
            x=calculateX(R1,R2);
            y=calculateY(R1,R2);
            z=calculateZ(R1,R2);
            vx=x-ox;
            vy=y-oy;
            vz=z-oz;
            dotproduct=vx*lightx+vy*lighty+vz*lightz;
            fincos=dotproduct/(lightd*R1);
            if(fincos<=1) ins='@';
            if(fincos<0.92) ins='&';
            if(fincos<0.76) ins='#';
            if(fincos<0.44) ins='*';
            if(fincos<0.28) ins='!';
            if(fincos<0.12) ins='=';
            if(fincos<-0.04) ins=';';
            if(fincos<-0.2) ins=':';
            if(fincos<-0.36) ins='~';
            if(fincos<-0.52) ins='-';
            if(fincos<-0.68) ins=',';
            if(fincos<-0.84) ins='.';
            picCalculate(x,y,z,ins);
        }
    }
}
int main(){
    float A=0,B=0;
    printf("\x1b[2J");
    while(1){
        memset(buffer,backgroundasciicode,length*width);    //each element is 1 byte
        memset(tBuffer,0,length*width*4);  //each element is 4 bytes
        Pointcalculate(A,B);
        printf("\x1b[H");
        for(int i=0; i<width*length ;i++){
            putchar( i % width ? buffer[i] : 10);
        }
        usleep(100);  //0
        A+=0.05;
        B+=0.05;
    }
}
