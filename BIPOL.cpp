#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h> 
#include "winbgi2.h"
#include "funkcje.h"
#include <windows.h>
#include <iostream>
#define clrscr() system("cls")
#define hold() system("pause")
using namespace std;
#define line() puts("")
#define space() printf("\t");
#include "BIPOL.h"

void BIPOL7();
void BIPOL9();
double BIPOL10();


void main()
{
//BIPOL9();


puts("Done\n");
system("pause");

}

double BIPOL10(){
	
	
	
	double b=15.5; //rozpietość
	double croot=2.2; //cięciwa przykadlubowa
	double S=25.5; //pow nośna

	double cg=S/b;	
	double ctip=2*cg-croot; //cieciwa koncowa

	
	double λ=ctip/croot;
	double Λ=b*b/S;
	double ca=2*croot*(1+λ+λ*λ)/(3*(1+λ));
	double lb=10.4;
	double xh=9.08;

	double sprawnosc=0.82;
	double V=100;
	double N=451000;
	double n_obr=1700;
	double omega_s=2*PI()*n_obr/60; 
	double k=1.25;
	double n=4.4;
	double g=9.80665;
	double L=2.97;
	double omegay=1;
	double omegaz=2.5;
	double turbinediameter=0.5/2;
	double Pzh=1000;
	

	double msilnika=150;
	double omegaturb=3500;

	double massprop=10;
	double massturbine=20;


	double Jsmiglo=massprop*L*L/12;
//	cout<<"Jsmiglo "<<Jsmiglo;

	double Jturb=massturbine*turbinediameter*turbinediameter/2;
//	cout<<"Jturb "<<Jturb;
	
	double Mx=k*N/omega_s;
	double Mgyrz=omegaz*(Jsmiglo*omega_s+omegaturb*Jturb);
	double Mgyry=omegay*(Jsmiglo*omega_s+omegaturb*Jturb);
//printf("Mx:%lf\nMgryz:%lf\nMgryy:%lf\n",Mx,Mgyrz,Mgyry);hold();exit(-1);


	double Qs=msilnika*g;
	
	double n_x=2.5;
	double n_y=1;
	double n_z=4.4;



	double Fx=n_x*Qs;
	double Fy=n_y*Qs;
	double Fz=n_z*Qs;

	double nosek=8*0.25*croot/1.5;
	double dzwigar1=nosek+0.2*croot;
	double dzwigar2=nosek+0.7*croot;
//	printf("QS:%lf\nFx:%lf\nFy:%lf\nFz:%lf\ndzwigar1:%lf\ndzwogar2:%lf\n",Qs,Fx,Fy,Fz,dzwigar1,dzwigar2);

	
	double MASA[15]={10.,150.,30.,50.,180.,75.,75.,120.,120.,1000.,55.,200.,150.,50.,50};
	double X[15]={0.,1.,1.2,1.68,2.6,2.64,3.6,3.84,3.84,3.84,4.4,5,5.2,6.8,9.08};

	FILE *gowno=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL10\\dane.xls","w");
	for (int i=0;i<15;i++){
		fprintf(gowno,"%lf\t%lf\n",X[i],MASA[i]);

	}
	fclose(gowno);

	int loa=(sizeof(MASA)/sizeof(*MASA));
		
	int *LP=(int*)malloc(loa*sizeof(int));
	double *MX=(double*)malloc(loa*sizeof(double));
	double *MXX=(double*)malloc(loa*sizeof(double));
	double *PN=(double*)malloc(loa*sizeof(double));
	double *PX=(double*)malloc(loa*sizeof(double));
	double *PE=(double*)malloc(loa*sizeof(double));

	double masa=0;
	double mx=0;
	double mxx=0;
	double Pn=0;
	double Px=0;

	
	gowno=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL10\\inne.xls","w");
	fprintf(gowno,"LP\tMx\tMXX\tPN\tPx\n");
	for (int i=0;i<loa;i++){
		LP[i]=i+1;
		MX[i]=MASA[i]*X[i];
		MXX[i]=MX[i]*X[i];
		PN[i]=-MASA[i]*g;
		PX[i]=PN[i]*X[i];
		masa+=MASA[i];
		mx+=MX[i];
		mxx+=MXX[i];
		Pn+=PN[i];
		Px+=PX[i];
		fprintf(gowno,"%d\t%lf\t%lf\t%lf\t%lf\n",LP[i],MX[i],MXX[i],PN[i],PX[i]);
	}

	
	double XSCk=mx/masa;
	double Iyy=mxx-XSCk*XSCk*masa;
	double lh=xh-XSCk;
	double epsilon=-Pzh*lh/Iyy;

	

//	double RB=-Pn*(XSCk-dzwigar1)/(dzwigar1-dzwigar2);
//	double RB=((XSCk-dzwigar1)*Pn)/(dzwigar1-dzwigar2);
	double RB=(Pn*dzwigar1-Px)/(dzwigar2-dzwigar1);

	double RA=-Pn-RB;


	double *XX=(double*)malloc((loa+3)*sizeof(double));
	double *PNX=(double*)malloc((loa+3)*sizeof(double));
	double *MG=(double*)malloc((loa+3)*sizeof(double));
	double *T=(double*)malloc((loa+3)*sizeof(double));

	for (int i=0;i<loa;i++){
		
		XX[i]=X[i];
		PNX[i]=PN[i];
		T[i]=0;
		MG[i]=0;

	}

	XX[loa]=dzwigar1;
	XX[loa+1]=dzwigar2;
	XX[loa+2]=lb;
	
	PNX[loa]=RA;
	PNX[loa+1]=RB;
	PNX[loa+2]=0;
	
	sortdouble(XX,PNX,loa+3);

	for (int i=1;i<loa+3;i++){

	T[i]=T[i-1]+PNX[i-1];
	MG[i]=T[i]*(XX[i]-XX[i-1])+MG[i-1];
	
	}	

	
	/*
	setbkcolor(WHITE);
	setcolor(BLACK);
	graphics(1000,1000);
	chart(XX,MG,loa+2,"X","Mg","wykres");
	*/
	
	hold();
	clrscr();
	clrscr();
	printf("n=1\nRa:%lf\nRb:%lf\nXX\tPN\tT\tMg\n",RA,RB);	
	
	for (int i=0;i<loa+3;i++){
		printf("%lf\t%lf\t%lf\t%lf\n",XX[i],PNX[i],T[i],MG[i]);
		
	}
	FILE *f=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL10\\n1.xls","w");
		fprintf(f,"n=1\nRa:%lf\nRb:%lf\nXX\tPN\tT\tMg\n",RA,RB);	
	
	for (int i=0;i<loa+3;i++){
		fprintf(f,"%lf\t%lf\t%lf\t%lf\n",XX[i],PNX[i],T[i],MG[i]);
		
	}
	fclose(f);
hold();


	double *TE=(double*)malloc((loa+3)*sizeof(double));
	double *MGE=(double*)malloc((loa+3)*sizeof(double));
	RA=epsilon*Iyy/(dzwigar2-dzwigar1);
	RB=-RA;
	
	for(int i=0;i<loa;i++){
		XX[i]=X[i];
		PE[i]=MASA[i]*(X[i]-XSCk)*epsilon;
		TE[i]=0;
		MGE[i]=0;

	}
	XX[loa]=dzwigar1;
	XX[loa+1]=dzwigar2;
	XX[loa+2]=lb;
	
	PE[loa]=RA;
	PE[loa+1]=RB;
	PE[loa+2]=0;

	sortdouble(XX,PE,loa+3);
	
	for (int i=1;i<loa+3;i++){

		TE[i]=TE[i-1]+PE[i-1];
		MGE[i]=TE[i]*(XX[i]-XX[i-1])+MGE[i-1];
	
	}
	clrscr();
	printf("epsylon\nRa:%lf\nRb:%lf\nXX\tPE\tT\tMg\n",RA,RB);	
	
	for (int i=0;i<loa+3;i++){
		printf("%lf\t%lf\t%lf\t%lf\n",XX[i],PE[i],TE[i],MGE[i]);
		
	}
	
hold();

f=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL10\\epsylony.xls","w");
		fprintf(f,"epsylon\nRa:%lf\nRb:%lf\nXX\tPN\tT\tMg\n",RA,RB);	
	
	for (int i=0;i<loa+3;i++){
		fprintf(f,"%lf\t%lf\t%lf\t%lf\n",XX[i],PE[i],TE[i],MGE[i]);
		
	}
	fclose(f);
	
	double *PZH=(double*)malloc((loa+3)*sizeof(double));
	double *TZH=(double*)malloc((loa+3)*sizeof(double));
	double *MGZH=(double*)malloc((loa+3)*sizeof(double));
	RB=(Pzh*(dzwigar1-xh))/(dzwigar2-dzwigar1);
	RA=-Pzh-RB;

	for(int i=0;i<loa;i++){
		XX[i]=X[i];
		PZH[i]=0;
		TZH[i]=0;
		MGZH[i]=0;

	}
	XX[loa]=dzwigar1;
	XX[loa+1]=dzwigar2;
	XX[loa+2]=lb;
	
	PZH[loa]=RA;
	PZH[loa+1]=RB;
	PZH[loa+2]=0;

	sortdouble(XX,PZH,loa+3);
	
	for (int i=1;i<loa+3;i++){

		TZH[i]=TZH[i-1]+PZH[i-1];
		MGZH[i]=TZH[i]*(XX[i]-XX[i-1])+MGZH[i-1];
	
	}


	clrscr();
	printf("PZH\nRa:%lf\nRb:%lf\nXX\tPE\tT\tMg\n",RA,RB);	
	
	for (int i=0;i<loa+3;i++){
		printf("%lf\t%lf\t%lf\t%lf\n",XX[i],PZH[i],TZH[i],MGZH[i]);
		
	}
hold();
	f=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL10\\Pzh.xls","w");
		fprintf(f,"PZH\nRa:%lf\nRb:%lf\nXX\tP\tT\tMg\n",RA,RB);	
	
	for (int i=0;i<loa+3;i++){
		fprintf(f,"%lf\t%lf\t%lf\t%lf\n",XX[i],PZH[i],TZH[i],MGZH[i]);
		
	}
	fclose(f);
	double nP=1;//11.238;
	n=1;//4.4;

	double *TSUM=(double*)malloc((loa+3)*sizeof(double));
	double *MGSUM=(double*)malloc((loa+3)*sizeof(double));
	
	for(int i=0;i<loa+3;i++){
		TSUM[i]=TZH[i]*nP+TE[i]+T[i]*n;
		MGSUM[i]=MGZH[i]*nP+MGE[i]+MG[i]*n;
	}
	clrscr();
	printf("SUM\nXX\tT\tMg\n");	
	
	for (int i=0;i<loa+3;i++){
		printf("%lf\t%lf\t%lf\n",XX[i],TSUM[i],MGSUM[i]);
		
	}

	f=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL10\\sum.xls","w");
		fprintf(f,"SUM\nXX\tT\tMg\n");	
	
	for (int i=0;i<loa+3;i++){
		fprintf(f,"%lf\t%lf\t%lf\n",XX[i],TSUM[i],MGSUM[i]);
		
	}
	fclose(f);

		hold();
	
	
	//wydruki**************
	
	
	clrscr();

	cout<<"masa"<< '\t'<< masa;
	line();
	cout<<"mx"<< '\t'<< mx;
	line();
	cout<<"mxx"<< '\t'
		<< mxx;
	line();
	cout <<"Pn"<< '\t'<<  Pn;
	line();

	cout << "Px" << '\t'<<  Px;
	hold();
	clrscr();



	printf("LP\tmasa\tX\n");	
	
	for (int i=0;i<loa;i++){
		printf("%d\t%lf\t%lf\n",LP[i],MASA[i],X[i]);
		
	}
	hold();
	clrscr();
	cout <<"XSCk"<< '\t'<< XSCk;
	line();
	cout <<"Iyy"<< '\t'<< Iyy;
	line();
	cout <<"lh"<< '\t'<< lh;
	line();
	cout <<"epsilon"<< '\t'<< epsilon;
	line();
	hold();

	clrscr();
	cout <<"Ra"<< '\t'<< RA;
	line();
	cout <<"Rb"<< '\t'<< RB;
	line();
	hold();
	
	clrscr();
	printf("MX\tMXX\tP\tPX\tPeps\n");	
	for (int i=0;i<loa;i++){
		printf("%lf\t%lf\t%lf\t%lf\t%lf\n",MX[i],MXX[i],PN[i],PX[i],PE[i]);
		
	}
	
	hold();
	

	return Iyy;
}






