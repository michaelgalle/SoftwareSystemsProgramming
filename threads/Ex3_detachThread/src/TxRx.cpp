/* TxRx.cpp : Implementation -- Multithreading example that use the
 *            C++11 std::thread
 *			  This example uses thread based member functions
 *			  Copyright Michael A. Galle
 */

#include <stdio.h>
#include <thread>		// std::thread - Multithreading compatible with all platforms (Windows, Linux, Mac)
#include <Windows.h>	// Sleep
#include <time.h>		// Record start and end time different
#include <string.h>		// String operations
#include "TxRx.h"

/* ************* Receive function ****************** */
int TxRx::RS232Rx(int timeout_us) {
	printf("\nStarting read from Rx buffer in another thread ...\n");
	while (true) {
		Sleep(timeout_us);
		if (this->signal == 1) {													// If a message has been received
			strcpy_s(this->rxBuff, this->txBuff);									// Simulate loopback from txBuff
			printf("\n%s\n", this->rxBuff);
			this->mtx.lock();
			this->signal = 0;														// Reset signal - indicate message read so can read another message
			this->mtx.unlock();
		} else {
			strcpy_s(this->rxBuff, "");												// Clear rxBuff
			printf(".");															// Print a dot to show no message received
		}
	}
	return(timeout_us);
}

/* ************* Transmit function ****************** */
int TxRx::RS232Tx(int timeout_us) {
	int randNum;
	int messageNum = 0;
	char numbuff[20];
	srand(time(NULL));

	// Simulate random message transmission
	printf("\nStarting random transmissions from Tx buffer in another thread ...\n");
	while (true) {
		Sleep(timeout_us);
		randNum = rand() % 10;
		//printf("\nrandnum = %d\n", randNum);
		if (randNum <= 2) {															// Message received
			this->mtx.lock();														// Lock the signal variable 
			this->signal = 1;														// Signal a Transmission
			messageNum++;															// Increment the counter
			this->mtx.unlock();
			//printf("\nNow transmitting bytes\n");
			strcpy_s(this->txBuff, "Message from txBuff #");						// Send the message
			sprintf_s(numbuff, "%d", messageNum);
			strcat_s(this->txBuff, numbuff); 
		}
	}
	
	return(timeout_us);
}

/* ************* Threaded version of the Transmit and Receive functions ****************** */
std::thread TxRx::RS232RxThread(int timeout_us) {
	return std::thread(&TxRx::RS232Rx, this, timeout_us);
}

std::thread TxRx::RS232TxThread(int timeout_us) {
	return std::thread(&TxRx::RS232Tx, this, timeout_us);
}

