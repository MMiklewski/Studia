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

//Wyznaczenie wysokości dla optymalnego rozprężu dyszy

double AkrytA(double kappa, double M){return pow((kappa+1)/2,(kappa+1)/(2*(kappa-1)))*M*pow((1+((kappa-1)/2)*M*M),(-1*(kappa+1))/(2*(kappa-1)));}
void NNL() {
	
	//Tworzenie plików z danymi do excela
	FILE *mfuell=fopen("c:/Users/Herkes/Desktop/Kompukomp\\mfuel.xls","a");
	fclose(mfuell);
		
	FILE *fHobl=fopen("c:/Users/Herkes/Desktop/Kompukomp\\fHobl.xls","a");
	fclose(fHobl);

	//czyszczenie plików z danymi
	mfuell=fopen("c:/Users/Herkes/Desktop/Kompukomp\\mfuel.xls","w");
	fprintf(mfuell,"iteracje\tilosc paliwa\tczas\twysokosc\n");
	fHobl=fopen("c:/Users/Herkes/Desktop/Kompukomp\\fHobl.xls","w");	
	fprintf(fHobl,"Hobl,\tpe,\tTe,\trhoe,\tV9,\tAe,\tThrust,\tH,\tIsp\n");

	
	double B=8314.4598484848; //kJ/mol/K Stała gazowwa
	//założenia
	double pc=20*1000000; //(M)Pa 
	double hmax=100000; //separation height meters
	double mpayload=10000; //masa wysyłana na orbitę kg
	double Dt=0.2;//średnica gardzieli m 

	//Z CEA
	double Tc=3466.13; //z CEA  Temperatura w komorze spalania. (K)  
	double OF=0.7; //z CEA najefektywniejsze
	double kappa=1.1591; // z CEA DLA POWIETRZA 1.4 WYZNACZYC dla spalin ( ok 1.2) (1.32-1.28)	
	double MH2O=19.885; // z CEA masa molowa spalin 

	//
	double R=B/MH2O; //Indywidualna stała gazowa 		
	double rhoc=pc/Tc/R; //gęstość w przekroju krytycznym
	
	//Z Cea ilość jonów (można wykorzystać do wyznaczania parametrów termodyn)
	double CO=0.23866;
	double CO2=0.08746;
	double COOH=0.00002;
	double Hy=0.01537;
	double HCO=0.00002;
	double H2=0.15774;
	double HCOOH=0.00001;
	double H20=0.47567;
	double H202=0.00001;
	double O=0.001119;
	double OH=0.02244;
	double O2=0.00138;
		
//zmienne
double Hobl=0;	
double flag=0;
double flag2=0;
double flag3=0;
double mfuel;
double t=0;
double Ispold=0;
double mstructure=0;
double mtotal=0;
double grav=9.81;
int iterzew=0;

while(true){ //pętla najzzewnętrzeniejsza - porównanie czy zmiana średnicy wylotowej na wydatek i optymalna średnicę wylotową
	Hobl=flag2;
	double pe=getStandardPressure(Hobl); //ciśnienie zewnętrzne
	//Parametry krytyczne
	double pt=pow(2/(kappa+1),(kappa/(kappa-1)))*pc; //ciśnienie gardzieli
	double Tt=(2/(kappa+1))*Tc; // temperatura gardzieli
	double At=PI()*Dt*Dt/4;  //powierzchnia gardzieli
	double rhot=rhoc*pow(2/(kappa+1),(1/(kappa-1))); //gęstość gardzieli
	double Qc=sqrt(kappa*pow(2/(kappa+1),((kappa+1)/(kappa-1))))*pc*At/sqrt(R*Tc); //wydatek na bazie par kryt i cisnienia w komorze i temperatury w komorze
	double at=sqrt(kappa*R*Tt); //prędkość dźwięku krytyczna
	double vt=at; //prędkość w przekroju krytycznym
	double mdot=At*vt*rhot; //wydatek masowy w przekroju krytycznym równy Qc
	if(fabs(mdot-Qc)>0.1){
		cout<<"Mass flow critical error";
		hold();
	}

	double H=0;
	int i;
	//Parametry w przekroju wylotowym
	double Te=Tt*pow(pe/pt,(kappa-1)/kappa);							// Temperatura na wylocie 
	double rhoe=pe/Te/R;												// Gęstość na wylocie
	double Me=sqrt((2/(kappa-1))*(pow(pc/pe,(kappa-1)/kappa)-1));		// Prędkość Macha na wylocie
	double a9=sqrt(kappa*R*Te);											// Prędkość dźwięku na wylocie
	double M9=sqrt(2*(kappa*R*(Tc-Te)/(kappa-1)))/sqrt(kappa*R*Te);		// Prędkość Macha na wylocie
	double V9=sqrt(2*(kappa*R*(Tc-Te)/(kappa-1)));						// Prędkość na wylocie
	double Ae=At/AkrytA(kappa,M9);										// Średnica wylotowa 
	double Qe=Ae*V9*rhoe;												// Wydatek masowy na wylocie
	if(fabs(Qe-Qc)>0.1){
		cout<<"Mass flow exit error";
		hold();
	}

	double Thrust=Qe*V9+Ae*(pe-getStandardPressure(H));					//Ciąg 
	
	//Zmienne do wewnętrzniejszej pętli
	double h;
	mfuel=Qc;
	double tank;
	int flagg=0;
	int engines=1;
	double v=0;
	int iterf=0;
	double step=0.1;												//krok całkowania
	
	
	//Obliczanie minimalnej ilości paliwa
	while(true){		
					
		mstructure=(mpayload+mfuel)*0.1;	//Wyznaczenie masy struktury
		mtotal=mfuel+mstructure+mpayload;	//Wyznaczenie masy całkowitej
		iterf++;							//Liczba iteracji (czas) całkowanie co sekundę 

		if(Thrust/mtotal<grav){ //Sprawdzenie czy ilość silników wystarczy do dźwignięcia (nie używane)
			cout<<"Za mały ciąg do wyniesienia rakiety";
			hold();
			engines++;
			mfuel=Qc;
		}
		v=0;														//prędkość obiektu
		h=0;														//wysokość lotu
		tank=mfuel;													//pojemność zbiornika
		t=0;														//czas lotu
		while(h<hmax){												//Liczenie do czasu uzyskania zadanej wysokości	
			Thrust=(Qe*V9+Ae*(pe-getStandardPressure(h)))*engines;  //Wyznaczenie ciągu na danej wysokości
			v+=(((Thrust/mtotal)-grav)+Qc*v/mtotal)*step;			//Całka siły ciagu
			h+=v*step;												//Całka prędkości
			tank-=Qc*engines*step;									//Ubytek paliwa
			mtotal-=engines*Qc*step;								//Zmiana masy całkowitej
			if(tank<=1)break;										//Sprawdzenie czy nie zużto całego dostępnego paliwa
			if(h>=hmax){											//Sprawdzenie czy osiągnięto wysokość
				flagg=1;
				break;
			}
			t+=step;												//zwiększenie czasu lotu
			
		}
		fprintf(mfuell,"%d\t%lf\t%lf\t%lf\n",iterf,mfuel,t,h);		//Wydruk danych
		if(flagg==1){												//Sprawdzenie warunku osiągniętej wyskości przerwanie pętli
			break;
		}
		
		mfuel+=Qc*step;	//Zwiększenie ilości paliwa		
	}


	//Pętla optymalnego rozprężu w dyszy

	//Zmienne
	double mfuel2;				
	double Velocity;	
	Hobl=0;

	while(Hobl<=hmax){	
		double time=1;															//czas lotu;
		double Isp=0;															//Impuls właściwy 
		mfuel2=mfuel;															//przywrócenie masy paliwa 
		H=0;																	//wyzerowanie wysokości obiektu
		Velocity=0;																//wyzerowanie prędkości obietku
		pe=getStandardPressure(Hobl);											//wyznaczenie ciśnienia zewnętrznego										
		
		
		//Pętla wewnętrzna
		while(H<hmax){			
			mstructure=(mfuel+mpayload)*0.1;
			mtotal=mfuel2+mstructure+mpayload;									//masa rakiety
			//Parametry wylotowe
			Te=Tt*pow(pe/pt,(kappa-1)/kappa);									
			rhoe=pe/Te/R;
			a9=sqrt(kappa*R*Te);
			M9=sqrt(2*(kappa*R*(Tc-Te)/(kappa-1)))/sqrt(kappa*R*Te);
			V9=sqrt(2*(kappa*R*(Tc-Te)/(kappa-1)));
			Ae=At/AkrytA(kappa,M9);
			Qe=Ae*V9*rhoe;
			
			if(fabs(Qe-Qc)>0.1){
				cout<<"Mass flow exit error (HOBL)";
				hold();
			}

			//Ciąg, prędkość, wysokość jak przy obliczaniu masy
			Thrust=Qe*V9+Ae*(pe-getStandardPressure(H));
			if(Thrust/mtotal<grav)break;										//Momentum Thrust mniejszy niż pressure thrust
			Velocity+=((Thrust/mtotal-grav)+Qc*v/mtotal)*step;
			H+=Velocity*step;

			Isp+=Thrust/Qc*step;												//Sumowanie kolejnych stosunków ciągu do wydatku 
			mfuel2-=Qc*step;													//zmiana masy paliwa
			time+=step;															//zwiększenie kroku czasowego

			if(mfuel2<0){
				cout<<Thrust<<"\t"<<pe<<"\t"<<getStandardPressure(H)<<"\t"<<H<<"\t"<<Hobl<<"\tbrak paliwa\n";
				break;													//sprawdzanie ilości pozostałego paliwa 

			}
		}

		Isp/=time;																//wyznaczenie impulsu właściwego

		//zapisanie danych do excela
		if(Thrust/mtotal>grav){
		fprintf(fHobl,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",Hobl,pe,Te,rhoe,V9,Ae,Thrust,mtotal*grav,H,Isp); 
		}
			if(flag<Isp){														//Sprawdzenie czy impuls jest wyższy od poprzedniego
			flag=Isp;															//Zapisanie wartości Impulsu i wysokości obliczeniowej
			flag2=Hobl;
			flag3=Ae;
		}

		Hobl+=1000;																//Zwiększenie wysokości projektowanej na dyszę
	}

	//Warunek pętli najzzewnętrzniejszej 
	if(fabs(Ispold-flag)<0.001)break;											//Gdy różnice maleją poniżej 0.001 zakończ program
	Ispold=flag;																//Zapisanie nowej wartośći Isp
	iterzew++;
	}
	hold();
	clrscr();
	line();
	cout<<flag<<"\n"<<flag2<<"\n"<<mfuel<<"\n"<<t<<"\n"<<iterzew<<"\n"<<flag3;

	
fclose(mfuell);
fclose(fHobl);


}