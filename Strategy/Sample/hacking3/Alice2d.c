// Counter trend trading, optimized ////////////////

function run()
{
	set(PARAMETERS+LOGFILE+TESTNOW+PLOTNOW);
	StartDate = 2010;
	EndDate = 2018; // fixed simulation period
	BarPeriod = 240;	// 4 hour bars
	LookBack = 500;
	if(Train) Detrend = TRADES;

	NumWFOCycles = 10; // activate WFO
	ReTrainDays = 147; // automatic retraining every 147 days
	if(ReTrain) {
		UpdateDays = -1;	// update price data from the server 
		SelectWFO = -1;	// select the last cycle for re-optimization
	}
	
// calculate the buy/sell signal
	vars Prices = series(price());
	vars Cycles = series(BandPass(Prices,30,2));
	vars Signals = series(FisherN(Cycles,500));
	var Threshold = optimize(1,0.8,1.2,0.1);

	LifeTime = optimize(100,50,150,10);
	Trail = Stop = optimize(10,4,20,2) * ATR(100);
	MaxLong = MaxShort = -1;

// buy and sell
	var Regime = FractalDimension(Prices,100);
	var RegimeThreshold = optimize(1.5,1.3,1.7,0.1);
	if(Regime > RegimeThreshold) {
		if(crossUnder(Signals,-Threshold))
			enterLong(); 
		else if(crossOver(Signals,Threshold))
			enterShort();
	} 
} 