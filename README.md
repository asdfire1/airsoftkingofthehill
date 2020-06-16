# King of the Hill
### This is the code for an Arduino based device which allows to play king of the hill gamemode in airsoft / paintball.
## Operation:
### Connect the power, turn the key / flip the admin switch to closed, if youre using an RGB strip it should glow red. Set the desired goal time using the potentiometer, programmed times: 5, 10, 15, 20, 30, 40, 60 minutes. Turn the key back to open position / flip the switch. Now when one of the teams presses their corresponding button their time will start counting down and the RGB strip will glow their color. Once a team gets to the goal time the RGB strip will blink alternating between the winning team color and red, the buzzer will beep and the display will also show which team won and how much time the other team had. After this the device can be reset using the admin key / switch.

### Parts list:
- 1*Arduino nano
- 2-4*npn transistors (for each team light sources + 1 for buzzer if higher voltage is used)
- 1*piezo buzzer
- 2-4*1k resistors (for the transistors)
- 1*I2C 16X2 LCD
- 2*Push button
- 1*Key switch
- 1*Potentiometer (Value does not reallly matter)
- 2* Team colored leds + resistors
- RGB LED strip or lights for each individual team
- Wires, possibly a prototyping pcb
- Some 12V power source or other voltage (I have used a 4S battery and a step down converter)


### Wiring:
- D12 -base of red light transistor through 1k resistor
- D11 - base of green light transistor through 1k resistor
- D10 - base of blue light transistor through 1k resistor
- D9 - base of buzzer NPN transistor through 1k resistor
- D2 - push button of 1st team, the button should be connected to ground as it uses the internal arduino pullup, this should be an interrupt pin
- D3 - Push button of 2nd team, the button should be connected to ground as it uses the internal arduino pullup, this should be an interrupt pin
- A1 - Settings / Admin reset switch, while closed the goal time can be changed and a team victory is cleared, uses pullup, connect to ground
- A7 - Potentiometer pin used to change goal time
- A4, A5 - I2C LCD pins
