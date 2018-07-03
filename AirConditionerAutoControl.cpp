#include "AirConditionerAutoControl.h"


AirControl::AirControl(char* ssid, char* pwd)
{
	dht.begin();
	irsend.begin();
}

void AirControl::listen()
{
	int temp = this->getSensorData();
	Serial.print(temp);
	if (temp > TEMP_COLD_MODE_LIMIT)
	{
		if (lastCommand == "shut")
		{
			this->sendIRcommand(irCold28);
			lastCommand = "cold";
		}
	}
	else if (-50 < temp < TEMP_HOT_MODE_LIMIT)
	{
		if (lastCommand == "shut")
		{
			this->sendIRcommand(irHot24);
			lastCommand = "hot";
		}
	}
	else if (TEMP_HOT_MODE_SET < temp < TEMP_COLD_MODE_SET)
	{
		if (lastCommand != "shut")
		{
			this->sendIRcommand(irShut);
			lastCommand = "shut";
		}
	}
}

int AirControl::getSensorData()
{
	//get temp data
	// float humi = dht.readHumidity();
    float temp = dht.readTemperature();
    // int h = (int)humi;
    int t = (int)temp;
    if (isnan(t)) {
      return -500;
    }
	if (t > 75)
	{
		return -500;
	}
	return t;
}

void AirControl::sendIRcommand(uint16_t command[])
{
	//send air conditioner ir signal
	irsend.sendRaw(command, 147, 38);
}


