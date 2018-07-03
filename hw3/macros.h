// Serial
#define BAUD_RATE 9600

// Pins
#define X A1
#define Y A4
#define Z A5
#define THUMB A2
#define PALM A3
#define PHOTOR A7
#define LED 13
#define NUM_DIGINPUTS 4
const int dig_pins[] = {0, 1, 5, 6};

// WASD directions
#define UP 'w'
#define LEFT 'a'
#define RIGHT 'd'
#define DOWN 's'
const char arrowkey[] = {RIGHT, DOWN, UP, LEFT};

// Other buttons (N64 emu specific)
#define C_UP 'i'
#define C_LEFT 'j'
#define C_RIGHT 'l'
#define C_DOWN 'k'
#define Z_TRIG ' '
#define L_TRIG 'z'
#define R_TRIG '/'
#define A_BTTN '.'
#define B_BTTN ','
const char special[] = {A_BTTN, DOWN, UP, B_BTTN};

// LPFs for Accelerometer
const float lpfFreq = 5.0; // cutoff frequency = 5 Hz
FilterOnePole lpfx(LOWPASS, lpfFreq);
FilterOnePole lpfy(LOWPASS, lpfFreq);
FilterOnePole lpfz(LOWPASS, lpfFreq);

// Accelerometer Thresholds
#define TH_UP -15
#define TH_LEFT -50
#define TH_RIGHT 15
#define TH_DOWN 30

// debouncers
#define DEBOUNCE_INTVERVAL 5
Bounce * buttons = new Bounce[NUM_DIGINPUTS];

// Keyboard
#define UPDATE_PERIOD 100 // ms

// Photoresistor
#define PHOTOR_DARK 733

// FSR
#define FSR_PRESS 500
