// Simple portfolio rotation /////////////
//////////////////////////////////////////

#define RISK	0.7	// no risk, no fun

var Momentums[100],Weights[100];

void rotate(int GoLong)
{
	var Invest = RISK*(Capital+ProfitTotal);
	for(listed_assets) {
		int NewLots = Invest*Weights[Itor]/MarginCost;
		if(Test) {
			if(NewLots > LotsPool && GoLong)
				enterLong(NewLots-LotsPool);
			else if(NewLots < LotsPool)
				exitLong(0,0,LotsPool-NewLots);
		} else if(Live) {
			int OldLots = brokerCommand(GET_POSITION,Asset);
			if(NewLots > OldLots && GoLong)
				enterLong(NewLots-OldLots);
			else if(NewLots < OldLots)
				enterShort(OldLots-NewLots);
		}
	}
}

void run() 
{
	set(PLOTNOW|LOGFILE);
	StartDate = ifelse(Live,NOW,20120101); 
	EndDate = 20181231;
	BarPeriod = 1440;
	LookBack = 100;
	SaveMode = 0;
	
	assetList("AssetsSP50");
	Capital = slider(1,10000,0,20000,"Capital","");
	
	for(listed_assets) { 
		asset(Asset);
		vars Prices = series(priceClose());
		Momentums[Itor] = ROC(Prices,LookBack-1);
	}

	if((Live && !is(LOOKBACK))
		|| (Test && tdm(0) == 1 && month(0)%2)) // first trading day of every second month
	{
		distribute(Weights,Momentums,NumAssetsListed,5,0.5); 
		rotate(0);	// exit old positions
		rotate(1);	// enter new positions
	}

	if(Live && !is(LOOKBACK)) quit("Ok!");
}