void BIPOL9(){

	//*****************************************DANE*****************************

	double b=15.5; //rozpietość
	double croot=2.2; //cięciwa przykadlubowa
	double S=25.5; //pow nośna

	double cg=S/b;	
	double ctip=2*cg-croot; //cieciwa koncowa
	double λ=ctip/croot;
	double Λ=b*b/S;
	double ca=2*croot*(1+λ+λ*λ)/(3*(1+λ));

//	printf("b:%.3lf\nCr:%.3lf\nCt:%.3lf\nS:%.3lf\nCa:%.3lf\nzbieznosc:%.3lf\nwydluzenie:%.3lf\n",b,croot,ctip,S,ca,λ,Λ);hold();	clrscr();

	double g=9.81;
	double a∞=5.5;
	double masa=2100; //przelotowa
	double Q=masa*g; //ciezar w przelocie

	//***************************************************************
	int lp=1000; //liczba przedzialow
	//***************************************************************
	
	double dy=b/2/lp; //jednostka podzialowa
	
	double Cz_max=1.4; //maksymalny wsp sily nosnej
	//	************DANE SCHRENK ENDS******************************************

	double mpl=298; //masa plata
	double mfuel=2*500; //masa paliwa

	double n=4.4;	//wsp obciazenia

	double Va=100; //predkosc dla a
	double ρ=gestosc(0); //gestosc na wysokosci obliczeniowej
	double mpodw=80; //masa podwozia

	double Δxai=0.4*ca;

	int fuelmin=30; //przedzial gdzie zaczyna sie paliwo %
	int fuelmax=80; //przedzial gdzie konczy sie zbiornik %

	int wheelmin=10; //przedzial gdzie zaczyna sie podwozie %
	int wheelmax=10; //przedzial gdzie konczy sie podwozie %
		//***************DANE SKLADOWE OBCIAZENIA*******************************

	double CmSA=-0.05;


//************************************DANEENDS********************************************




	printf("Q:%.3lf\ndy:%.3lf\nCzmax:%.3lf\n",Q,dy,Cz_max);hold();clrscr();

	double *Yi=(double*)malloc((lp+2)*sizeof(double));
	double *Ci=(double*)malloc((lp+2)*sizeof(double));
	double *Si=(double*)malloc((lp+2)*sizeof(double));
	double *Cei=(double*)malloc((lp+2)*sizeof(double));
	double *Ci_bezw=(double*)malloc((lp+2)*sizeof(double));
	double *Cei_bezw=(double*)malloc((lp+2)*sizeof(double));
	double *Si_bezw=(double*)malloc((lp+2)*sizeof(double));
	double *CZ=(double*)malloc((lp+2)*sizeof(double));
	double *CZ_max=(double*)malloc((lp+2)*sizeof(double));


	Yi[0]=0;
	Yi[1]=dy/2;

	for (int i=2;i<(lp+1);i++){
		Yi[i]=Yi[i-1]+dy;
	}
	Yi[lp+1]=b/2;
	
	double Scheck=0;
	double Sbezcheck=0;
	clrscr();
	

	Ci[0]=croot;Si[0]=0;Cei[0]=(4*S/(4*atan(1.)*b));Ci_bezw[0]=1; Si_bezw[0]=0; CZ[0]=0.5*(1+Cei[0]/Ci[0]);Cei_bezw[0]=Cei[0]/Cei[0];CZ_max[0]=CZ[0]*Cz_max;

	for (int i=1;i<(lp+2);i++){
		Ci[i]=croot*(1-(2*Yi[i]/b)*(1-λ));
		Si[i]=Ci[i]*dy;
		Cei[i]=(4*S/(4*atan(1.)*b))*sqrt(1-(2*Yi[i]/b)*(2*Yi[i]/b));
		Ci_bezw[i]=Ci[i]/croot;
		Cei_bezw[i]=Cei[i]/Cei[0];
		Si_bezw[i]=Si[i]/S;
		CZ[i]=0.5*(1+Cei[i]/Ci[i]);
		CZ_max[i]=CZ[i]*Cz_max;
		Scheck+=Si[i];
		Sbezcheck+=Si_bezw[i];
				
	}


	Scheck=Scheck-Si[lp+1]-Si[0];
	Sbezcheck=Sbezcheck-Si_bezw[0]-Si_bezw[lp+1];

	Si[lp+1]=0;
	Si_bezw[lp+1]=0;

	if(fabs(Scheck-0.5*S)<0.01)puts("S:OK");
	if(fabs(Sbezcheck-0.5)<0.01)puts("Sbez:OK\n");

	printf("Scheck:%lf\nSbezchceck:%lf\n",Scheck*2,Sbezcheck);
/*	graphics(1000,1000);
	setbkcolor(WHITE);
	setcolor(BLACK);
	chart(Yi,CZ,lp,"y[m]","Cz","Schrenk");
	hold();
	*/

	FILE *SCHRENK;
	SCHRENK=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL9\\Schrenk.xls","w");
	

	fprintf(SCHRENK,"nr\tYi\tCi\tSi\tCel\tCibez\tCelbez\tSibez\tCz\tCzmax\n");
	for (int i=0;i<(lp+2);i++){
		fprintf(SCHRENK,"%d\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\n",i,Yi[i],Ci[i],Si[i],Cei[i],Ci_bezw[i],Cei_bezw[i],Si_bezw[i],CZ[i],CZ_max[i]);
	}

	fclose(SCHRENK);
//SCHRENK ENDS

	double *Pzi=(double*)malloc((lp+2)*sizeof(double));
	double *P_wing=(double*)malloc((lp+2)*sizeof(double));
	double *P_fuel=(double*)malloc((lp+2)*sizeof(double));
	double *P_podw=(double*)malloc((lp+2)*sizeof(double));
	double *P_m=(double*)malloc((lp+2)*sizeof(double));
	double *Fti=(double*)malloc((lp+2)*sizeof(double));
	double *Tj=(double*)malloc((lp+2)*sizeof(double));
	double *M_ni=(double*)malloc((lp+2)*sizeof(double));
	double *Mg=(double*)malloc((lp+2)*sizeof(double));
	double *Ti_pal=(double*)malloc((lp+2)*sizeof(double));
	
	P_wing[lp+2]=0;P_fuel[lp+2]=0;P_podw[lp+2]=0;P_m[lp+2]=0;Fti[lp+2]=0;Tj[lp+2]=0;
	M_ni[lp+2]=0;Mg[lp+2]=0;Ti_pal[lp+2]=0;

	int zfmin=(int)floor((double)fuelmin/100*(double)lp);
	int zfmax=(int)ceil((double)fuelmax/100*(double)lp);



	int zpmin=(int)floor((double)wheelmin/100*(double)lp);
	int zpmax=(int)ceil((double)wheelmax/100*(double)lp);

	printf("Paliwo  %d - %d\npodwozie %d - %d\n",zfmin,zfmax,zpmin,zpmax);
	for (int i=0;i<lp+2;i++){
		P_fuel[i]=0;
		P_podw[i]=0;
		Pzi[i]=0;
		P_wing[i]=0;
		P_m[i]=0;
		Fti[i]=0;
		Ti_pal[i]=0;


	}
		double fuel=0;

	for (int i=zfmin;i<zfmax+1;i++){
		P_fuel[i]=0.5*mfuel*g/(zfmax-zfmin);
		fuel+=P_fuel[i];
	}
	P_podw[zpmin]=0.5*mpodw*g;

	double checkTnace=0;
	line();hold();
	clrscr();
	double pow=0;
	cout<<fuel<<"\t paliwo \t"<<mfuel*g/2;space();cout<<mfuel;
		
	double wing=0;
	double podw=0;
	for (int i=1;i<lp+2;i++){
		Pzi[i]=masa*g*Si[i]/S*CZ[i];
		P_wing[i]=Si[i]/S*mpl*g;
		P_m[i]=(P_wing[i]+P_fuel[i]+P_podw[i]);
		Fti[i]=(Pzi[i]-P_m[i])*n;
		Tj[i]=0;
		Mg[i]=0;
		M_ni[i]=0;
		Ti_pal[i]=0;
		wing+=P_wing[i];
		podw+=P_podw[i];
		pow+=Si[i];

	}
	line();cout<<wing<<"\t plat \t"<<mpl*g/2;space();cout<<mpl;line();cout<<podw<<"\t podwozie \t"<<mpodw*g/2;space();cout<<mpodw;line();cout<<pow<<"\t powierzchnie \t"<<S/2;line();
	Mg[lp+2]=0;
	Tj[lp+2]=0;
	Ti_pal[lp+2]=0;
	

	for (int i=lp+1;i>-1;i--){
		Ti_pal[i]=Ti_pal[i+1]+(Fti[i+1]+P_fuel[i+1]*n);
		Tj[i]=Tj[i+1]+Fti[i+1];
		M_ni[i]=M_ni[i+1]+(Fti[i+1]+P_fuel[i+1]*n)*Yi[1]+Ti_pal[i+1]*dy;
		Mg[i]=Mg[i+1]+Fti[i+1]*Yi[1]+Tj[i+1]*dy;
		
	}
	for (int i=0;i<lp+2;i++){
		checkTnace=checkTnace+Pzi[i];
	}
	hold();
	clrscr();
	cout<<masa*g*n/2<<"\tTtotal\t"<<Tj[0];
	line();
	cout<<masa*g*n/2<<"\tbezpaliwa\t"<<Ti_pal[0]+mpodw*g*n/2+mpl*g*n/2;
	line();

	hold();

	

	puts("\n");
	clrscr();
	cout<<"sprawdzenie masy";

	line();
	cout<<checkTnace<<"\t"<<(masa)*g/2;
	line();
/*	

	closegraph();
	graphics(1000,1000);
	setbkcolor(WHITE);
	setcolor(BLACK);
	chart(Yi,Mg,lp,"y[m]","Mg[N]","Momentygnace");
	hold();
	closegraph();

	*/
	FILE *SCHRENK2;
	SCHRENK2=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL9\\rozkladobciazen.xls","w");

	fprintf(SCHRENK2,"Yi\tPzi\tPwing\tPfuel\tPpodw\tPm\tFt\tTi\tMg\tTipal\n");
		
	for (int i=0;i<lp+2;i++){
		fprintf(SCHRENK2,"%lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\n",Yi[i],Pzi[i],P_wing[i],P_fuel[i],P_podw[i],P_m[i],Fti[i],Tj[i],Mg[i],Ti_pal[i],M_ni[i]);
	}

	fclose(SCHRENK2);

	//*****************************************************ROZKLAD OBCIAZEN IS OVER**************************************************************************




	double *ΔM_Pzi=(double*)malloc((lp+2)*sizeof(double));
	double *ΔMsi=(double*)malloc((lp+2)*sizeof(double));
	double *Ms_fuel=(double*)malloc((lp+2)*sizeof(double));
	double *ΔMs_ofi=(double*)malloc((lp+2)*sizeof(double));
	double *Ms_nofuel=(double*)malloc((lp+2)*sizeof(double));


	Δxai=0.4;
	


	for (int i=0;i<lp+2;i++){
		ΔM_Pzi[i]=((-Pzi[i]*n*0.25*Ci[i])+(P_m[i]*n*Δxai*Ci[i]));
		ΔMsi[i]=0.5*ρ*Va*Va*CmSA*Si[i]/S+ΔM_Pzi[i];

		ΔMs_ofi[i]=0.5*ρ*Va*Va*CmSA*Si[i]/S+n*(Pzi[i]*0.25*Ci[i]-(Δxai*Ci[i]*(P_m[i]-P_fuel[i])));
		Ms_fuel[i]=0;
		Ms_nofuel[i]=0;
	}

	for (int i=lp+1;i>-1;i--){
		Ms_fuel[i]=Ms_fuel[i+1]+ΔMsi[i];
		Ms_nofuel[i]=Ms_nofuel[i+1]+ΔMs_ofi[i];
	}
	/*
	graphics(1000,1000);
	setbkcolor(WHITE);
	setcolor(BLACK);
	chart(Yi,Ms_nofuel,lp,"y[m]","Ms[Nm]","Monmentskrecajacy");
	hold();
	closegraph();
	*/
	

	FILE *SCHRENK3;
	SCHRENK3=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL9\\momentyskrecajace.xls","w");
	

	fprintf(SCHRENK3,"Y\tMPzi\tdMs\tMsfuel\tdMsof\tMsnofuel\n");
	for (int i=0;i<lp+2;i++)fprintf(SCHRENK3,"%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\n",Yi[i],ΔM_Pzi[i],ΔMsi[i],Ms_fuel[i],ΔMs_ofi[i],Ms_nofuel[i]);
	fclose(SCHRENK3);

	//*********************************Rozkladcisnien********************************************************


	double V=100;
	
	double cs=ca/6;  //zgaduje ze cieciwa lotki
	double φ=cs/ca;  
	double q=0.5*ρ*V*V;

	double a1=3.166;
	double a2=2.4;

	double αzh=radiany(-3.097);
	double δmax=radiany(10);
	
	double ΔCz=a1*αzh+a2*δmax;
	double ΔCm=-0.003+CmSA;
	double Cz=2*masa*g/g/V/V/S;


	double p=(11*Cz-60*CmSA)*q/8;
	double h=(25*Cz-300*CmSA)*q/8;

	double Δp=((2*φ+0.5)*ΔCz-6*ΔCm*q/φ);
	double Δh=(0.5*ΔCz+6*ΔCm)*q/(φ*(1-φ));

	double X[4]={0,0.2*cg,cg*(1-cs/ca),1*cg};

	double P[4];
	double H[4]={h,0,0,0};

	double ΔP[4];
	double ΔH[4];

	double plaski[4];
	double lotka [4];
	double sum[4];


	for (int i=0;i<4;i++){
		P[i]=p*(1-X[i]/cg);
		ΔP[i]=Δp*(1-X[i]/cg);
		ΔH[i]=Δh*(1-X[i]/(cg*(1-cs/ca)));
		ΔH[3]=0;

		plaski[i]=P[i]+H[i];
		lotka[i]=ΔP[i]+ΔH[i];
		sum[i]=plaski[i]+lotka[i];

	}
	FILE *SCHRENK4;
	SCHRENK4=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL9\\rozkladcisnien.xls","w");

//	fprintf(SCHRENK4,"X\tP\tH\tdP\tdH\tplaski\tlotka\tsum\n");
//	for(int i=0;i<4;i++)fprintf(SCHRENK4,"%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\n",X[i],P[i],H[i],ΔP[i],ΔH[i],plaski[i],lotka[i],sum[i]);

	fclose(SCHRENK4);


	//********************************OBCIAZENIA USTERZENIA POZIOMEGO*******************************
	//***************************warunki rownowagi*****************************88



	





	//******************************rozklad cisnienia usterzenia******************************

	CmSA=-0.05;

	double VX[4]={50.,0.,100.,140.}; //A F C D
	double wys=0.;

	 a1=3.165957;
	 a2=2.2402820;

	double b2=-0.331401;
	double b1=-0.132429;

	double Sh=6.1;
	
	double cah=0.83;
	double Λh=3;
	double bh=sqrt(Λh*Sh);
	double csh=cah/3;
	double Ssh=csh*bh;


	double CMBU[4]={0.105156,0,-0.055481,0.0585};


	double δH[4]={-0.08,-0.01,0,0.02};
	double CZX[4];
	double CZH[4];
	double αh[4];
	double L_H[4];
	double a1_prim=a1*(1-a2*b1/a1/b2);
	double a1alfaH[4];
	double a2deltaH[4];
	double deltaL_H[4];
	double b1alfaH[4];
	double b2deltaH[4];
	double CM[4];
	double M_zH[4];
	double deltaM_zH[4];



	Cz_max=1.4;
	FILE *Z=fopen("C:/Users/Herkes/Desktop/bipol/BIPOL9\\usterzenie.xls","w");

	
	fprintf(Z,"V\tCZX\tCmbu\taflah\tdeltah\tLH\tCzH\ta1alfaH\tdeltaLH\ta2deltaH\tb1alfaH\tb2deltaH\tCm\tMzH\tdeltaMzh\n");
	for (int i=0;i<4;i++){
		CZX[i]=2*masa*g/gestosc(wys)/VX[i]/VX[i]/S;
		CZX[0]=Cz_max;
		CZH[i]=CZX[i]*0.04-0.07; //aproksymacja Czh(Cz)
		αh[i]=CZH[i]/a1_prim;
		L_H[i]=0.5*gestosc(wys)*Sh*VX[i]*VX[i]*CZH[i];
		a1alfaH[i]=a1*αh[i];
		a2deltaH[i]=a2*δH[i];
		deltaL_H[i]=0.5*gestosc(wys)*Sh*VX[i]*VX[i]*CZH[i];
		b1alfaH[i]=b1*αh[i];
		b2deltaH[i]=b2*δH[i];
		CM[i]=b1alfaH[i]+b2deltaH[i];
		M_zH[i]=b1alfaH[i]*cah*Sh*VX[i]*VX[i]*gestosc(wys)*0.5;
		deltaM_zH[i]=b2deltaH[i]*csh*Ssh*VX[i]*VX[i]*gestosc(wys)*0.5;
		
		fprintf(Z,"%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",VX[i],CZX[i],CMBU[i],stopnie(αh[i]),stopnie(δH[i]),L_H[i],CZH[i],a1alfaH[i],deltaL_H[i],a2deltaH[i],b1alfaH[i],b2deltaH[i],CM[i],M_zH[i],deltaM_zH[i]);
	}

	fprintf(Z,"a1:%lf\na2:%lf\nb1:%lf\nb2:%lf\nSh:%lf\nSsh:%lf\nCsh:%lf\n",a1,a2,b1,b2,Sh,Ssh,csh);
	fclose(Z);


	//MAKSYMALNE WYCHYLENIE STERU +- 10stopni

	double dPdh_plus=0.5*VX[0]*VX[0]*Sh*(radiany(10.)-δH[0]);
	double dPdh_minus=0.5*VX[0]*VX[0]*Sh*(radiany(-10.)-δH[0]);

	double Pdh_plus=L_H[0]+dPdh_plus;
	double Pdh_minus=L_H[0]+dPdh_minus;

	//MAKSYMALNE PRZYSPIESZENIE KATOWE

	double Iyy=BIPOL10(); //69226.6;

	double ε1[4];
	double ε2[4];

	double dPdh_1[4];
	double dPdh_2[4];
	double Pdh_1[4];
	double Pdh_2[4];


	double lh=5;
	double nm=4.4;

	double Ude[4]={0,25,50,25};
	double Ude_ms[4];
	double dLht[4];
	double PzH[4];

	double a=4.603;
	double WnaS=masa*g/S;

	double ug=2*WnaS/gestosc(wys)/ca/a/g;

	double kg=0.88*ug/(5.3+ug);
	
	double dεpodα=2*a/3.14/Λ;

	for (int i=2;i<4;i++){
		ε1[i]=39/knotts(VX[i])*nm*(nm-1.5);
		ε2[i]=-ε1[i];

		dPdh_1[i]=ε1[i]*Iyy/lh;
		dPdh_2[i]=ε2[i]*Iyy/lh;

		Pdh_1[i]=L_H[i]+dPdh_1[i];
		Pdh_2[i]=L_H[i]+dPdh_2[i];

		Ude_ms[i]=Ude[i]*0.3048;
		dLht[i]=0.5*gestosc(wys)*Sh*a1*kg*Ude_ms[i]*VX[i]*(1-dεpodα);
		PzH[i]=L_H[i]+dLht[i];


	}
	line();
	cout<"kg";line();
	cout<<kg;
	hold();
	



FILE *f=fopen("C:/Users/Herkes/Desktop/bipol/BIPOL9\\obciazeniamanewrowe.xls","w");


fprintf(f,"dPdh_plus\tdPdh_minus\tPdh_plus\tPdh_minus\t\tV[kts]\teps1\teps2\tdpdh1\tdpdh2\tpdh1\tpdh2\t\tudeft\tudems\tdLht\tpzh\n");
for (int i=0;i<4;i++){
fprintf(f,"%.3lf\t%.3lf\t%.3lf\t%.3lf\t\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t\t%.3lf\t%.3lf\t%.3lf\t%.3lf\n",dPdh_plus,dPdh_minus,Pdh_plus,Pdh_minus,knotts(VX[i]),ε1[i],ε2[i],dPdh_1[i],dPdh_2[i],Pdh_1[i],Pdh_2[i],Ude[i],Ude_ms[i],dLht[i],PzH[i]);

}
fclose(f);


//Schrenk dla usterzenia**************************************************

	bh=7.81;
	dy=bh/2/lp;
	 a1=3.166;
	 a2=2.4;

	 αzh=radiany(-3.097);
	 δmax=radiany(10);
	    
	 ΔCz=a2*δmax;
	 ΔCm=b2*δmax;

	double Czh_max=a1*αzh;
	
	double cgh=Sh/bh;	
	double λh=1;
	λ=1;
	Λ=b*b/S;
	cah=0.83;
	Va=100; //predkosc dla a
	ρ=gestosc(0); //gestosc na wysokosci obliczeniowej

	double Δxaih=0.4*cgh;
	double mplh=64;
	double dyh=bh/2/lp;

	double *Yih=(double*)malloc((lp+2)*sizeof(double));
	double *Cih=(double*)malloc((lp+2)*sizeof(double));
	double *Sih=(double*)malloc((lp+2)*sizeof(double));
	double *Ceih=(double*)malloc((lp+2)*sizeof(double));
	double *Cih_bezw=(double*)malloc((lp+2)*sizeof(double));
	double *Ceih_bezw=(double*)malloc((lp+2)*sizeof(double));
	double *Sih_bezw=(double*)malloc((lp+2)*sizeof(double));
	double *CZh=(double*)malloc((lp+2)*sizeof(double));
	double *CZh_max=(double*)malloc((lp+2)*sizeof(double));

	double crooth=cah;

	Yih[0]=0;
	Yih[1]=dyh/2;
	

	for (int i=2;i<(lp+1);i++){
		Yih[i]=Yih[i-1]+dyh;
	}
	Yih[lp+1]=bh/2;
	
	double Shcheck=0;
	double Shbezcheck=0;


	
	for (int i=0;i<(lp+2);i++){
		Cih[i]=cah;
		Sih[i]=Cih[i]*dyh;
		Ceih[i]=(4*Sh/(4*atan(1.)*bh))*sqrt(1-(2*Yih[i]/bh)*(2*Yih[i]/bh));
		Cih_bezw[i]=Cih[i]/crooth;
		Ceih_bezw[i]=Ceih[i]/Ceih[0];
		Sih_bezw[i]=Sih[i]/Sh;
		CZh[i]=0.5*(1+Ceih[i]/Cih[i]);
		CZh_max[i]=CZh[i]*Czh_max;
		Shcheck+=Sih[i];
		Shbezcheck+=Sih_bezw[i];
				
	}


		FILE *SCHRENKh;
	SCHRENKh=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL9\\Schrenkustrzeenie.xls","w");
	

	fprintf(SCHRENKh,"Yi\tCi\tSi\tCel\tCibez\tCelbez\tSibez\tCz\tCzmax\n");
	for (int i=0;i<(lp+2);i++){
		fprintf(SCHRENKh,"%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\n",Yih[i],Cih[i],Sih[i],Ceih[i],Cih_bezw[i],Ceih_bezw[i],Sih_bezw[i],CZh[i],CZh_max[i]);
	}

	fclose(SCHRENKh);

	double *Pzih=(double*)malloc((lp+2)*sizeof(double));
	double *Ph_wing=(double*)malloc((lp+2)*sizeof(double));
	double *Ph_m=(double*)malloc((lp+2)*sizeof(double));
	double *Ftih=(double*)malloc((lp+2)*sizeof(double));
	double *Tjh=(double*)malloc((lp+2)*sizeof(double));
	double *Mh_ni=(double*)malloc((lp+2)*sizeof(double));
	double *Mgh=(double*)malloc((lp+2)*sizeof(double));
	
	
	Ph_wing[lp+2]=0;Ph_m[lp+2]=0;Ftih[lp+2]=0;Tjh[lp+2]=0;
	Mh_ni[lp+2]=0;Mgh[lp+2]=0;

	for (int i=0;i<lp+2;i++){
		Pzih[i]=0.5*ρ*Va*Va*Sih[i]/Sh*CZh[i];
		Ph_wing[i]=Sih[i]/Sh*mplh*g;
		Ph_m[i]=(Ph_wing[i]);
		Ftih[i]=(Pzih[i]-Ph_m[i]*n);
		Tjh[i]=0;
		Mgh[i]=0;
		Mh_ni[i]=0;
		

	}
	
	Mgh[lp+2]=0;
	Tjh[lp+2]=0;

	
	for (int i=lp+1;i>-1;i--){
		Tjh[i]=Tjh[i+1]+Ftih[i+1];
		Mgh[i]=Mgh[i+1]+Ftih[i+1]*Yih[1]+Tjh[i+1]*dyh;
	}
		

	FILE *SCHRENK2h;
	SCHRENK2h=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL9\\rozkladobciazenusterzenie.xls","w");

	fprintf(SCHRENK2h,"Yih\tPzi\tPwing\tPm\tFt\tTi\tMg\n");
		
	for (int i=0;i<lp+1;i++){
		fprintf(SCHRENK2h,"%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\n",Yih[i],Pzih[i],Ph_wing[i],Ph_m[i],Ftih[i],Tjh[i],Mgh[i]);
	}

	fclose(SCHRENK2h);

	

	double *ΔMh_Pzi=(double*)malloc((lp+2)*sizeof(double));
	double *ΔMsih=(double*)malloc((lp+2)*sizeof(double));
	double *Msh=(double*)malloc((lp+2)*sizeof(double));


	



	for (int i=0;i<lp+2;i++){
		
		ΔMh_Pzi[i]=Pzih[i]*0.25*Cih[i]-Ph_m[i]*Δxaih*Ci[i];


		
		ΔMsih[i]=0.5*ρ*Va*Va*CmSA*Sih[i]/Sh+ΔMh_Pzi[i];
		Msh[i]=0;
	}

	for (int i=lp+1;i>-1;i--){
		Msh[i]=Msh[i+1]+ΔMsih[i];
		
	}
	FILE *SCHRENK3h;
	SCHRENK3h=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL9\\momentyskrecajaceustzerzenie.xls","w");
	

	fprintf(SCHRENK3h,"Y\tMPzi\tdMs\tMs\n");
	for (int i=0;i<lp+2;i++)fprintf(SCHRENK3,"%.3lf\t%.3lf\t%.3lf\t%.3lf\n",Yih[i],ΔMh_Pzi[i],ΔMsih[i],Msh[i]);
	fclose(SCHRENK3h);

	
	V=100;
	double ch=cah/1.48;		//cieciwa statecznika
	csh=ch*0.4;
	  //zgaduje ze cieciwa lotki
	 φ=csh/cah;  
	 q=0.5*gestosc(0)*V*V;

	 a1=3.166;
	 a2=2.4;

	 αzh=radiany(-3.097);
	 δmax=radiany(10);
	    
	 ΔCz=a2*δmax;
	 ΔCm=b2*δmax;
	 clrscr();
	

	 Cz=2*masa*g/g/V/V/S;
	double Czh=0.04*Cz-0.07;
	Czh=αzh*a1+a2*δmax;

	line();
	clrscr();
	line();
	cout<<"Czh";
	line();cout<<Czh;
	line();	
	CmSA=αzh*b1+b2*δmax;
	clrscr();
	cout<<"CmSA";space();cout<<CmSA;line();
	cout<<"CS";space();cout<<csh;line();
	cout<<"q";space();cout<<q;line();
	double ph=(11*Czh-60*CmSA)*q/8;
	double hh=(25*Czh-300*CmSA)*q/8;

	double Δph=((2*φ-0.5)*ΔCz-6*ΔCm)*q/φ;
	double Δhh=(0.5*ΔCz+6*ΔCm)*q/(φ*(1-φ));

	double Xh[4]={0,0.2*cah,cah*(1-φ),cah};

	double Ph[4];
	double Hh[4]={hh,0,0,0};

	double ΔPh[4];
	double ΔHh[4];

	double plaskih[4];
	double lotkah [4];
	double sumh[4];


	for (int i=0;i<4;i++){
		Ph[i]=ph*(1-Xh[i]/cah);
		ΔPh[i]=Δph*(1-Xh[i]/cah);
		ΔHh[i]=Δhh*(1-Xh[i]/cah);
		ΔHh[3]=0;

		plaskih[i]=Ph[i]+Hh[i];
		lotkah[i]=ΔPh[i]+ΔHh[i];
		sumh[i]=plaskih[i]+lotkah[i];

	}
	FILE *SCHRENK4h;
	SCHRENK4h=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL9\\rozkladcisnienusterzenie.xls","w");

	fprintf(SCHRENK4h,"X\tP\tH\tdP\tdH\tplaski\tster\tsum\n");
	for(int i=0;i<4;i++)fprintf(SCHRENK4,"%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\n",Xh[i],Ph[i],Hh[i],ΔPh[i],ΔHh[i],plaskih[i],lotkah[i],sumh[i]);

	fclose(SCHRENK4h);
	line();

	//cout<<"Czhmax:"<<Czh_max<<"\n";
	hh=-hh;
	ph=-ph;

	double adp=q*((4*φ-1)*a2*δmax-12*b2*δmax)/2/φ;
	double adh=q*(a2*δmax+12*b2*δmax)/2/φ/(1-φ);
	double ap1=ph+hh+adp+adh;
	double ap2=0.8*(ph+adp)+(0.8-φ)/(1-φ)*adh;
	double ap3=φ*(p+adp);

	double aq1=0.1*(ap1+5*ap2*(1-φ)+ap3*(4-5*φ));
	double aq2=0.5*φ*ap3;
	
	double x1=1*(ap1+2*ap2+15*(0.8-φ)*(ap2+ap3)+25*(0.8-φ)*(0.8*φ)*(ap2+2*ap3))/150/aq1;
	double x2=1-2*φ/3;

	FILE *SCHRENK5h;
	SCHRENK5h=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL9\\tabelkacisnien.xls","w");

	fprintf(SCHRENK5h,"p\t%lf\nh\t%lf\ndp\t%lf\ndh\t%lf\np1\t%lf\np2\t%lf\np3\t%lf\nq1\t%lf\nq2\t%lf\nx1\t%.5lf\nx2\t%lf",ph,hh,Δph,Δhh,ap1,ap2,ap3,aq1,aq2,x1,x2);
	fclose(SCHRENK5h);

	line();
//	cout<<a;
	line();
//	cout<<(ap1+2*ap2+15*(0.8-φ)*(ap2+ap3)+25*(0.8-φ)*(0.8*φ)*(ap2+2*ap3))/aq1/150;
	line();
//	cout<<x2;
	line();
//	cout<<φ;
	
//	cout<<Sh;




}









