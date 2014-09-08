#ifndef RT_PLOTTER_INCLUDED
#define RT_PLOTTER_INCLUDED

#include <mgl2/mgl.h>
#include <mgl2/fltk.h>
#include "shm-access.h"

#include <vector>


class RTPlotter : public mglDraw
{


public:
	RTPlotter();
	~RTPlotter();
		
	void SetGraphic(mglFLTK *gr);
	void RunTh();
	void Stop();
	
private:
	int Draw(mglGraph *gr);
	void GrabData(int ch);
	
	static void plotter_thread(void *param);
	void plotter_thread_worker();
	
	mglFLTK *m_gr; // graphics to be updated
	double **m_data_from_shared_memory;
	ShmAccess *m_shm_access;
	std::vector<double> *m_data_to_plot;
	int m_nchannel;
	
	bool m_is_running;

	
};

#endif