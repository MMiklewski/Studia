using System;
using System.Drawing;
using System.Windows.Forms;



namespace Objectmoving
{
        

    
    public partial class FormView : Form
    {
        enum Position
        {
                Left,Right,Up,Down
        }

         double time;
         double multip=0.01;
         double Distance=25;

     
       
        Pen black = new Pen(Brushes.Black);
        Pen red = new Pen(Color.FromArgb(255, 128, 128));
        Pen lime = new Pen(Brushes.Lime);
        Pen cyan = new Pen(Brushes.Cyan);
        Pen yellow = new Pen(Brushes.Yellow);
        double Radius = 6.371;
       
      public  double xangle=90;
      public  double yangle;
      public  double zangle;

      public double rp;
      public double ra;

      
      public static double aaaa=0;
      public static double bbbb=0;
      public static double cccc=0;
      public static double dddd=0;
      public static double eeee = 0;
      public int keypressedV = 0;
      public int keypressedother = 0;

      public static double DV1 = 0;
      public static double DV2 = 0;

      public bool cliked = false;
     
    
        public int xV;
        public int yV;

        public double Vr = 0;
      
        public double rxxx = 0;
        public double Vtotal = 0;
        
       
        
        double arx, ary;
        public double anomally = 0;
        public double hx; //aaaa * Math.Cos(0) * 1000000;
        public double hy; //aaaa * Math.Sin(0) * 1000000;
        
        public static double MM = 5.972 * Math.Pow(10, 24);
        public static double GG = 6.66748 * Math.Pow(10, (-11));
        public static double MG = GG * MM;
        public static double Vtan = 0; //mps
       // public double Vtann = Vtan;
       public double Vtx, Vty;
        double Vtanold = -1;
        double aaaaold = -1;
        double bbbbold = -1;
        double ccccold = -1;
        double ddddold = -1;

       
       public double rrrr = aaaa-0.00000001;
       public double[] poss = new double[3] ;
   

       public double nx ;
       public double ny ;


       
        
        public FormView()
        {


            InitializeComponent();
            
         
         //   DispatcherTimer tmrMoving = new DispatcherTimer();
          //  tmrMoving.Tick += new System.EventHandler(tmrMoving);
         //   tmrMoving.Interval = new System.TimeSpan(0, 0, 1);
        //    tmrMoving.Start();
            
            this.MouseWheel += new MouseEventHandler(sizee_MouseWheel);
       
            this.DoubleBuffered = true;

            textBox5.Text = xangle.ToString();
            textBox6.Text = yangle.ToString();
            textBox7.Text = zangle.ToString();
            
            textBox1.Text = aaaa.ToString();
            textBox2.Text = bbbb.ToString();
            textBox3.Text = cccc.ToString();
            textBox4.Text = dddd.ToString();
           
            textBox8.Text = Vtan.ToString();
            textBox9.Text = DV1.ToString();
            textBox10.Text = DV2.ToString();
           
            apogee_value.Text = Math.Floor(rp).ToString();
            pedegriee_value.Text = Math.Floor(ra).ToString();

  


         //   Distance = this.ClientSize.Width / Math.Tan(DtR(45)) / 2 / 1000;

        }

        private void sizee_MouseWheel(object sender, MouseEventArgs e)
        {

            if (Distance < 1) Distance = 1;
            
             if (Distance < 25) Distance -= e.Delta / 100;
            else Distance -= e.Delta / 10;
   
            
            


        }





