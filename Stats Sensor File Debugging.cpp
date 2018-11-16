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
bool backwards_with_check (int state[BITS], int & minus_counter) {
	
	static int i = 0;	// "Static" initializes i once in function and future calls to the function use previous value of i
	const int EXPECTED[STATES][BITS] = {{0,1}, {0,0}, {1,0}, {1,1}};	// Input correct sequence (currently using assumed values)
	int a = 0;
	
	if (i == 0 || i == 1)
		a = i + 4;
	else
		a = i;
	
	// cout << state[1] << " " << EXPECTED[a-2][0] << " " << EXPECTED[i][0] << endl;
	// cout << state[0] << " " << EXPECTED[a-2][1] << " " << EXPECTED[i][1] << endl;	

	if ((state[1] == EXPECTED[a-2][0]) && (state[0] == EXPECTED[a-2][1])) {
		minus_counter++;
		i--;
		// cout << "UEAAEGEGSG" << endl;
		if (i == -1)
			i = 3;
		a = 0;
		return 0;
	}

	
	if ((state[1] != EXPECTED[i][0]) || (state[0] != EXPECTED[i][1])) 
		return 1;
	i++;
	if (i == 4)
		i = 0;
	a = 0;
	return 0;
}

int main() {
	
	ifstream fin("sensor.txt");
	if (!fin)
	{
		cout << "No file";
		return EXIT_FAILURE;
	}
	
	int prev_state[BITS] = {0};
	int state[BITS] = {0};
	int total_dist = 0, counter = 0, minus_counter = 0;
	bool B1 = 0, B2 = 0, L1, L2;
	int j = 0, first = 0;
	// B1 is start button, B2 is reset button
	// L1 is light 1, l2 is light 2
	
	// while (B1 == 0) {}	// Do nothing until start button is pressed
	
	// Set prev_state to first black/white combination
	prev_state[1] = L1;	// Set prev_state to first black/white combination
	prev_state[0] = L2;
	
	// While loop until reset button is pressed
	while (j < 1000) {	
		
		// Set state to current black/white combination and compare to prev_state
		fin >> state[1];
		fin >> state[0];
		
		if (state != prev_state || first > 0) {
			
			first = backwards_with_check(state, minus_counter);
			if ( first == true) {
				cout << "ERROR: Skipped Sequence" << endl;
				return EXIT_FAILURE;	// End Program
			}
			
			counter++;
			memcpy(prev_state, state, sizeof(prev_state));	// Sets prev_state equal to state, C++ does not all "prev_state = state"
		}
		j++;
		// cout << minus_counter << "Counter <-" << endl;
		// cout << counter << endl;
		cout << (counter - 2 * minus_counter ) << endl;
		// cout << j << endl;
	}
	
	total_dist = DIST * (counter - 2 * minus_counter);
	cout << "Total distance is " << total_dist;	
	

	fin.close();
	
	return EXIT_SUCCESS;
}
