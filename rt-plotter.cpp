#include <unistd.h>
#include "rt-plotter.h"


// TODO: Put these to external configuration file
key_t SHM_ID = 5678;
int SHM_SIZE = 64;
int PLOT_BUFFER_SIZE = 100;

RTPlotter::RTPlotter()
{
	m_is_running = true;
	
	// Guess number of channel from hte SHM_SIZE
	m_nchannel = SHM_SIZE / 8;
	printf("m_nchannel = %i\n", m_nchannel);
	
	m_data_from_shared_memory = new double *[PLOT_BUFFER_SIZE];
	for (int i = 0; i < PLOT_BUFFER_SIZE; i++) {
		m_data_from_shared_memory[i] = new double[m_nchannel];
	}
		
	m_shm_access = new ShmAccess(SHM_SIZE, SHM_ID);
	m_data_to_plot = new std::vector<double> [m_nchannel];
	for (int i = 0; i < m_nchannel; i++){
		for (int j = 0; j < PLOT_BUFFER_SIZE; j++){
			m_data_to_plot[i].push_back(0.0);
		}
	}
}

RTPlotter::~RTPlotter()
{
	printf("cleaning up...\n");
	m_is_running = false;
	delete [] m_data_from_shared_memory;	
	delete m_shm_access;
}

void RTPlotter::GrabData(int ch)
{
	double *shm = m_shm_access->GetShmAddr();
	
	for (int i = 0; i < m_nchannel; i++) {
		m_data_to_plot[i].push_back((double)shm[i]);
		//printf("%f\n", m_data_to_plot[i].at(m_data_to_plot[i].size()-2));
		printf("%i\n", m_data_to_plot[i].size());
		if (m_data_to_plot[i].size() > PLOT_BUFFER_SIZE)
			m_data_to_plot[i].erase(m_data_to_plot[i].begin());
	}
	usleep(1000);
		
	m_gr->Update(); // update window
}


int RTPlotter::Draw(mglGraph* gr)
{
	gr->Clf();
	
	gr->SetRanges(0, PLOT_BUFFER_SIZE); 
	gr->SetOrigin(0, 0);;
	gr->SetFontSize(3);
	gr->Axis();
	
	int ch_to_plot = 0;
	mglData dat(PLOT_BUFFER_SIZE);
	for (int i = 0; i < PLOT_BUFFER_SIZE; i++) {
		dat.a[i] = m_data_to_plot[ch_to_plot].at(i);
//		printf("%f\n", dat.a[i]);
	}
	fflush(stdout);

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