        private void SQUARE(object sender, PaintEventArgs e)
        {
            if (cliked == true) button1.ForeColor = Color.Green;
            else
            {
                button1.ForeColor = Color.Black;
                
            }
           
            //     Console.WriteLine(hScrollBar1.Value.ToString());
            //   Console.WriteLine(hScrollBar2.Value.ToString());




            black.Width = 4.0F;
            //   black.LineJoin = System.Drawing.Drawing2D.LineJoin.Round;

            double cw = (this.ClientSize.Width - 264) / 2;
            double ch = (this.ClientSize.Height / 2);




            double[,] projection = new double[,] { 
                                                { 1, 0, 0 }, 
                                                { 0, 1, 0 } 
                                                };


            xangle = DtR(xangle);
            yangle = DtR(yangle);
            zangle = DtR(zangle);
            double[,] rotate = new double[,] {
                {Math.Cos(zangle)*Math.Cos(yangle),                                                     Math.Sin(zangle)*Math.Cos(yangle),                                                    -Math.Sin(yangle)},
                {Math.Cos(zangle)*Math.Sin(yangle)*Math.Sin(xangle)-Math.Cos(xangle)*Math.Sin(zangle),Math.Sin(xangle)*Math.Sin(yangle)*Math.Sin(zangle)+Math.Cos(xangle)*Math.Cos(zangle),Math.Sin(xangle)*Math.Cos(yangle)},
                {Math.Cos(xangle)*Math.Sin(yangle)*Math.Cos(zangle)+Math.Sin(xangle)*Math.Sin(zangle),Math.Cos(xangle)*Math.Sin(yangle)*Math.Sin(zangle)-Math.Sin(xangle)*Math.Cos(zangle),Math.Cos(xangle)*Math.Cos(yangle)}

            };

            xangle = RtD(xangle);
            yangle = RtD(yangle);
            zangle = RtD(zangle);

            double scale;
            scale = 100 / (double)Distance;

            double[,] Scale = new double[,] {{scale, 0, 0},
                                        {0,scale,0},
                                        {0,0,scale}};
            double[,] translate = new double[,] {{cw,0,0},
                                                 {ch,0,0},
                                                 {0,0,0}};



            //Rysowanie 6scianu działa


            /*
            PVector v= new PVector(100,75,50);


       

      //    

            double[,] point = VECtoMAT(v);
            double[,] projected = matmul(projection, point);
       

            projected = matmul(projection, v);

            PVector[] pointts = new PVector[8];
            pointts[0] = new PVector(-1,     -1,    -1);
            pointts[1] = new PVector(1,      -1,    -1);
            pointts[2] = new PVector(1,       1,    -1);
            pointts[3] = new PVector(-1,      1,    -1);
            pointts[4] = new PVector(-1,      -1,     1);
            pointts[5] = new PVector(1,       -1,    1);
            pointts[6] = new PVector(1,       1,     1);
            pointts[7] = new PVector(-1,      1,     1);

            




            PVector[] projected2d= new PVector[pointts.GetLength(0)];
            PVector[] scaled = new PVector[pointts.GetLength(0)];
            PVector[] rotatedV = new PVector[pointts.GetLength(0)];
            PVector[] tranlatedV = new PVector[pointts.GetLength(0)];

  
            PVector[] toconnect= new PVector[8];

            int index=0;


            for (int i = 0; i < pointts.GetLength(0); i++)
            {
                scaled[i] = MATtoVEC(matmul(Scale, pointts[i]));
                rotatedV[i] = MATtoVEC(matmul(rotatex, scaled[i]));
                rotatedV[i] = MATtoVEC(matmul(rotatez, rotatedV[i]));
                rotatedV[i] = MATtoVEC(matmul(rotatey, rotatedV[i]));
                projected2d[i] = MATtoVEC(matmul(projection, rotatedV[i]));
                tranlatedV[i] = matsumV(MATtoVEC(translate), projected2d[i]);

                toconnect[index] = tranlatedV[i];
                index++;
          //      printpoint(sender, e, tranlatedV[i]);

            }
 //           e.Graphics.DrawLines(black, PointCreator(tranlatedV));

      //      for (int i = 0; i < 4; i++) { connect(sender, e, i, (i + 1) % 4, toconnect,black); connect(sender, e, i + 4, ((i + 1) % 4) + 4, toconnect,black); connect(sender, e, i, i + 4, toconnect,black); }
            
           
            */

            //Rysujemy ziemie


            int depoints = EarthGenerator(0).GetLength(0);
            int depoints2 = EarthGenerator(0).GetLength(0);
            int dHpoints = EarthGenerator(0).GetLength(0);
            int dHpoints2 = EarthGenerator(0).GetLength(0);

            double[,] Epoints = new double[depoints, 3];
            double[,] Epoints2 = new double[depoints, 3];
            double[,] Hpoints = new double[depoints, 3];
            double[,] Hpoints2 = new double[depoints, 3];


            PVector[] VEpoints = new PVector[depoints];
            PVector[] VEpoints2 = new PVector[depoints];
            PVector[] VHpoints = new PVector[dHpoints];
            PVector[] VHpoints2 = new PVector[dHpoints2];





            /*     for (int i = 0; i < Epoints.GetLength(0); i++)  
                 {
               
                 VEpoints[i] = new PVector(Epoints[i, 0], Epoints[i, 1], Epoints[i, 2]);//Punkty trafiają do macierzy wektorów.
            
                     Erotatedz[i] = MATtoVEC(matmul(rotatey, VEpoints[i]));
             //        Erotatedz[i] = MATtoVEC(matmul(rotatez, Erotatedz[i]));
             //        Erotatedz[i] = MATtoVEC(matmul(rotatex, Erotatedz[i]));
                     Eprojected2d[i] = matsumV(MATtoVEC(translate), Erotatedz[i]);
            

                 }
            
     */
            double omegaeeeeeee = 7.292115 * 0.00001;
            Epoints2 = EarthGenerator2(-RtD((time * omegaeeeeeee)));
            Epoints2 = matmul(Epoints2, Scale);
            for (int phi = 0; phi < 180; phi += 30)
            {
                Epoints = EarthGenerator(phi - (int)RtD((time * omegaeeeeeee)));
                
                Hpoints = Horizontals(phi);
                Hpoints2 = Horizontals(-phi);


                Epoints = matmul(Epoints, Scale);
           
                Hpoints = matmul(Hpoints, Scale);
                Hpoints2 = matmul(Hpoints2, Scale);


                for (int i = 0; i < depoints; i++)
                {


                    VEpoints[i] = new PVector(Epoints[i, 0], Epoints[i, 1], Epoints[i, 2]);//Punkty trafiają do macierzy wektorów.
                    VEpoints2[i] = new PVector(Epoints2[i, 0], Epoints2[i, 1], Epoints2[i, 2]);
                    VHpoints[i] = new PVector(Hpoints[i, 0], Hpoints[i, 1], Hpoints[i, 2]);
                    VHpoints2[i] = new PVector(Hpoints2[i, 0], Hpoints2[i, 1], Hpoints2[i, 2]);


                    VEpoints[i] = MATtoVEC(matmul(rotate, VEpoints[i]));
                    VEpoints2[i] = MATtoVEC(matmul(rotate, VEpoints2[i]));
                    VHpoints[i] = MATtoVEC(matmul(rotate, VHpoints[i]));
                    VHpoints2[i] = MATtoVEC(matmul(rotate, VHpoints2[i]));

                    //             VEpoints[i] = perspective(VEpoints[i]);
                    //           VHpoints[i] = perspective(VEpoints[i]);
                    //            VHpoints2[i] = perspective(VEpoints[i]);


                    VEpoints[i] = matsumV(MATtoVEC(translate), VEpoints[i]);
                    VEpoints2[i] = matsumV(MATtoVEC(translate), VEpoints2[i]);
                    VHpoints[i] = matsumV(MATtoVEC(translate), VHpoints[i]);
                    VHpoints2[i] = matsumV(MATtoVEC(translate), VHpoints2[i]);

                    /*         
                             VEpoints[i] = MATtoVEC(matmul(rotatey, VEpoints[i]));
                             VHpoints[i] = MATtoVEC(matmul(rotatey, VHpoints[i]));
                             VHpoints2[i] = MATtoVEC(matmul(rotatey, VHpoints2[i]));

                             VEpoints[i] = MATtoVEC(matmul(rotatex, VEpoints[i]));
                             VHpoints[i] = MATtoVEC(matmul(rotatex, VHpoints[i]));
                             VHpoints2[i] = MATtoVEC(matmul(rotatex, VHpoints2[i]));

                             VEpoints[i] = MATtoVEC(matmul(rotatez, VEpoints[i]));
                             VHpoints[i] = MATtoVEC(matmul(rotatez, VHpoints[i]));
                             VHpoints2[i] = MATtoVEC(matmul(rotatez, VHpoints2[i]));
                      */





                }
                for (int i = 0; i < depoints - 1; i++) connect(sender, e, i, i + 1, VEpoints, black); //e.Graphics.DrawLines(black, PointCreator(VEpoints)); // 
                for (int i = 0; i < depoints2 - 1; i++) connect(sender, e, i, i + 1, VEpoints2, red); //e.Graphics.DrawLines(black, PointCreator(VEpoints)); // 
                for (int i = 0; i < dHpoints - 1; i++) connect(sender, e, i, i + 1, VHpoints, black);//e.Graphics.DrawLines(black, PointCreator(VHpoints));// 
                for (int i = 0; i < dHpoints2 - 1; i++) connect(sender, e, i, i + 1, VHpoints2, black);//e.Graphics.DrawLines(black, PointCreator(VHpoints2));// 

            }


            double orbitradius = aaaa;
            double eccentricity = bbbb;
            double inclination = cccc;
            double ascnode = dddd;

            
 

            if (eccentricity < 0.000) eccentricity = 0;
            if (eccentricity < 1)
            {
                int dorbits = Orbit(0, 1, 1, 1).GetLength(0);
                double[,] Orbits = new double[dorbits, 3];
                PVector[] VOrbits = new PVector[dorbits];
                double Enum;

                Enum = ((double)time / (double)dorbits - Math.Floor((double)time / (double)dorbits)) * (double)dorbits;
                Orbits = Orbit(eccentricity, orbitradius, ascnode, inclination);
                Orbits = matmul(Orbits, Scale);

                for (int i = 0; i < dorbits; i++)
                {
                    VOrbits[i] = new PVector(Orbits[i, 0], Orbits[i, 1], Orbits[i, 2]);
                    VOrbits[i] = MATtoVEC(matmul(rotatex(inclination), VOrbits[i]));
                    VOrbits[i] = MATtoVEC(matmul(rotatey(ascnode), VOrbits[i]));
                    VOrbits[i] = MATtoVEC(matmul(rotate, VOrbits[i]));

                    VOrbits[i] = matsumV(MATtoVEC(translate), VOrbits[i]);

                }
                for (int i = 0; i < dorbits - 1; i++) connect(sender, e, i, i + 1, VOrbits, black);
                connect(sender, e, 0, dorbits / 2, VOrbits, red);
            //    printpoint(sender, e, VOrbits[(int)Enum]);
                double hhhhh = Math.Sqrt(orbitradius*1000000 * MG * (1 + eccentricity));
                ra = hhhhh * hhhhh * (1 / (1 - eccentricity)) / MG / 1000000;
                rp = hhhhh * hhhhh * (1 / (1 + eccentricity)) / MG /1000000;
                double polos = (ra * 1000000 + rp * 1000000) / 2 ;
                double okres = 2*Math.PI*Math.Sqrt(polos*polos*polos/MG);
                polos /= 1000000;
                apogee_value.Text = (Math.Floor(ra)).ToString();
                pedegriee_value.Text = (Math.Floor(rp)).ToString();
                PolosValue.Text = polos.ToString();
                okres_value.Text = Math.Floor(okres).ToString();

            }
            else
            {
                int dorbits = Orbit(eccentricity, 1, 1, 1).GetLength(0);
                double[,] Orbits = new double[dorbits, 3];
                PVector[] VOrbits = new PVector[dorbits];
                double Enum;

                Enum = ((double)time / (double)dorbits - Math.Floor((double)time / (double)dorbits)) * (double)dorbits;
                Orbits = Orbit(eccentricity, orbitradius, ascnode, inclination);
                Orbits = matmul(Orbits, Scale);

                for (int i = 0; i < dorbits; i++)
                {
                    VOrbits[i] = new PVector(Orbits[i, 0], Orbits[i, 1], Orbits[i, 2]);
                    VOrbits[i] = MATtoVEC(matmul(rotatex(inclination), VOrbits[i]));
                    VOrbits[i] = MATtoVEC(matmul(rotatey(ascnode), VOrbits[i]));
                    VOrbits[i] = MATtoVEC(matmul(rotate, VOrbits[i]));
                    VOrbits[i] = matsumV(MATtoVEC(translate), VOrbits[i]);

                }
                for (int i = 0; i < dorbits - 1; i++) connect(sender, e, i, i + 1, VOrbits, black);
                e.Graphics.DrawLine(red, (float)cw, (float)ch, (float)VOrbits[dorbits / 2].x, (float)VOrbits[dorbits / 2].y);


                if (time < VOrbits.GetLength(0) - 2) ; //printpoint(sender, e, VOrbits[(int)Enum]);
                else
                {

                    //      printpoint(sender, e, VOrbits[0]);
                }
            }
      

            //osie
            
                PVector center = new PVector(cw, ch);
                printpoint(sender, e, center);


                PVector[] xasis = new PVector[6];
                xasis[0] = new PVector(cw / 4, 0, 0);
                xasis[1] = new PVector(0, 0, 0);
                xasis[2] = new PVector(cw / 4 - 20, 20, 0);
                xasis[3] = new PVector(cw / 4 - 20, -20, 0);
                xasis[4] = new PVector(cw / 4 - 20, 0, 20);
                xasis[5] = new PVector(cw / 4 - 20, 0, -20);

                for (int i = 0; i < 6; i++)
                {
                    xasis[i] = MATtoVEC(matmul(rotate, xasis[i]));
                    xasis[i] = matsumV(MATtoVEC(translate), xasis[i]);
                }

                for (int i = 0; i < 6; i++) connect(sender, e, 0, i, xasis, red);

                PVector[] yasis = new PVector[6];
                yasis[0] = new PVector(0, -cw / 4, 0);
                yasis[1] = new PVector(0, 0, 0);
                yasis[2] = new PVector(20, -cw / 4 + 20, 0);
                yasis[3] = new PVector(-20, -cw / 4 + 20, 0);
                yasis[4] = new PVector(0, -cw / 4 + 20, 20);
                yasis[5] = new PVector(0, -cw / 4 + 20, -20);

                for (int i = 0; i < 6; i++)
                {
                    yasis[i] = MATtoVEC(matmul(rotate, yasis[i]));
                    yasis[i] = matsumV(MATtoVEC(translate), yasis[i]);
                }
                for (int i = 0; i < 6; i++) connect(sender, e, 0, i, yasis, lime);

                PVector[] zasis = new PVector[6];
                zasis[0] = new PVector(0, 0, cw / 4);
                zasis[1] = new PVector(0, 0, 0);
                zasis[2] = new PVector(20, 0, cw / 4 - 20);
                zasis[3] = new PVector(-20, 0, cw / 4 - 20);
                zasis[4] = new PVector(0, 20, cw / 4 - 20);
                zasis[5] = new PVector(0, -20, cw / 4 - 20);

                for (int i = 0; i < 6; i++)
                {
                    zasis[i] = MATtoVEC(matmul(rotate, zasis[i]));
                    zasis[i] = matsumV(MATtoVEC(translate), zasis[i]);
                }
                for (int i = 0; i < 6; i++) connect(sender, e, 0, i, zasis, cyan);
            





            //PRędkości//////////////////////////////////////////////////////////////////
         
   
          //      double hx, hy, hz;
                double rx, ry, rz;

          
            double g = 9.81;
            double height = rrrr * 1000000;
          //  hx = height;// *Math.Cos(anomally);
          //  hy =0;// height * Math.Sin(anomally);
            
         //   Vtan = Math.Sqrt(MG / height);
            double sma = aaaa;
            double[,] velocity = new double[1, 3];
            double GM = 398600;//3.986324056*Math.Pow(10, 14);
            double h=0;
            double dt = 0.1;
            double flagggg=dt;
            double flagggg2=dt;
            double dV = eeee;
          
       

            if (time <= 0.1) { hx = 0; hy = 0; Vtx = 0; Vty = 0; }

            else if (Vtan!=Vtanold){
                if (keypressedother == 1)
                {
                    hx = aaaa * Math.Cos(0) * 1000000;
                    hy = aaaa * Math.Sin(0) * 1000000;
                    Vtx = 0;
                    Vty = Vtan;
                    Vtanold = Vtan;
                }
               


                if (keypressedV == 1)
                {
                    Vtan += dV;
                    Vty += dV;
                    Vtx = 0;
                    hx = aaaa * 1000000;
                    hy = 0;
                    Vtanold = Vtan;
                    eeee = 0;
                    dV = 0;
                   
                }
            }
            else {
                if (cliked == true)
                {
                    if (Math.Floor(Math.Abs(anomally)) < 1 && DV2!=0)
                    {

                        Vty += DV1 * nx;
                        Vtx += -DV1 * ny;
                        hx = hx;
                        hy = hy;
                     //   Vtanold = Vtan;
                        DV1 = 0;
                        textBox9.Text = "0";
                        textBox9.ForeColor = Color.Black;
                        
                    }
                    if (Math.Floor(Math.Abs(anomally - 180)) < 1 && DV1 == 0)
                    {
                       // Vtan += DV2;
                        Vty += DV2 * nx;
                        Vtx += -DV2*ny;
                        hx = hx;
                        hy = hy;
                      //  Vtanold = Vtan;
                        DV2 = 0;
                        textBox10.Text = "0";
                        textBox10.ForeColor = Color.Black;
                    }
                }
                if (keypressedother == 1)
                {
                    hx = hx; hy = hy; Vtx = Vtx; Vty = Vty;
                }
                if (keypressedV == 1)
                {
                    hx = hx; hy = hy; Vtx += -dV*ny; Vty += dV*nx;
                    eeee = 0;
                    dV = 0;
                }
            }
            if (cliked == true && DV1 == 0 && DV2 == 0)
            {
                aaaa = Math.Sqrt(hx * hx + hy * hy) / 1000000;
                aaaaold = aaaa;
            }
            if ((aaaa != aaaaold || bbbb!=bbbbold || cccc!=ccccold || dddd!=ddddold) && cliked==false)
            {
                //textBox1.ForeColor = Color.Black;
                if (keypressedother == 1)
                {
                  
                    anomally = 0;
                    Vtan = Math.Sqrt(MG * (1 + eccentricity) / (aaaa * 1000000));
                    hx = aaaa * Math.Cos(anomally) * 1000000;
                    hy = aaaa * Math.Sin(anomally) * 1000000;
                    Vtx = 0;
                    Vty = Vtan;
                   // Vtan = Math.Sqrt(aaaa * 1000000 * MG) / (aaaa * 1000000 * (1 + eccentricity));
                  
                    aaaaold = aaaa;
                    bbbbold = bbbb;
                    ccccold = cccc;
                    ddddold = dddd;
                   
                }
            }
          



            Console.Write("{0:F} {1:F} {2:F}\n", cliked, DV1, DV2);

          
            

     


            
            //Vtx = 0;// Vtan * Math.Sin(anomally);
           // Vty = Vtan;// *Math.Cos(anomally);
        //    Vtan = 0;
           // nx = (hxx / Math.Abs(Math.Sqrt(hxx * hxx + hyy * hyy))); //cosinus anomalii prawawdz
         //   ny = (hyy / Math.Abs(Math.Sqrt(hxx * hxx + hyy * hyy))); // sinus anomallii prawdz

         //   Vty = Vtan * ny;
         //   Vtx = Vtan * nx;
           // if (bbbb < 1){
                           
                /* //Freefall
                    while (flagggg < multip)
                    {
                        int n = (int)(rrrr / Math.Abs(rrrr));
                     //   int nx = (int)(Rrx / Math.Abs(Rrx));
                     //   int ny = (int)(Rry / Math.Abs(Rry));
                     //   int nz = (int)(Rrz/ Math.Abs(Rrz));
                        if (Math.Abs(rrrr) > Radius)
                        {
                        
                          //  anomally = Vtan / Math.Sqrt(rx * rx + ry * ry + rz * rz) * dt;
                        //    anomally = Math.Atan(Vr /Vtan);

                            ar = -MG / height / height * n;
                            height += ar * dt * dt / 2 + Vr * dt;
                            Vr += ar * dt;
                        
                        }


                        else
                        {
                            ar = -g * rrrr / Radius;
                            height += ar * dt * dt / 2 + Vr * dt;
                            Vr += ar * dt;
                      
         
                        
                        }
                   
                        flagggg += dt;
                        rrrr = height / 1000000;
                       // xtan = xtan / 1000000;
                        //   rrrr = Math.Sqrt(xtan*xtan+height*height) / 1000000;
                    }
                    */
            if (bbbb > 0.9999999999999)
            {
                if (Math.Sqrt((hx * hx + hy * hy)) > 50 * aaaa * 1000000)
                {
                    hy *= -1;
                    Vtx *= -1;            
                }
                
            }
                while (flagggg2 < multip)
                {
                    double pierw = Math.Sqrt(hx * hx + hy * hy);

                    nx = (hx / pierw); //cosinus anomalii prawawdz
                    ny = (hy / pierw); // sinus anomallii prawdz

                    arx = -MG / pierw / pierw * nx; //f(x)
                    ary = -MG / pierw / pierw * ny; // f(x)

                    hx += arx * dt * dt + Vtx * dt;
                    hy += ary * dt * dt + Vty * dt;
                    
                    Vtx += arx * dt;
                    Vty += ary * dt;

                    
                    flagggg2 += dt;
                    if(Vtx<0)anomally = RtD(Math.Acos(hx / (pierw)));
                    else if(Vtx>=0)anomally = 360 - RtD(Math.Acos(hx/pierw));
                }



          
                  // Console.WriteLine(r.ToString();

                PVector position = new PVector();

                rx = hx / 1000000;//rrrr * Math.Cos(anomally) +xtan * Math.Sin(anomally) / 1000000;
                ry = hy / 1000000;//rrrr * Math.Sin(anomally) + xtan * Math.Cos(anomally)/1000000 ;
                rz = 0;
                if (Math.Sqrt(rx * rx + ry * ry) <= 6.376) ;

                position.x = rx;//+= Force * dtime * dtime * Math.Cos(DtR(anomally)) ;
                position.z = ry;//+= Force * dtime * dtime * Math.Sin(DtR(anomally));
                position.y += 0;

             //   anomally = Math.Atan(ry / rx);
               // anomally = Vtan / Math.Sqrt(rx * rx + ry * ry + rz * rz) * dt;

                double[,] pos = new double[1, 3];
              
                pos[0, 0] =position.x;
                pos[0, 1] =position.y;
                pos[0, 2] =position.z;



                pos = matmul(pos, Scale);
                position.x = pos[0, 0];
                position.y = pos[0, 1];
                position.z = pos[0, 2];

                position = MATtoVEC(matmul(rotatex(inclination), position));
                position = MATtoVEC(matmul(rotatey(ascnode), position));
                position = MATtoVEC(matmul(rotate, position));
                position = matsumV(MATtoVEC(translate), position);
                
                double[,] path = new double[1,3];

                double ann = anomally;// (anomally / 360 - Math.Floor(anomally / 360)) * 360;
                anomaliaprawdziwavalue.Text = Math.Floor(ann).ToString();
                velocity_value.Text = (Math.Floor(Math.Sqrt(Vty*Vty+Vtx*Vtx))).ToString();
                Vx_Value.Text = Vtx.ToString();
                Vy_Value.Text = Vty.ToString();
                printpoint(sender, e, position);
                poss[0] = pos[0, 0];                
                poss[1] = pos[0, 1];
                poss[2] = pos[0, 2];
                  
               
                path= AddToArray(path, poss);

                eeee = 0;
                dV = 0;
                
            


            //else if (bbbb == 1)
            //{
            //    rp = h * h / GM * 0.5;
            //    ra = 0;
            //    apogee_value.Text = ra.ToString();
            //    pedegriee_value.Text = rp.ToString();



            //}

            //else if (bbbb > 1)
            //{
            // //   r = h * h / GM * (1 / (1 + bbbb * Math.Cos(anomally)));
            //   // ra = r;
            //    rp = 0;
            //    apogee_value.Text = ra.ToString();
            //    pedegriee_value.Text = rp.ToString();


            //}

            //Vtan = h / r;
            //Vr = GM / h * bbbb * Math.Sin(DtR(anomally));
            //   a = (ra + rp) / 2;
            // rp = h*h/GM*0.5;
            //  ra = 0;





            double[,] newpath = new double[path.GetLength(0), path.GetLength(1)];
            PVector[] Vnewpath = new PVector[newpath.GetLength(0)];
            for (int i = 0; i < path.GetLength(0) - 1; i++)
            {
                newpath[i, 0] = path[i, 0];
                newpath[i, 1] = path[i, 1];
                newpath[i, 2] = path[i, 2];
          
            newpath = matmul(newpath, Scale);
            }
            Vnewpath[0]=new PVector(0, 0, 0);
            for (int i=0;i<newpath.GetLength(0) - 1 ; i++)
            {
            Vnewpath[i].x = newpath[i, 0];
            Vnewpath[i].y = newpath[i, 1];
            Vnewpath[i].z = newpath[i, 2];

            Vnewpath[i] = MATtoVEC(matmul(rotatex(inclination), Vnewpath[i]));
            Vnewpath[i] = MATtoVEC(matmul(rotatey(ascnode), Vnewpath[i]));
            Vnewpath[i] = MATtoVEC(matmul(rotate, Vnewpath[i]));
            Vnewpath[i] = matsumV(MATtoVEC(translate), Vnewpath[i]);
            }

           
      

           
           // for (int i = 0; i < newpath.GetLength(0) - 1; i++) connect(sender, e, i, i + 1, Vnewpath, black);


            if (DV1 == 0 && DV2 == 0) cliked = false;

        }//koniec SQUARE



   

