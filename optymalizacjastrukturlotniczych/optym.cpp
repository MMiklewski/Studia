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
#define PI() 4*atan(1.)




void OPTYM(int, int, int);


double FE(double B,double CG,double mbp,double rho,double vc,double vmin,double czmax, double cx0){
	
double	S=B*CG;
double	LAMBADA=B*B/S;
double	E=4.61*(1-0.045*pow(LAMBADA,0.68))-3.1;
double	MP=4.936*S*pow(LAMBADA,0.3);
double	M=mbp+MP;
double	CZ=2*M*9.81/rho/S/vc/vc;
double	CZMIN=2*M*9.81/rho/S/vmin/vmin;
double	K=((1/(czmax-CZ))-(1/(czmax-CZMIN)))*((1/(czmax-CZ))-(1/(czmax-CZMIN)));
double	D=rho*vc*vc*0.5*S*(cx0+CZ*CZ/3.14/LAMBADA/E);
double	F=D+K;

return F;

	}

double DE(double B,double CG,double mbp,double rho,double vc,double vmin,double czmax, double cx0){
	
double	S=B*CG;
double	LAMBADA=B*B/S;
double	E=4.61*(1-0.045*pow(LAMBADA,0.68))-3.1;
double	MP=4.936*S*pow(LAMBADA,0.3);
double	M=mbp+MP;
double	CZ=2*M*9.81/rho/S/vc/vc;
double	D=rho*vc*vc*0.5*S*(cx0+CZ*CZ/3.14/LAMBADA/E);


return D;

	}
double CZVMIN(double B,double CG,double mbp,double rho,double vc,double vmin,double czmax, double cx0){
	
double	S=B*CG;
double	LAMBADA=B*B/S;
double	E=4.61*(1-0.045*pow(LAMBADA,0.68))-3.1;
double	MP=4.936*S*pow(LAMBADA,0.3);
double	M=mbp+MP;
double	CZ=2*M*9.81/rho/S/vc/vc;
double	CZMIN=2*M*9.81/rho/S/vmin/vmin;


return CZMIN;

	}

void DRRIPK2();



void main()
{
	




OPTYM(6,6,-6);
	

puts("Done\n");
system("pause");

}







