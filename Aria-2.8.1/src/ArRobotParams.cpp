/*
Adept MobileRobots Robotics Interface for Applications (ARIA)
Copyright (C) 2004, 2005 ActivMedia Robotics LLC
Copyright (C) 2006, 2007, 2008, 2009, 2010 MobileRobots Inc.
Copyright (C) 2011, 2012, 2013 Adept Technology

     This program is free software; you can redistribute it and/or modify
     it under the terms of the GNU General Public License as published by
     the Free Software Foundation; either version 2 of the License, or
     (at your option) any later version.

     This program is distributed in the hope that it will be useful,
     but WITHOUT ANY WARRANTY; without even the implied warranty of
     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
     GNU General Public License for more details.

     You should have received a copy of the GNU General Public License
     along with this program; if not, write to the Free Software
     Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

If you wish to redistribute ARIA under different terms, contact 
Adept MobileRobots for information about a commercial version of ARIA at 
robots@mobilerobots.com or 
Adept MobileRobots, 10 Columbia Drive, Amherst, NH 03031; +1-603-881-7960
*/
#include "ArExport.h"


#include "ariaOSDef.h"
#include "ArRobotParams.h"
#include "ariaInternal.h"
#include <sstream>

bool ArRobotParams::ourUseDefaultBehavior = true;
std::string ourPowerOutputDisplayHint;

void ArRobotParams::internalSetUseDefaultBehavior(bool useDefaultBehavior,
    const char *powerOutputDisplayHint)
{
  ourUseDefaultBehavior = useDefaultBehavior;
  ourPowerOutputDisplayHint = powerOutputDisplayHint;

  ArLog::log(ArLog::Normal, 
	     "ArRobotParams: Setting use default behavior to %s, with power output display hint '%s'", 
	     ArUtil::convertBool(ourUseDefaultBehavior),
	     ourPowerOutputDisplayHint.c_str());
}

bool ArRobotParams::internalGetUseDefaultBehavior(void)
{
  return ourUseDefaultBehavior;
}

AREXPORT ArRobotParams::ArRobotParams() :
  ArConfig(NULL, true),
  mySonarUnitGetFunctor(this, &ArRobotParams::getSonarUnits),
  mySonarUnitSetFunctor(this, &ArRobotParams::parseSonarUnit),
  myIRUnitGetFunctor(this, &ArRobotParams::getIRUnits),
  myIRUnitSetFunctor(this, &ArRobotParams::parseIRUnit),
  myCommercialProcessFileCB(this, &ArRobotParams::commercialProcessFile)
{
  myCommercialConfig = NULL;

  sprintf(myClass, "Pioneer");
  mySubClass[0] = '\0';
  myRobotRadius = 250;
  myRobotDiagonal = 120;
  myRobotWidth = 400;
  myRobotLength = 500; 
  myRobotLengthFront = 0; 
  myRobotLengthRear = 0; 
  myHolonomic = true;
  myAbsoluteMaxVelocity = 0;
  myAbsoluteMaxRVelocity = 0;
  myHaveMoveCommand = true;
  myAngleConvFactor = 0.001534;
  myDistConvFactor = 1.0;
  myVelConvFactor = 1.0;
  myRangeConvFactor = 1.0;
  myVel2Divisor = 20;
  myNumSonar = 0;
  myGyroScaler = 1.626;
  myTableSensingIR = false;
  myNewTableSensingIR = false;
  myFrontBumpers = false;
  myNumFrontBumpers = 5;
  myRearBumpers = false;
  myNumRearBumpers = 5;
  myNumSonarUnits = 0;
  // MPL TODO why do we need these counts?
  mySonarBoardCount = 0;
  myBatteryMTXBoardCount = 0;
  myLCDMTXBoardCount = 0;
  mySonarMTXBoardCount = 0;

  mySonarMap.clear();

  myNumIR = 0;
  myIRMap.clear();

  
  myRequestIOPackets = false;
  myRequestEncoderPackets = false;
  mySwitchToBaudRate = 38400;

  mySettableVelMaxes = true;
  myTransVelMax = 0;
  myRotVelMax = 0;

  mySettableAccsDecs = true;
  myTransAccel = 0;
  myTransDecel = 0;
  myRotAccel = 0;
  myRotDecel = 0;

  myHasLatVel = false;
  myLatVelMax = 0;
  myLatAccel = 0;
  myLatDecel = 0;
  myAbsoluteMaxLatVelocity = 0;

  myGPSX = 0;
  myGPSY = 0;
  strcpy(myGPSPort, "COM2");
  strcpy(myGPSType, "standard");
  myGPSBaud = 9600;

  //strcpy(mySonarPort, "COM2");
  //strcpy(mySonarType, "standard");
  //mySonarBaud = 115200;
			
  //strcpy(myBatteryMTXBoardPort, "COM1");
  //strcpy(myBatteryMTXBoardType, "mtxbatteryv1");
  //myBatteryMTXBoardBaud = 115200;

  strcpy(myCompassType, "robot");
  strcpy(myCompassPort, "");

  if (ourUseDefaultBehavior)
    internalAddToConfigDefault();
}

AREXPORT ArRobotParams::~ArRobotParams()
{

}


