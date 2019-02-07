int rLedPin = 7;
int gLedPin = 6;
int yLedPin = 5;
int bLedPin = 4;
int wLedPin = 2;
int buzzerPin = 8;

int velocity = 2000;
const int MAX_LEVEL = 50;
int sequence[MAX_LEVEL];
int your_sequence[MAX_LEVEL];
int level = 1;
int tones[] = { 262, 330, 392, 494 };
int flash = 0;
int ledState = 0;
int period = 200;
unsigned long time_now = 0;
int co = 0;

void setup()
{
	pinMode(rLedPin, OUTPUT);
	pinMode(gLedPin, OUTPUT);
	pinMode(yLedPin, OUTPUT);
	pinMode(bLedPin, OUTPUT);
	pinMode(wLedPin, OUTPUT);
	pinMode(A0, INPUT);
	pinMode(A1, INPUT);
	pinMode(A2, INPUT);
	pinMode(A3, INPUT);
	allPinsOff();
	digitalWrite(wLedPin, LOW);
	flash = 1;
}


void loop()
{
	if (millis() > time_now + period) {
		time_now = millis();
		ledState = !ledState;
		if (ledState)
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
	if (ledState) {
		digitalWrite(wLedPin, HIGH);
	}
	else {
		digitalWrite(wLedPin, LOW);
	}


	if (level == 1)
		generate_sequence();//generate a sequence;

	if (digitalRead(A4) == LOW || level != 1) //If start button is pressed or you're winning
	{
		flash = 0;
		digitalWrite(wLedPin, LOW);
		show_sequence();    //show the sequence
		get_sequence();     //wait for your sequence

	}

}

void show_sequence()
{

	allPinsOff();

	for (int i = 0; i < level; i++)
	{
		digitalWrite(sequence[i], HIGH);
		delay(velocity);
		digitalWrite(sequence[i], LOW);
		delay(200);
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
				tone(buzzerPin, tones[0], 100);
				digitalWrite(rLedPin, HIGH);
				your_sequence[i] = rLedPin;
				flag = 1;
				delay(200);
				if (your_sequence[i] != sequence[i])
				{
					wrong_sequence();
					flash = 1;
					return;
				}
				digitalWrite(rLedPin, LOW);
			}

			if (digitalRead(A1) == LOW)
			{
				tone(buzzerPin, tones[1], 100);
				digitalWrite(gLedPin, HIGH);
				your_sequence[i] = gLedPin;
				flag = 1;
				delay(200);
				if (your_sequence[i] != sequence[i])
				{
					wrong_sequence();
					flash = 1;
					return;
				}
				digitalWrite(gLedPin, LOW);
			}

			if (digitalRead(A2) == LOW)
			{
				tone(buzzerPin, tones[2], 100);
				digitalWrite(yLedPin, HIGH);
				your_sequence[i] = yLedPin;
				flag = 1;
				delay(200);
				if (your_sequence[i] != sequence[i])
				{
					wrong_sequence();
					flash = 1;
					return;
				}
				digitalWrite(yLedPin, LOW);
			}

			if (digitalRead(A3) == LOW)
			{
				tone(buzzerPin, tones[3], 100);
				digitalWrite(bLedPin, HIGH);
				your_sequence[i] = bLedPin;
				flag = 1;
				delay(200);
				if (your_sequence[i] != sequence[i])
				{
					wrong_sequence();
					flash = 1;
					return;
				}
				digitalWrite(bLedPin, LOW);
			}

		}
	}
	right_sequence();
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
	for (int i = 0; i < 3; i++)
	{
		allPinsOn();
		delay(250);
		allPinsOff();
		delay(250);
	}
	level = 1;
	velocity = 1000;

}

void right_sequence()
{
	allPinsOff();
	delay(250);
	allPinsOn();

	delay(500);
	allPinsOff();
	delay(500);

	if (level < MAX_LEVEL);
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
