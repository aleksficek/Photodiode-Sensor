#include <iostream>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std; 

const int DIST = 5;
const int BITS = 2;
const int STATES = 4;

// If error return true, otherwise return false
bool error_check (int state[BITS]) {
	
	static int i = 0;	// "Static" initializes i once in function and future calls to the function use previous value of i
	const int EXPECTED[STATES][BITS] = {{0,1}, {0,0}, {1,0}, {1,1}};	// Input correct sequence (currently using assumed values)
	
	if (state[1] != EXPECTED[i][0]) 
		return 1;
	if (state[0] != EXPECTED[i][1]) 
		return 1;
	
	i++;
	if (i == 4)
		i = 0;
		
	return 0;
}

int main() {
	
	int prev_state[BITS] = {0};
	int state[BITS] = {0};
	int total_dist = 0, counter = 0;
	bool B1 = 0, B2 = 0, L1, L2;
	// B1 is start button, B2 is reset button
	// L1 is light 1, l2 is light 2
	
	while (B1 == 0) {}	// Do nothing until start button is pressed
	
	// Set prev_state to first black/white combination
	prev_state[1] = L1;	// Set prev_state to first black/white combination
	prev_state[0] = L2;
	
	// While loop until reset button is pressed
	while (B2 != 1) {	
		
		// Set state to current black/white combination and compare to prev_state
		state[1] = L1;
		state[0] = L2;
		
		if (state != prev_state) {
			
			if (error_check(state) == true) {
				cout << "ERROR: Skipped Sequence" << endl;
				return EXIT_FAILURE;	// End Program
			}
			
			counter++;
			memcpy(prev_state, state, sizeof(prev_state));	// Sets prev_state equal to state, C++ does not all "prev_state = state"
		}
	}
	
	total_dist = DIST * counter;
	cout << "Total distance is " << total_dist;	
		
	return EXIT_SUCCESS;
}