void BIPOL7(){

int size=16;
	double skala=0.03886363636;
	double g=9.81;
	
	double S=25.5; //pole pow. nosnej
	double Sh=6.1; //pole pow. usterzenia
	double Ssh=1.48; //pole pow steru
	
	double Xh=5;		//odleglosc miedzy 0.25sca plata i 0.25sca usterzenia 
	double Λh=10;		//wydluzenie usterzenia
	double crooth=1.1;	//cieciwa przykadlubowa usterzenia
	double cah=0.83;	//srednia cieciwa aerodynamiczna usterzenia
	double Λ=9.38;		//wydluzenie
	double wydluzenie=Λ;
	double ctiph=0.45;	//cieciwa koncowa usterzenia
	double λh=0.4;		//zbieznosc
	double bh=7.81;		//rozpietosc
	double Sbf=4.2;		//pole pow poziom kadluba do 0.25sca
	double lb=10.4;		// dlugosc kadluba
	double Sb=11.72;	//rzut kadulba na xy
	double w=1.6;		//rozpietosc
	double croot=2.2;	//przykadlubowa
	double masa=1800;	//masa w locie
	double lbf=3.61;	//odleglosc od noska do 0.25sca
	double ln=lbf; 
	double b=15.5;		// rozpiętość płata


	double bsh=2.72;	//rozpietosc steru
	double Zc=0.233;	//wysokosc SC
	double Cmsa=-0.05;	//moment pochylajacy plata
	double Xsca=0.246;	//polozenie srodka aerodynamicznego od noska plata
	double Xs=0.25-Xsca;//Ramie poziome sily aerodynamicznej od XC
	double Zs=0.233;	//Ramie pionowe sily aerodynamicznej
	
	double Ca=1.71;		//srednia cieciwa aerodynamiczna plata
	double a=4.603;		// dCz/dα dla plata
	double H=5000;		//wysokosc przelotowa
	double V=100;		//predkosc przelotowa
	double δ=0.09;		//grubos profilu usterzenia
	double a∞=5.5;		// dCz/α profilu
	
	double ρ=gestosc(H);
	double M=V/predkoscdzwieku(H); //Mach

double H1=1.75;
double H2=2.5;
double H3=3.375;

double S1=2.44;
double S2=2.44;
double Svu=8;

double Sv1=0.8125;
double Sv2=0.1875;
double Sv3=0.14;
double Sv=1;

double crootv=3;
double ctipv=1.5;
double cva=7/3;

double Λv=1.95;
double λV=0.5;
double lv=5;

	S1=H2*H2/Λv;



double av10T=6.85; //w010105

double Reynolds=V*Ca/lepkosckinematyczna(H);


double a10doa10T=0.85; //W010105

double av10=a10doa10T*av10T;


//C010101 

double cvf=0.5;
double MACH=V/predkoscdzwieku(H);



double av1=2.52;
double av2=1.584;


//A050109



double k=a*sqrt(1-MACH*MACH)/2/(4*atan(1.));



double A050109=-0.008;

//Wymiary lotki
	double cf=0.25*Ca;     
	double bf=7.775;
	//hold();clrscr();

//b1b2	

	double ainf=5.74;
	

	double b1inf=stopnie(-0.0057);
	double b2inf=stopnie(-0.00970);
	


	double ηsh=0.267;

	double b1=b1inf*a/ainf;
	double b2=b2inf+((a/ainf)-1)*b1*ηsh;


//A060101

	double a10=5.74;
	double a10m=a10*sqrt(1-M*M);

	k=a10m/2/4/atan(1.);
	
	
	double A060101rys85=0.55;
	double lp=-A060101rys85*k/sqrt(1-M*M);

	

	double zav=1.94;

	double clpf=-av1*zav*zav*S1*0.85/b/b/S;
	double Clp=clpf+0.5*lp;



	//Ocena
	double lksi=-0.17;

	double Ix=69226;
	double Ldeltaa=gestosc(H)*V*V*0.5*S*b*lksi/Ix;

	double Lp=gestosc(H)*V*V*0.5*S*b*b*2*Clp/2/Ix/V;

	double Tr=-1/Lp;

	
	double V3[3]={100,60,30};

	double T[3];
	double KSI[3]={-10,-10,-10};
	double FI[3]={45,45,30};


	double TR[3];
	/*
	printf("wydluzenie:%lf\n:%lf\n",Λv,Λv*sqrt(1-MACH*MACH));
	printf("Mach:%lf\nReynolds:%lf\na10:%lf\n",M,Reynolds/1000000,av10);hold();clrscr();
	printf("k:%lf\nA0601009:%lf\n",k,Λ*sqrt(1-MACH*MACH)/k);
	printf("Sh/S:%lf\n",0.25*(b-bf)/b);
	printf("b1:%lf\nb2:%lf\n",b1,b2);
	printf("k:%lf\n%lf\n",k,sqrt(1-M*M)*wydluzenie/k);
	printf("lp:%lf\nclpf:%lf\nClp:%lf\n",lp,clpf,Clp); */
	printf("lp:%lf\nclpf:%lf\nClp:%lf\nLdeltaa:%lf\nLp:%lf\nTr:%lf\n",lp,clpf,Clp,Ldeltaa,Lp,Tr);
	
	//printf("%lf\n\n",clpf);
	puts("\nCzasy\n");
	for (int i=0;i<3;i++){
		T[i]=-FI[i]*b*Clp/KSI[i]/V3[i]/lksi;
		TR[i]=-1/(gestosc(H)*V3[i]*V3[i]*0.5*S*b*b*2*Clp/2/Ix/V3[i]);
		printf("%lf\t%lf\n",T[i],TR[i]);

	}
	
}



