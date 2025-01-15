/* main.cpp : Multithreading example that use the 
 *            C++11 std::thread
 *			  This example uses thread based member functions
 *			  Copyright Michael A. Galle
 */

#include <iostream>		// std::cout
#include <thread>		// std::thread
#include <unistd.h>		// sleep
#include "TxRx.h"		// Class

int main() {
	int timeout_s = 1;														// 3 second timeout
	TxRx* txrx = new TxRx();												// Instantiate object

	std::cout << "\nSending and receiving messages. Press Ctrl+C to stop simulation\n";

	std::thread tx = txrx->RS232TxThread(timeout_s);						// Spawn a thread that calls the transmit operation of the TxRx class
	std::thread rx = txrx->RS232RxThread(timeout_s);						// Spawn a thread that calls the receive operation of the TxRx class 

	// Option 1: Uncomment to run - Wait for other thread to complete and join main - Both threads do not complete but keep running 					
	//tx.join();																// Wait for the tx thread to complete
	//rx.join();																// Wait for the rx thread to complete


	// Option 2: Uncomment to run - Detach and run separately (uncomment to run)
	rx.detach();															// detach rx thread so it runs separately
	tx.detach();															// detach tx thread so it runs separately 
	sleep(10);																// Entire program (and threads) end after 10 seconds	
	
	return(0);
}