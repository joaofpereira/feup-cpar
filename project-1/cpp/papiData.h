#ifndef PAPIDATA_H
#define PAPIDATA_H

class PapiData {
private:
	int EventSet;					// PAPI CPU Events Set
	char header[1024];					// Results header
	long long values[108];			// PAPI results
	int ret;						// PAPI functions return value

public:
	PapiData();
	~PapiData();

	void handleError (int retval);	// Print specific PAPI error
	void initPapi();				// Init PAPI Variables
	void startPapi();				// Start PAPI Counters
	void stopPapi();				// Stop PAPI Counters
	void resetPapi();				// Reset PAPI Counters
	void setPapiEvents();			// Add CPU Events to be captured
	void printHeader();				// Print Results Info Header
	void printPapiResults();		// Print PAPI Counters
	void removeAndDestoyPapi();		// Remove Events and destroy papi Variables
};

#endif