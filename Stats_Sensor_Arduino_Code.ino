const int DIST = 5;
const int BITS = 2;
const int STATES = 4;
String error_text = "ERROR: Skipped Sequence";

// INPUT CORRECT PIN NUMBERS FOR PHOTODIODES!
int Pin_L1 = 13, Pin_L2 = 14;

// INPUT CORRECT INITIAL STATE VALUES (WHEN IN INITIAL POSITION)!
int prev_state[BITS] = {0};

int state[BITS] = {0};
int total_dist = 0, counter = 0, minus_counter = 0;
bool failure = 0;


void setup() {

  pinMode(Pin_L1, INPUT);
  pinMode(Pin_L2, INPUT);
  Serial.begin(9600);

  prev_state[1] = digitalRead(Pin_L1);
  prev_state[0] = digitalRead(Pin_L2);
  
}


void loop() {

  state[1] = digitalRead(Pin_L1);
  state[0] = digitalRead(Pin_L2);

  if (state != prev_state) {
  
    failure = backwards_with_check(state, minus_counter);
    if (failure == true) {
      Serial.println(error_text);
      // Consider Ending Program Here
    }
    
    counter++;

    // Sets prev_state equal to state, C++/Arduino does not all "prev_state = state"
    memcpy(prev_state, state, sizeof(prev_state));  
    
    state[1] = prev_state[1];
    state[0] = prev_state[0];
  }
  
  total_dist = DIST * (counter - 2 * minus_counter);
  Serial.println(total_dist);
}


bool backwards_with_check (int state[BITS], int & minus_counter) {
  // This function counts backward motion and checks for error (skipped combination in sequence)
  
  static int i = 0; // "Static" initializes i once in function and future calls to the function use previous value of i

  // INPUT CORRECT SEQUENCE (ASSUMED SEQUENCE CURRENTLY USED)!
  const int EXPECTED[STATES][BITS] = {{0,1}, {0,0}, {1,0}, {1,1}};
  
  int a = 0;

  // This if statement decides the location of the binary pair when starting to move backwards
  if (i == 0 || i == 1)
    a = i + 4;
  else
    a = i;

  if ((state[1] == EXPECTED[a-2][0]) && (state[0] == EXPECTED[a-2][1])) {
    minus_counter++;
    i--;
    if (i == -1)
      i = 3;
    a = 0;
    return 0;
  }

  // Return error if state is not equal to expected and checking for backwards motion was false
  if ((state[1] != EXPECTED[i][0]) || (state[0] != EXPECTED[i][1])) 
    return 1;
    
  i++;
  // Reset static i to 0 if length of combination array has been reached
  if (i == 4)
    i = 0;
    
  a = 0;
  return 0;
  
}