void zapasstatecznosci(double xc,double V[], double XN[], double XNprim[], double XM[], double XMprim[], int size,double m, double g, double ca, double H,double Sh, double xh, double a2, double b2, double Ssh, double przelozenie, double csh ){

	double *ZXN=(double*)malloc(size*sizeof(double));
	double *ZXNprim=(double*)malloc(size*sizeof(double));
	double *ZXM=(double*)malloc(size*sizeof(double));
	double *ZXMprim=(double*)malloc(size*sizeof(double));
	
	for(int i =0; i<size;i++){
		ZXN[i]=XN[i]-xc;
		ZXNprim[i]=XNprim[i]-xc;
		ZXM[i]=XM[i]-xc;
		ZXMprim[i]=XMprim[i]-xc;

	}

	
	char filename[100];
	sprintf(filename,"c:/Users/Herkes/Desktop/bipol/BIPOL6\\zapas statecznosci dla %.2lf .xls",xc);
	char filename2[100];
	sprintf(filename2,"c:/Users/Herkes/Desktop/bipol/BIPOL6\\gradienty dla %.2lf .xls",xc);

	//puts(filename);
	FILE *fp1;
	fp1=fopen(filename,"w");
	fprintf(fp1,"V\tXN\tXN'\tXM\tXM'\n");
	for (int i=0;i<size;i++){
		fprintf(fp1,"%lf\t%lf\t%lf\t%lf\t%lf\n",V[i],ZXN[i],ZXNprim[i],ZXM[i],ZXMprim[i]);
	}
	
	
	FILE *fp2;
	fp2=fopen(filename2, "w");

	double *δhpodV=(double*)malloc(size*sizeof(double));
	double *δhpodn=(double*)malloc(size*sizeof(double));
	double *silapodV=(double*)malloc(size*sizeof(double));
	double *silapodn=(double*)malloc(size*sizeof(double));

	for(int i=0;i<size;i++){
		δhpodV[i]=4*m*g*ca/gestosc(H)/V[i]/V[i]/V[i]/Sh/xh/a2*ZXN[i];
		δhpodn[i]=(-2)*m*g*ca/gestosc(H)/V[i]/V[i]/Sh/xh/a2*ZXM[i];
		silapodV[i]=(-2)*m*g*ca*Ssh*b2*csh*przelozenie/V[i]/xh/Sh/a2*ZXNprim[i];
		silapodn[i]=m*g*ca*Ssh*b2*csh*przelozenie/xh/Sh/a2*ZXMprim[i];
	}
	fprintf(fp2,"V\tdeltahpodV\tdeltahpodn\tsilapodV\tsilapodn\n");
	for (int i=0;i<size;i++){
		fprintf(fp2,"%lf\t%lf\t%lf\t%lf\t%lf\n",V[i],stopnie(δhpodV[i]),stopnie(δhpodn[i]),silapodV[i],silapodn[i]);
	}
	
	
}


