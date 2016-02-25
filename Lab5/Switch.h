// Switch.h
// Runs on TM4C123
// Switches Driver
// John Starich and Jon Ambrose
// February 24, 2016

#include <stdbool.h>

/** The different kinds of buttons we can press. */
typedef enum {
	Play,
	Stop,
	Rewind
} Button;

/**
 * Initialize the switches on the correct port, the pins, and the
 * interrupts necessary to handle button presses.
 */
void Switch_Init(void);

/**
 * Return whether or not the request button is pressed.
 */
bool Switch_Pressed(Button buttonToCheck);

/**
 * Acknowlege a button being pressed so a subsequent call to Switch_Pressed
 * would return false if the button was still held down.
 */
void Switch_AcknowledgePressed(Button buttonToAcknowledge);