        PVector perspective(PVector a)
        {

     //      Console.WriteLine(Distance.ToString());
           if (Distance - a.z < 1) return a;
           else
            {
                double z = 1 / (Distance - a.z);
                a.x = a.x *z;
                a.y = a.y *z;
            }


            return a;

        }





    public double DtR(double a)
        {
            return a*Math.Atan(1)/45 ;

        }
    public double RtD(double a)
        {
            return  a*45/(Math.Atan(1)) ;

        }


    public void printpoint(object sender, PaintEventArgs e, PVector b)
        {

            e.Graphics.FillEllipse(Brushes.Black, (float)b.x-5, (float)b.y-5, 10, 10);
           
           
        }


    public void connect(object sender, PaintEventArgs e, int i, int j, PVector[] points, Pen color)
        {

            


           e.Graphics.SmoothingMode =  System.Drawing.Drawing2D.SmoothingMode.HighQuality;

            PVector a = points[i];
            PVector b= points[j];
            
            
            e.Graphics.DrawLine(color,(int)a.x,(int)a.y,(int)b.x,(int)b.y);

          }

    public double[,] VECtoMAT(PVector v/*double[] a*/)
        {
            double[,] m = new double[3, 1];
            m[2,0] = v.x;
            m[1,0] = v.y;
            m[0,0] = v.z;

             return m;
           

        }

