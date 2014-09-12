#ifndef RT_PLOTTER_INCLUDED
#define RT_PLOTTER_INCLUDED

#include <mgl2/mgl.h>
#include <mgl2/fltk.h>
#include "shm-access.h"

#include <vector>
#include <libconfig.h>
#include <string>
#include <algorithm>

using namespace std;


class RTPlotter : public mglDraw
{


public:
	RTPlotter(const char * config_fn);
	~RTPlotter();
		
	void SetGraphic(mglFLTK *gr);
	void RunTh();
	void Stop();
	
private:
	void LoadConfig(const char *fn);
	int Draw(mglGraph *gr);
	void GrabData();
	
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
	std::vector<const char *> m_colors;
	std::vector<int> m_channels_to_plot;
	std::vector<const char *> m_legends;
	
	char *m_title;
};

#endif