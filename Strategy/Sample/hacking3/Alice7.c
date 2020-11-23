// Alice's Scam Robot /////////////////////
#include <profile.c>

//#define HISTOGRAM
#define HIGHWINRATE
//#define MARTINGALE
//#define MARGINCHECK
#define STEPS	500

function run()
{
	if(!require(2.06)) return;
#ifdef HISTOGRAM	
	NumTotalCycles = 3000; // run this simulation 3000 times
#else
	set(PLOTNOW|LOGFILE);
#endif

#ifdef MARTINGALE
	StartDate = EndDate = 2015; // 1 year only
#else
	StartDate = 2013;
	EndDate = 2018;
#endif
	BarPeriod = 1440;
	LookBack = 0;
	asset("EUR/USD");

#ifdef MARGINCHECK
	if(Equity < -250) {
		quit("Game over!");
		return;
	} 
#endif
	
#ifdef HIGHWINRATE
	Stop = 200*PIP;
	TakeProfit = 10*PIP;
	if(NumOpenTotal == 0)
#endif
	{
#ifdef MARTINGALE
		var ProfitGoal = 100*PIP*Bar;
		Lots = (ProfitGoal-ProfitClosed*PIP/PIPCost)/TakeProfit; 
		Lots = clamp(Lots,1,100);
#endif	
		if(random() > 0)
			enterLong();
		else 
			enterShort();
	}
}

// generate a profit distribution chart
#ifdef HISTOGRAM	
function evaluate()
{
	plotHistogram("Profit",ProfitClosed/PIPCost,STEPS,1,RED);	
	static var AllProfits,MaxProfit,MinProfit;
	static int AllTrades;
	if(TotalCycle == 1) {
		AllProfits = MaxProfit = MinProfit = 0; 
		AllTrades = 0;
	}
	AllProfits += ProfitClosed/PIPCost;
	MaxProfit = max(MaxProfit,ProfitClosed/PIPCost);
	MinProfit = min(MinProfit,ProfitClosed/PIPCost);
	AllTrades += NumWinTotal + NumLossTotal;
	if(TotalCycle == NumTotalCycles) {
		//plotHistogram("Scale",-22000,STEPS,1,TRANSP);	
		plotHistogram("Scale",30000,STEPS,1,TRANSP);	
		printf("\n-------------------------------------------");
		printf("\nProfit Avg  %.0fp  Max %.0fp  Min %.0fp\nProfit per Trade: %0.1fp",
			AllProfits/NumTotalCycles,MaxProfit,MinProfit,AllProfits/AllTrades);
		printf("\n-------------------------------------------\n");
	}
}
#endif