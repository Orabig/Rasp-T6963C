Rasp-T6963C
===========

C library for driving a T6963C-based LCD screen from a Raspberry Pi.

I successfully run it to control a **DG-24128-01 Datavision** LCD display, and control it from my Raspberry.

flow diagram
------------

![Flow diagram](https://raw.githubusercontent.com/Orabig/Rasp-T6963C/master/doc/Rasp-T6963C-1.png)

As you can see, the T6963C need 3 separate power supplies :
* +5V for logic
* -15V for LCD (this power can easily be achieved from a +5V with the aid of a **TL497 chip**)
* a 75V AC for the backlight. You'll need a CCFL for this, which cannot be powered from a +5V. In my case, I found you that could be driven with a +12V tension)

The T6963C needs at least 10 control data lines (12 is better, however, FNT and REV are optional and may be hard-wired)

To spare several GPIO outputs on the raspberry, I chose to use an **HC595 shift register**, which can generate 8 data lines from 3 coming from the raspberry :

![HC595 wiring](https://raw.githubusercontent.com/Orabig/Rasp-T6963C/master/doc/Rasp-T6963C-2.png)

Finally, here is the wiring schema for the T6963C.

![T6963C wiring](https://raw.githubusercontent.com/Orabig/Rasp-T6963C/master/doc/Rasp-T6963C-3.png)

Some inputs are hard-wired :

| Pin          | Value     | Explanation |
| ------------- | ----------- | ---------------------------------------------- |
| /RD  (Read)  | 1 (=5V)  | We never set the display in READ mode |
| /WR (Write)  | 0 (=0V)  | For the same reason, the display is always in WRITE mode |
| RST (Reset)  | 1 (=5V)  | Attached to +5V through a capacitor/resistor network (100nF/10kΩ). See T6963C data sheet. |