    public PVector MATtoVEC(double[,] m)
        {
       
            PVector v =  new PVector();
             v.x = m[0, 0];
             v.y = m[1, 0];
          if(m.GetLength(0)>2){
              v.z = m[2, 0];
          }

            return v;



        }

    public double[,] matmul(PVector a, PVector b)
    {

        double[,] m = VECtoMAT(b);
        double[,] n = VECtoMAT(a);
        return matmul(n, m);
            

    }

    public double[,] matmul(double[,] a, PVector b)
        {
            double[,] m = VECtoMAT(b);
            return matmul(a, m);
            
        }

    public PVector matsumV(PVector a, PVector b)
        {
            PVector v = new PVector();
            v.x = a.x + b.x;
            v.y = a.y + b.y;
            v.z = a.z + b.z;

            
            return v;

        }

    public double[,] matsum(double[,] a, PVector b)
        {
            double[,] m = VECtoMAT(b);
            return matsum(a, m);

        }

    public double[,] matsum(double[,] a, double[,] b)
        {
            int colsA = a.GetLength(1);
            int rowsA = a.GetLength(0);

            int colsB = b.GetLength(1);
            int rowsB = b.GetLength(0);
            if (colsA != colsB && rowsA != rowsB)
            {
                Console.WriteLine("MATRIX ERROR");
                return null;
            }
            double[,] result = new double[rowsA, colsB];
            for (int i = 0; i < rowsA; i++)
            {
                for (int j = 0; j < colsB; j++)
                {
                    double sum = 0;
                    sum += a[i,j] + b[i,j];
                    result[i,j] = sum;
                }
            }
            return result ;     

        }
    public double[,] matmul(double[,] a, double[,] b)
        {
            int colsA = a.GetLength(1);
            int rowsA = a.GetLength(0);

            int colsB = b.GetLength(1);
            int rowsB = b.GetLength(0);

            if (colsA != rowsB)
            {
                Console.WriteLine("MATRIX ERROR");
                
                return null;
                
                
            }
            double[,] result = new double[rowsA, colsB];
            for (int i = 0; i < rowsA; i++)
            {
                for (int j = 0; j < colsB; j++)
                {
                    double sum = 0;
                    for (int k = 0; k < colsA; k++)
                    {
                        sum += a[i,k] * b[k,j];
                    }
                    result[i,j] = sum;
                }
            }



            return result ;
        }