void ArRobotParams::internalAddToConfigDefault(void)
{
  addComment("Robot parameter file");
//  addComment("");
  //addComment("General settings");
  std::string section;
  section = "General settings";
  addParam(ArConfigArg("Class", myClass, "general type of robot", 
		 sizeof(myClass)), section.c_str(), ArPriority::TRIVIAL);
  addParam(ArConfigArg("Subclass", mySubClass, "specific type of robot", 
		       sizeof(mySubClass)), section.c_str(), 
	   ArPriority::TRIVIAL);
  addParam(ArConfigArg("RobotRadius", &myRobotRadius, "radius in mm"), 
	   section.c_str(), ArPriority::NORMAL);
  addParam(ArConfigArg("RobotDiagonal", &myRobotDiagonal, 
		 "half-height to diagonal of octagon"), "General settings",
	   ArPriority::TRIVIAL);
  addParam(ArConfigArg("RobotWidth", &myRobotWidth, "width in mm"), 
	   section.c_str(), ArPriority::NORMAL);
  addParam(ArConfigArg("RobotLength", &myRobotLength, "length in mm of the whole robot"),
	   section.c_str(), ArPriority::NORMAL);
  addParam(ArConfigArg("RobotLengthFront", &myRobotLengthFront, "length in mm to the front of the robot (if this is 0 (or non existent) this value will be set to half of RobotLength)"),
	   section.c_str(), ArPriority::NORMAL);
  addParam(ArConfigArg("RobotLengthRear", &myRobotLengthRear, "length in mm to the rear of the robot (if this is 0 (or non existent) this value will be set to half of RobotLength)"), 
	   section.c_str(), ArPriority::NORMAL);
  addParam(ArConfigArg("Holonomic", &myHolonomic, "turns in own radius"), 
	   section.c_str(), ArPriority::TRIVIAL);
  addParam(ArConfigArg("MaxRVelocity", &myAbsoluteMaxRVelocity, 
		       "absolute maximum degrees / sec"), section.c_str(),
	   ArPriority::TRIVIAL);
  addParam(ArConfigArg("MaxVelocity", &myAbsoluteMaxVelocity, 
		 "absolute maximum mm / sec"), section.c_str(), 
	   ArPriority::TRIVIAL);
  addParam(ArConfigArg("MaxLatVelocity", &myAbsoluteMaxLatVelocity, 
		 "absolute lateral maximum mm / sec"), section.c_str(), 
	   ArPriority::TRIVIAL);
  addParam(ArConfigArg("HasMoveCommand", &myHaveMoveCommand, 
		 "has built in move command"), section.c_str(),
	   ArPriority::TRIVIAL);
  addParam(ArConfigArg("RequestIOPackets", &myRequestIOPackets,
		 "automatically request IO packets"), section.c_str(),
	   ArPriority::NORMAL);
  addParam(ArConfigArg("RequestEncoderPackets", &myRequestEncoderPackets,
		       "automatically request encoder packets"), 
	   section.c_str(), ArPriority::NORMAL);
  addParam(ArConfigArg("SwitchToBaudRate", &mySwitchToBaudRate, 
		 "switch to this baud if non-0 and supported on robot"), 
	   section.c_str(), ArPriority::IMPORTANT);
  
  section = "Conversion factors";
  addParam(ArConfigArg("AngleConvFactor", &myAngleConvFactor,
		     "radians per angular unit (2PI/4096)"), section.c_str(),
	   ArPriority::TRIVIAL);
  addParam(ArConfigArg("DistConvFactor", &myDistConvFactor,
		       "multiplier to mm from robot units"), section.c_str(),
	   ArPriority::IMPORTANT);
  addParam(ArConfigArg("VelConvFactor", &myVelConvFactor,
		     "multiplier to mm/sec from robot units"), 
	   section.c_str(),
	   ArPriority::NORMAL);
  addParam(ArConfigArg("RangeConvFactor", &myRangeConvFactor, 
		       "multiplier to mm from sonar units"), section.c_str(),
	   ArPriority::TRIVIAL);
  addParam(ArConfigArg("DiffConvFactor", &myDiffConvFactor, 
		     "ratio of angular velocity to wheel velocity (unused in newer firmware that calculates and returns this)"), 
	   section.c_str(),
	   ArPriority::TRIVIAL);
  addParam(ArConfigArg("Vel2Divisor", &myVel2Divisor, 
		       "divisor for VEL2 commands"), section.c_str(),
	   ArPriority::TRIVIAL);
  addParam(ArConfigArg("GyroScaler", &myGyroScaler, 
		     "Scaling factor for gyro readings"), section.c_str(),
	   ArPriority::IMPORTANT);

  section = "Accessories the robot has";
  addParam(ArConfigArg("TableSensingIR", &myTableSensingIR,
		       "if robot has upwards facing table sensing IR"), 
	   section.c_str(),
	   ArPriority::TRIVIAL);
  addParam(ArConfigArg("NewTableSensingIR", &myNewTableSensingIR,
		 "if table sensing IR are sent in IO packet"), 
	   section.c_str(),
	   ArPriority::TRIVIAL);
  addParam(ArConfigArg("FrontBumpers", &myFrontBumpers, 
		 "if robot has a front bump ring"), section.c_str(),
	   ArPriority::IMPORTANT);
  addParam(ArConfigArg("NumFrontBumpers", &myNumFrontBumpers,
		     "number of front bumpers on the robot"), 
	   section.c_str(),
	   ArPriority::TRIVIAL);
  addParam(ArConfigArg("RearBumpers", &myRearBumpers,
		       "if the robot has a rear bump ring"), section.c_str(),
	   ArPriority::IMPORTANT);
  addParam(ArConfigArg("NumRearBumpers", &myNumRearBumpers,
		       "number of rear bumpers on the robot"), section.c_str(),
	   ArPriority::TRIVIAL);

  section = "IR parameters";
  addParam(ArConfigArg("IRNum", &myNumIR, "number of IRs on the robot"), section.c_str(), ArPriority::NORMAL);
   addParam(ArConfigArg("IRUnit", &myIRUnitSetFunctor, &myIRUnitGetFunctor,
			"IRUnit <IR Number> <IR Type> <Persistance, cycles> <x position, mm> <y position, mm>"), 
	    section.c_str(), ArPriority::TRIVIAL);


    
  section = "Movement control parameters";
  setSectionComment(section.c_str(), "if these are 0 the parameters from robot flash will be used, otherwise these values will be used");
  addParam(ArConfigArg("SettableVelMaxes", &mySettableVelMaxes, "if TransVelMax and RotVelMax can be set"), section.c_str(),
	   ArPriority::TRIVIAL);
  addParam(ArConfigArg("TransVelMax", &myTransVelMax, "maximum desired translational velocity for the robot"), section.c_str(), 
	   ArPriority::IMPORTANT);
  addParam(ArConfigArg("RotVelMax", &myRotVelMax, "maximum desired rotational velocity for the robot"), section.c_str(),
	   ArPriority::IMPORTANT);
  addParam(ArConfigArg("SettableAccsDecs", &mySettableAccsDecs, "if the accel and decel parameters can be set"), section.c_str(), ArPriority::TRIVIAL);
  addParam(ArConfigArg("TransAccel", &myTransAccel, "translational acceleration"), 
	   section.c_str(), ArPriority::IMPORTANT);
  addParam(ArConfigArg("TransDecel", &myTransDecel, "translational deceleration"), 
	   section.c_str(), ArPriority::IMPORTANT);
  addParam(ArConfigArg("RotAccel", &myRotAccel, "rotational acceleration"), 
	   section.c_str());
  addParam(ArConfigArg("RotDecel", &myRotDecel, "rotational deceleration"),
	   section.c_str(), ArPriority::IMPORTANT);

  addParam(ArConfigArg("HasLatVel", &myHasLatVel, "if the robot has lateral velocity"), section.c_str(), ArPriority::TRIVIAL);

  addParam(ArConfigArg("LatVelMax", &myLatVelMax, "maximum desired lateral velocity for the robot"), section.c_str(), 
	   ArPriority::IMPORTANT);
  addParam(ArConfigArg("LatAccel", &myLatAccel, "lateral acceleration"), 
	   section.c_str(), ArPriority::IMPORTANT);
  addParam(ArConfigArg("LatDecel", &myLatDecel, "lateral deceleration"), 
	   section.c_str(), ArPriority::IMPORTANT);

  section = "GPS parameters";
    // Yes, there is a "P" in the middle of the position parameters. Don't remove it if
    // you think it's irrelevant, it will break all robot parameter files.
  addParam(ArConfigArg("GPSPX", &myGPSX, "x location of gps receiver antenna on robot, mm"), section.c_str(), ArPriority::NORMAL);
  addParam(ArConfigArg("GPSPY", &myGPSY, "y location of gps receiver antenna on robot, mm"), section.c_str(), ArPriority::NORMAL);
  addParam(ArConfigArg("GPSType", myGPSType, "type of gps receiver (trimble, novatel, standard)", sizeof(myGPSType)), section.c_str(), ArPriority::IMPORTANT);
  addParam(ArConfigArg("GPSPort", myGPSPort, "port the gps is on", sizeof(myGPSPort)), section.c_str(), ArPriority::NORMAL);
  addParam(ArConfigArg("GPSBaud", &myGPSBaud, "gps baud rate (9600, 19200, 38400, etc.)"), section.c_str(), ArPriority::NORMAL);

  section = "Compass parameters";
  addParam(ArConfigArg("CompassType", myCompassType, "type of compass: robot (typical configuration), or serialTCM (computer serial port)", sizeof(myCompassType)), section.c_str(), ArPriority::NORMAL);
  addParam(ArConfigArg("CompassPort", myCompassPort, "serial port name, if CompassType is serialTCM", sizeof(myCompassPort)), section.c_str(), ArPriority::NORMAL);

  section = "Sonar parameters";
  addParam(ArConfigArg("SonarNum", &myNumSonar, 
		     "Number of sonars on the robot."), section.c_str(),
	   ArPriority::NORMAL);
  addParam(ArConfigArg("SonarUnit", &mySonarUnitSetFunctor, &mySonarUnitGetFunctor,
		       "SonarUnit <sonarNumber> <x position, mm> <y position, mm> <heading of disc, degrees> <MTX sonar board> <MTX sonar board unit position> <MTX gain> <MTX detection threshold> <MTX max range> <autonomous driving sensor flag>"), section.c_str(), ArPriority::TRIVIAL);

  int i;
  for (i = 1; i <= Aria::getMaxNumSonarBoards(); i++)
    addSonarBoardToConfig(i, this, ourUseDefaultBehavior);

  for (i = 1; i <= Aria::getMaxNumLasers(); i++)
  {
    if (i == 1)
    {
      section = "Laser parameters";
    }
    else
    {
      char buf[1024];
      sprintf(buf, "Laser %d parameters", i);
      section = buf;
    }

    addLaserToConfig(i, this, ourUseDefaultBehavior, section.c_str());
  }

  for (i = 1; i <= Aria::getMaxNumBatteries(); i++)
    addBatteryToConfig(i, this, ourUseDefaultBehavior);

  for (i = 1; i <= Aria::getMaxNumLCDs(); i++)
    addLCDToConfig(i, this, ourUseDefaultBehavior);

  /** PTZ parameters here too */
  myPTZParams.resize(Aria::getMaxNumPTZs());
  for(size_t i = 0; i < Aria::getMaxNumPTZs(); ++i)
    addPTZToConfig(i, this);

  /* Parameters used by ArVideo library */
  myVideoParams.resize(Aria::getMaxNumVideoDevices());
  for(size_t i = 0; i < Aria::getMaxNumVideoDevices(); ++i)
    addVideoToConfig(i, this);
}



