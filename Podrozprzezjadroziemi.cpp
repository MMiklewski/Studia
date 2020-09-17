#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>


#define clrscr() system("cls")
#define hold() system("pause")
using namespace std;

#define PI 4*atan(1.) 

void main(){

	double R=6.37841*pow(10.,6);
	double masaziemi=5.9722*pow(10.,24);
	double gestosc=masaziemi/(4*R*R*R*PI/3);
	double G=6.6740831*pow(10.,-11);

	double check=gestosc*R*R*R*4*PI/3;
	double a=G*masaziemi/R/R;cout<<a<<"\n"<<check;
	clrscr();

	double t=0;
	double Velocity=0;
	double czas=0;
	double dt=0.00001;
	double dR=10;
	double t1;
	double V1=0;
	double x;

/*	while(R>0){
	
		a=G*gestosc*R*4/3*PI;	
		t1=0;
		x=0;
		while(dR>x){
		x=a*t1*t1/2+V1*t1;
		t1+=0.1;
		}
		
		V1+=a*t1;
		R-=dR;
		czas+=t1;

	
	}
	*/
	
	while(R>0.0001){
		
		a=G*gestosc*R*4/3*PI;
		R-=a*dt*dt/2+Velocity*dt;
		Velocity+=a*dt;
		t+=dt;
	}
	t*=2;
	int mins=floor(t/60);
	int sec= (int)t % 60 ;
	
	system("pause");
	
	cout<<"czas: "<<t<<"\nminut: "<<mins<<"\nsekund: "<<sec<<"\na:"<<a<<"\nV:"<<Velocity;
	system("pause");
}