    public void logMatrix(double[,] m)
        {
            int cols = m.GetLength(1);
            int rows = m.GetLength(0);

           Console.Write("{0:D} x {1:D}\n",rows.ToString(), cols.ToString());
            Console.WriteLine((" ").PadRight(24, '-'));
          
  //          Console.WriteLine(cols.ToString());
            
            for (int i=0; i<rows; i++) {
                for (int j=0; j<cols;j++){
                    double a=m[i,j];
                   Console.Write("{0:F} ",a);
                }
               Console.Write("\n");
            }
         

         }





    public double[,] closepoints(double[,] a)
        {
            double[] b = new double [a.GetLength(1)];
            for (int i =0 ; i<a.GetLength(1);i++){
                b[i] = a[0,i];
        }

            return AddToArray(a, b); 
        }


        double[,] to2D(double [,]a){

            double[,] m = new double[a.GetLength(0),2];
            for(int i=0;i<a.GetLength(0);i++){
                m[i,0]=a[i,0];
                m[i,1]=a[i,1];
            }
        return m;                 

            
        }

      public   double[,] AddToArray(double[,] array, double[] dataToAdd)
        {
            var dim0 = array.GetLength(0);
            var dim1 = array.GetLength(1);
            if (dim1 != dataToAdd.Length) throw new ArgumentException();

            var na = new double[dim0 + 1, dim1];
            Array.Copy(array, na, array.Length);
            for (var i = 0; i < dim1; ++i) na[dim0, i] = dataToAdd[i];

            return na;
        }
        Point[] PointCreator(PVector[] v)
        {
         Point[] m = new Point[v.GetLength(0)];
         for (int i = 0; i < v.GetLength(0); i++)
            {
             m[i] = new Point((int)v[i].x, (int)v[i].y);
             }
         return m;

        }

