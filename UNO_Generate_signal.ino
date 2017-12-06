
int SPEAKER = 12;    // The speaker is on pin 12

int freq = 10;      // Starting frequency

void setup()
{
    pinMode(SPEAKER, OUTPUT);
}

void loop()
{
    freq += 50;      // add 50 to freq

    if (freq >30000)
    {
        noTone(SPEAKER);
        freq = 10;
    }

    tone(SPEAKER, freq);

    delay(100);
}

