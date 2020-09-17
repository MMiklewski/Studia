#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 
#include "winbgi2.h"
#include "funkcje.h"
#include <windows.h>
#include <iostream>
#include <string>
#define clrscr() system("cls")
#define line() cout<<"\n"
#define hold() system("pause")
#define PI() 3.14159265359
#define MAXN 10


using namespace std;


double manewryorbitalne(double& value){
	
//STAŁE
	float nhu=398600; //standard gravitional parameter
	float Re=6371; //earth radius
	double omegae=(2*4*atan(1.)+2*4*atan(1.)/365.26)/24/3600;


// Parametry orbirty przejściowej
	float hp1=250; //wysokość perygeum
	float ha1=35786; // wysokośc apogeum
	float i1=2*4*atan(1.)/180.; // inklinacja (deg)
	float rp1=hp1+Re;
	float ra1=ha1+Re;

// Parametry orbity obecnej
	float hp=35774;
	float ha=35798;
	float e=0.0002792; //ekscentryczność
	float i=0.0516*4*atan(1.)/180;
	float Omega=332.3475*4*atan(1.)/180; //rektascencja węzła wstępującego
	float omega=345.71838*4*atan(1.)/180; //argument prerygeum
	float npd=1.00272036; //liczba obiegów na dzień
	float Theta=190.6385*4*atan(1.)/180; // średnia anomalia w czasie epoki

	float rp=hp+Re; //promieñ perygeum
	float ra=ha+Re; //promien apogeum

	float a=rp/2+ra/2; //półoś
	double h=sqrt(rp*nhu*(1+e)); //Moment orbitalny

//redefinicja geo

	float alfa=Omega+omega+Theta;  //kąt gwiadowy
	float ex=e*cos(omega+Omega);
	float ey=e*cos(omega+Omega);
	float ix=i*cos(Omega);
	float iy=i+sin(Omega);
	float M=Theta; //bo niski mimośród

	float ThetaG=304.9833333*4*atan(1.)/180;//124.664742*8*atan(1.)/180; //16.07.18 2018/07/16
	 M=3.555601624-omega-Omega+5.32296333;
	 int GMT=2;
	time_t current_time;
	struct tm  local_time;

	time ( &current_time );
	localtime_s(&local_time, &current_time);
	int Year   = local_time.tm_year + 1900;
	int Month  = local_time.tm_mon + 1;
	int Day    = local_time.tm_mday;

	int Hour   = local_time.tm_hour-GMT;
	int Min    = local_time.tm_min;
	int Sec    = local_time.tm_sec;
	 cout<<Year<<"-"<<Month<<"-"<<Day<<"\n"<<Hour<<":"<<Min<<":"<<Sec;
	//cout<<M<<M*180/4/atan(1.);
	line();
	int secs=Sec+Min*60+Hour*3600;
	int days;
	int FEB;
	if(Year%4==0)FEB=29;
	else FEB=28;
		 if(Month==1) {days=Day;}
	else if(Month==2) {days=Day+31;}
	else if(Month==3) {days=Day+31+FEB;}
	else if(Month==4) {days=Day+31*2+FEB;}
	else if(Month==5) {days=Day+31*2+FEB+30;}
	else if(Month==6) {days=Day+31*3+FEB+30;}
	else if(Month==7) {days=Day+31*3+FEB+30*2;}
	else if(Month==8) {days=Day+31*4+FEB+30*2;}
	else if(Month==9) {days=Day+31*5+FEB+30*2;}
	else if(Month==10){days=Day+31*5+FEB+30*3;}
	else if(Month==11){days=Day+31*6+FEB+30*3;}
	else if(Month==12){days=Day+31*6+FEB+30*4;}

	int dwhole =367*Year-INT(7*(Year+INT((Month+9)/12))/4)+INT(275*Month/9)+Day-730531.5;
	double dfrac = ((double)Hour + (double)Min/60 + (double)Sec/3600.)/24.;
	double days2000 = (double)dwhole + dfrac;

	double GMST1=(280.46061837+360.98564736629*days2000);
	long double fraction=GMST1/360;
	long double GMST=abs(fraction-ceil(fraction))*360;

	double tilltoday=(Year-2000)*365+floor((Year-2000.)/4.)+days+(Hour-12+Min/60.+Sec/3600.)/24.;
	double anglegreen=tilltoday/360-floor(tilltoday/360.);

//	cout<<tilltoday;line();cout<<anglegreen;
//	if(GMST1<1)
//	cout<<GMST1;line();cout<<fraction;line();cout<<GMST;	


//Budżety prędkości



//Ukołowienie orbity przejściowej
	double et=(ra1-rp1)/(ra1+rp1);
	double ht=sqrt(rp1*nhu*(1+et));
	double V1=ht/(ra1);
	double V2=sqrt(nhu/ra);

	double deltaVp=fabs(V2-V1);

//	 cout<<deltaVp;
//	 hold();


//zerowanie inklinacji

	double Vgeo=omegae*(ha+Re);	
	double deltai0=2*Vgeo*sin(i1/2);
//	cout<<deltai0;line();hold();

//Zmiana położenia satelity na orbicie geostacjonarnej. phasing maneuver
	float nm=3;
	
	
	//1zmiana
	double deltalambada1=RAD(-10.);
	double TWE1=(deltalambada1+nm*2*PI())/nm/omegae;
	double aWE1=pow(TWE1*pow(nhu,0.5f)/2/(float)PI(),2./3.);
	double rcWE1=2*aWE1-rp;
	double eWE1=(ra-rcWE1)/(ra+rcWE1);
	double hWE1=sqrt(aWE1*nhu*(1-eWE1*eWE1));
	double VWE1=hWE1/rp;
	double deltaVWE1=fabs(2*(VWE1-Vgeo));
//	cout<<eWE1; hold();


	//2zmiana
	double deltalambada2=RAD(-10.);
	double TWE2=(deltalambada2+nm*2*PI())/nm/omegae;
	double aWE2=pow(TWE2*sqrt(nhu)/2/PI(),2./3.);
	double rcWE2=2*aWE2-rp;
	double eWE2=(ra-rcWE2)/(ra+rcWE2);
	double hWE2=sqrt(aWE2*nhu*(1-eWE2*eWE2));
	double VWE2=hWE2/rp;
	double deltaVWE2=fabs(2*(VWE2-Vgeo));

	//3zmiana
	double deltalambada3=RAD(-20.);
	double TWE3=(deltalambada3+nm*2*PI())/nm/omegae;
	double aWE3=pow(TWE3*sqrt(nhu)/2/PI(),2./3.);
	double rcWE3=2*aWE3-rp;
	double eWE3=(ra-rcWE3)/(ra+rcWE3);
	double hWE3=sqrt(aWE3*nhu*(1-eWE3*eWE3));
	double VWE3=hWE3/rp;
	double deltaVWE3=fabs(2*(VWE3-Vgeo));

	double deltaVEsum=fabs((deltaVWE1+deltaVWE2+deltaVWE3));

//	cout<<deltaVEsum*1000;
//	hold();

//transfer na cmentarną 300km

	double deltahp=300;
	double rd=rp+deltahp;
	double ad=rd/rp;

	double deltaVd=((1/sqrt(ad))-((sqrt(2.)*(1-ad))/(sqrt(ad*(1+ad))))-1)*sqrt(nhu/rp);
	//cout<<deltaVd;hold();


//Utrzymanie inklinacji

	double is=23.45; //DEG!!!! kąt nachylenia ekliptyki do równika ziemskiego
	double ism=5.35;   //DEG!!!! średni kąt nachylenia orbity Księżycayca do ekliptyki
	double omegan=0.337806; //RAD/Yr prędkość obrotowa pola grawitacyjnego Księżyca
	double Ksun=0.00269; // DEG/day 
	double Kmoon=0.005844; //DEG/day
	
	double tdn=(Year-1960)*365.25;
	double tyn=Year-1960;
	double deltat=365;

	double sumdeltaVi0=0;
//	printf("yearrr\timn\tOmegan\tOmegamn\tKn\tHn\tdeltai\tdeltaisum\tdeltaVi0\n");
	for(int yearrr=2009; yearrr<2024; yearrr++){ //ZMIENIc na 2009
		tyn=yearrr-1960;
		tdn=(yearrr-1960)*365.25;
		double imn=RAD(23.736)+RAD(5.133)*sin(omegan*(yearrr-2001.7433));  //wzór w DEG!!!! Kąt pomiędzy orbitą Księżyca a płaszczyzną równika ziemskiego
		double Omegan=RAD(178.78-0.05295*tdn);   //wzór w DEG!!!    Kąt pomiędzy orbitą Księżyca a ekliptyką  360-floor(Omegan/360);
		double Omegamn=asin((sin(RAD(ism))*sin(Omegan))/(sin(imn)));  //RAD!!!!
	
		double Kn=3*Kmoon*cos(Omegamn)*sin(2*imn)/8+3*Ksun*sin(2*RAD(is))/8;  //DEG!!!
		double Hn=-3*Kmoon*sin(Omegamn)*sin(2*imn)/8;  //DEGGG
		double deltai=sqrt(Kn*Kn+Hn*Hn);   //DEGG

	
		double deltaisum=deltai*deltat;
		double deltaVi0=2*Vgeo*sin(RAD(deltaisum)/2);
		sumdeltaVi0+=deltaVi0;
	
	//printf("%d\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.6lf\t%.5lf\t%.5lf\t%.5lf\n",yearrr,DEG(imn),360-fabs(ceil(DEG(Omegan)/360)*360-DEG(Omegan)),DEG(Omegamn),Kn,Hn,deltai,deltaisum,deltaVi0);
	
	}

//Utrzymanie pozycji na orbicie Upno
	double LAMBDAN[4]={-7,3,13,33}; 	//DEG!!!
	double czasUpno[4]={2,2,3,8};	//CZas przebywania satelity na pozycji
	double nUpno[4];
	double deltaVUpno[4];
	double sumdeltaVUpno[4];
	double deltalambdaUpno=0.1;
	double deltaVsumUpno=0;

	for(int iUpno=0;iUpno<4;iUpno++){
	double d2lambdaUpno=-0.00168*sin(RAD(2*(LAMBDAN[iUpno]-75)));
	double tauUpno=4*sqrt(deltalambdaUpno/d2lambdaUpno);
	nUpno[iUpno]=ceil(czasUpno[iUpno]*365/tauUpno);
	deltaVUpno[iUpno]=11.36*sqrt(d2lambdaUpno*deltalambdaUpno);
	sumdeltaVUpno[iUpno]=deltaVUpno[iUpno]*nUpno[iUpno];
//	cout<<deltaVUpno[iUpno];line();hold();
	deltaVsumUpno+=sumdeltaVUpno[iUpno];
	}
	deltaVsumUpno/=1000;











//SUMA

	clrscr();
	cout<<"deltaVd"<<"\t \t" <<deltaVd<<"\t" <<"-transfer na cmentarna";line();
	cout<<"deltaVEsum"<<"\t" <<deltaVEsum<<"\t" <<"-ustalanie szerokości geogr. phasing maneuver" ;line();
	cout<<"deltai0"<<"\t \t" <<deltai0<<"\t" <<"-wyzerowanie inklinacji poczatkowej";line();
	cout<<"deltaVp"<<"\t \t" <<deltaVp<<"\t \t" <<"-ukolowienie orbity przejsciowej";line();
	cout<<"sumdeltaVi0"<<"\t" <<sumdeltaVi0<<"\t" <<"-utrzymanie zadanej inklinacji orbity";line();
	cout<<"deltaVsumUpno"<<"\t" <<deltaVsumUpno<<"\t" <<"-Utrzymanie pozycji na orbicie";line();
//	hold();clrscr();

	double dVtotal=deltaVd+deltaVEsum+deltai0+deltaVp+sumdeltaVi0+deltaVsumUpno;
	value=dVtotal;
	return dVtotal*1000;

	
	}