AREXPORT void ArRobotParams::addLaserToConfig(
	int laserNumber, ArConfig* config, bool useDefaultBehavior, 
	const char *section)
{
  ArConfigArg::RestartLevel restartLevel;
  // if we're using default behavior set it to none, since we can't
  // change it
  if (useDefaultBehavior)
    restartLevel = ArConfigArg::NO_RESTART;
  // otherwise make it restart the software
  else 
    restartLevel = ArConfigArg::RESTART_SOFTWARE;

  config->addSection(ArConfig::CATEGORY_ROBOT_PHYSICAL,
                     section,
                     "Information about the connection to this laser and its position on the vehicle.");

  LaserData *laserData = new LaserData;
  myLasers[laserNumber] = laserData;

  strcpy(laserData->mySection, section);

  std::string displayHintPlain = "Visible:LaserAutoConnect=true";
  std::string displayHintCheckbox = displayHintPlain + "&&Checkbox";

  std::string displayHintCustom;

  char tempDescBuf[512];
  snprintf(tempDescBuf, sizeof(tempDescBuf),
           "Laser_%d exists and should be automatically connected at startup.",
           laserNumber);
       
  displayHintCustom = "Checkbox";

  config->addParam(
	  ArConfigArg("LaserAutoConnect", &laserData->myLaserAutoConnect,
                tempDescBuf),
	  section, ArPriority::FACTORY, 
	  displayHintCustom.c_str(), restartLevel);

  config->addParam(ArConfigArg(ArConfigArg::SEPARATOR),
		   section, ArPriority::FACTORY);

  config->addParam(
	  ArConfigArg("LaserX", &laserData->myLaserX, 
		      "Location (in mm) of the laser in X (+ front, - back) relative to the robot's idealized center of rotation."), 
	  section, ArPriority::FACTORY, 
	  displayHintPlain.c_str(), restartLevel);
  config->addParam(
	  ArConfigArg("LaserY", &laserData->myLaserY, 
		      "Location (in mm) of the laser in Y (+ left, - right) relative to the robot's idealized center of rotation."), 
	  section, ArPriority::FACTORY, 
	  displayHintPlain.c_str(), restartLevel);
  config->addParam(
	  ArConfigArg("LaserTh", &laserData->myLaserTh, 
		      "Rotation (in deg) of the laser (+ counterclockwise, - clockwise).", -180.0, 180.0), 
	  section, ArPriority::FACTORY, 
	  displayHintPlain.c_str(), restartLevel);
  config->addParam(
	  ArConfigArg("LaserZ", &laserData->myLaserZ, 
		      "Height (in mm) of the laser from the ground. 0 means unknown.", 0),
	  section, ArPriority::FACTORY, 
	  displayHintPlain.c_str(), restartLevel);
  config->addParam(
	  ArConfigArg("LaserIgnore", laserData->myLaserIgnore, 
		      "Angles (in deg) at which to ignore readings, +/1 one degree. Angles are entered as strings, separated by a space.",
		      sizeof(laserData->myLaserIgnore)), 
	  section, ArPriority::FACTORY, 
	  displayHintPlain.c_str(), restartLevel);
  
  snprintf(tempDescBuf, sizeof(tempDescBuf),
           "Laser_%i is upside-down.",
           laserNumber);

  config->addParam(
	  ArConfigArg("LaserFlipped", &laserData->myLaserFlipped,
		            tempDescBuf),
	  section, ArPriority::FACTORY, 
	  displayHintCheckbox.c_str(), restartLevel);

  config->addParam(ArConfigArg(ArConfigArg::SEPARATOR),
		   section, ArPriority::FACTORY);

  displayHintCustom = displayHintPlain + "&&" + Aria::laserGetChoices();
  config->addParam(
	  ArConfigArg("LaserType", laserData->myLaserType, 
		      "Type of laser.", 
		      sizeof(laserData->myLaserType)), 
	  section,ArPriority::FACTORY, 
	  displayHintCustom.c_str(), restartLevel);

  displayHintCustom = (displayHintPlain + "&&" + 
		 Aria::deviceConnectionGetChoices());
  config->addParam(
	  ArConfigArg("LaserPortType", laserData->myLaserPortType, 
		      "Type of port the laser is on.", 
		      sizeof(laserData->myLaserPortType)), 

	  section, ArPriority::FACTORY, 
	  displayHintCustom.c_str(), restartLevel);

  config->addParam(
	  ArConfigArg("LaserPort", laserData->myLaserPort, 
		      "Port the laser is on.", 
		      sizeof(laserData->myLaserPort)), 
	  section, ArPriority::FACTORY, 
	  displayHintPlain.c_str(), restartLevel);

  if (!ourPowerOutputDisplayHint.empty())
    displayHintCustom = displayHintPlain + "&&" + ourPowerOutputDisplayHint;
  else
    displayHintCustom = displayHintPlain;


  config->addParam(
	  ArConfigArg("LaserPowerOutput", 
		      laserData->myLaserPowerOutput,
		      "Power output that controls this laser's power.",
		      sizeof(laserData->myLaserPowerOutput)), 
	  section, ArPriority::FACTORY,
	  displayHintCustom.c_str(), restartLevel);

  config->addParam(
	  ArConfigArg("LaserStartingBaudChoice", 
		      laserData->myLaserStartingBaudChoice, 
		      "StartingBaud for this laser. Leave blank to use the default.", 
		      sizeof(laserData->myLaserStartingBaudChoice)),
	  section, ArPriority::FACTORY, 
	  displayHintPlain.c_str(), restartLevel);
  config->addParam(
	  ArConfigArg("LaserAutoBaudChoice", 
		      laserData->myLaserAutoBaudChoice, 
		      "AutoBaud for this laser. Leave blank to use the default.", 
		      sizeof(laserData->myLaserAutoBaudChoice)),
	  section, ArPriority::FACTORY, 
	  displayHintPlain.c_str(), restartLevel);

  config->addParam(ArConfigArg(ArConfigArg::SEPARATOR),
		   section, ArPriority::FACTORY);

  if (!useDefaultBehavior)
    return;

  config->addParam(
	  ArConfigArg("LaserPowerControlled", 
		            &laserData->myLaserPowerControlled,
		            "When enabled (true), this indicates that the power to the laser is controlled by the serial port line."), 
	  section,
	  ArPriority::NORMAL);
  config->addParam(
	  ArConfigArg("LaserMaxRange", (int *)&laserData->myLaserMaxRange, 
		      "Maximum range (in mm) to use for the laser. This should be specified only when the range needs to be shortened. 0 to use the default range."),
	  section,
	  ArPriority::NORMAL);
  config->addParam(
	  ArConfigArg("LaserCumulativeBufferSize", 
		      (int *)&laserData->myLaserCumulativeBufferSize, 
		      "Cumulative buffer size to use for the laser. 0 to use the default."), 
	  section,
	  ArPriority::NORMAL);
  
  config->addParam(
	  ArConfigArg("LaserStartDegrees", laserData->myLaserStartDegrees, 
		            "Start angle (in deg) for the laser. This may be used to constrain the angle. Fractional degrees are permitted. Leave blank to use the default.",
                sizeof(laserData->myLaserStartDegrees)),
	  section,
	  ArPriority::NORMAL);
  config->addParam(
	  ArConfigArg("LaserEndDegrees", laserData->myLaserEndDegrees, 
		            "End angle (in deg) for the laser. This may be used to constrain the angle. Fractional degreees are permitted. Leave blank to use the default.",
                sizeof(laserData->myLaserEndDegrees)),
	  section,
	  ArPriority::NORMAL);
  config->addParam(
	  ArConfigArg("LaserDegreesChoice", laserData->myLaserDegreesChoice, 
		            "Degrees choice for the laser. This may be used to constrain the range. Leave blank to use the default.",
                sizeof(laserData->myLaserDegreesChoice)),
	  section,
	  ArPriority::NORMAL);
  config->addParam(
	  ArConfigArg("LaserIncrement", laserData->myLaserIncrement, 
		            "Increment (in deg) for the laser. Fractional degrees are permitted. Leave blank to use the default.",
                sizeof(laserData->myLaserIncrement)),
	  section,
	  ArPriority::NORMAL);
  config->addParam(
	  ArConfigArg("LaserIncrementChoice", laserData->myLaserIncrementChoice, 
		            "Increment choice for the laser. This may be used to increase the increment. Leave blank to use the default.",
                sizeof(laserData->myLaserIncrementChoice)),
	  section,
	  ArPriority::NORMAL);
  config->addParam(
	  ArConfigArg("LaserUnitsChoice", laserData->myLaserUnitsChoice, 
		            "Units for the laser. This may be used to increase the size of the units. Leave blank to use the default.",
                sizeof(laserData->myLaserUnitsChoice)),
	  section,
	  ArPriority::NORMAL);
  config->addParam(
	  ArConfigArg("LaserReflectorBitsChoice", 
		            laserData->myLaserReflectorBitsChoice, 
		            "ReflectorBits for the laser. Leave blank to use the default.",
                sizeof(laserData->myLaserReflectorBitsChoice)),
    section,
	  ArPriority::NORMAL);

}

AREXPORT void ArRobotParams::addBatteryToConfig(
	int batteryNumber, ArConfig* config, bool useDefaultBehavior)
{
  ArConfigArg::RestartLevel restartLevel;
  // if we're using default behavior set it to none, since we can't
  // change it
  if (useDefaultBehavior)
    restartLevel = ArConfigArg::NO_RESTART;
  // otherwise make it restart the software
  else 
    restartLevel = ArConfigArg::RESTART_SOFTWARE;

  char buf[1024];
  sprintf(buf, "Battery_%d", batteryNumber);
  std::string section = buf;
  std::string batteryName = buf;
 
  config->addSection(ArConfig::CATEGORY_ROBOT_PHYSICAL,
                     section.c_str(),
                     "Information about the connection to this battery.");

  BatteryMTXBoardData *batteryMTXBoardData = new BatteryMTXBoardData;
  myBatteryMTXBoards[batteryNumber] = batteryMTXBoardData;

  myBatteryMTXBoardCount++;

  std::string displayHintPlain = "Visible:BatteryAutoConnect=true";

  std::string displayHintCustom;

  displayHintCustom = "Checkbox&&Visible:Generation!=Legacy";

  char tempDescBuf[512];
  snprintf(tempDescBuf, sizeof(tempDescBuf),
           "%s exists and should be automatically connected at startup.",
           batteryName.c_str());

  config->addParam(
	  ArConfigArg("BatteryAutoConnect", 
		            &batteryMTXBoardData->myBatteryMTXBoardAutoConn, 
                tempDescBuf),
	  section.c_str(), ArPriority::FACTORY,
	  displayHintCustom.c_str(), restartLevel);

  config->addParam(ArConfigArg(ArConfigArg::SEPARATOR),
		   section.c_str(), ArPriority::FACTORY);

  displayHintCustom = displayHintPlain + "&&" + Aria::batteryGetChoices();
  config->addParam(
	  ArConfigArg("BatteryType", 
		      batteryMTXBoardData->myBatteryMTXBoardType, 
		      "Type of battery.", 
		      sizeof(batteryMTXBoardData->myBatteryMTXBoardType)),
	  section.c_str(), ArPriority::FACTORY,
	  displayHintCustom.c_str(), restartLevel);

  displayHintCustom = (displayHintPlain + "&&" + 
		 Aria::deviceConnectionGetChoices());
  config->addParam(
	  ArConfigArg("BatteryPortType", 
		      batteryMTXBoardData->myBatteryMTXBoardPortType, 
		      "Port type that the battery is on.", 
		      sizeof(batteryMTXBoardData->myBatteryMTXBoardPortType)), 
	  section.c_str(), ArPriority::FACTORY,
	  displayHintCustom.c_str(), restartLevel);

  config->addParam(
	  ArConfigArg("BatteryPort", 
		      batteryMTXBoardData->myBatteryMTXBoardPort, 
		      "Port the battery is on.", 
		      sizeof(batteryMTXBoardData->myBatteryMTXBoardPort)),
	  section.c_str(), ArPriority::FACTORY,
	  displayHintPlain.c_str(), restartLevel);
  config->addParam(
	  ArConfigArg("BatteryBaud", 
		      &batteryMTXBoardData->myBatteryMTXBoardBaud, 
		      "Baud rate to use for battery communication (9600, 19200, 38400, etc.)."), 
	  section.c_str(), ArPriority::FACTORY,
	  displayHintPlain.c_str(), restartLevel);

  // MPL TODO remove this since it's redundant (it's set in the constructor)
  //batteryMTXBoardData->myBatteryMTXBoardAutoConn = false;

}

