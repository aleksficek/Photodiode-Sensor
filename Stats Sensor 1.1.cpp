#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std; 

const int DIST = 5;
const int BITS = 2;

int main() {
	
	int prev_state[BITS] = {0};
	int state[BITS] = {0};
	int total_dist = 0, counter = 0;
	bool B1 = 0, B2 = 0, L1, L2;
	// B1 is start button
	// B2 is reset button
	// L1 is light 1
	// l2 is light 2
	
	while (B1 == 0) {}
	
	prev_state[1] = L1;
	prev_state[0] = L2;
	
	while (B2 != 1) {
		
		state[1] = L1;
		state[0] = L2;
		
		if (state != prev_state) {
			counter++;
			prev_state = state;
		}
	}
	
	total_dist = DIST * counter;
	
	cout << "Total distance is " << total_dist;	
		
	return EXIT_SUCCESS;
}
