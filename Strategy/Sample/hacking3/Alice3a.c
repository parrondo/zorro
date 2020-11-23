// Alice3a: Portfolio trading ///////////////////

function tradeCounterTrend()
{
	TimeFrame = frameSync(4);
	vars Prices = series(price());
	vars Cycles = series(BandPass(Prices,30,2));
	vars Signals = series(FisherN(Cycles,500));
	var Threshold = optimize(1,0.8,1.2,0.1);

	LifeTime = 4*optimize(100,50,150,10);
	Trail = Stop = optimize(10,4,20,2)*ATR(100);
	MaxLong = MaxShort = -1;
	
	var Regime = FractalDimension(Prices,100);
	var RegimeThreshold = optimize(1.5,1.3,1.7,0.1);
	if(Regime > RegimeThreshold)
	{
		if(crossUnder(Signals,-Threshold))
			enterLong(); 
		else if(crossOver(Signals,Threshold))
			enterShort();
	} 
}

function tradeTrend()
{
	TimeFrame = 1;
	vars Prices = series(price());
	vars Trends = series(Laguerre(Prices,optimize(0.05,0.02,0.15,0.01)));
	
	Stop = optimize(10,4,20,2)*ATR(100);
	Trail = 0;
	LifeTime = 0;
	MaxLong = MaxShort = -1;
	
	var MMI_Period = optimize(300,100,400,100);
	vars MMI_Raws = series(MMI(Prices,MMI_Period));
	vars MMI_Avgs = series(SMA(MMI_Raws,MMI_Period));
	
	if(falling(MMI_Avgs)) {
		if(valley(Trends))
			enterLong();
		else if(peak(Trends))
			enterShort();
	}
}

function run()
{
	set(PARAMETERS+LOGFILE+TESTNOW+PLOTNOW);
	StartDate = 2010; // further back due to WFO
	EndDate = 2018;   // fixed simulation period
	BarPeriod = 60;	// 1 hour bars
	LookBack = 4*500;	// needed for FisherN()
	if(Train) Detrend = TRADES;

	NumWFOCycles = 10; // activate WFO
	NumCores = -1;		// multicore training (Zorro S only)
	ReTrainDays = 147;
	if(ReTrain) {
		UpdateDays = -1;	// update price data from the server 
		SelectWFO = -1;	// select the last cycle for re-optimization
	}
	
// portfolio loop
	while(asset(loop("EUR/USD","GBP/USD")))
	//while(asset(loop("EUR/USD")))
	while(algo(loop("TRND","CNTR")))
	//while(algo(loop("CNTR")))
	//while(algo(loop("TRND")))
	{
		if(Algo == "TRND") 
			tradeTrend();
		else if(Algo == "CNTR") 
			tradeCounterTrend();
	}	
}