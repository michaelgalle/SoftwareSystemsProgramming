/* main.cpp : Multithreading example that use the 
 *            C++11 std::thread
 *			  This example uses thread based member functions
 *			  Copyright Michael A. Galle
 */

#include <stdio.h>
#include <thread>		// std::thread
#include <Windows.h>	// Sleep
#include <time.h>		// Record start and end time different
#include <string.h>		// String operations
#include "TxRx.h"		// Class

int main() {
	int timeout_us = 1000;													// 3 second timeout
	TxRx* txrx = new TxRx();												// Instantiate object

	std::thread tx = txrx->RS232TxThread(timeout_us);						// Spawn a thread that calls the transmit operation of the TxRx class
	std::thread rx = txrx->RS232RxThread(timeout_us);						// Spawn a thread that calls the receive operation of the TxRx class 
	
	rx.detach();															// detach rx thread so it runs separately
	tx.detach();															// detach tx thread so it runs separately 
	
	Sleep(20000);															// Entire program ends after 20 seconds	

	return(0);
}