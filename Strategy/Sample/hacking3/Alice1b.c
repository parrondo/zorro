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
	
	vars MMI_Raws = series(MMI(Prices,300));
	vars MMI_Avgs = series(SMA(MMI_Raws,300));
	
	if(falling(MMI_Avgs)) {
		if(valley(Trends))
			enterLong();
		else if(peak(Trends))
			enterShort();
	}
	
	set(LOGFILE); // log all trades
	//plot("MMI_Raw",MMI_Raws,NEW,GREY);
	//plot("MMI_Avgs",MMI_Avgs,0,BLACK);
}