#include "ofMain.h"
#include "ofAppNoWindow.h"
#include "DFRobot_C4001.h"

class ofApp : public ofBaseApp
{
        public:
		DFRobot_C4001_I2C* mmSensor;

		void setup()
		{
			/*
		     * The Df Robot sensor has a switch 
		     * for address selection a maximum
		     * of two sensors on I2C: address = 0x2A || 0x2B
		     */

		    mmSensor = new DFRobot_C4001_I2C("/dev/i2c-1", 0x2A);
		    mmSensor->begin();
		    mmSensor->setSensorMode(eSpeedMode);
		    mmSensor->setDetectThres(30, 600, 10);
		    mmSensor->setFrettingDetection(eON);
		}

		void update(){
			if(mmSensor->getTargetNumber() > 0) {
				ofLog() << mmSensor->getTargetRange();
			}
		}

		void exit(){
			ofExit(0);
		}
};

int main( ){
    ofAppNoWindow w;
	ofSetupOpenGL(&w,0,0, OF_WINDOW);
	ofRunApp( new ofApp() );
}