AREXPORT void ArRobotParams::addLCDToConfig(
	int lcdNumber, ArConfig* config, bool useDefaultBehavior)
{
  ArConfigArg::RestartLevel restartLevel;
  // if we're using default behavior set it to none, since we can't
  // change it
  if (useDefaultBehavior)
    restartLevel = ArConfigArg::NO_RESTART;
  // otherwise make it restart the software
  else 
    restartLevel = ArConfigArg::RESTART_SOFTWARE;

  char buf[1024];
  sprintf(buf, "LCD_%d", lcdNumber);
  std::string section = buf;
  std::string lcdName = buf;

  config->addSection(ArConfig::CATEGORY_ROBOT_PHYSICAL,
                     section.c_str(),
                     "The physical definition of this LCD.");
  
  LCDMTXBoardData *lcdMTXBoardData = new LCDMTXBoardData;
  myLCDMTXBoards[lcdNumber] = lcdMTXBoardData;

  /// MPL TODO what's this for?
  myLCDMTXBoardCount++;

  std::string displayHintPlain = "Visible:LCDAutoConnect=true";
  std::string displayHintCheckbox = displayHintPlain + "&&Checkbox";

  std::string displayHintCustom;

  /// MPL TODO remove, this is already set in the constructor
  //lcdMTXBoardData->myLCDMTXBoardAutoConn = false;
  displayHintCustom = "Checkbox&&Visible:Generation!=Legacy";

  char tempDescBuf[512];
  snprintf(tempDescBuf, sizeof(tempDescBuf),
           "%s exists and should automatically be connected at startup.",
           lcdName.c_str());

  config->addParam(
	  ArConfigArg("LCDAutoConnect", 
		            &lcdMTXBoardData->myLCDMTXBoardAutoConn, 
                tempDescBuf),
	  section.c_str(), ArPriority::FACTORY,
	  displayHintCustom.c_str(), restartLevel);
  /// MPL TODO remove, this is already set in the constructor
  //lcdMTXBoardData->myLCDMTXBoardConnFailOption = false

  config->addParam(
	  ArConfigArg("LCDDisconnectOnConnectFailure", 
		      &lcdMTXBoardData->myLCDMTXBoardConnFailOption, 
		      "The LCD is a key component and is required for operation. If this is enabled and there is a failure in the LCD communications, then the robot will restart."),
	  section.c_str(), ArPriority::FACTORY,
	  displayHintCheckbox.c_str(), restartLevel);
  
  config->addParam(ArConfigArg(ArConfigArg::SEPARATOR),
		   section.c_str(), ArPriority::FACTORY);

  displayHintCustom = displayHintPlain + "&&" + Aria::lcdGetChoices();
  config->addParam(
	  ArConfigArg("LCDType", 
		      lcdMTXBoardData->myLCDMTXBoardType, 
		      "Type of LCD.", 
		      sizeof(lcdMTXBoardData->myLCDMTXBoardType)), 
	  section.c_str(), ArPriority::FACTORY,
	  displayHintCustom.c_str(), restartLevel);

  displayHintCustom = (displayHintPlain + "&&" + 
		       Aria::deviceConnectionGetChoices());
  config->addParam(
	  ArConfigArg("LCDPortType", 
		      lcdMTXBoardData->myLCDMTXBoardPortType, 
		      "Port type that the LCD is on.",
		      sizeof(lcdMTXBoardData->myLCDMTXBoardPortType)), 
	  section.c_str(), ArPriority::FACTORY,
	  displayHintCustom.c_str(), restartLevel);

  config->addParam(
	  ArConfigArg("LCDPort", 
		      lcdMTXBoardData->myLCDMTXBoardPort, 
		      "Port that the LCD is on.", 
		      sizeof(lcdMTXBoardData->myLCDMTXBoardPort)), 
	  section.c_str(), ArPriority::FACTORY,
	  displayHintPlain.c_str(), restartLevel);

  if (!ourPowerOutputDisplayHint.empty())
    displayHintCustom = displayHintPlain + "&&" + ourPowerOutputDisplayHint;
  else
    displayHintCustom = displayHintPlain;
  config->addParam(
	  ArConfigArg("LCDPowerOutput", 
		      lcdMTXBoardData->myLCDMTXBoardPowerOutput, 
		      "Power output that controls this LCD's power.", 
		      sizeof(lcdMTXBoardData->myLCDMTXBoardPowerOutput)), 
	  section.c_str(), ArPriority::FACTORY,
	  displayHintCustom.c_str(), restartLevel);

  config->addParam(
	  ArConfigArg("LCDBaud", 
		      &lcdMTXBoardData->myLCDMTXBoardBaud, 
		      "Baud rate for the LCD communication (9600, 19200, 38400, etc.)."), 
	  section.c_str(), ArPriority::FACTORY,
	  displayHintPlain.c_str(), restartLevel);
}

AREXPORT void ArRobotParams::addSonarBoardToConfig(
	int sonarBoardNumber, ArConfig* config, bool useDefaultBehavior)
{
  ArConfigArg::RestartLevel restartLevel;
  // if we're using default behavior set it to none, since we can't
  // change it
  if (useDefaultBehavior)
    restartLevel = ArConfigArg::NO_RESTART;
  // otherwise make it restart the software
  else 
    restartLevel = ArConfigArg::RESTART_SOFTWARE;

  char buf[1024];
  sprintf(buf, "SonarBoard_%d", sonarBoardNumber);
  std::string section = buf;
  std::string sonarBoardName = buf;

  std::string displayHintPlain = "Visible:SonarAutoConnect=true";

  std::string displayHintCustom;
  
  config->addSection(ArConfig::CATEGORY_ROBOT_PHYSICAL,
                     section.c_str(),
                     "Information about the connection to this Sonar Board.");

  SonarMTXBoardData *sonarMTXBoardData = new SonarMTXBoardData;
  mySonarMTXBoards[sonarBoardNumber] = sonarMTXBoardData;

  /// MPL TODO what's this do?
  mySonarMTXBoardCount++;

  /// MPL TODO remove this next line (it's in the constructor
  //sonarMTXBoardData->mySonarMTXBoardAutoConn = false;
  displayHintCustom = "Checkbox&&Visible:Generation!=Legacy";

  char tempDescBuf[512];
  snprintf(tempDescBuf, sizeof(tempDescBuf),
           "%s exists and should be automatically connected at startup.",
           sonarBoardName.c_str());
 
  config->addParam(
	  ArConfigArg("SonarAutoConnect", 
		       &sonarMTXBoardData->mySonarMTXBoardAutoConn, 
           tempDescBuf),
	  section.c_str(), ArPriority::FACTORY,
	  displayHintCustom.c_str(), restartLevel);
  
  config->addParam(ArConfigArg(ArConfigArg::SEPARATOR),
		   section.c_str(), ArPriority::FACTORY);

  displayHintCustom = displayHintPlain + "&&" + Aria::sonarGetChoices();
  config->addParam(
	  ArConfigArg("SonarBoardType", 
		      sonarMTXBoardData->mySonarMTXBoardType, 
		      "Type of the sonar board.", 
		      sizeof(sonarMTXBoardData->mySonarMTXBoardType)), 
	  section.c_str(), ArPriority::FACTORY,
	  displayHintCustom.c_str(), restartLevel);

  displayHintCustom = (displayHintPlain + "&&" + 
		 Aria::deviceConnectionGetChoices());
  config->addParam(
	  ArConfigArg("SonarBoardPortType", 
		      sonarMTXBoardData->mySonarMTXBoardPortType, 
		      "Port type that the sonar is on.", 
		      sizeof(sonarMTXBoardData->mySonarMTXBoardPortType)),
	  section.c_str(), ArPriority::FACTORY,
	  displayHintCustom.c_str(), restartLevel);

  config->addParam(
	  ArConfigArg("SonarBoardPort", 
		       sonarMTXBoardData->mySonarMTXBoardPort, 
		       "Port the sonar is on.", 
		      sizeof(sonarMTXBoardData->mySonarMTXBoardPort)), 
	  section.c_str(), ArPriority::FACTORY,
	  displayHintPlain.c_str(), restartLevel);

  if (!ourPowerOutputDisplayHint.empty())
    displayHintCustom = displayHintPlain + "&&" + ourPowerOutputDisplayHint;
  else
    displayHintCustom = displayHintPlain;
  config->addParam(
	  ArConfigArg("SonarBoardPowerOutput", 
		      sonarMTXBoardData->mySonarMTXBoardPowerOutput, 
		      "Power output that controls this Sonar Board's power.", 
		      sizeof(sonarMTXBoardData->mySonarMTXBoardPowerOutput)), 
	  section.c_str(), ArPriority::FACTORY,
	  displayHintCustom.c_str(), restartLevel);

  config->addParam(
	  ArConfigArg("SonarBaud", 
		      &sonarMTXBoardData->mySonarMTXBoardBaud, 
		      "Baud rate for the sonar board communication. (9600, 19200, 38400, etc.)."), 
	  section.c_str(), ArPriority::FACTORY,
	  displayHintPlain.c_str(), restartLevel);

  /// MPL Remove this, it's in the constructor
  //  sonarMTXBoardData->mySonarDelay = 1;
  config->addParam(
	  ArConfigArg("SonarDelay", 
		      &sonarMTXBoardData->mySonarDelay, 
		      "Sonar delay (in ms).", 0, 10), 
	  section.c_str(), ArPriority::FACTORY,
	  displayHintPlain.c_str(), restartLevel);

  /// MPL Remove this sonar gain, it's in the constructor
  //sonarMTXBoardData->mySonarGain = 5;
  config->addParam(
	  ArConfigArg("SonarGain", 
		      &sonarMTXBoardData->mySonarGain, 
		      "Default sonar gain for the board, range 0-31.", 0, 31), 
	  section.c_str(), ArPriority::FACTORY,
	  displayHintPlain.c_str(), restartLevel);

  // MPL TODO remove (moved this to constructor)
  //strcpy(&sonarMTXBoardData->mySonarThreshold[0],"3000|1500|2000");
  config->addParam(
	  ArConfigArg("SonarDetectionThreshold", 
		      &sonarMTXBoardData->mySonarDetectionThreshold, 
		      "Default sonar detection threshold for the board.",
		      0, 65535),
	  section.c_str(), ArPriority::FACTORY,
	  displayHintPlain.c_str(), restartLevel);

	/*
  config->addParam(
	  ArConfigArg("SonarNoiseDelta", 
		      &sonarMTXBoardData->mySonarNoiseDelta, 
		      "Default sonar noise delta for the board.",
		      0, 65535),
	  section.c_str(), ArPriority::FACTORY,
	  displayHintPlain.c_str(), restartLevel);
	*/

  config->addParam(
	  ArConfigArg("SonarMaxRange", 
		      &sonarMTXBoardData->mySonarMaxRange, 
		      "Default maximum sonar range for the board.",
		      0, 255*17),
	  section.c_str(), ArPriority::FACTORY,
	  displayHintPlain.c_str(), restartLevel);

  
/*
  ArLog::log(ArLog::Normal, "ArRobotParams: added sonar board %d with params %s %s %s %d %d %d",
  i, &sonarMTXBoardData->mySonarMTXBoardType[0], sonarMTXBoardData->mySonarMTXBoardPortType, 
  sonarMTXBoardData->mySonarMTXBoardPort, sonarMTXBoardData->mySonarMTXBoardBaud, 
  sonarMTXBoardData->mySonarMTXBoardAutoConn, 
  sonarMTXBoardData->mySonarDelay");
*/
  
}

