/* TxRx.cpp : Implementation -- Multithreading example that use the
 *            C++11 std::thread
 *			  This example uses thread based member functions
 *			  Copyright Michael A. Galle
 */

#include <iostream>		// std::cout
#include <stdio.h>
#include <thread>		// std::thread - Multithreading compatible with all platforms (Windows, Linux, Mac)
#include <unistd.h>		// sleep
#include <time.h>		// Record start and end time different
#include <string.h>		// string operations
#include <stdlib.h>		// srand() and rand()
#include "TxRx.h"


/* ************* Receive function ****************** */
int TxRx::RS232Rx(int timeout_s) {
	std::cout << "\nStarting read from Rx buffer in another thread ...\n";
	while (true) {
		sleep(timeout_s);
		if (this->signal == 1) {													// If a message has been received
			this->mtx.lock();														// Lock the signal variable (MUTEX)
			strcpy(this->rxBuff, this->txBuff);										// Simulate loopback from txBuff
			std::cout << "\n" << this->rxBuff << "\n";
			this->signal = 0;														// Reset signal - indicate message read so can read another message
			this->mtx.unlock();
		} else {
			strcpy(this->rxBuff, "");												// Clear rxBuff
			printf(".");															// Print a dot to show no message received
			//std::cout << ".";
		}
	}
	return(timeout_s);
}

/* ************* Transmit function ****************** */
int TxRx::RS232Tx(int timeout_s) {
	int randNum;
	int messageNum = 0;
	char numbuff[20];
	srand(time(NULL));

	// Simulate random message transmission
	std::cout << "\nStarting transmissions from Tx buffer in another thread ...\n";
	while (true) {
		sleep(timeout_s);
		randNum = rand() % 10;														// Simulate sending message at random times (only send when randNum <= 2)
		if (randNum <= 2) {															// Signals a message was sent 
			this->mtx.lock();														// Lock the signal variable (MUTEX varioable)
			this->signal = 1;														// Signal a Transmission
			messageNum++;															// Increment the counter
			strcpy(this->txBuff, "Message from txBuff #");							// Send the message
			sprintf(numbuff, "%d", messageNum);
			strcat(this->txBuff, numbuff); 
			this->mtx.unlock();
		}
	}
	return(timeout_s);
}

/* ************* Threaded version of the Transmit and Receive functions ****************** */
std::thread TxRx::RS232RxThread(int timeout_s) {
	return std::thread(&TxRx::RS232Rx, this, timeout_s);
}

std::thread TxRx::RS232TxThread(int timeout_s) {
	return std::thread(&TxRx::RS232Tx, this, timeout_s);
}

