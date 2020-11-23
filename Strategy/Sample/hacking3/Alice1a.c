// Trend Trading ///////////////////
#include <profile.c>

function run()
{
	StartDate = 2013;
	EndDate = 2018; // fixed simulation period
	
	vars Prices = series(price());
	vars Trends = series(Laguerre(Prices,0.05));
	
	Stop = 10*ATR(100);
	MaxLong = MaxShort = -1;
	
	if(valley(Trends))
		enterLong();
	else if(peak(Trends))
		enterShort();
	
	//set(LOGFILE); // log all trades
	//plotTradeProfile(-50); 
}