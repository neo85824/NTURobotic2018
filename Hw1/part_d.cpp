#include "Aria.h"

int main(int argc, char **argv)
{
	ArRobot robot;
	ArSonarDevice sonar;

	robot.addRangeDevice(&sonar);

	Aria::init();
	
	ArSimpleConnector connector(&argc,argv);

	if (!connector.connectRobot(&robot)){
		printf("Could not connect to robot... exiting\n");
		Aria::shutdown();
		Aria::exit(1);
	}

	robot.comInt(ArCommands::ENABLE, 1);

	robot.runAsync(false);

  // Used to perform actions when keyboard keys are pressed
  ArKeyHandler keyHandler;
  Aria::setKeyHandler(&keyHandler);

  // ArRobot contains an exit action for the Escape key. It also 
  // stores a pointer to the keyhandler so that other parts of the program can
  // use the same keyhandler.
  robot.attachKeyHandler(&keyHandler);
  printf("You may press escape to exit\n");

	int num_of_sonar = robot.getNumSonar();
	// TODO: control the robot
	while(true)  {
		int input = keyHandler.getKey();
		if(input == 258) {  //left
			robot.lock();
			robot.setRotVel(40);
			robot.unlock();
		}
		else if(input == 259) {  //right
			robot.lock();
			if(robot.getVel() <= 400.0)
			{
				robot.setVel(robot.getVel()+100.0);
			}
			robot.unlock();
		}
		else {
			ArUtil::sleep(300);
			if(robot.getVel() >= 0.0 ){
				if(robot.getVel()-100.0 < 0) {
					robot.setVel(0);
				}
				else robot.setVel(robot.getVel()-100.0);
			}
			if(robot.getRotVel() >= 0.0) {
				if(robot.getRotVel()-5.0 < 0) {
					robot.setRotVel(0);
				}
				else robot.setRotVel(robot.getRotVel() -5.0);
			}

		}
		//check each sonar no.1~6 
 		for(int i=1; i<=6; i++)
		{
			if(robot.getSonarRange(i) <= 1000) 
			{		
				robot.lock();
				robot.setVel(0);
				robot.unlock();
			}
		}
		printf("X:%f Y:%f Vel:%f\n", robot.getX(), robot.getY(), robot.getVel());
	}
			
	// Start of controling

	// 1. Lock the robot

	// 2. Write your control code here, 
	//    e.g. robot.setVel(150);  
	//
	

	// 3. Unlock the robot
	robot.unlock();

	// 4. Sleep a while and let the robot move
	

	// End of controling


	Aria::shutdown();

	Aria::exit(0);
}
