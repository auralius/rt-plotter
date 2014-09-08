#include <unistd.h>
#include "rt-plotter.h"


RTPlotter::RTPlotter()
{
	m_is_running = true;
	
	// Load the configurations
	LoadConfig("./rt-plotter-config.cfg");
	
	// Guess number of channel from the SHM_SIZE (double is 8 byte)
	m_nchannel = m_shm_size / 8;
	printf("m_nchannel = %i\n", m_nchannel);
	printf("m_shm_size = %i\n", m_shm_size);
	printf("m_shm_id = %i\n", m_shm_id);
	printf("m_plot_delay = %i\n", m_plot_delay);
	
	m_shm_access = new ShmAccess(m_shm_size, m_shm_id);
	m_data_to_plot = new std::vector<double> [m_nchannel];
	
	for (int i = 0; i < m_nchannel; i++)
		for (int j = 0; j < m_plot_buffer_size; j++)
			m_data_to_plot[i].push_back(0.0);
}


RTPlotter::~RTPlotter()
{
	printf("cleaning up...\n");
	m_is_running = false;
	delete m_shm_access;
}

void RTPlotter::GrabData(int ch)
{
	double *shm = m_shm_access->GetShmAddr();
	
	for (int i = 0; i < m_nchannel; i++) {
		m_data_to_plot[i].push_back((double)shm[i]);
		if (m_data_to_plot[i].size() > m_plot_buffer_size)
			m_data_to_plot[i].erase(m_data_to_plot[i].begin());
	}
	usleep(m_plot_delay);
		
	m_gr->Update(); // update window
}

void RTPlotter::LoadConfig(char* fn)
{
	/*Initialization */
    config_t cfg;  
    config_init(&cfg);
  
    /* Read the file. If there is an error, report it and exit. */
    if (!config_read_file(&cfg, fn))
    {
		printf("%s:%d - %s\n", config_error_file(&cfg), config_error_line(&cfg), config_error_text(&cfg));
		printf("%s not found...\n", fn);
		config_destroy(&cfg);
		return;
    }    
    
    config_lookup_int(&cfg, "shm_key", &m_shm_id);
	config_lookup_int(&cfg, "shm_size", &m_shm_size);
    config_lookup_int(&cfg, "plot_buffer_size", &m_plot_buffer_size);
    config_lookup_int(&cfg, "plot_delay", &m_plot_delay);
    
	const char *string_tmp;
	config_lookup_string(&cfg, "channels_to_plot", &string_tmp);
    config_lookup_string(&cfg, "colors", &string_tmp);
}


int RTPlotter::Draw(mglGraph* gr)
{
	gr->Clf();
	
	gr->SetRanges(0, m_plot_buffer_size); 
	gr->SetOrigin(0, 0);;
	gr->SetFontSize(3);
	gr->Axis();
	
	int ch_to_plot = 0;
	mglData dat(m_plot_buffer_size);
	for (int i = 0; i < m_plot_buffer_size; i++) {
		dat.a[i] = m_data_to_plot[ch_to_plot].at(i);
	}

	gr->Plot(dat,"b");
	
	
	return 0;
}

void RTPlotter::SetGraphic(mglFLTK* gr)
{
	m_gr = gr;
}

void RTPlotter::RunTh()
{
	pthread_t plotter_thread_id;
	pthread_create(&plotter_thread_id, NULL, plotter_thread, (void *) this);
}

void RTPlotter::Stop()
{
	m_is_running = false;
}

void RTPlotter::plotter_thread(void *param)
{
	RTPlotter *o = (RTPlotter *) param;
	o->plotter_thread_worker();
}

void RTPlotter::plotter_thread_worker()
{
	while (m_is_running)
		GrabData(0);
}




