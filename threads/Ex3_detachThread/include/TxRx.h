/* TxRx.cpp : Interface (Class definition) -- Multithreading example that use the
 *            C++11 std::thread
 *			  This example uses thread based member functions
 *			  Copyright Michael A. Galle
 */
#pragma once

#include <thread> 
#include <mutex>

class TxRx {
  public:
	char rxBuff[140];
	char txBuff[140];
	std::mutex mtx;													// Mutex variable
	int signal;														// Variable to signal a Tx message
	int RS232Rx(int timeout_us);
	int RS232Tx(int timeout_us);
	std::thread RS232RxThread(int timeout_us);						// Thread based member function
	std::thread RS232TxThread(int timeout_us);						// Thread based member function
};
