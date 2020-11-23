// Simple option system //////////////////////////////////////////
#include <contract.c>

#define CALLPREMIUM	5.00
#define PUTPREMIUM	10.00
#define WEEKS		6 

void run() 
{
	set(PLOTNOW|LOGFILE);
	StartDate = 20120101; // exact dates because history is not split in years
	EndDate = 20181231;
	BarPeriod = 1440;
	History = ".t8";
	
	assetList("AssetsIB");
	asset("SPY");
	Multiplier = 100;

	vars Prices = series(priceClose());
// load today's contract chain
	if(!contractUpdate(Asset,0,CALL|PUT)) return;
// filter by volatility
	var Vola = abs(ROC(Prices,WEEKS*5));
	if(NumOpenShort || Vola > 10) return;
		 
// Enter new positions
	if(combo(
		contractFind(CALL,WEEKS*7,CALLPREMIUM,2),1, 
		contractFind(PUT,WEEKS*7,PUTPREMIUM,2),1,
		0,0,0,0)) 
	{
		MarginCost = 0.15*Prices[0]/2;
		Commission = 1.0/Multiplier;
		enterShort(comboLeg(1));
		enterShort(comboLeg(2));
	}
}