# Sound-Activated RGB LED Controller

A simple Arduino-based project that changes the color of an RGB LED in response to sound levels detected by a microphone sensor.

## Hardware Components

- **Arduino Uno (or compatible)**
- **Sound sensor module** connected to analog pin A0
- **Common cathode RGB LED**
- **220Ω resistors** (×3) for LED channels
- Jumper wires and breadboard

## Wiring

1. **Sound Sensor**
   - VCC → 5V
   - GND → GND
   - OUT → A0 (soundSensorPin)

2. **RGB LED**
   - Common cathode → GND
   - Red channel → Digital pin D9 (redPin), via 220Ω resistor
   - Green channel → Digital pin D10 (greenPin), via 220Ω resistor
   - Blue channel → Digital pin D11 (bluePin), via 220Ω resistor

## Code Overview

- **Threshold (`threshold`)**: Minimum sound reading to trigger a color change.
- **Debounce Delay (`debounceDelay`)**: Minimum interval (in ms) between sensor triggers to avoid rapid state changes.
- **State Variable (`state`)**: Tracks current LED mode:
  0. Red
  1. Green
  2. Blue
  3. Off

### Main Logic
1. Read the analog value from the sound sensor.
2. If the reading exceeds the threshold and enough time has passed since the last change:
   - Increment the `state` (cycles 0→1→2→3→0).
   - Update `lastTime` for debouncing.
   - Call `updateColor()` to apply the new LED color.

### `updateColor()` Function
Sets the RGB LED channels HIGH or LOW based on the current `state`:
- **State 0**: Red on, Green off, Blue off
- **State 1**: Red off, Green on, Blue off
- **State 2**: Red off, Green off, Blue on
- **State 3**: All channels off

## Usage

1. Upload the sketch to the Arduino.
2. Ensure the hardware is wired as described.
3. Open the Serial Monitor at 9600 baud to observe sound readings.
4. Make a sound (e.g., clap) louder than the threshold to cycle through LED colors.

## Calibration

- Adjust the `threshold` value to match your environment’s noise level.
- Modify `debounceDelay` to control how quickly the LED responds to successive sounds.