void ArRobotParams::addPTZToConfig(int i, ArConfig *config)
{
  std::stringstream sectionStream;
  sectionStream << "PTZ " << i+1 << " parameters";
  std::string section = sectionStream.str();
  config->addSection(ArConfig::CATEGORY_ROBOT_PHYSICAL, section.c_str(), "Information about the connection to a pan/tilt unit (PTU) or pan/tilt/zoom control (PTZ) of a camera");
  config->addParam(ArConfigArg("PTZAutoConnect", &(myPTZParams[i].connect), "If true, connect to this PTZ by default."), section.c_str());
  config->addParam(ArConfigArg("PTZType", &(myPTZParams[i].type), "PTZ or PTU type"), section.c_str());
  config->addParam(ArConfigArg("PTZInverted", &(myPTZParams[i].inverted), "If unit is mounted inverted (upside-down)"), section.c_str());
  config->addParam(ArConfigArg("PTZSerialPort", &(myPTZParams[i].serialPort), "serial port, or none if not using serial port communication"), section.c_str());
  config->addParam(ArConfigArg("PTZRobotAuxSerialPort", &(myPTZParams[i].robotAuxPort), "Pioneer aux.  serial port, or -1 if not using aux.  serial port for communication."), section.c_str());
  config->addParam(ArConfigArg("PTZAddress", &(myPTZParams[i].address), "IP address or hostname, or none if not using network communication."), section.c_str());
  config->addParam(ArConfigArg("PTZTCPPort", &(myPTZParams[i].tcpPort), "TCP Port to use for HTTP network connection"), section.c_str());
}


void ArRobotParams::addVideoToConfig(int i, ArConfig *config)
{
  std::stringstream sectionStream;
  sectionStream << "Video " << i+1 << " parameters";
  std::string section = sectionStream.str();
  config->addSection(ArConfig::CATEGORY_ROBOT_PHYSICAL, section.c_str(), "Information about the connection to a video acquisition device, framegrabber, or camera");
  config->addParam(ArConfigArg("VideoAutoConnect", &(myVideoParams[i].connect), "If true, connect to this device by default."), section.c_str());
  config->addParam(ArConfigArg("VideoType", &(myVideoParams[i].type), "Device type"), section.c_str());
  //if (i == 0)
  //  printf("XXX added VideoType param for Video 1, its target is 0x%x, initial value is %s\n", &(myVideoParams[i].type), myVideoParams[i].type.c_str());
  config->addParam(ArConfigArg("VideoInverted", &(myVideoParams[i].inverted), "If image should be flipped (for cameras mounted inverted/upside-down)"), section.c_str());
  config->addParam(ArConfigArg("VideoWidth", &(myVideoParams[i].imageWidth), "Desired width of image"), section.c_str());
  addParam(ArConfigArg("VideoHeight", &(myVideoParams[i].imageHeight), "Desired height of image"), section.c_str());
  addParam(ArConfigArg("VideoDeviceIndex", &(myVideoParams[i].deviceIndex), "Device index"), section.c_str());
  config->addParam(ArConfigArg("VideoDeviceName", &(myVideoParams[i].deviceName), "Device name (overrides VideoDeviceIndex)"), section.c_str());
  config->addParam(ArConfigArg("VideoChannel", &(myVideoParams[i].channel), "Input channel"), section.c_str());
  addParam(ArConfigArg("VideoAnalogSignalFormat", &(myVideoParams[i].analogSignalFormat), "NTSC or PAL"), section.c_str(), ArPriority::NORMAL, "Choices:NTSC;;PAL");
  config->addParam(ArConfigArg("VideoAddress", &(myVideoParams[i].address), "IP address or hostname, or none if not using network communication."), section.c_str());
  config->addParam(ArConfigArg("VideoTCPPort", &(myVideoParams[i].tcpPort), "TCP Port to use for HTTP network connection"), section.c_str());
}


AREXPORT bool ArRobotParams::parseSonarUnit (ArArgumentBuilder *builder)
{
	// PS 9/5/12 - we need to support the old way, ie 4 parameters and the
	// new way - so test the size first
	if (builder->getArgc() == 4) {
		if (builder->getArgc() != 4 || !builder->isArgInt (0) ||
		    !builder->isArgInt (1) || !builder->isArgInt (2) ||
		    !builder->isArgInt (3)) {
			ArLog::log (ArLog::Terse, "ArRobotParams: SonarUnit parameters invalid");
			return false;
		}
		mySonarMap[builder->getArgInt (0)][SONAR_X] = builder->getArgInt (1);
		mySonarMap[builder->getArgInt (0)][SONAR_Y] = builder->getArgInt (2);
		mySonarMap[builder->getArgInt (0)][SONAR_TH] = builder->getArgInt (3);

    ArLog::log(ArLog::Verbose, "ArRobotParams::parseSonarUnit done parsing");
		
		return true;
	} else {
		return parseMTXSonarUnit (builder);
	}
}

#if 0
AREXPORT const std::list<ArArgumentBuilder *> *ArRobotParams::getSonarUnits(void)
{
  std::map<int, std::map<int, int> >::iterator it;
  int num, x, y, th;
  ArArgumentBuilder *builder;

  for (it = mySonarMap.begin(); it != mySonarMap.end(); it++)
  {
    num = (*it).first;
    x = (*it).second[SONAR_X];
    y = (*it).second[SONAR_Y];
    th = (*it).second[SONAR_TH];
    builder = new ArArgumentBuilder;
    builder->add("%d %d %d %d", num, x, y, th);
    myGetSonarUnitList.push_back(builder);
  }
  return &myGetSonarUnitList;
}
#endif