        public Point[] PointCreator(double[,] a)
        {

            Point[] m = new Point[a.GetLength(0)];
            int b = a.GetLength(0);
            int[,] c = new int[a.GetLength(0), 2];
            for (int i = 0; i < b; i++)
            {
                c[i, 0] = (int)to2D(a)[i, 0];
                c[i, 1] = (int)to2D(a)[i, 1];
                m[i] = new Point(c[i, 0], c[i, 1]);
            }
            return m;
        }

        public PVector[] PointGeneratorV()
        {
            double[,] pointo = new double[0, 3];
            double[] added = new double[3];
            double Radius =100;
            double pi = 3.1415;
            
            for (int i = 0; i < 90; i++)
            {
                added[0] = 500 + Radius * Math.Cos(4*i * pi / 180);    //WZÓR X
                added[1] = 300 + Radius * Math.Sin(4*i * pi / 180);   //WZÓR Y
                added[2] = 0;                                                       //WZÓR Z

                pointo = AddToArray(pointo, added);

            }
            pointo=closepoints(pointo);
            PVector[] V = new PVector[pointo.GetLength(0)];
            for (int i = 0; i < 90; i++)
            {
                V[i].x=pointo[i,0];
                V[i].y = pointo[i, 1];
                V[i].z=pointo[i,2];
 
                }
            return V;                
        }


        public double[,] PointGenerator()
        {
            double[,] pointo = new double[0, 3];
            double[] added = new double[3];
            double Radius =100;
            for (int i = 0; i < 90; i++)
            {
                added[0] = 500 + Radius * Math.Cos(4*i * 4 * Math.Atan(1) / 180);    //WZÓR X
                added[1] = 300 + Radius * Math.Sin(4*i * 4 * Math.Atan(1) / 180);   //WZÓR Y
                added[2] = 0;                                                       //WZÓR Z

                pointo = AddToArray(pointo, added);
            }
            return pointo;
        }



        double[,] EarthGenerator2(double dphi)  //szerokości
        {
            double[,] pointo = new double[0, 3];
            double[] added = new double[3];

            double phi = dphi-90;
            double pi = 3.1415;//dla danego dphi wygeneruje
            //       for (int phi = 0; phi < 180; phi += dphi)    
            //       {

            for (int i = 0; i < 91; i++)
            {
                added[2] = Radius * Math.Cos(4 * i * pi / 180) * Math.Cos(phi * pi / 180);    //WZÓR X
                added[0] = Radius * Math.Cos(4 * i * pi / 180) * Math.Sin(phi * pi / 180);   //WZÓR Y
                added[1] = Radius * Math.Sin(4 * i * pi / 180);                                                       //WZÓR Z

                pointo = AddToArray(pointo, added);
            }
            //        }

            return pointo;
        }

