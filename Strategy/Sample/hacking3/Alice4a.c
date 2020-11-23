// Machine learning ////////////////////////////

function run()
{
	//Detrend = SHUFFLE;	// reality check
	set(RULES+TESTNOW+PLOTNOW+LOGFILE);// generate rules, test after training
	StartDate = 2010; 
	EndDate = 2018;
	BarPeriod = 1440; // 1 day
	BarZone = WET;		// West European session
	Weekend = 1;	// don't merge Friday and Sunday bars
	//LookBack = 3;	// only 3 bars needed	
	asset("EUR/USD");
	
	WFOPeriod = 2000;
	DataHorizon = 3;		// equal to max lifetime of a trade

	if(Train) Hedge = 2;	// for training, allow long + short	
	LifeTime = 3; 
	Stop = 500*PIP;		// just a large stop distance
	MaxLong = MaxShort = -1; 
	
	if(adviseLong(PATTERN+2+RETURNS,0,
		priceHigh(2),priceLow(2),priceClose(2),
		priceHigh(1),priceLow(1),priceClose(1),
		priceHigh(1),priceLow(1),priceClose(1),
		priceHigh(0),priceLow(0),priceClose(0)) > 50)
		enterLong();
	
	if(adviseShort() > 50)
		enterShort();
}