AREXPORT bool ArRobotParams::parseMTXSonarUnit(ArArgumentBuilder *builder)
{
  // there has to be at least 5 arguments, 1st 5 are ints
  // fix for bug 1959
  //if (5 < builder->getArgc() > 10 || !builder->isArgInt(0) || 
  if (builder->getArgc() < 5 /*|| builder->getArgc() > 8*/ || !builder->isArgInt(0) || 
      !builder->isArgInt(1) || !builder->isArgInt(2) ||
      !builder->isArgInt(3) || !builder->isArgInt(4) ||
      !builder->isArgInt(5))
	{
		ArLog::log(ArLog::Normal, "ArRobotParams: SonarUnit parameters invalid, must include at least 5 integer values (MTX-style SonarUnit).",
								builder->getArgc());
		return false;
	}

  myNumSonarUnits++;

  mySonarMap[builder->getArgInt(0)][SONAR_X] = builder->getArgInt(1);
  mySonarMap[builder->getArgInt(0)][SONAR_Y] = builder->getArgInt(2);
  mySonarMap[builder->getArgInt(0)][SONAR_TH] = builder->getArgInt(3);
  mySonarMap[builder->getArgInt(0)][SONAR_BOARD] = builder->getArgInt(4);
  mySonarMap[builder->getArgInt(0)][SONAR_BOARDUNITPOSITION] = builder->getArgInt(5);
  SonarMTXBoardData *sonarMTXBoardData = getSonarMTXBoardData(builder->getArgInt(4));
  if(sonarMTXBoardData)
	  sonarMTXBoardData->myNumSonarTransducers++;
	
  // prob should get these defaults from board
  mySonarMap[builder->getArgInt(0)][SONAR_GAIN] = 0;//SONAR_DEFAULT_GAIN;
	/*
  mySonarMap[builder->getArgInt(0)][SONAR_NOISE_DELTA] = 0;
	*/
  mySonarMap[builder->getArgInt(0)][SONAR_DETECTION_THRESHOLD] = 0;
  mySonarMap[builder->getArgInt(0)][SONAR_MAX_RANGE] = 0;
  mySonarMap[builder->getArgInt(0)][SONAR_USE_FOR_AUTONOMOUS_DRIVING] = true;
  
  if (builder->getArgc() > 6) {
    // gain arg will either be an int or "default"
    if (builder->isArgInt(6)) {
      mySonarMap[builder->getArgInt(0)][SONAR_GAIN] = builder->getArgInt(6);
    }
    else
    {
      ArLog::log(ArLog::Terse, "ArRobotParams: SonarUnit parameters invalid, 7th value (gain) must be an integer value.");
      return false;
    }
  }
  
  if (builder->getArgc() > 7) {
    // gain arg will either be an int or "default"
    if (builder->isArgInt(7)) {
      mySonarMap[builder->getArgInt(0)][SONAR_DETECTION_THRESHOLD] = builder->getArgInt(7);
    }
    else
    {
      ArLog::log(ArLog::Terse, "ArRobotParams: SonarUnit parameters invalid, 8th value (detect. thresh.) must be an integer value.");
      return false;
    }
  }
  if (builder->getArgc() > 8) {
    // gain arg will either be an int or "default"
    if (builder->isArgInt(8)) {
      mySonarMap[builder->getArgInt(0)][SONAR_MAX_RANGE] = builder->getArgInt(8);
    }
    else
    {
      ArLog::log(ArLog::Terse, "ArRobotParams: SonarUnit parameters invalid, 9th value (max range) must be an integer value.");
      return false;
    }
  }
  if (builder->getArgc() > 9) {
    // 
    if (builder->isArgBool(9)) {
      mySonarMap[builder->getArgBool(0)][SONAR_USE_FOR_AUTONOMOUS_DRIVING] = builder->getArgBool(9);
    }
    else
    {
     ArLog::log(ArLog::Terse, "ArRobotParams: SonarUnit parameters invalid, 10th value (use for autonomous) must be a boolean value.");

     return false;
    }
  }

/*
if (builder->getArgc() > 10) {
    // gain arg will either be an int or "default"
    if (builder->isArgInt(10)) {
      mySonarMap[builder->getArgInt(0)][SONAR_NOISE_FLOOR] = builder->getArgInt(9);
    }
    else
    {
      ArLog::log(ArLog::Terse, "ArRobotParams: SonarUnit parameters invalid, 11th value (noise floor) must be an integer value.");
      return false;
    }
  }
*/

  ArLog::log(ArLog::Verbose, "ArRobotParams::parseSonarUnit() parsed unit %d %d %d ", myNumSonarUnits,
	     mySonarMap[builder->getArgInt(0)][SONAR_BOARD],
	     mySonarMap[builder->getArgInt(0)][SONAR_BOARDUNITPOSITION]);



  // PS 9/5/12 - make numsonar = noumsonarunits
  myNumSonar = myNumSonarUnits;

  return true;
}

AREXPORT const std::list<ArArgumentBuilder *> *ArRobotParams::getSonarUnits(void)
//AREXPORT const std::list<ArArgumentBuilder *> *ArRobotParams::getMTXSonarUnits(void)
{
//  ArLog::log(ArLog::Normal, "Saving sonar units?");

  std::map<int, std::map<int, int> >::iterator it;
  int unitNum, x, y, th, boardNum, boardUnitPosition, gain, noiseDelta, detectionThreshold, numEchoSamples;
	bool useForAutonomousDriving;
  ArArgumentBuilder *builder;

  for (it = mySonarMap.begin(); it != mySonarMap.end(); it++)
  {
    unitNum = (*it).first;
    x = (*it).second[SONAR_X];
    y = (*it).second[SONAR_Y];
    th = (*it).second[SONAR_TH];
    boardNum = (*it).second[SONAR_BOARD];
    boardUnitPosition = (*it).second[SONAR_BOARDUNITPOSITION];
    gain = (*it).second[SONAR_GAIN];
		/*
    noiseDelta = (*it).second[SONAR_NOISE_DELTA];
		*/
    detectionThreshold = (*it).second[SONAR_DETECTION_THRESHOLD];
    numEchoSamples = (*it).second[SONAR_MAX_RANGE];
    useForAutonomousDriving = (*it).second[SONAR_USE_FOR_AUTONOMOUS_DRIVING];
    builder = new ArArgumentBuilder;

		/* for noiseDelta
    builder->add("%d %d %d %d %d %d %d %d %d %d", 
		 unitNum, x, y, th, boardNum, boardUnitPosition, gain, noiseDelta, detectionThreshold, numEchoSamples);
		*/
    builder->add("%d %d %d %d %d %d %d %d %d %d", 
		 unitNum, x, y, th, boardNum, boardUnitPosition, gain, detectionThreshold, numEchoSamples, useForAutonomousDriving);

    myGetSonarUnitList.push_back(builder);
  }
  return &myGetSonarUnitList;
}

AREXPORT void ArRobotParams::internalSetSonar(int num, int x, int y, int th,
    int mtxboard, int mtxunit, int mtxgain, int mtxthresh, int mtxmax )
{
  mySonarMap[num][SONAR_X] = x;
  mySonarMap[num][SONAR_Y] = y;
  mySonarMap[num][SONAR_TH] = th;
  mySonarMap[num][SONAR_BOARD] = mtxboard;
  mySonarMap[num][SONAR_BOARDUNITPOSITION] = mtxunit;
  mySonarMap[num][SONAR_GAIN] = mtxgain;
  mySonarMap[num][SONAR_DETECTION_THRESHOLD] = mtxthresh;
  mySonarMap[num][SONAR_MAX_RANGE] = mtxmax;
  mySonarMap[num][SONAR_USE_FOR_AUTONOMOUS_DRIVING] = true;
}

AREXPORT bool ArRobotParams::parseIRUnit(ArArgumentBuilder *builder)
{
  if (builder->getArgc() != 5 || !builder->isArgInt(0) || 
      !builder->isArgInt(1) || !builder->isArgInt(2) || 
      !builder->isArgInt(3) || !builder->isArgInt(4))
  {
    ArLog::log(ArLog::Terse, "ArRobotParams: IRUnit parameters invalid");
    return false;
  }
  myIRMap[builder->getArgInt(0)][IR_TYPE] = builder->getArgInt(1);
  myIRMap[builder->getArgInt(0)][IR_CYCLES] = builder->getArgInt(2);
  myIRMap[builder->getArgInt(0)][IR_X] = builder->getArgInt(3);
  myIRMap[builder->getArgInt(0)][IR_Y] = builder->getArgInt(4);
  return true;
}

AREXPORT const std::list<ArArgumentBuilder *> *ArRobotParams::getIRUnits(void)
{
  std::map<int, std::map<int, int> >::iterator it;
  int num, type, cycles,  x, y;
  ArArgumentBuilder *builder;

  for (it = myIRMap.begin(); it != myIRMap.end(); it++)
  {
    num = (*it).first;
    type = (*it).second[IR_TYPE];
    cycles = (*it).second[IR_CYCLES];
    x = (*it).second[IR_X];
    y = (*it).second[IR_Y];
    builder = new ArArgumentBuilder;
    builder->add("%d %d %d %d %d", num, type, cycles, x, y);
    myGetIRUnitList.push_back(builder);
  }
  return &myGetIRUnitList;
}

AREXPORT void ArRobotParams::internalSetIR(int num, int type, int cycles, int x, int y)
{
  myIRMap[num][IR_TYPE] = type;
  myIRMap[num][IR_CYCLES] = cycles;
  myIRMap[num][IR_X] = x;
  myIRMap[num][IR_Y] = y;
}

AREXPORT bool ArRobotParams::save(void)
{
  char buf[10000];
  sprintf(buf, "%sparams/", Aria::getDirectory());
  setBaseDirectory(buf);
  sprintf(buf, "%s.p", getSubClassName());
  return writeFile(buf, false, NULL, false);
}

