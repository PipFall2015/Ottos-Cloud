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

public class ArTCM2 {
  /* (begin code from javabody typemap) */

  private long swigCPtr;
  protected boolean swigCMemOwn;

  /* for internal use by swig only */
  public ArTCM2(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  /* for internal use by swig only */
  public static long getCPtr(ArTCM2 obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  /* (end code from javabody typemap) */

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        AriaJavaJNI.delete_ArTCM2(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public boolean connect() {
    return AriaJavaJNI.ArTCM2_connect(swigCPtr, this);
  }

  public boolean blockingConnect(long connectTimeout) {
    return AriaJavaJNI.ArTCM2_blockingConnect__SWIG_0(swigCPtr, this, connectTimeout);
  }

  public boolean blockingConnect() {
    return AriaJavaJNI.ArTCM2_blockingConnect__SWIG_1(swigCPtr, this);
  }

  public double getHeading() {
    return AriaJavaJNI.ArTCM2_getHeading(swigCPtr, this);
  }

  public boolean haveHeading() {
    return AriaJavaJNI.ArTCM2_haveHeading(swigCPtr, this);
  }

  public double getCompass() {
    return AriaJavaJNI.ArTCM2_getCompass(swigCPtr, this);
  }

  public double getPitch() {
    return AriaJavaJNI.ArTCM2_getPitch(swigCPtr, this);
  }

  public boolean havePitch() {
    return AriaJavaJNI.ArTCM2_havePitch(swigCPtr, this);
  }

  public double getRoll() {
    return AriaJavaJNI.ArTCM2_getRoll(swigCPtr, this);
  }

  public boolean haveRoll() {
    return AriaJavaJNI.ArTCM2_haveRoll(swigCPtr, this);
  }

  public double getXMagnetic() {
    return AriaJavaJNI.ArTCM2_getXMagnetic(swigCPtr, this);
  }

  public boolean haveXMagnetic() {
    return AriaJavaJNI.ArTCM2_haveXMagnetic(swigCPtr, this);
  }

  public double getYMagnetic() {
    return AriaJavaJNI.ArTCM2_getYMagnetic(swigCPtr, this);
  }

  public boolean haveYMagnetic() {
    return AriaJavaJNI.ArTCM2_haveYMagnetic(swigCPtr, this);
  }

  public double getZMagnetic() {
    return AriaJavaJNI.ArTCM2_getZMagnetic(swigCPtr, this);
  }

  public boolean haveZMagnetic() {
    return AriaJavaJNI.ArTCM2_haveZMagnetic(swigCPtr, this);
  }

  public double getTemperature() {
    return AriaJavaJNI.ArTCM2_getTemperature(swigCPtr, this);
  }

  public boolean haveTemperature() {
    return AriaJavaJNI.ArTCM2_haveTemperature(swigCPtr, this);
  }

  public int getError() {
    return AriaJavaJNI.ArTCM2_getError(swigCPtr, this);
  }

  public double getCalibrationH() {
    return AriaJavaJNI.ArTCM2_getCalibrationH(swigCPtr, this);
  }

  public boolean haveCalibrationH() {
    return AriaJavaJNI.ArTCM2_haveCalibrationH(swigCPtr, this);
  }

  public double getCalibrationV() {
    return AriaJavaJNI.ArTCM2_getCalibrationV(swigCPtr, this);
  }

  public boolean haveCalibrationV() {
    return AriaJavaJNI.ArTCM2_haveCalibrationV(swigCPtr, this);
  }

  public double getCalibrationM() {
    return AriaJavaJNI.ArTCM2_getCalibrationM(swigCPtr, this);
  }

  public boolean haveCalibrationM() {
    return AriaJavaJNI.ArTCM2_haveCalibrationM(swigCPtr, this);
  }

  public void commandOff() {
    AriaJavaJNI.ArTCM2_commandOff(swigCPtr, this);
  }

  public void commandOnePacket() {
    AriaJavaJNI.ArTCM2_commandOnePacket(swigCPtr, this);
  }

  public void commandContinuousPackets() {
    AriaJavaJNI.ArTCM2_commandContinuousPackets(swigCPtr, this);
  }

  public void commandUserCalibration() {
    AriaJavaJNI.ArTCM2_commandUserCalibration(swigCPtr, this);
  }

  public void commandAutoCalibration() {
    AriaJavaJNI.ArTCM2_commandAutoCalibration(swigCPtr, this);
  }

  public void commandStopCalibration() {
    AriaJavaJNI.ArTCM2_commandStopCalibration(swigCPtr, this);
  }

  public void commandSoftReset() {
    AriaJavaJNI.ArTCM2_commandSoftReset(swigCPtr, this);
  }

  public void commandJustCompass() {
    AriaJavaJNI.ArTCM2_commandJustCompass(swigCPtr, this);
  }

  public int getPacCount() {
    return AriaJavaJNI.ArTCM2_getPacCount(swigCPtr, this);
  }

  public void addHeadingDataCallback(SWIGTYPE_p_ArFunctor1T_double_t f) {
    AriaJavaJNI.ArTCM2_addHeadingDataCallback(swigCPtr, this, SWIGTYPE_p_ArFunctor1T_double_t.getCPtr(f));
  }

}
