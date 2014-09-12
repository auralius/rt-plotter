#include <unistd.h>
#include "rt-plotter.h"

///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////


int main(int argc,char **argv)
{
	const char * fn = argv[1];
	if (fn == NULL) {
		printf("usage : %s [configuration file]\n", argv[0]);
		exit(1);
	}
	
	RTPlotter rt_plotter(fn);	
    mglFLTK gr(&rt_plotter,"rt-plotter");
	
	rt_plotter.SetGraphic(&gr);
	
	rt_plotter.RunTh();
	gr.Run();
	
	rt_plotter.Stop();
	sleep(1);
	
	return 0;
}
