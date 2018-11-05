#pragma once
#include <Timers.h>
#include <vector>

//LEDS PINS
constexpr auto RED_ENTRY = 8; //Dont drive! (Entry)
constexpr auto GREEN = 7; //Drive! (Entry)

constexpr auto RED_EXIT = 6; //Dont drive! (EXIT)
constexpr auto BLUE = 5; //Drive! (Exit)

//SENSORS PINS
constexpr auto ENTRY = A0;
constexpr auto EXIT = A1;

//Default variables
int parkingCount = 0; //Number of cars on parking
int parkingCapacity = 50; //Number of maximal amount cars on parking
int timeBetwenTwoCarsEntryInSeconds = 5; //Amount of time for car to drive into parking
int timeBetwenTwoCarsExitInSeconds = 4; //Amount of time for car to drive out from parking

//Create vector (package) of elements
std::vector<int> LEDs; //Pins of LEDs in one place
std::vector<prog_uint8_t> Sensors; //Pins of Sensors in one place

//Crete a timers
Timer entryTime; //Create timer (entry)
Timer leaveTime; //Create timer (leave)

//Create boolean for time check (time{timeName}.time())
bool isTimeEnd = false;

//Default arduino setup function
void setup() {
	//Start timers
	entryTime.begin(SECS(timeBetwenTwoCarsEntryInSeconds));
	leaveTime.begin(SECS(timeBetwenTwoCarsExitInSeconds);

	//Add LEDs to LEDs 
	LEDs.push_back(RED_ENTRY);
	LEDs.push_back(GREEN);
	LEDs.push_back(RED_EXIT);
	LEDs.push_back(BLUE);

	//Say Arduino what pins are use for LEDs
	for (auto x : LEDs) {
		pinMode(x, OUTPUT);
	}

	//Add sensors to Sensoes vector
	/*
		ATTENTION! program use photoresitor!, need implementation
	*/

	//Open comunication port with PC/Laptop/Phone
	Serial.begin(115200);

	//LEDs check
	Serial.println("LEDs test");
	Serial.println("LED would blink 5 times!");
	for (int i = 0; i <= 5; i++) {
		for (auto x : LEDs)
			digitalWrite(x, HIGH);
		Sleep(300);
		for (auto x : LEDs)
			digitalWrite(x, LOW);
		Sleep(300);
	}
	Serial.println("If LEDs didn't blink TURN OFF POWER SUPPLY!, check them and conections!");

	//Time for user to turn of an circuit if he have some issuses
	Sleep(5000);
}

//Give resistantion from photoresistor
int sensorRead(prog_uint8_t sensor) {
	return analogRead(sensor);
}

//Control of Entry LEDs
void entry() {
	//Chceck state of entryTime
	isTimeEnd = entryTime.available();

	if (sensorRead(ENTRY) < 5 && isTimeEnd ) {
		entryTime.restart();
		digitalWrite(RED_ENTRY, LOW);
		digitalWrite(BLUE, HIGH);
		parkingCount++;
	}
	else if(!isTimeEnd) {
		digitalWrite(RED_ENTRY, LOW);
		digitalWrite(BLUE, HIGH);
	}
	else {
		digitalWrite(RED_ENTRY, HIGH);
		digitalWrite(BLUE, LOW);
	}

	return;
}

//Default arduio loop function
void loop() {
	entry();
	//exit()
	Sleep(30);
	Serial.println(parkingCount);
}