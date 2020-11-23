// Filter test ///////////////////

function run()
{
	BarPeriod = 60;
	MaxBars = 1000;
	LookBack = 100;
	asset(""); // dummy asset
	ColorUp = ColorDn = 0; // don't plot a price curve
	PlotHeight1 = PlotHeight2 = 200;
	PlotWidth = 800;
	set(PLOTNOW);
	
	vars Chirp = series(genSine(3,60));
	int Color = BLACK;
	plot("Chirp",Chirp[0],0,Color);
	plot("BandPass",BandPass(Chirp,30,0.1),NEW,Color);
	plot("HighPass",HighPass2(Chirp,20),NEW,Color);
	plot("Laguerre",Laguerre(Chirp,5),NEW,Color);
	plot("EMA",EMA(Chirp,30),NEW,Color);
}