void ArRobotParams::internalAddToConfigCommercial(
	ArConfig *config)
{
  ArLog::log(ArLog::Normal, "ArRobotParams: Adding to config");
  
  // initialize some values
  myCommercialConfig = config;
  myCommercialAddedConnectables = false;
  myCommercialProcessedSonar = false;
  myCommercialNumSonar = 16;
  myCommercialMaxNumberOfLasers = 4;
  myCommercialMaxNumberOfBatteries = 1;
  myCommercialMaxNumberOfLCDs = 1;
  myCommercialMaxNumberOfSonarBoards = 2;

  // add the callback
  myCommercialConfig->addProcessFileCB(&myCommercialProcessFileCB, 90);

  /// reset some values from their default
  sprintf(myClass, "MTX");
  /// these probably aren't actually used anywhere, but just in case
  myFrontBumpers = true;
  myRearBumpers = true;
  myRobotRadius = 255;
  myRobotWidth = 400;
  myRobotLengthFront = 255;
  myRobotLengthRear = 255;

  // now add the normal config
  std::string section = "General";
  config->addSection(ArConfig::CATEGORY_ROBOT_PHYSICAL,
                     section.c_str(),
                     "The general definition of this vehicle");

  ArConfigArg generationArg(
	  "Generation", myClass, 
	  "The generation of technology this is.  The MT400 and Motivity Core this should be Legacy.  Everything else is MTX.", 
	  sizeof(myClass));
  generationArg.setExtraExplanation("This main external thing this affects is that for a Legacy lasers are named by type (for backwards compatibility with existing config files), whereas for MTX they are named by their number (for easier future compatibility).");

  myCommercialConfig->addParam(
	  generationArg,
	  section.c_str(), ArPriority::FACTORY, "Choices:Legacy;;MTX",
	  ArConfigArg::RESTART_SOFTWARE);

  myCommercialConfig->addParam(
	  ArConfigArg("Model", mySubClass, 
		      "The model name. This should be human readable and is only for human consumption.", 
		      sizeof(mySubClass)), 
	  section.c_str(), ArPriority::FACTORY, "",
	  ArConfigArg::RESTART_SOFTWARE);

  myCommercialConfig->addParam(ArConfigArg(ArConfigArg::SEPARATOR),
		   section.c_str(), ArPriority::FACTORY);

  myCommercialConfig->addParam(
	  ArConfigArg("Radius", 
		      &myRobotRadius, 
		      "The radius in mm that is needed to turn in place safely. (mm)", 
		      1), 
	  section.c_str(), ArPriority::FACTORY, "",
	  ArConfigArg::RESTART_SOFTWARE);
  myCommercialConfig->addParam(
	  ArConfigArg("Width", 
		      &myRobotWidth, 
		      "Width in mm (mm)",
	      1), 
	  section.c_str(), ArPriority::FACTORY, "",
	  ArConfigArg::RESTART_SOFTWARE);
  myCommercialConfig->addParam(
	  ArConfigArg("LengthFront", 
		      &myRobotLengthFront, 
		      "Length in mm from the idealized center of rotation to the front (mm)", 
		      1),
	   section.c_str(), ArPriority::FACTORY, "",
	   ArConfigArg::RESTART_SOFTWARE);
  myCommercialConfig->addParam(
	  ArConfigArg("LengthRear", 
		      &myRobotLengthRear, 
		      "Length in mm from the idealized center of rotation to the rear (mm)", 
		      1), 
	  section.c_str(), ArPriority::FACTORY, 
	  "", ArConfigArg::RESTART_SOFTWARE);

  myCommercialConfig->addParam(ArConfigArg(ArConfigArg::SEPARATOR),
		   section.c_str(), ArPriority::FACTORY);


  myCommercialConfig->addParam(
	  ArConfigArg("DistanceCalibrationFactor",
		      &myDistConvFactor, "The per-vehicle calibration factor for distance errors.  A perfect vehicle would have a value of 1.  Travelled distances are multiplied by this, so if the vehicle drove 1% to far you'd make this value .99. This is to account for differences within a model that ideally (ideally there wouldn't be any).  (multiplier)", 0),
	  section.c_str(), ArPriority::CALIBRATION,
	  "", ArConfigArg::RESTART_SOFTWARE);

  myCommercialConfig->addParam(ArConfigArg(ArConfigArg::SEPARATOR),
		   section.c_str(), ArPriority::FACTORY);

  myCommercialConfig->addParam(
	  ArConfigArg("NumberOfFrontBumpers", &myNumFrontBumpers,
			       "Number of front bumpers", 0, 7), 
	  section.c_str(), ArPriority::FACTORY, 
	  "SpinBox", ArConfigArg::RESTART_SOFTWARE);
  myCommercialConfig->addParam(
	  ArConfigArg("NumberOfRearBumpers", &myNumRearBumpers,
		      "Number of rear bumpers", 0, 7), 
	  section.c_str(), ArPriority::FACTORY, 
	  "SpinBox", ArConfigArg::RESTART_SOFTWARE);
  
  myCommercialConfig->addParam(
	  ArConfigArg(ArConfigArg::SEPARATOR),
	  section.c_str(), ArPriority::FACTORY);

  myCommercialConfig->addParam(
	  ArConfigArg("MaxNumberOfLasers", 
		      &myCommercialMaxNumberOfLasers,
		      "Max number of lasers", 1, 9), 
	  section.c_str(), ArPriority::FACTORY, 
	  "SpinBox", ArConfigArg::RESTART_SOFTWARE);
  
  myCommercialConfig->addParam(
	  ArConfigArg("MaxNumberOfBatteries", 
		      &myCommercialMaxNumberOfBatteries,
		      "Max number of Batteries", 0, 9), 
	  section.c_str(), ArPriority::FACTORY, 
	  "SpinBox&&Visible:Generation!=Legacy", 
	  ArConfigArg::RESTART_SOFTWARE);

  myCommercialConfig->addParam(
	  ArConfigArg("MaxNumberOfLCDs", 
		      &myCommercialMaxNumberOfLCDs,
		      "Max number of LCDs", 0, 9), 
	  section.c_str(), ArPriority::FACTORY, 
	  "SpinBox&&Visible:Generation!=Legacy", 
	  ArConfigArg::RESTART_SOFTWARE);

  myCommercialConfig->addParam(
	  ArConfigArg("MaxNumberOfSonarBoards", 
		      &myCommercialMaxNumberOfSonarBoards,
		      "Max number of Sonar Boards", 0, 9), 
	  section.c_str(), ArPriority::FACTORY, 
	  "SpinBox&&Visible:Generation!=Legacy", 
	  ArConfigArg::RESTART_SOFTWARE);

  myCommercialConfig->addParam(ArConfigArg(ArConfigArg::SEPARATOR),
		   section.c_str(), ArPriority::FACTORY);

}

AREXPORT bool ArRobotParams::commercialProcessFile(void)
{
  myRobotLength = myRobotLengthFront + myRobotLengthRear;

  // MPL CONFIG TODO process the sonar

  if (myCommercialAddedConnectables && !myCommercialProcessedSonar)
  {
    processSonarCommercial(myCommercialConfig);
    myCommercialProcessedSonar = true;
  }

  if (!myCommercialAddedConnectables)
  {
    ArLog::log(ArLog::Normal, "ArRobotParams: Adding connectables");

    myCommercialAddedConnectables = true;
    Aria::setMaxNumLasers(myCommercialMaxNumberOfLasers);

    // if it's an MTX set the types
    if (ArUtil::strcasecmp(myClass, "Legacy") != 0)
    {
      Aria::setMaxNumBatteries(myCommercialMaxNumberOfBatteries);
      Aria::setMaxNumLCDs(myCommercialMaxNumberOfLCDs);
      Aria::setMaxNumSonarBoards(myCommercialMaxNumberOfSonarBoards);
      addSonarToConfigCommercial(myCommercialConfig, true);
    }
    else
    {
      Aria::setMaxNumBatteries(0);
      Aria::setMaxNumLCDs(0);
      Aria::setMaxNumSonarBoards(0);
      addSonarToConfigCommercial(myCommercialConfig, false);
    }

    int i;
    for (i = 1; i <= Aria::getMaxNumSonarBoards(); i++)
      addSonarBoardToConfig(i, myCommercialConfig, ourUseDefaultBehavior);
    
    for (i = 1; i <= Aria::getMaxNumLasers(); i++)
    {
      char buf[1024];
      sprintf(buf, "Laser_%d", i);
      
      addLaserToConfig(i, myCommercialConfig, ourUseDefaultBehavior, buf);
    }
    
    for (i = 1; i <= Aria::getMaxNumBatteries(); i++)
      addBatteryToConfig(i, myCommercialConfig, ourUseDefaultBehavior);
    
    for (i = 1; i <= Aria::getMaxNumLCDs(); i++)
      addLCDToConfig(i, myCommercialConfig, ourUseDefaultBehavior);
  }
  

  return true;
}


