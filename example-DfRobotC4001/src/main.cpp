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
		    while (!mmSensor->begin()){
				ofLog() << "Waiting to connect to sensor ...";
				usleep(1000);
			}
			
			usleep(1000);
			ofLog() << "setSensorMode...";

		    if (!mmSensor->setSensorMode(eSpeedMode))
		    {
				ofLog() << "Failed to setSensorMode";
			}
		    
		    usleep(1000);
			ofLog() << "setDetectThres...";

		    if (!mmSensor->setDetectThres(30, 600, 10))
		    {
				ofLog() << "Failed to setDetectThres";
			}
		    
		    usleep(1000);
			ofLog() << "setFrettingDetection...";

		    mmSensor->setFrettingDetection(eON);
		    
		}

		void update(){
			usleep(1000);
			ofLog() << "Getting Data...";
			if(mmSensor->getTargetNumber() > 0) {
				ofLog() << (int)mmSensor->getTargetNumber();
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
