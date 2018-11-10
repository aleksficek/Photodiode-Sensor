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

