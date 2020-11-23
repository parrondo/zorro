// Workshop 5: Counter trend trading ///////////////////

function run()
{
	StartDate = 2013;
	EndDate = 2018; // fixed simulation period
	BarPeriod = 240;	// 4 hour bars
	
// calculate the buy/sell signal
	vars Prices = series(price());
	var Period = 30; //DominantPeriod(Prices,500);
	vars Cycles = series(BandPass(Prices,Period,2));
	vars Signals = series(FisherN(Cycles,500));
	var Threshold = 1.0;

// buy and sell
	LifeTime = 100;
	Trail = Stop = 10*ATR(100);
	MaxLong = MaxShort = -1;
	if(crossUnder(Signals,-Threshold))
		enterLong(); 
	else if(crossOver(Signals,Threshold))
		enterShort();

// plot signals and thresholds
	plot("Cycles",Cycles,NEW,RED);
	plot("Signals",Signals,NEW,GREEN);
	plot("Threshold+",Threshold,0,BLACK);
	plot("Threshold-",-Threshold,0,BLACK);
	set(LOGFILE+PLOTNOW);
} 