#include "goHome.hh"

// Constructor for the reactive class. Add any  you need (which
// will probably be stored in a state variable).

PipGoToHome::PipGoToHome() : ArAction("goHome") {
  myRobot = NULL;
// Store any parameters in state variables
}

// This will look the same for any reactive class. Just substitute the
// name of your class for "Drive".

void PipGoToHome::setRobot(ArRobot *robot) {
  myRobot = robot;
  myLaser = myRobot->findRangeDevice("urg2.0_1");                               
                               

  std::list< ArRangeDevice * > *list = myRobot->getRangeDeviceList();

// check if list is empty,else grab first item, set to myLaser, pew pew pew

  if (myLaser == NULL){
    std::cout << "deactivating because there is no laser attached" << std::endl;
    deactivate();
  }
  std::cout << "Message: PipFollow laser check: " << myLaser->getName() << std::endl;
}
  
// This is the key method for your reactive classes, as it defines what
// action should be taken. Again, add the sensing/action code you need.

ArActionDesired *PipGoToHome::fire(ArActionDesired currentDesired) {

// The "myDesired" variable is a place to store the list of actions 
// that you want the robot to take if this rule fires. Initially, we
// must clear any previous actions.
  myDesired.reset();
  myDesired.setVel(500);
  sleep(5);
  myDesired.setVel(0);
  ///ArActionGoto gotoPoseAction("goto",ArPose(0.0, 0.0, 0.0),100,400, 150,7);

// Add your code to access the sonar sensors, decide whether the reaction
// fires, and add commands to myDesired if it does.



  ///std::cout << "Going home ...\n" << std::endl;



  ///myDesired.merge(&gotoPoseAction);




// Return the list of desired actions.
  return &myDesired;
}
