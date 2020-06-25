/*--------------------------------------------------------------------
Copyright 2020 fukuen
eSpeak demo is free software: you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation, either version 3 of the
License, or (at your option) any later version.
This software is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with This software.  If not, see
<http://www.gnu.org/licenses/>.
--------------------------------------------------------------------*/

#include <Arduino.h>
#include <MaixCube_eSpeak.h>
#include <Wire.h>

MaixCubeESpeak speak;

#define AXP173_ADDR 0x34

void axp173_init() {
  Wire.begin((uint8_t) SDA, (uint8_t) SCL, 400000);
  Wire.beginTransmission(AXP173_ADDR);
  int err = Wire.endTransmission();
  if (err) {
    Serial.printf("Power management ic not found.\n");
    return;
  }
  Serial.printf("AXP173 found.\n");
  // Clear the interrupts
  Wire.beginTransmission(AXP173_ADDR);
  Wire.write(0x46);
  Wire.write(0xFF);
  Wire.endTransmission();
  // set target voltage and current of battery(axp173 datasheet PG.)
  // charge current (default)780mA -> 190mA
  Wire.beginTransmission(AXP173_ADDR);
  Wire.write(0x33);
  Wire.write(0xC1);
  Wire.endTransmission();
  // REG 10H: EXTEN & DC-DC2 control
  Wire.beginTransmission(AXP173_ADDR);
  Wire.write(0x10);
  Wire.endTransmission();
  Wire.requestFrom(AXP173_ADDR, 1, 1);
  int reg = Wire.read();
  Wire.beginTransmission(AXP173_ADDR);
  Wire.write(0x10);
  Wire.write(reg & 0xFC);
  Wire.endTransmission();
}

void setup() {
	pll_init();
	plic_init();
    uarths_init();
    axp173_init();

	speak.begin();

	sleep(1);
	speak.speak("Hello.");

	sleep(1);
	speak.speak("One two three.");

	sleep(1);
	speak.speak("I'm maix cube.");

}

void loop() {
  // put your main code here, to run repeatedly:
}