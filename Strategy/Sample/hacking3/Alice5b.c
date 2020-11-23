// Simple Option system, money management //////////////////////////////////////////
#include <contract.c>

#define CALLPREMIUM	5.00
#define PUTPREMIUM	10.00
#define WEEKS		6 
#define LEVERAGE	4
#define LIQUIDATE		

void run() 
{
	set(PLOTNOW|LOGFILE);
	StartDate = ifelse(Live,NOW,20120101); 
	EndDate = 20181231;
	BarPeriod = 1440;
	History = ".t8";
	Capital = slider(1,10000,0,20000,"Capital","");
	
	assetList("AssetsIB");
	asset("SPY");
	Multiplier = 100;
	setf(TradeMode,TR_GTC); // don't wait for the execution of trades

// sell any open underlying positions
	contractSellUnderlying();

	vars Prices = series(priceClose());
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
		Commission = 1.0/Multiplier;
#ifdef LIQUIDATE // accept margin call and underlying liquidation
		MarginCost = 0.15*Prices[0]/2;
#else
		MarginCost = comboStrike(2)/LEVERAGE/2;
#endif
		var TotalCost = 2*Multiplier*MarginCost;
		Lots = (Capital+ProfitClosed)/TotalCost;
		if(Lots >= 1) {
			enterShort(Lots*comboLeg(1));
			enterShort(Lots*comboLeg(2));
		}
	}
	if(Live && !is(LOOKBACK)) quit("Ok!");
}