void ArRobotParams::addSonarToConfigCommercial(ArConfig *config, 
					       bool isMTXSonar)
{
  std::string section = "Sonar";

  int maxSonar = 64;
  
  config->addSection(ArConfig::CATEGORY_ROBOT_PHYSICAL,
                     section.c_str(),
                     "Definition of the sonar on this vehicle.");

  config->addParam(ArConfigArg("NumSonar", myCommercialNumSonar, "Number of sonars on this robot.", 0, maxSonar),
		   section.c_str(), ArPriority::FACTORY,
		   "SpinBox", ArConfigArg::RESTART_SOFTWARE);
  
  ArConfigArg sonar(ArConfigArg::LIST, "Sonar", "Definition of this single sonar transducer.");
  sonar.setConfigPriority(ArPriority::FACTORY);
  sonar.setRestartLevel(ArConfigArg::RESTART_SOFTWARE);

  ArConfigArg sonarX("X", 0, 
		     "Location (in mm) of this sonar transducer in X (+ front, - back) relative to the robot's idealized center of rotation.");
  sonarX.setConfigPriority(ArPriority::FACTORY);
  sonarX.setRestartLevel(ArConfigArg::RESTART_SOFTWARE);
  myCommercialSonarFieldMap[sonar.getArgCount()] = SONAR_X;
  sonar.addArg(sonarX);

  ArConfigArg sonarY("Y", 0, 
		     "Location (in mm) of this sonar transducer in Y (+ left, - right) relative to the robot's idealized center of rotation.");
  sonarY.setConfigPriority(ArPriority::FACTORY);
  sonarY.setRestartLevel(ArConfigArg::RESTART_SOFTWARE);
  myCommercialSonarFieldMap[sonar.getArgCount()] = SONAR_Y;
  sonar.addArg(sonarY);

  ArConfigArg sonarTh("Th", 0, 
		     "Rotation (in deg) of this sonar transducer (+ counterclockwise, - clockwise).", 
		     -180, 180);
  sonarTh.setConfigPriority(ArPriority::FACTORY);
  sonarTh.setRestartLevel(ArConfigArg::RESTART_SOFTWARE);
  myCommercialSonarFieldMap[sonar.getArgCount()] = SONAR_TH;
  sonar.addArg(sonarTh);

  if (isMTXSonar)
  {
    ArConfigArg sonarBoard("SonarBoard", 0, 
			   "Sonar board that is used by this transducer. 0 means that it is not yet configured.",
			   0, Aria::getMaxNumSonarBoards());
    sonarBoard.setConfigPriority(ArPriority::FACTORY);
    sonarBoard.setRestartLevel(ArConfigArg::RESTART_SOFTWARE);
    myCommercialSonarFieldMap[sonar.getArgCount()] = SONAR_BOARD;
    sonar.addArg(sonarBoard);

    ArConfigArg sonarBoardUnitPosition("SonarBoardUnitPosition", 0, 
          "Position of the transducer on the sonar board. 0 means that it is not yet configured.",
				       0, 8);
    sonarBoardUnitPosition.setConfigPriority(ArPriority::FACTORY);
    sonarBoardUnitPosition.setRestartLevel(ArConfigArg::RESTART_SOFTWARE);
    myCommercialSonarFieldMap[sonar.getArgCount()] = SONAR_BOARDUNITPOSITION;
    sonar.addArg(sonarBoardUnitPosition);
    
    ArConfigArg sonarGain("Gain", 0, 
			  "Sonar gain to be used by this transducer. 0 to use the board default.", 0, 31);

    sonarGain.setConfigPriority(ArPriority::FACTORY);
    sonarGain.setRestartLevel(ArConfigArg::RESTART_SOFTWARE);
    myCommercialSonarFieldMap[sonar.getArgCount()] = SONAR_GAIN;
    sonar.addArg(sonarGain);

		/*
    ArConfigArg sonarNoiseDelta("NoiseDelta", 0, 
				"Sonar noise delta to be used by this transducer. 0 to use the board default.", 0, 65535);
    sonarNoiseDelta.setConfigPriority(ArPriority::FACTORY);
    sonarNoiseDelta.setRestartLevel(ArConfigArg::RESTART_SOFTWARE);
    myCommercialSonarFieldMap[sonar.getArgCount()] = SONAR_NOISE_DELTA;
    sonar.addArg(sonarNoiseDelta);
		*/

    ArConfigArg sonarDetectionThreshold("DetectionThreshold", 0, 
					"Sonar detection threshold to be used by this transducer. 0 to use the board default.", 0, 65535);
    sonarDetectionThreshold.setConfigPriority(ArPriority::FACTORY);
    sonarDetectionThreshold.setRestartLevel(ArConfigArg::RESTART_SOFTWARE);
    myCommercialSonarFieldMap[sonar.getArgCount()] = SONAR_DETECTION_THRESHOLD;
    sonar.addArg(sonarDetectionThreshold);

    ArConfigArg sonarMaxRange("MaxRange", 0, 
			      "Maximum range for this transducer. 0 to use the board default.", 0, 17*255);
    sonarMaxRange.setConfigPriority(ArPriority::FACTORY);
    sonarMaxRange.setRestartLevel(ArConfigArg::RESTART_SOFTWARE);
    myCommercialSonarFieldMap[sonar.getArgCount()] = SONAR_MAX_RANGE;
    sonar.addArg(sonarMaxRange);

    ArConfigArg sonarUseForAutonomousDriving("UseForAutonomousDriving", true, 
					"Checked means use for Autonomous Driving (aka Path Planning) as well as all other driving.  Not checked means use the sonar will still be used by all other driving.");
    sonarUseForAutonomousDriving.setConfigPriority(ArPriority::FACTORY);
    sonarUseForAutonomousDriving.setRestartLevel(ArConfigArg::RESTART_SOFTWARE);
    sonarUseForAutonomousDriving.setDisplayHint("Checkbox");
    myCommercialSonarFieldMap[sonar.getArgCount()] = SONAR_USE_FOR_AUTONOMOUS_DRIVING;
    sonar.addArg(sonarUseForAutonomousDriving);
  }

  char displayHintBuf[1024];
  char nameBuf[1024];
  
  for (int ii = 0; ii < maxSonar; ii++)
  {
    snprintf(nameBuf, sizeof(nameBuf), 
             "Sonar_%d",
	     ii+1);

    snprintf(displayHintBuf, sizeof(displayHintBuf), 
             "Visible:NumSonar>%d",
	     ii);

    ArConfigArg *arg = new ArConfigArg(
	    nameBuf, sonar);

    config->addParam(*arg, section.c_str(), ArPriority::FACTORY,
		     displayHintBuf, ArConfigArg::RESTART_SOFTWARE);
  }    

  
}

void ArRobotParams::processSonarCommercial(ArConfig *config)
{
  int ii;


  std::string configSection = "Sonar";

  ArConfigSection *section = NULL;
  if ((section = Aria::getConfig()->findSection(configSection.c_str())) == NULL)
  {
    ArLog::log(ArLog::Normal, 
	       "ArRobotParams:processSonarCommercial: Can't find section '%s'", 
	       configSection.c_str());
    return;
  }

  char nameBuf[1024];

	myNumSonarUnits = myCommercialNumSonar;
	myNumSonar = myCommercialNumSonar;

  for (ii = 0; ii < myCommercialNumSonar; ii++)
  {
    snprintf(nameBuf, sizeof(nameBuf), 
             "Sonar_%d",
	     ii+1);

    ArConfigArg *argFromConfig = NULL;
    if ((argFromConfig = section->findParam(nameBuf)) == NULL)
    {
      ArLog::log(ArLog::Normal, 
	       "ArRobotParams:processSonarCommercial: Can't find parameter '%s' in section '%s'", 
		 nameBuf, configSection.c_str());
      continue;
    }

    for (int jj = 0; jj < argFromConfig->getArgCount(); jj++)
    {
      // this sets the sonar number ii field jj (mapped when added) to
      // the value of the integer, doing the same thing normally done
      // with the SonarInfo enum, but automatically instead of relying
      // on pesky humans typing
      if (argFromConfig->getArg(jj)->getType() == ArConfigArg::INT)
	mySonarMap[ii][jj] = argFromConfig->getArg(jj)->getInt();    
      else if (argFromConfig->getArg(jj)->getType() == ArConfigArg::BOOL)
	mySonarMap[ii][jj] = argFromConfig->getArg(jj)->getBool();    
    }
  }


  
}


AREXPORT void ArVideoParams::merge(const ArVideoParams& other)
{
  //printf("merge: other.type=%s, this.type=%s.\n", other.type.c_str(), type.c_str());
  if(other.type != "unknown" && other.type != "none" && other.type != "")
  {
    //printf("merge: replacing this type %s with other %s\n", type.c_str(), other.type.c_str());
    type = other.type;
  }
  if(other.connectSet)
  {
    //printf("merge: replacing this connect %d with other %d\n", connect, other.connect);
    connect = other.connect;
    connectSet = true;
  }
  if(other.imageWidth != -1)
  {
    imageWidth = other.imageWidth;
  }
  if(other.imageHeight != -1)
  {
    imageHeight = other.imageHeight;
  }
  if(other.deviceIndex != -1)
  {
    deviceIndex = other.deviceIndex;
  }
  if(other.deviceName != "none" && other.deviceName != "")
  {
    deviceName = other.deviceName;
  }
  if(other.channel != -1)
  {
    channel = other.channel;
  }
  if(other.analogSignalFormat != "none" && other.analogSignalFormat != "")
  {
    analogSignalFormat = other.analogSignalFormat;
  }
  if(other.address != "none" && other.address != "")
  {
	  //printf("merge: replacing this address %s with other %s\n", address.c_str(), other.address.c_str());
    address = other.address;
  }
  if(other.tcpPortSet)
  {
    tcpPort = other.tcpPort;
    tcpPortSet = true;
  }
  if(other.invertedSet)
  {
    //printf("merge: replacing this inverted %d with other %d\n", inverted, other.inverted);
    inverted = other.inverted;
    invertedSet = true;
  }
}

void ArPTZParams::merge(const ArPTZParams& other)
{
  if(other.type != "unknown" && other.type != "none" && other.type != "")
  {
    //printf("merge: replacing this type %s with other %s\n", type.c_str(), other.type.c_str());
    type = other.type;
  }
  if(other.connectSet)
  {
    //printf("merge: replacing this connect %d with other %d\n", connect, other.connect);
    connect = other.connect;
    connectSet = true;
  }
  if(other.serialPort != "none" && other.serialPort != "")
  {
    //printf("merge: replacing this serialPort %s with other %s\n", serialPort.c_str(), other.serialPort.c_str());
    serialPort = other.serialPort;
  }
  if(other.robotAuxPort != -1)
  {
    //printf("merge: replacing this robotAuxPort %d with other %d\n", robotAuxPort, other.robotAuxPort);
    robotAuxPort = other.robotAuxPort;
  }
  if(other.address != "none")
  {
    //printf("merge: replacing this address %s with other %s\n", address.c_str(), other.address.c_str());
    address = other.address;
  }
  if(other.tcpPortSet)
  {
    //printf("merge: replacing this tcpPort %d with other %d\n", tcpPort, other.tcpPort);
    tcpPort = other.tcpPort;
    tcpPortSet = true;
  }
  if(other.invertedSet)
  {
    //printf("merge: replacing this inverted %d with other %d\n", inverted, other.inverted);
    inverted = other.inverted;
    invertedSet = true;
  }
}

