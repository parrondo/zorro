// Reality Check ////////////////////////////
#include <profile.c>

function run()
{
	if(Test) {
		NumTotalCycles = 1000;
		if(TotalCycle > 1) 
			Detrend = SHUFFLE;
	}
	set(RULES+PRELOAD);
	StartDate = 2010; 
	EndDate = 2018;
	BarPeriod = 1440; // 1 day
	BarZone = WET;		// West European session
	Weekend = 1;	// don't merge Friday and Sunday bars
	LookBack = 3;	// only 3 bars needed
	asset("EUR/USD");

	WFOPeriod = 2000;
	DataHorizon = 3;		// equal to max lifetime of a trade

	if(Train) Hedge = 2;	// for training, allow long + short	
	LifeTime = 3; 
	Stop = 500*PIP;		// just a large stop distance
	MaxLong = MaxShort = -1; 

	if(adviseLong(PATTERN+FAST+2+RETURNS,0,
		priceHigh(2),priceLow(2),priceClose(2),
		priceHigh(1),priceLow(1),priceClose(1),
		priceHigh(1),priceLow(1),priceClose(1),
		priceHigh(0),priceLow(0),priceClose(0)) > 50)
		enterLong();
	
	if(adviseShort() > 50)
		enterShort();
}

function evaluate()
{
	static var OriginalProfit, Probability;
	if(TotalCycle == 1) {
		OriginalProfit = Balance;
		Probability = 0;
	} else {
		plotHistogram("Random",Balance,10,1,RED);	
		if(Balance > OriginalProfit)
			Probability += 100./NumTotalCycles;
	}
	if(TotalCycle == NumTotalCycles) {
		plotHistogram("Original",OriginalProfit,10,45,BLACK);	
		printf("\n-------------------------------------------");
		printf("\nP-Value %.1f%%",Probability);
		if(Probability <= 1)
			printf("\nResult is significant");
		else if(Probability <= 5)
			printf("\nResult is possibly significant");
		else 
			printf("\nResult is statistically insignificant");
		printf("\n-------------------------------------------");
	} 
}