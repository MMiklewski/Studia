

void UAV(){
	double b=3.35; //rozpietość 
	double S=1.17; //pow nośna
	double Λ=b*b/S;
	double ca=S/b;
	

	
	double g=9.81;
	double a∞=5.5;
	double masa=20; //przelotowa
	double Q=masa*g; //ciezar w przelocie

	int lp=100; //liczba przedzialow

	double dy=b/2/lp; //jednostka podzialowa

	double Cz_max=1.4; //maksymalny wsp sily nosnej

	double mpl=5.57; //masa plata
	double mfuel=1; //masa paliwa

	double Va=25; //predkosc dla a
	double ρ=gestosc(0.5); //gestosc na wysokosci obliczeniowej

	double CmSA=-0.05;
	double Δxai=0.4*ca;

	double n=1;

	double lh=1.1;
	double mh=0.257;
	double Czh=-0.07249;
	double Sh=0.2;

	
	double ywing=0.33*3.35/2;
	double massforceh=mh*g;
//	line();cout<<massforceh<<"\t-massforce";hold();clrscr();
	double forcelifth=ρ*Va*Va*Sh*0.5;
//	line();cout<<forcelifth<<"\t-nosnausterzenia";hold();clrscr();
	line();
	cout<<forcelifth-massforceh<<"\tdiffer";
//	hold();
	/////////////////////////////////////////////////////////////////
//	printf("Q:%.3lf\ndy:%.3lf\nCzmax:%.3lf\n",Q,dy,Cz_max);hold();clrscr();

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

	int flag=0;
	
	for (int i=2;i<(lp+1);i++){
		if(Yi[i]-ywing < 0.001){
//			flag=i;
			Yi[i]=Yi[i-1]+dy;
		}
		else Yi[i]=Yi[i-1]+dy;	
	}


	for (int i=2;i<(lp+1);i++){
		if(Yi[i]-ywing < 0.001 && i>flag){
			flag=i;
			
		}
	}

	Yi[lp+1]=b/2;
//	clrscr();	cout<<flag; line(); cout<< flag*dy; line(); cout<<ywing; line();hold();

	double Scheck=0;
	double Sbezcheck=0;
	clrscr();
	

	Ci[0]=ca;Si[0]=0;Cei[0]=(4*S/(4*atan(1.)*b));Ci_bezw[0]=1; Si_bezw[0]=0; CZ[0]=0.5*(1+Cei[0]/Ci[0]);Cei_bezw[0]=Cei[0]/Cei[0];CZ_max[0]=CZ[0]*Cz_max;
//	hold();
	for (int i=1;i<(lp+2);i++){
		Ci[i]=ca;
		Si[i]=Ci[i]*dy;
		Cei[i]=(4*S/(4*atan(1.)*b))*sqrt(1-(2*Yi[i]/b)*(2*Yi[i]/b));
		Ci_bezw[i]=Ci[i]/ca;
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
	*/
//	hold();
	

	FILE *UAV;
	UAV=fopen("c:/Users/Herkes/Desktop/UAV\\UAV.xls","w");
	

	fprintf(UAV,"nr\tYi\tCi\tSi\tCel\tCibez\tCelbez\tSibez\tCz\tCzmax\n");
	for (int i=0;i<(lp+2);i++){
		fprintf(UAV,"%d\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\t%.4lf\n",i,Yi[i],Ci[i],Si[i],Cei[i],Ci_bezw[i],Cei_bezw[i],Si_bezw[i],CZ[i],CZ_max[i]);
	}

	fclose(UAV);
//SCHRENK ENDS

	double *Pzi=(double*)malloc((lp+2)*sizeof(double));
	double *P_wing=(double*)malloc((lp+2)*sizeof(double));
	double *P_m=(double*)malloc((lp+2)*sizeof(double));
	double *Fti=(double*)malloc((lp+2)*sizeof(double));
	double *Tj=(double*)malloc((lp+2)*sizeof(double));
	double *Mg=(double*)malloc((lp+2)*sizeof(double));

	
	P_wing[lp+2]=0;
	P_m[lp+2]=0;Fti[lp+2]=0;Tj[lp+2]=0;
	Mg[lp+2]=0;


	for (int i=0;i<lp+2;i++){

		Pzi[i]=0;
		P_wing[i]=0;
		P_m[i]=0;
		Fti[i]=0;
	


	}

	double checkTnace=0;
	//line();hold();
	clrscr();
	double pow1=0;
	
	
		
	double wing=5.57;
	double podw=0;
	for (int i=1;i<lp+2;i++){
		
		Pzi[i]=masa*g*Si[i]/S*CZ[i];
		P_wing[i]=Si[i]/S*mpl*g;
		
		P_m[i]=P_wing[i];
		Fti[i]=(Pzi[i]-P_m[i])*n;
		Tj[i]=0;
		Mg[i]=0;
		
		pow1+=Si[i];
		
	}

	for(int i = 0; i<flag;i++){
		P_wing[i]+=(massforceh-forcelifth);

	}


	clrscr();
	line();cout<<wing<<"\t plat \t"<<mpl*g/2;space();cout<<mpl;line();
	Mg[lp+2]=0;
	Tj[lp+2]=0;

	

	for (int i=lp+1;i>-1;i--){
		
		Tj[i]=Tj[i+1]+Fti[i+1];
		
		Mg[i]=Mg[i+1]+Fti[i+1]*Yi[1]+Tj[i+1]*dy;
		
	}
	for (int i=0;i<lp+2;i++){
		checkTnace=checkTnace+Pzi[i];
	}
//	hold();
	clrscr();
	cout<<masa*g*n/2<<"\tTtotal\t"<<Tj[0];
	line();
//	hold();

	

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
	SCHRENK2=fopen("c:/Users/Herkes/Desktop/UAV\\rozkladobciazen.xls","w");

	fprintf(SCHRENK2,"Yi\tPzi\tPwing\tPm\tFt\tTi\tMg\n");
		
	for (int i=0;i<lp+2;i++){
		fprintf(SCHRENK2,"%lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\t%.3lf\n",Yi[i],Pzi[i],P_wing[i],P_m[i],Fti[i],Tj[i],Mg[i]);
	}

	fclose(SCHRENK2);

	//*****************************************************ROZKLAD OBCIAZEN IS OVER**************************************************************************




	double *ΔM_Pzi=(double*)malloc((lp+2)*sizeof(double));
	double *ΔMsi=(double*)malloc((lp+2)*sizeof(double));
//	double *ΔMs_ofi=(double*)malloc((lp+2)*sizeof(double));
//	double *Ms_nofuel=(double*)malloc((lp+2)*sizeof(double));


	Δxai=0.4;
	


	for (int i=0;i<lp+2;i++){
		ΔM_Pzi[i]=((-Pzi[i]*n*0.25*Ci[i])+(P_m[i]*n*Δxai*Ci[i]));
		ΔMsi[i]=0.5*ρ*Va*Va*CmSA*Si[i]/S+ΔM_Pzi[i];
/*
		ΔMs_ofi[i]=0.5*ρ*Va*Va*CmSA*Si[i]/S-n*(Pzi[i]*0.25*Ci[i]-(Δxai*Ci[i]*(P_m[i])));
	
		Ms_nofuel[i]=0;
	}

	for (int i=lp+1;i>-1;i--){
		Ms_nofuel[i]=Ms_nofuel[i+1]+ΔMs_ofi[i]; */
	} 

	for (int i=0;i<flag;i++){
		ΔMsi[i]+=(massforceh-forcelifth)*lh;
	}
/*	graphics(1000,1000);
	setbkcolor(WHITE);
	setcolor(BLACK);
	chart(Yi,ΔMsi,lp,"y[m]","Ms[Nm]","Monmentskrecajacy");
	hold();
	closegraph();
	*/
	FILE *SCHRENK3;
	SCHRENK3=fopen("c:/Users/Herkes/Desktop/UAV\\momentyskrecajace.xls","w");
	

	fprintf(SCHRENK3,"Y\tMPzi\tMs\n");
	for (int i=0;i<lp+2;i++)fprintf(SCHRENK3,"%.3lf\t%.3lf\t%.3lf\t%.6lf\n",Yi[i],ΔM_Pzi[i],ΔMsi[i]);
	fclose(SCHRENK3);

	

	/////////////////////////////////////////////////////////////////wydymala


	double d_zew=46.5;
	double d_wew=45.5;

	double I=Ig(d_zew)-Ig(d_wew);
//	clrscr();cout<<I;line();hold();
	double *SIGMA=(double*)malloc((lp+2)*sizeof(double));
	double *SKRET=(double*)malloc((lp+2)*sizeof(double));
	double *HUBER=(double*)malloc((lp+2)*sizeof(double));
	SIGMA[0]=0;
	
	
	for (int i=lp+1;i>-1;i--){
		SIGMA[i]=Mg[i]*d_zew/2/I;
		SKRET[i]=ΔMsi[i]*d_zew/I;
		HUBER[i]= pow(SIGMA[i]*SIGMA[i]+3*SKRET[i]*SKRET[i],0.5);
	}