void OPTYM(int lN, int ldx, int lalfa){
	 

	double s=25.5;
	double cg=1.645;
	double b=15.5;
	double rho=gestosc(0);
	double lambada=b*b/s;
	double e=4.61*(1-0.045*pow(lambada,0.68))-3.1;
	double vc=140;
	double vmin=40;
	double cx0=0.02303;
	double mc=1800;
	double mpl=4.936*s*pow(lambada,0.3);
	double mbp=mc-mpl;
	double Czvmax=2*mc*9.81/rho/s/vc/vc;
	double czvmin=2*mc*9.81/rho/s/vmin/vmin;
	double czmax=1.4;

	int iter=2;
long	double dx;
long	double alfa;
	int N=100;


long double *B=(long double*)malloc((iter)*sizeof(long double));
long double *CG=(long double*)malloc((iter)*sizeof(long double));
long double *S=(long double*)malloc((iter)*sizeof(long double));
double *LAMBADA=(double*)malloc((iter)*sizeof(double));
long double *E=(long double*)malloc((iter)*sizeof(long double));
long double *CZ=(long double*)malloc((iter)*sizeof(long double));
long double *MP=(long double*)malloc((iter)*sizeof(long double));
long double *CZMIN=(long double*)malloc((iter)*sizeof(long double));
long double *M=(long double*)malloc((iter)*sizeof(long double));
long double *K=(long double*)malloc((iter)*sizeof(long double));
long double *D=(long double*)malloc((iter)*sizeof(long double));
long double *F=(long double*)malloc((iter)*sizeof(long double));
	
long double *B1=(long double*)malloc((iter)*sizeof(long double));
long double *B2=(long double*)malloc((iter)*sizeof(long double));
		
long double *CG3=(long double*)malloc((iter)*sizeof(long double));
long double *CG4=(long double*)malloc((iter)*sizeof(long double));
	
long double GRAD1;
long double GRAD2;
	
	

	FILE *POTYM;
	POTYM=fopen("C:/Users/mmikl/Desktop\\POTYM.xls","w");
	fclose(POTYM);
	POTYM=fopen("C:/Users/mmikl/Desktop\\POTYM.xls","a");

	B[0]=b;
	CG[0]=cg;
	S[0]=B[0]*CG[0];
	LAMBADA[0]=B[0]*B[0]/S[0];
	E[0]=4.61*(1-0.045*pow(LAMBADA[0],0.68))-3.1;
	MP[0]=4.936*S[0]*pow(LAMBADA[0],0.3);
	M[0]=mbp+MP[0];
	CZ[0]=2*M[0]*9.81/rho/S[0]/vc/vc;
	CZMIN[0]=2*M[0]*9.81/rho/S[0]/vmin/vmin;
	K[0]=((1/(czmax-CZ[0]))-(1/(czmax-CZMIN[0])));
 	D[0]=rho*vc*vc*0.5*S[0]*(cx0+CZ[0]*CZ[0]/3.14/LAMBADA[0]/E[0]);
	K[0]=((1/(czmax-CZ[0]))-(1/(czmax-CZMIN[0])));
	F[0]=D[0]+K[0];

	

//	fprintf(POTYM,"B[0]\tCG[0]\tS[0]\tLAMBADA[0]\tE[0]\tMP[0]\tM[0]\tCZ[0]\tCZMIN[0]\tK[0]\tD[0]\tF[0]\n%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",B[0],CG[0],S[0],LAMBADA[0],E[0],MP[0],M[0],CZ[0],CZMIN[0],K[0],D[0],F[0]);
	
	

	fprintf(POTYM,"iteracje\tB\tCG\tB1\tB2\tCG3\tCG4\tGRAD1\tGRAD2\tS\tF\tCzvmin\tD\n");
	
	int i=1;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*
	int lN=6;
	int ldx=-6;
	int lalfa=-6;*/

	N=(int)(pow(10.,(double)lN));
	dx=(pow(10.,(double)(ldx)));
	alfa=dx=(pow(10.,(double)(lalfa)));



for(int j=0;j<N;j++){


	B1[i]=B[i-1]+dx;
	B2[i]=B[i-1]-dx;

	CG3[i]=CG[i-1]+dx;
	CG4[i]=CG[i-1]-dx;

	GRAD1=(FE(B1[i],CG[i-1],mbp,rho,vc,vmin,czmax,cx0)-FE(B2[i],CG[i-1],mbp,rho,vc,vmin,czmax,cx0))/2/dx;
	GRAD2=(FE(B[i-1],CG3[i],mbp,rho,vc,vmin,czmax,cx0)-FE(B[i-1],CG4[i],mbp,rho,vc,vmin,czmax,cx0))/2/dx;
	
	B[i]=B[i-1]-alfa*GRAD1;
	CG[i]=CG[i-1]-alfa*GRAD2;

	B[i-1]=B[i];
	CG[i-1]=CG[i];

//	cout<<"GRAD1\t"<<GRAD1<<"\nGRAD2\t"<<GRAD2<<"\nB\t"<<B[i]<<"\ncg\t"<<CG[i];hold();clrscr();
	//	printf("%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",B[i],CG[i],B1[i],B2[i],CG3[i],CG4[i],GRAD1,GRAD2,CG[i]*B[i],FE(B[i],CG[i],mbp,rho,vc,vmin,czmax,cx0),CZVMIN(B[i],CG[i],mbp,rho,vc,vmin,czmax,cx0),DE(B[i],CG[i],mbp,rho,vc,vmin,czmax,cx0));
	
	//cout<<".";
	if(j%1000==0)cout<<"B\t"<<B[i]<<"\tcg\t"<<CG[i]<<"\n";
	if(j%1000==0)fprintf(POTYM,"%d\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\t%lf\n",j,B[i],CG[i],B1[i],B2[i],CG3[i],CG4[i],GRAD1,GRAD2,CG[i]*B[i],FE(B[i],CG[i],mbp,rho,vc,vmin,czmax,cx0),CZVMIN(B[i],CG[i],mbp,rho,vc,vmin,czmax,cx0),DE(B[i],CG[i],mbp,rho,vc,vmin,czmax,cx0));
	if(GRAD1<0.000001 && GRAD2<0.000001)break;
	
}
	

fclose(POTYM);

free(B);
free(CG);
free(S);
free(LAMBADA);
free(E);
free(MP);
free(M);
free(CZ);
free(CZMIN);
free(K);
free(D);
free(F);

free(B1);
free(B2);

free(CG3);
free(CG4);



}











