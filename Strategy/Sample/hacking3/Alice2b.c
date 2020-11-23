// Workshop 5: Counter trend trading ///////////////////

function run()
{
	StartDate = 2013;
	EndDate = 2018; // fixed simulation period
	BarPeriod = 240;	// 4 hour bars
	
// calculate the buy/sell signal
	vars Prices = series(price());
	vars Cycles = series(BandPass(Prices,30,2));
	vars Signals = series(FisherN(Cycles,500));
	var Threshold = 1.0;

	LifeTime = 100;
	Trail = Stop = 10*ATR(100);
	MaxLong = MaxShort = -1;

	var Regime = FractalDimension(Prices,100);
	if(Regime > 1.5)
	{
		if(crossUnder(Signals,-Threshold))
			enterLong(); 
		else if(crossOver(Signals,Threshold))
			enterShort();
	} 

// plot signals and thresholds
	plot("Cycles",Cycles,NEW,RED);
	plot("Signals",Signals,NEW,GREEN);
	plot("Threshold1",1,0,BLACK);
	plot("Threshold2",-1,0,BLACK);
	plot("Regime",Regime,NEW,BLUE);
	set(LOGFILE|PLOTNOW);
} 