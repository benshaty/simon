#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27,16,2);

int rLedPin = 7;
int gLedPin = 6;
int yLedPin = 5;
int bLedPin = 4;
int easyLedPin = 2;
int hardLedPin = 11;
int buzzerPin = 8;

int velocity = 1000;
const int MAX_LEVEL = 50;
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level = 0;
int tones[] = { 1900, 1700, 1600, 1500 };
int flash = 0;
int ledState = 0;
int period = 200;
unsigned long time_now = 0;
int co = 0;
int easy = 1;

void setup()
{
	pinMode(rLedPin, OUTPUT);
	pinMode(gLedPin, OUTPUT);
	pinMode(yLedPin, OUTPUT);
	pinMode(bLedPin, OUTPUT);
	pinMode(easyLedPin, OUTPUT);
	pinMode(hardLedPin, OUTPUT);
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	pinMode(A3, INPUT);
	pinMode(9, INPUT);
	
	allPinsOff();
	digitalWrite(easyLedPin, LOW);
	digitalWrite(hardLedPin, LOW);
	flash = 1;
	lcd.begin();   // iInit the LCD for 16 chars 2 lines
	lcd.backlight();   // Turn on the backligt (try lcd.noBaklight() to turn it off)
	lcd.setCursor(0, 0); //First line
	lcd.print("Simon Game!");
	lcd.setCursor(0, 1); //Second line
	lcd.print("Good luck");
	delay(1500);
}


void loop()
{
	if (millis() > time_now + period) {
		time_now = millis();
		ledState = !ledState;
		if (ledState && co < 10 && flash)
		{
			if (co % 2) {
				tone(buzzerPin, 1000, 50);
			}
			else {
				tone(buzzerPin, 500, 50);
			}
			co++;
		}
	}
	if (!flash) {
		ledState = 0;
	}
	else {
		lcd.setCursor(0, 0); //First line
		lcd.print("Simon Game!");
		lcd.setCursor(0, 1); //Second line
		lcd.print("Press btn");
	}
	if (ledState) {
		digitalWrite(easyLedPin, HIGH);
		digitalWrite(hardLedPin, HIGH);
	}
	else {
		digitalWrite(easyLedPin, LOW);
		digitalWrite(hardLedPin, LOW);
	}


	if (level == 0)
		generate_sequence();//generate a sequence;
	if (!level) {
		if (digitalRead(9) == LOW)
		{
			easy = 1;
			flash = 0;
			digitalWrite(easyLedPin, LOW);
			digitalWrite(hardLedPin, LOW);
			level = 1;
		}
		if (digitalRead(10) == LOW)
		{
			easy = 0;
			flash = 0;
			digitalWrite(easyLedPin, LOW);
			digitalWrite(hardLedPin, LOW);
			level = 1;
		}
	}
	
	if (level != 0) {
		show_sequence();    //show the sequence
		get_sequence();     //wait for your sequence
	}

}

void show_sequence()
{

	allPinsOff();
	/* easy mode */
	if (easy) {
		for (int i = 0; i < level; i++)
		{
			digitalWrite(sequence[i], HIGH);
			delay(velocity);
			digitalWrite(sequence[i], LOW);
			delay(200);
		}
	}
	else {
		/* hard mode */
		digitalWrite(sequence[level-1], HIGH);
		delay(velocity);
		digitalWrite(sequence[level-1], LOW);
		delay(400);
	}
}

void get_sequence()
{
	int flag = 0; //this flag indicates if the sequence is correct

	for (int i = 0; i < level; i++)
	{
		flag = 0;
		while (flag == 0)
		{
			if (digitalRead(A0) == LOW)
			{
				tone(buzzerPin, tones[0], 50);
				digitalWrite(rLedPin, HIGH);
				your_sequence[i] = rLedPin;
				delay(200);
				if (your_sequence[i] != sequence[i])
				{
					wrong_sequence();
					flash = 1;
					return;
				}
				flag = 1;
				digitalWrite(rLedPin, LOW);
			}

			if (digitalRead(A1) == LOW)
			{
				tone(buzzerPin, tones[1], 50);
				digitalWrite(gLedPin, HIGH);
				delay(200);
				your_sequence[i] = gLedPin;
				if (your_sequence[i] != sequence[i])
				{
					wrong_sequence();
					flash = 1;
					return;
				}
				flag = 1;
				digitalWrite(gLedPin, LOW);
			}

			if (digitalRead(A2) == LOW)
			{
				tone(buzzerPin, tones[2], 50);
				digitalWrite(yLedPin, HIGH);
				delay(200);
				your_sequence[i] = yLedPin;
				if (your_sequence[i] != sequence[i])
				{
					wrong_sequence();
					flash = 1;
					return;
				}
				flag = 1;
				digitalWrite(yLedPin, LOW);
			}

			if (digitalRead(A3) == LOW)
			{
				tone(buzzerPin, tones[3], 50);
				digitalWrite(bLedPin, HIGH);
				delay(200);
				your_sequence[i] = bLedPin;
				if (your_sequence[i] != sequence[i])
				{
					wrong_sequence();
					flash = 1;
					return;
				}
				flag = 1;
				digitalWrite(bLedPin, LOW);
			}

		}
	}
	if (flag) {
		right_sequence();
	}
}

void generate_sequence()
{
	randomSeed(millis());
	for (int i = 0; i < MAX_LEVEL; i++)
	{
		sequence[i] = random(4, 8);
	}
}

void wrong_sequence()
{
	lcd.clear();
	lcd.setCursor(0, 0); //First line
	lcd.print("OHHHHHHH!!!!");
	lcd.setCursor(0, 1); //Second line
	lcd.print("You Lose!");
	int loseTone[] = { 261, 277, 294, 311, 330, 349, 370, 392, 415, 440 };
	for (int lt = 10;lt > 0;lt--) {
		tone(buzzerPin, loseTone[lt], 100);
		delay(120);
	}
	for (int i = 0; i < 3; i++)
	{
		allPinsOn();
		delay(250);
		allPinsOff();
		delay(250);
	}
	level = 0;
	velocity = 1000;
	co = 0;
	delay(1000);
}

void right_sequence()
{
	lcd.clear();
	lcd.setCursor(0, 0); //First line
	lcd.print("Cool!!!");
	lcd.setCursor(0, 1); //Second line
	lcd.print("Level: ");
	lcd.print(level);
	//play the 1Up noise
	allPinsOff();
	tone(buzzerPin, 1318, 150);   //E6
	delay(175);
	allPinsOn();
	tone(buzzerPin, 1567, 150);   //G6
	delay(175);
	tone(buzzerPin, 2637, 150);   //E7
	delay(175);
	tone(buzzerPin, 2093, 150);   //C7
	delay(175);
	allPinsOff();
	tone(buzzerPin, 2349, 150);   //D7
	delay(175);
	tone(buzzerPin, 3135, 500);   //G7


	delay(200);

	if (level < MAX_LEVEL)
		level++;

	velocity -= 50; //increase difficulty
	

}

void allPinsOn() {
	digitalWrite(rLedPin, HIGH);
	digitalWrite(gLedPin, HIGH);
	digitalWrite(yLedPin, HIGH);
	digitalWrite(bLedPin, HIGH);
}

void allPinsOff() {
	digitalWrite(rLedPin, LOW);
	digitalWrite(gLedPin, LOW);
	digitalWrite(yLedPin, LOW);
	digitalWrite(bLedPin, LOW);
}