void BIPOL6(){
	FILE *Daneclr;
	Daneclr=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL6\\Dane.xls","w");
	fclose(Daneclr);
	FILE *Dane;
	Dane=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL6\\Dane.xls","a");

	int size=16;
	double skala=0.03886363636;
	double g=9.81;
	
	double S=25.5; //pole pow. nosnej
	double Sh=6.1; //pole pow. usterzenia
	double Ssh=1.48; //pole pow steru
	
	double Xh=5;		//odleglosc miedzy 0.25sca plata i 0.25sca usterzenia 
	double Λh=10;		//wydluzenie usterzenia
	double crooth=1.1;	//cieciwa przykadlubowa usterzenia
	double cah=0.83;	//srednia cieciwa aerodynamiczna usterzenia
	double Λ=9.38;		//wydluzenie
	double ctiph=0.45;	//cieciwa koncowa usterzenia
	double λh=1;		//zbieznosc
	double bh=7.81;		//rozpietosc
	double Sbf=4.2;		//pole pow poziom kadluba do 0.25sca
	double lb=10.4;		// dlugosc kadluba
	double Sb=11.72;	//rzut kadulba na xy
	double w=1.6;		//rozpietosc
	double croot=2.2;	//przykadlubowa
	double masa=1800;	//masa w locie
	double lbf=3.61;	//odleglosc od noska do 0.25sca
	double ln=lbf; 
	double b=15.5;		// rozpiętość płata


	double bsh=2.72;	//rozpietosc steru
	double Zc=0.233;	//wysokosc SC
	double Cmsa=-0.05;	//moment pochylajacy plata
	double Xsca=0.246;	//polozenie srodka aerodynamicznego od noska plata
	double Xs=0.25-Xsca;//Ramie poziome sily aerodynamicznej od XC
	double Zs=0.233;	//Ramie pionowe sily aerodynamicznej
	
	double Ca=1.71;		//srednia cieciwa aerodynamiczna plata
	double a=4.603;		// dCz/dα dla plata
	double H=5000;		//wysokosc przelotowa
	double V=100;		//predkosc przelotowa
	double δ=0.09;		//grubos profilu usterzenia
	double a∞=5.5;		// dCz/α profilu
	
	double ρ=gestosc(H);
	double M=V/predkoscdzwieku(H); //Mach
	double cf=0.272;	//Lokalna cięciwa klapy przed osią obrotu [steru]
	double bf=3.11;		//Zewnętrzna rozpiętość klap
	double bfi=0.389;	//Wewnętrzna rozpiętość klap
	
	double ch=cah/1.48;		//cieciwa statecznika
	double csh=ch*0.4;		//cieciwa steru
	double cszh=csh*5/6;	//cieciwa steru	za osia obrotu
	double csph=csh/6;	//cieciwasteru przed osia obrotu
	
	double iw=2*masa*g/(gestosc(H)*(V*V)*S*a); //kat zaklinowania profilu
	double aa=predkoscdzwieku(H);
	double MACH=V/predkoscdzwieku(H);
	double Reynolds=V*cah/lepkosckinematyczna(H);
	
	fprintf(Dane,"Mach:%lf\npredkoscdzwieku:=%lf\nRe:%.3lfMPA \n",MACH,aa,Reynolds/1000000);
	fprintf(Dane,"Csnh/Csh:%.2lf\nCsh\Ch:%.2lf\n\n",csph/cszh,(cszh+csph)/ch);
	fprintf(Dane,"Sbf*lbf/Sb*lb:%lf\nww/Sb:%lf\n\n",Sbf*lbf/Sb/lb,w*w/Sb);
	fprintf(Dane,"Cr/lb:%lf\nln/lb:%lf\n\n",croot/lb,ln/lb);

	
	double wykresCmob=-0.1;				//Z WYKRESU INSTRUKCJI (BARDZO EDYTOWALNE)
	double wykresΔxsak=0.4;				//Z WYKRESU INSTRUKCJI (BARDZO EDYTOWALNE)


	
	double Czprzel=2*masa*g/gestosc(H)/V/V/S;

//MOMENT POCHYLAJĄCY KADŁUBA ESDU

	fprintf(Dane,"\n\nlb:%lf\nSb:%lf\nlbf:%lf\nsbf:%lf\nw:%lf\nb:%lf\nc:%lf\nS:%lf\niw:%lf\nCl:%lf\nCN:%lf\na:%lf\n\n",lb,Sb,lbf,Sbf,w,b,Ca,S,stopnie(iw),Czprzel,Cmsa,a);
	

	
	
	double Reynoldskoza=600/3.6*1.2/lepkosckinematyczna(10000);
//	printf("\nReynoldskoza:%lf\n",Reynoldskoza/1000000);

//iteracja usterzenia
	Λh=3;
	bh=sqrt(Λh*Sh);

//	printf("\nbh : %lf\n",bh);

	double k=0.15;
	
	double Λ025=radiany(20);
	double Λe=Λ025-atan(Λ025/(radiany(45)*Λh*(1+λh)));
	//printf("lambadae:%lf\n",stopnie(Λe));
	double	Λem=Λe*1/sqrt(1-M*M);
	//printf("labmadaem:%lf\n",Λem);
	

	double a10=6.03;
	double a10M=a10/sqrt(1-M*M*cos(Λe)*cos(Λe));

	//printf("wspolczynnikW010101:%lf\n",Λh/a10M/cos(Λe));
	
	double τ=0.02;

	double a1=1/(1/(a10M*cos(Λe))+(1+τ)*k);

	fprintf(Dane,"\na1:%lf",a1);
//C010103


	cf=cah/3;
	double t=0.09*cah;
	double a20T=4.5; // z wykresu C0101013

	double a20doa20T=0.9;
	double a20=a20T*a20doa20T;

	//printf("a20:%lf\n",a20);
	//printf("C010106:%lf\n",Λh*sqrt(1-M*M));
	
	double c010106=1.13;
	double a2=c010106*a1*a20/a10;
	fprintf(Dane,"\ta2:%lf\n\n",a2);

	// F010104

	bf=0.8*bh;
	bfi=0.3*bh;
	double η=bf/bh;
//	printf("eta:%.2lf",η);
	double k1=0.85;
	double k2=0.005;
	double k3=0.025;
	double K1=k1*(1+k2*(Λh-6)+k3*sin(Λ025));

	

	double k21=0.4;
	double k22=0.005;
	double k23=0.1;

	double K2=k21*(1+k22*(Λh-6)+k23*sin(Λ025));

	double K=K1-K2;
	//printf("\nK:%lf",K);
	
	
	
	
	double Cmo=wykresCmob*iw*Sb*lb/S/Ca;
	double Δxsak=wykresΔxsak*w*croot*croot/S/Ca;
	
	fprintf(Dane,"\nCmo:%lf\n(-deltaXsak):%lf\n\n",Cmo,Δxsak);


	double α[16]={-11.72438443,-9.237499412,-6.8317619,-4.446311263,-2,0.405737512,2.811475024,5.217212536,7.622950049,10.02868756,12.33299069,14.63729383,16.84016259,18.59672008,20.39385132,22.13012194};
	double Cz[16]={-0.875069554,-0.633018409,-0.431309121,-0.239685298,-0.017805081,0.183904207,0.385613494,0.587322782,0.78903207,0.990741358,1.142023324,1.293305289,1.394159933,1.273134361,1.172279717,1.04116868};
	double Cx[16]={0.078213494,0.061802956,0.051726594,0.044898083,0.041232257,0.043663931,0.049337502,0.058472969,0.071950333,0.089549593,0.105419658,0.12518954,0.142613804,0.121795344,0.108797649,0.09483408};

	double *Cmbu=(double*)malloc(16*sizeof(double));
	
	FILE *alfaCzCx=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL6\\alfaCzCx.xls","w");
	puts("alfa  \t\tCz:  \t\tCx:  \n");
	fprintf(alfaCzCx,"alfa-iw\tCz\tCx\n");
	for (int i=0;i<16;i++){
		α[i]-=stopnie(iw);
		printf("%.2d  \t\t%.2lf  \t\t %.4lf\n",int(α[i]),Cz[i],Cx[i]);
		fprintf(alfaCzCx,"%.2d  \t%.2lf  \t %.4lf\n",int(α[i]),Cz[i],Cx[i]);
		}	

	for (int i=0;i<16;i++){
		Cmbu[i]=Cmsa+Cz[i]*Xs-(Cx[i]-radiany(α[i])*Cz[i])*Zs+Cmo+Cz[i]*Δxsak;
		
	}
	
		FILE *filecmbu;
	filecmbu=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL6\\cmbu.xls","w");
	fprintf(filecmbu,"Cz\tCmbu\n");
for (int i=0;i<16;i++){fprintf(filecmbu,"%lf\t%lf\n",Cz[i],Cmbu[i]);}


	double dεpodα=2*a/3.14/Λ;
	//double a1=4.26; //Bardzo edytowalne
	//double a2=1.27*a1*sqrt(Ssh/Sh)*(1-0.2*(Ssh/Sh));
	
	//printf("deps/dafa:%lf\na1:%.2lf\na2:%.4lf\nSsh/Sh:%lf\n",dεpodα,a1,a2,(Ssh/Sh));hold();clrscr();

	double ckh=csh*0.2;


	double b1inf=stopnie(-0.0044);
	double b2inf=stopnie(-0.00622);
	double b3inf=stopnie(0);
	double ηsh=0.4;
	double a1inf=a10;

	//Mechanika Lotu

	csh=cah/3;
	Ssh=csh*bh;
	


//	hold();	clrscr();printf("csh:%lf\nssh:%lf\ncrooth:%lf,\nctip:%lf\n%lf",csh,Ssh,crooth,ctiph,Ssh/Sh);hold();	clrscr();

	


	double b1=b1inf*a1/a1inf;
	double b2=b2inf+((a1/a1inf)-1)*b1*ηsh;
	
	printf("b1:%lf\tb2:%lf\n",b1,b2);
	hold();
	

	double Skh=0;				//pole trymera
	double bkh=0;			//rozpietosc trymera
	
	double S0kh=0*2*2*95*skala*skala;		//pow trymera jakby na calej rozpietosci
	
	double Kkl=0*Skh*bkh/S0kh/bsh;

//	printf("S0kh:%lf\nbkh:%lf\nSkh:%lf\nKkl:%lf\nSkh/Sh:%lf\n",S0kh,bkh,Skh,Kkl,(Skh/Sh));hold();clrscr();

	double ηskh=0;
	

//	printf("b1:%lf\nb2:%lf\nb3:%lf\n",b1,b2,0);hold();clrscr();
	
	double przelozenie=-1.5;	//bardzo edytowalne
	double ld=0.5;				//dlugosc drazka
	double Ksd=(1/ld)*przelozenie;
	
	Czprzel=2*masa*g/gestosc(H)/V/V/S;
	double Kh=(Xh/Ca)*(Sh/S)*0.85;
	double Cmbu0=Cmsa+Czprzel*Xs-((0.041+0.05*Czprzel*Czprzel)-(Czprzel/a)*Czprzel)*Zs+Cmo+Czprzel*Δxsak;
	

	double Czh0=(a1*Czprzel/a)*Kh;
	double αzh=Cmbu0/Kh/a1-Czprzel*(1-dεpodα)/a;
	double δh0=Cmbu0/Kh/a2-(a1/a2)*((Czprzel/a)*(1-dεpodα)+αzh);
	double Cmh0=Kh*Czh0;
//	double δnk=(-b1/1*(Czprzel/a*(1-dεpodα)+αzh))*0;

	double Pdh0=0.5*gestosc(H)*Ssh*csh*Ksd*V*V*((b1*((Czprzel/a)*(1-dεpodα)+αzh)));
	
	fprintf(Dane,"\nro:%lf\nV:%lf\ncsh:%lf\nSsh:%lf\nde/dalfa:%lf\na:%lf\nKsd:%lf\nCzprzel:%lf\n\nKh:%lf\nalfazh:%lf\n",gestosc(H),V,csh,Ssh,dεpodα,a,Ksd,Czprzel,Kh,stopnie(αzh));hold();clrscr();
	fprintf(Dane,"\nCmbu0:%lf\nCmh0:%lf\ndeltah0:%lf\nPdh0:%lf\n",Cmbu0,Cmh0,δh0,Pdh0);

	
	double *δh=(double*)malloc(16*sizeof(double));
	double *Cmzh=(double*)malloc(16*sizeof(double));
	double *αh=(double*)malloc(16*sizeof(double));
	double *Pd=(double*)malloc(16*sizeof(double));
	double *Vp=(double*)malloc(16*sizeof(double));

	
	double V0=30;

	for(int i=0;i<16;i++){
		if(Cz[i]<0){
			Vp[i]=0;
			αh[i]=Cz[i]/a*(1-dεpodα)+αzh;
			δh[i]=Cmbu[i]/Kh/a2-(a1/a2)*((Cz[i]/a)*(1-dεpodα)+αzh);
			Cmzh[i]=b1*αh[i]+b2*δh[i];
			Pd[i]=0;
		}
		
		
		else {
			Vp[i]=sqrt(2*masa*g/gestosc(H)/S/Cz[i]);
			αh[i]=Cz[i]/a*(1-dεpodα)+αzh;
			δh[i]=Cmbu[i]/Kh/a2-(a1/a2)*((Cz[i]/a)*(1-dεpodα)+αzh);
			Cmzh[i]=b1*αh[i]+b2*δh[i];
			Pd[i]=-0.5*gestosc(H)*Ssh*csh*Ksd*Vp[i]*Vp[i]*Cmzh[i];
		}
	}
	
	
	puts("V\t\tPd\n");
	for(int i=0;i<16;i++){
		printf("%.2lf\t\t%lf\n",Vp[i],Pd[i]);
	
	}hold();clrscr();

	FILE *filecmzh;
	filecmzh=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL6\\cmzh.xls","w");

	
	puts("alfa\t  Cz\t  V\t alfah\t\t  deltah\t  Cmzh\n");
	fprintf(filecmzh,"alfa\tCz\tV\talfah\tdeltah\tCmzh\n");
	for(int i=0;i<16;i++){
		fprintf(filecmzh,"%.2lf\t  %.2lf\t %.2lf\t %.4lf\t  %.4lf\t  %.4lf\n",α[i],Cz[i],Vp[i],αh[i],δh[i],Cmzh[i]);	
		printf("%.2lf\t  %.2lf\t %.4lf\t %.4lf\t  %.4lf\t  %.4lf\n",α[i],Cz[i],Vp[i],αh[i],δh[i],Cmzh[i]); 
	}
	hold();clrscr();
	puts("\n");
	


	
	double μ0=2*masa/gestosc(H)/S/Xh;
	double A2=(1-(a2*b1/(a1*b2)));
	double A3=a/μ0;

	double kghN=1/(1+Sh*a1*0.85*(1-dεpodα)/(S*a));
	double kghNprim=kghN/A2;
	double kghM=1/(1+Sh*a1*0.85*((1-dεpodα)+2*A3)/(S*a));
	double kghMprim=kghM/A2;

	fprintf(Dane,"\nni0:%lf\nA2:%lf\nA3:%lf\n\nKghN:%lf\nKgh/':%lf\nKghM:%lf\nKghM/':%lf\n\n",μ0,A2,A3,kghN,kghNprim,kghM,kghMprim);

	
	double B1[16];
	double B2[16];
	double B3[16];
	double B4[16];

	for(int i=0;i<16;i++){
		B1[i]=(Xsca+Δxsak+Zs*(2*Cz[i]*(1/(3.14*Λ*0.8)-1/a)-(2*3.14/180))+Kh*(a1/a)*(1-dεpodα))*kghN;
		B2[i]=(Xsca+Δxsak+Zs*(2*Cz[i]*(1/(3.14*Λ*0.8)-1/a)-(2*3.14/180))+Kh*(a1/a)*(1-(a2*b1/(a1*b2)))*(1-dεpodα))*kghNprim;
		B3[i]=(Xsca+Δxsak+Zs*(2*Cz[i]*(1/(3.14*Λ*0.8)-1/a)-(2*3.14/180))+Kh*(a1/a)*(1-dεpodα+(a/μ0)))*kghM;
		B4[i]=(Xsca+Δxsak+Zs*(2*Cz[i]*(1/(3.14*Λ*0.8)-1/a)-(2*3.14/180))+Kh*(a1/a)*(1-(a2*b1/(a1*b2)))*(1-dεpodα+(a/μ0)))*kghMprim;
	}
	
		
	FILE *file2;
	file2=fopen("c:/Users/Herkes/Desktop/bipol/BIPOL6\\XNXM.xls","w");

	//puts("\tXN  \tXN'  \tXM  \tXM'");
	fprintf(file2,"V\tXN\tXN'\tXM\tXM'\n");
	for (int i=0;i<16;i++){
		//printf("%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\n",Vp[i],B1[i],B2[i],B3[i],B4[i]);
		fprintf(file2,"%.2lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\n",Vp[i],B1[i],B2[i],B3[i],B4[i]);
	}
	

	double xc1=0.18;
	double xc2=0.3;

zapasstatecznosci(xc1,Vp,B1,B2,B3,B4,size,masa,g,Ca,H,Sh,Xh,a2,b2,Ssh,przelozenie,csh);
zapasstatecznosci(xc2,Vp,B1,B2,B3,B4,size,masa,g,Ca,H,Sh,Xh,a2,b2,Ssh,przelozenie,csh);

	// Warunek 
	
	double Amin=93;
	double Amax=250;
	double nmax=6;
	double nmin=-3;


	double dfpodnmax=fabs(Amax/(nmax-1));
	double dfpodnmin=fabs(Amin/(nmax-1));
	printf("\nAmax:%lf\tAmin:%lf\n",dfpodnmax,dfpodnmin);

	
		
	hold();
	graphics(1000,1000);
	setbkcolor(WHITE);
	setcolor(BLACK);

	chart(α,Cz,16,"alfa","cz","wykres");
	

	hold();
	clrscr();

	printf("Chroot:%lf\nChtip:%lf\nCsh:%lf\nbfi:%lf\nbf:%lf\nλh:%lf\nb:%lf\n",crooth,ctiph,cf,bfi,bf,λh,bh);
	hold();



free(Cmbu);
free(Cmzh);
free(αh);
free(Pd);
free(δh);

fclose(filecmbu);
fclose(file2);

}
