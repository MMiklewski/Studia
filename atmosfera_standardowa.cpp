

 // Temperature is in kelvins = 273.15 + Celsius
float getStandardTemperature(float geopot_height,float height)
      {
        // Standard atmospheric pressure
        // Below 51 km: Practical Meteorology by Roland Stull, pg 12
        // Above 51 km: http://www.braeunig.us/space/atmmodel.htm

        if (geopot_height <= 11)          // Troposphere
          return 288.15f - (6.5 * geopot_height);
        else if (geopot_height <= 20)     // Stratosphere starts
          return 216.65f;
        else if (geopot_height <= 32)
          return 196.65f + geopot_height;
        else if (geopot_height <= 47)
          return 228.65f + 2.8 * (geopot_height - 32);
        else if (geopot_height <= 51)     // Mesosphere starts
          return 270.65f;
        else if (geopot_height <= 71)
          return 270.65f - 2.8 * (geopot_height - 51);
        else if (geopot_height <= 84.85)
          return 214.65f - 2 * (geopot_height - 71);
		else if (geopot_height <=91)
			return 186.8673;
		else if (geopot_height <=110)
			return 263.1905+(-76.3232)*pow((1-((height-91)*(height-91)/(-19.9429)/(-19.9429))),0.5);

		// Thermosphere has high kinetic temperature (500 C to 2000 C) but temperature
        // as measured by a thermometer would be very low because of almost vacuum.

      }
float getGeopotential(float altitude_km)
      {
        float EARTH_RADIUS =  6356.766; // km

        return EARTH_RADIUS * altitude_km / (EARTH_RADIUS + altitude_km);
      }
float getStandardPressure (float height){

	height=height/1000.0f;
	float geopot_height = getGeopotential(height);
	float t=getStandardTemperature(geopot_height,height);
	
	if(geopot_height <= 11)
		return 101325*pow(288.15f /t, -5.255877f);
	else if (geopot_height <= 20)
          return 22632.06 * exp(-0.1577f * (geopot_height - 11));
    else if (geopot_height <= 32)
          return 5474.889f * pow(216.65f / t, 34.16319f);
    else if (geopot_height <= 47)
          return 868.0187f * pow(228.65f / t, 12.2011f);
    else if (geopot_height <= 51)
          return 110.9063f * exp(-0.1262f * (geopot_height - 47));
    else if (geopot_height <= 71)
          return 66.93887f * pow(270.65f / t, -12.2011f);
    else if (geopot_height <= 84.85)
          return 3.956420f * pow(214.65f / t, -17.0816f);
	 else if (geopot_height <= 91)
		 return exp(2.159582*pow(10,-6.)*height*height*height-4.836957*pow(10,-4.)*height*height-0.1425192*height+13.47530);
	 else if (geopot_height <= 100)
		 return exp(3.304895*pow(10,-5.)*height*height*height-0.009062730*height*height+0.6516698*height-11.03037);
		 

}