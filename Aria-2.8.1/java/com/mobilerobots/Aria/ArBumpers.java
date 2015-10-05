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
/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 1.3.40
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.mobilerobots.Aria;

public class ArBumpers extends ArRangeDevice {
  /* (begin code from javabody_derived typemap) */

  private long swigCPtr;

  /* for internal use by swig only */
  public ArBumpers(long cPtr, boolean cMemoryOwn) {
    super(AriaJavaJNI.SWIGArBumpersUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  /* for internal use by swig only */
  public static long getCPtr(ArBumpers obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  /* (end code from javabody_derived typemap) */

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        AriaJavaJNI.delete_ArBumpers(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public ArBumpers(long currentBufferSize, long cumulativeBufferSize, String name, int maxSecondsToKeepCurrent, double angleRange) {
    this(AriaJavaJNI.new_ArBumpers__SWIG_0(currentBufferSize, cumulativeBufferSize, name, maxSecondsToKeepCurrent, angleRange), true);
  }

  public ArBumpers(long currentBufferSize, long cumulativeBufferSize, String name, int maxSecondsToKeepCurrent) {
    this(AriaJavaJNI.new_ArBumpers__SWIG_1(currentBufferSize, cumulativeBufferSize, name, maxSecondsToKeepCurrent), true);
  }

  public ArBumpers(long currentBufferSize, long cumulativeBufferSize, String name) {
    this(AriaJavaJNI.new_ArBumpers__SWIG_2(currentBufferSize, cumulativeBufferSize, name), true);
  }

  public ArBumpers(long currentBufferSize, long cumulativeBufferSize) {
    this(AriaJavaJNI.new_ArBumpers__SWIG_3(currentBufferSize, cumulativeBufferSize), true);
  }

  public ArBumpers(long currentBufferSize) {
    this(AriaJavaJNI.new_ArBumpers__SWIG_4(currentBufferSize), true);
  }

  public ArBumpers() {
    this(AriaJavaJNI.new_ArBumpers__SWIG_5(), true);
  }

  public void setRobot(ArRobot robot) {
    AriaJavaJNI.ArBumpers_setRobot(swigCPtr, this, ArRobot.getCPtr(robot), robot);
  }

  public void processReadings() {
    AriaJavaJNI.ArBumpers_processReadings(swigCPtr, this);
  }

  public void addBumpToBuffer(int bumpValue, int whichBumper) {
    AriaJavaJNI.ArBumpers_addBumpToBuffer(swigCPtr, this, bumpValue, whichBumper);
  }

}