         double[,] EarthGenerator(int dphi)  //szerokości
        {
            double[,] pointo = new double[0, 3];
            double[] added = new double[3];
            
            int phi = dphi;
            double pi = 3.1415;//dla danego dphi wygeneruje
     //       for (int phi = 0; phi < 180; phi += dphi)    
     //       {

                for (int i = 0; i < 91; i++)
                {
                    added[2] = Radius * Math.Cos(4 * i * pi / 180) * Math.Cos( phi * pi / 180);    //WZÓR X
                    added[0] = Radius * Math.Cos(4 * i * pi / 180) * Math.Sin( phi * pi / 180);   //WZÓR Y
                    added[1] = Radius * Math.Sin(4 * i * pi/ 180);                                                       //WZÓR Z

                    pointo = AddToArray(pointo, added);
                }
    //        }
                
            return pointo;
        }
        double[,] Horizontals(int dphi)  //szerokości
        {
            double[,] pointo = new double[0, 3];
            double[] added = new double[3];
            
            double Radiusb;
            int phi = dphi;//dla danego dphi wygeneruje
            //       for (int phi = 0; phi < 180; phi += dphi)    
            //       {
            Radiusb =Radius* Math.Cos(phi * 4 * Math.Atan(1) / 180);
            double pi=3.1415;

            for (int i = 0; i < 180; i++)
            {
                added[0] = Radiusb * Math.Cos(4 * i * pi / 180);    //WZÓR X
                added[1] = Radius * Math.Sin(phi * pi/ 180);   //WZÓR Y
                added[2] = Radiusb * Math.Sin(4 * i * pi/ 180);                                                       //WZÓR Z

                pointo = AddToArray(pointo, added);
            }
            //        }
          
            return pointo;
        }

        public double[,] rotatez(double angle)
        {

            angle = DtR(angle);
         double [,] rotatde = new double[,] {
                {Math.Cos(angle),Math.Sin(angle),0},
                {-Math.Sin(angle),Math.Cos(angle),0},
                {0,0,1}
            };
         return rotatde;

        }
      public  double[,] rotatey(double angle)
        {

            angle = DtR(angle);
            double[,] rotatde = new double[,] {
            {Math.Cos(angle),0,-Math.Sin(angle)},    
            {0,1,0},
            {Math.Sin(angle),0,Math.Cos(angle)}
                
            };
            return rotatde;
        }

     public   double[,] rotatex(double angle)
        {

            angle = DtR(angle);
            double[,] rotatde = new double[,] {
                {1,0,0},
            {0, Math.Cos(-(angle)),Math.Sin(-angle)},
            {0, -Math.Sin(-angle),Math.Cos(-angle)}
                
            };
            return rotatde;
        }


      /// <summary>
        /// r w kilometrach od środka ziemi
      /// </summary>
      /// <param name="e"></param>
      /// <param name="r"></param>
      /// <param name="omega"></param>
      /// <param name="i"></param>
      /// <returns></returns>
        double[,] Orbit(double e, double r,double omega, double i)
        {
            double[,] pointo = new double[0, 3];
            double[] added = new double[3];
            
            double pi = 3.1415;
            //      double G = 6.67408* Math.Pow(10, -11);
            //    double M = 5.9722* Math.Pow(10, 24);

            double GM = 398600;//3.986324056*Math.Pow(10, 14);
            double h = Math.Sqrt(r * GM * (1 + e));
            r/=1000;
            if (e < 1)
            {
                for (int j = 0; j < 361; j += 5)
                {
                   
                    {
                        r = h * h / GM / (1 + e * Math.Cos(DtR(j)));

                        added[0] = r * Math.Cos(DtR(j));    //WZÓR X
                        added[1] = 0;   //WZÓR Y
                        added[2] = r * Math.Sin(DtR(j));                                                       //WZÓR Z

                        pointo = AddToArray(pointo, added);
                    }
                }
                return pointo;
            }
            else {

                int x01=-300;
                int x02=0;
                double flag;
                for (int j = -180; j < 180; j++)
                {
                    flag=Math.Abs(1 + e * Math.Cos(DtR(j)));
                    if(flag<0.01*e && x01<-299)x01=j;
                    if (flag < 0.01*e && x01 >-299) x02 = j;
                //    else { x01 = 0; x02 = 0; }
                 //   Console.WriteLine(flag.ToString());

                }



                for (int j =x01+1;j<x02-1 ; j++)
                {
                  //  Console.WriteLine((Math.Abs(e * Math.Cos(DtR(j))) - 1).ToString());
           //         if ((Math.Abs( e * Math.Cos(DtR(j)) - 1)) < 0.01) continue;
            //        if (h * h / GM / (1 + e * Math.Cos(DtR(j)))>this.ClientSize.Height)break;

              //      else
                    {
                        r = h * h / GM / (1 + e * Math.Cos(DtR(j)));

               //         Console.WriteLine(r.ToString());
                        added[0] = r * Math.Cos(DtR(j));    //WZÓR X
                        added[1] = 0;   //WZÓR Y
                        added[2] = r * Math.Sin(DtR(j));                                                       //WZÓR Z

                        pointo = AddToArray(pointo, added);
                    }

                }
                return pointo;
            
            
            
            
            
            
            }









        }
         








     
    
    

  

        //(1246, 576);
        private void hScrollBar4_Scroll(object sender, ScrollEventArgs e)
        {
            multip = Math.Pow(10, (double)hScrollBar4.Value);
            label6.Text = multip.ToString();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            time += 1*multip;
            current_time.Text = Math.Floor(time).ToString();

           Invalidate();
           
        }

     

       private void Form1_Load(object sender, EventArgs e){}
       

  


        public Graphics graphics { get; set; }

        private void hScrollBar1_DragEnter(object sender, DragEventArgs e){ }

       private void FormView_Load(object sender, EventArgs e){}

         

