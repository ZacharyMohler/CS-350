# CS-350 (Embedded Systems)

## Summarize the project and what problem it was solving.
In this repository there are two codebases. Both utilized Texas Instruments' Code Composer Studio, and a Texas Instruments board "TI SimpleLink Wi-Fi CC3220S"

### One for a GPIO project that displays a morse code message depending on which button was pressed.
This project uses a C implementation of a state machine for the logic. When run the LEDs on the board display the message "SOS" in morse code. When the button is pressed it completes the SOS message, then changes to display "OK". 

### The other is a project involving PWMLED, UART, and TIMER aspects to achieve the functionality of a thermostat. 
This project uses a UART to display the current temperature, the temperature set point, the binary indicator of the 'heater' LED (1/0), and the time elapsed (in seconds) since the program began running. When the measured temperature is below the set point, an LED is activated to indicate the 'heater' turning on. When the temperature rises above the set point, the 'heater' LED is turned off.

## What did you do particularly well?
I think my code was very neat and readable, as well as stuck close to standards of best practice.

## Where could you improve?
I could always do with expanding to a more in-depth knowledge of embedded systems programming. I would consider my current knowledge only beginner.

## What tools and/or resources are you adding to your support network?
The main resource I used (and this is common to most platforms I'm developing with/for) was Texas Instruments published documentation. 

## What skills from this project will be particularly transferable to other projects and/or course work?
Development and debugging for embedded systems, practical application of state machines in code, and diagramming state machine and timing diagrams. 

## How did you make this project maintainable, readable, and adaptable?
By adhering to the standards of best practice in developing for embedded systems—as well as very clean, neat, and commented code.
