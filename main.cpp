#include <unistd.h>
#include "rt-plotter.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


int main(int argc,char **argv)
{
	RTPlotter rt_plotter;	
    mglFLTK gr(&rt_plotter,"MathGL examples");
	
	rt_plotter.SetGraphic(&gr);
	
	rt_plotter.RunTh();
	gr.Run();
	
	rt_plotter.Stop();
	sleep(1);
	
	return 0;
}
