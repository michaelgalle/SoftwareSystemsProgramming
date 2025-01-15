/* main.cpp : Multithreading example that use the 
 *            C++11 std::thread
 *			  Copyright Michael A. Galle
 */

#include <iostream>     // For std::cout
#include <thread>		// For std::thread
#include <time.h>		// For measuring wall-clock time
#include <unistd.h>     // For sleep

int RS232Rx(int timeout_s) {
	std::cout <<"\nNow reading from Rx buffer in another thread ...\n";
	sleep(timeout_s);                                                               // Simulate work
	return(timeout_s);
}

int RS232Tx(int timeout_s) {
	std::cout <<"\nNow transmitting bytes\n";
	sleep(timeout_s);                                                               // Simulate work
	return(timeout_s);
}

int main() {
	int timeout_s = 3;													            // 3 second timeout

    // Record start time using std::chrono
    auto start = std::chrono::high_resolution_clock::now();
	
	std::thread Rx_thread(RS232Rx, timeout_s);							            // Spawn a thread that calls Rx operation 
	RS232Tx(timeout_s);													            // Start Tx operation in the main thread by calling it here directly 
	Rx_thread.join();														        // Wait for the Rx thread to complete and join the main thread
	
	// Record the stop time using std::chrono
    auto stop = std::chrono::high_resolution_clock::now();	
    
    std::chrono::duration<double> elapsed = stop - start;
    														        // Show that less than 6 seconds has elapsed since both functions are in separate threads
	std::cout << "\nRx thread now completed\n";
	std::cout << "\nTotal time elapsed: " << elapsed.count() << " seconds, which is less than the 6 seconds it would take if it was not multithreaded\n";		// Should be around 3 seconds, not 6 if this were single threaded

	return(0);
}
