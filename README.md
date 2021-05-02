# Digital-Stopwatch

The Objective of this Project is to implement a digital stopwatch based on ATmega16 microcontroller and multiplexed 7-segments modules.

ATmega16 Drivers:
Timer1 CTC Mode is used to count the time for the stopwatch.

Interrupts:

- INT0 (Triggered on falling edge using the internal pull up resistor)         --> reset the stop watch
- INT1 (Triggered on raising edge using the external pull down resistor)   --> pause the stop watch
- INT2 (Triggered on falling edge using the internal pull up resistor)         --> resume the stop watch