        private void hScrollBar1_ValueChanged(object sender, EventArgs e)
        {
            if (hScrollBar1.Value < -360) hScrollBar1.Value = 359;
            if (hScrollBar1.Value > 360) hScrollBar1.Value = -359;
            
           xangle = hScrollBar1.Value;
           textBox5.Text = (xangle).ToString();
           
        }
        private void hScrollBar2_ValueChanged(object sender, EventArgs e)
        {

            if (hScrollBar2.Value < -360) hScrollBar2.Value = 359;
            if (hScrollBar2.Value > 360) hScrollBar2.Value = -359;
              yangle = hScrollBar2.Value;
              textBox6.Text = yangle.ToString();
        }
        
        private void hScrollBar3_ValueChanged(object sender, EventArgs e)
        {
          
            if (hScrollBar3.Value < -360) hScrollBar3.Value = 359;
            if (hScrollBar3.Value > 360) hScrollBar3.Value = -359;

            zangle = hScrollBar3.Value;
            textBox7.Text = zangle.ToString();
        }

        private void backgroundWorker1_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
        {
        //    TextBox5.Text = (Math.Floor(xangle * 180 / 3.1415)).ToString();
         //   TextBox6.Text = (Math.Floor(yangle * 180 / 3.1415)).ToString();
        //    TextBox7.Text = (Math.Floor(zangle * 180 / 3.1415)).ToString();
        }


        private void textBox5_KeyPress(object sender, KeyPressEventArgs e)
        {
            double number;
            bool sucess = double.TryParse(textBox5.Text, out number);

            if (sucess == true)
            {
                xangle=number ;
                if (Math.Abs(xangle) < 360) hScrollBar1.Value = (int)(xangle);
                else
                {
                    xangle = (xangle/360 - Math.Floor(xangle/360))*360;
                    hScrollBar1.Value = (int)(xangle);
                }
            }
                  
                        

         
        }

        private void textBox6_KeyPress(object sender, KeyPressEventArgs e)
        {
            double number;
            bool sucess = double.TryParse(textBox6.Text, out number);

            if (sucess == true)
            {
                yangle = number;
                if (Math.Abs(yangle) < 360) hScrollBar2.Value = (int)(yangle);
                else
                {
                    yangle = (yangle / 360 - Math.Floor(yangle / 360)) * 360;
                    hScrollBar2.Value = (int)(yangle);
                }
            }
                 
         
        }

        private void textBox7_KeyPress(object sender, KeyPressEventArgs e)
        {
            double number;
            bool sucess = double.TryParse(textBox7.Text, out number);

            if (sucess == true)
            {
                zangle = number;
                if (Math.Abs(zangle) < 360) hScrollBar3.Value = (int)(zangle);
                else
                {
                    zangle = (zangle / 360 - Math.Floor(zangle / 360)) * 360;
                    hScrollBar3.Value = (int)(zangle);
                }
            }
                 
        }

      
       
        
        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {

            char ch = e.KeyChar;

            if (ch == 46 && textBox1.Text.IndexOf(".") != -1)
            {
                e.Handled = true;
                return;
            }

            if (!Char.IsDigit(ch) && ch!=8 && ch!=46)
            {
                e.Handled = true;
            }
        //    double.TryParse(textBox1.Text, out aaaa);
             textBox1.ForeColor = Color.Black;
             if (Convert.ToInt32(e.KeyChar) == 13)
             {
                 textBox1.ForeColor = Color.Green; //[0,192,0];
                 time = 0;
                 keypressedother = 1;
                 keypressedV = 0;
                 anomally = 0;

                 if (double.TryParse(textBox1.Text, out aaaa)) ;
             }
        }

        private void textBox2_KeyPress(object sender, KeyPressEventArgs e)
        {
             textBox2.ForeColor = Color.Black;
             if (Convert.ToInt32(e.KeyChar) == 13)
             {
                 textBox2.ForeColor = Color.Green; //[0,192,0];
                 if (double.TryParse(textBox2.Text, out FormView.bbbb)) ;
                 time = 0;
                 keypressedother = 1;
                 keypressedV = 0;
             }
        }

        private void textBox3_KeyPress(object sender, KeyPressEventArgs e)
        {
             textBox3.ForeColor = Color.Black;
             if (Convert.ToInt32(e.KeyChar) == 13)
             {
                 textBox3.ForeColor = Color.Green; //[0,192,0];
                 if (double.TryParse(textBox3.Text, out FormView.cccc)) ;
                 time = 0;
                 keypressedother = 1;
                 keypressedV = 0;
             }
        }

        private void textBox4_KeyPress(object sender, KeyPressEventArgs e)
        {
             textBox4.ForeColor = Color.Black;
             if (Convert.ToInt32(e.KeyChar) == 13)
             {
                 textBox4.ForeColor = Color.Green; //[0,192,0];
                 if (double.TryParse(textBox4.Text, out FormView.dddd)) ;
                 time = 0;
                 keypressedother = 1;
                 keypressedV = 0;
             }
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void textBox8_KeyPress(object sender, KeyPressEventArgs e)
        {
            textBox8.ForeColor = Color.Black;
             if (Convert.ToInt32(e.KeyChar) == 13)
            {
                textBox8.ForeColor = Color.Green; //[0,192,0];
                if (double.TryParse(textBox8.Text, out FormView.eeee)) ;
                keypressedV = 1;
                keypressedother = 0;
            }
        }
        private void textBox8_KeyDown(object sender, KeyEventArgs e)
        {
           
        }

        private void textBox9_KeyPress(object sender, KeyPressEventArgs e)
        {
            textBox9.ForeColor = Color.Black;
              if (Convert.ToInt32(e.KeyChar) == 13)
            {
                textBox9.ForeColor = Color.Green; //[0,192,0];
                if (double.TryParse(textBox9.Text, out FormView.DV1)) ;
              
            }
        }

        private void textBox10_KeyPress(object sender, KeyPressEventArgs e)
        {
                textBox10.ForeColor = Color.Black;
            if (Convert.ToInt32(e.KeyChar) == 13)
            {
                textBox10.ForeColor = Color.Green; //[0,192,0];
                if (double.TryParse(textBox10.Text, out FormView.DV2)) ;

            }
        }
        private void button1_Click(object sender, EventArgs e)
        {
           cliked=true;


        }

   

     


     



     
    }


    public class PVector
    {
        public double x;
        public double y;
        public double z;

        public PVector(){}

        public PVector(double xx, double yy, double zz)
        {
            x = xx;
            y = yy;
            z = zz;

        }
        public PVector(double xx, double yy)
        {
            x = xx;
            y = yy;
        }


    }


}
