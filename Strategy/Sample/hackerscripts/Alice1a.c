// Trend Trading ///////////////////
#include <profile.c>

function run()
{
	vars Price = series(price());
	vars Trend = series(LowPass(Price,500));
	Stop = 4*ATR(100);
	
	if(valley(Trend))
		enterLong();
	else if(peak(Trend))
		enterShort();
	
	StartDate = 2010;
	EndDate = 2015; // fixed simulation period 2010-2015
	asset("EUR/USD");

	set(LOGFILE); // log all trades
	PlotWidth = 800;
	PlotHeight1 = 300;
	//plotTradeProfile(-50); 
	//ColorWin = ColorLoss = 0;
	//ColorUp = ColorDn = 0;
	//ColorDD = 0x010101;
	//ColorEquity = GREY;
}