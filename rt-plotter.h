#ifndef RT_PLOTTER_INCLUDED
#define RT_PLOTTER_INCLUDED

#include <mgl2/mgl.h>
#include <mgl2/fltk.h>
#include "shm-access.h"

#include <vector>
#include <libconfig.h>
#include <regex>


class RTPlotter : public mglDraw
{


public:
	RTPlotter();
	~RTPlotter();
		
	void SetGraphic(mglFLTK *gr);
	void RunTh();
	void Stop();
	
private:
	void LoadConfig(char *fn);
	int Draw(mglGraph *gr);
	void GrabData(int ch);
	
	static void plotter_thread(void *param);
	void plotter_thread_worker();
	
	mglFLTK *m_gr; // graphics to be updated
	ShmAccess *m_shm_access;
	std::vector<double> *m_data_to_plot;
	int m_nchannel;
	
	bool m_is_running;
	
	key_t m_shm_id;
	int m_shm_size;
	int m_plot_buffer_size;
	int m_plot_delay;
	char *m_colors;
	int *channels_to_plot;

	
};

#endif