#include "Aria.h"
#include <math.h>       /* acos */


#define PI 3.14159265

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
  //ArKeyHandler keyHandler;
  //Aria::setKeyHandler(&keyHandler);

  // ArRobot contains an exit action for the Escape key. It also 
  // stores a pointer to the keyhandler so that other parts of the program can
  // use the same keyhandler.
  //robot.attachKeyHandler(&keyHandler);
  //printf("You may press escape to exit\n");

	// TODO: control the robot
	double x,y,th;
	scanf("%lf %lf %lf",&x,&y,&th);
	printf("%f %f %f\n", robot.getX(), robot.getY(), robot.getTh());
	
	double orient = atan (y/x) * 180.0 / PI;
	
	robot.lock();
	robot.setHeading(orient);
	robot.unlock();
	while (1)
	{
		robot.lock();
		if (robot.isHeadingDone())
		{
			robot.unlock();
			break;
		}
		robot.unlock();
	}	
	
	robot.lock();
	robot.setVel(sqrt((x-2)*(x-2)+(y-1)*(y-1)));
	robot.unlock();
	while(1)
	{
		
		if(abs(robot.getX()) > abs(x-2) || abs(robot.getY()) > abs(y-1))
		{
			robot.setVel(0);
			break;
		}
		printf("%f %f %f\n", robot.getX(), robot.getY(), robot.getTh());
	}
	ArUtil::sleep(300);

	robot.lock();
	robot.setHeading(th * 180.0 / PI);
	robot.unlock();
	while (1)
	{
		robot.lock();
		if (robot.isHeadingDone())
		{
			robot.unlock();
			break;
		}
		robot.unlock();
	}	
	
	robot.lock();
	robot.setRotVel(1);
	robot.unlock();
	while (1)
	{	
		
		if( abs(robot.getTh() - (fmod(th,6.28) * 180.0 / PI)) <= 1 ) 
		{
			robot.setRotVel(0);
			break;
		}
		printf("%f %f %f\n", robot.getX(), robot.getY(), robot.getTh());
	}	
	printf("result: %f %f %f\n", robot.getX(), robot.getY(), robot.getTh());
	
	

			
	// Start of controling

	// 1. Lock the robot

	// 2. Write your control code here, 
	//    e.g. robot.setVel(150);  
	//
	

	// 3. Unlock the robot

	// 4. Sleep a while and let the robot move
	

	// End of controling


	Aria::shutdown();

	Aria::exit(0);
}
