# PushButton

The `PushButton` class provides functionality to handle push button inputs with support for short and long press detection.

## File: PushButton.cpp

This file contains the implementation of the `PushButton` class methods.

### Class Methods

#### `void Initialise(int pin, byte notification, int longPressStart, int longPressEnd)`

Initializes the push button with the specified parameters.

- `pin`: The Arduino pin number connected to the button.
- `notification`: Bitwise flags to enable short press and/or long press notifications.
- `longPressStart`: The duration (in milliseconds) to start considering a long press.
- `longPressEnd`: The duration (in milliseconds) to confirm a long press.

#### `int CheckState()`

Checks the current state of the button and returns the button state.

- Returns: An integer representing the button state (NO_CHANGE, SHORT_PRESS, LONG_PRESS_PENDING, or LONG_PRESS).

### State Machine

The `CheckState()` method implements a state machine to handle different button states:

1. IDLE: Waiting for a button press.
2. BUTTON_DOWN: Button has been pressed, waiting for release or long press.
3. LONG_PRESS: Long press detected, waiting for the long press end time.
4. ZOMBIE: Long press completed, waiting for button release.

### Debouncing

The implementation includes basic debouncing by checking if the button state has remained stable for at least 50 milliseconds before registering a change.

### Usage

To use the `PushButton` class:

1. Include the `PushButton.hpp` header in your Arduino sketch.
2. Create a `PushButton` object.
3. Call the `Initialise()` method to set up the button.
4. Regularly call the `CheckState()` method in your `loop()` function to detect button presses.
