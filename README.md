EnviroClock is an embedded system project based on the LPC2148 ARM7 microcontroller.
It functions as a real-time digital clock that displays the Time (hh:mm:ss), Date (DD:MM:YYYY), and Day of the Week (Sun–Sat) on a 16x2 LCD.
The project also integrates an LM35 temperature sensor to measure ambient temperature using the microcontroller’s ADC (Analog-to-Digital Converter.
The system is ideal for learning embedded systems concepts such as RTC interfacing, ADC programming, and LCD display control using Embedded C.
⚙️ Features
✅ Displays real-time Time, Date, and Day
✅ Measures Temperature using LM35 sensor
✅ Uses ADC of LPC2148 for analog reading
✅ User-friendly 16x2 LCD Display
✅ Modular code structure for easy understanding
✅ Low power and reliable operation

 Working Principle:
RTC (Real-Time Clock) module provides accurate time and date values.
LM35 Sensor outputs an analog voltage proportional to ambient temperature (10 mV/°C).
The ADC of LPC2148 converts this analog voltage to a digital value.
The microcontroller processes the data and displays Time, Date, Day, and Temperature on the LCD.
The display updates continuously to show real-time information.

Applications:
Digital environmental clock
Home automation systems
Smart temperature and time displays
Educational embedded projects
