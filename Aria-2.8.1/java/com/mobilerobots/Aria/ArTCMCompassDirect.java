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

public class ArTCMCompassDirect extends ArTCM2 {
  /* (begin code from javabody_derived typemap) */

  private long swigCPtr;

  /* for internal use by swig only */
  public ArTCMCompassDirect(long cPtr, boolean cMemoryOwn) {
    super(AriaJavaJNI.SWIGArTCMCompassDirectUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  /* for internal use by swig only */
  public static long getCPtr(ArTCMCompassDirect obj) {
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
        AriaJavaJNI.delete_ArTCMCompassDirect(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public ArTCMCompassDirect(ArDeviceConnection devCon) {
    this(AriaJavaJNI.new_ArTCMCompassDirect__SWIG_0(ArDeviceConnection.getCPtr(devCon), devCon), true);
  }

  public ArTCMCompassDirect(String serialPortName) {
    this(AriaJavaJNI.new_ArTCMCompassDirect__SWIG_1(serialPortName), true);
  }

  public ArTCMCompassDirect() {
    this(AriaJavaJNI.new_ArTCMCompassDirect__SWIG_2(), true);
  }

  public boolean connect() {
    return AriaJavaJNI.ArTCMCompassDirect_connect(swigCPtr, this);
  }

  public boolean blockingConnect(long connectTimeout) {
    return AriaJavaJNI.ArTCMCompassDirect_blockingConnect__SWIG_0(swigCPtr, this, connectTimeout);
  }

  public boolean blockingConnect() {
    return AriaJavaJNI.ArTCMCompassDirect_blockingConnect__SWIG_1(swigCPtr, this);
  }

  public void commandAutoCalibration() {
    AriaJavaJNI.ArTCMCompassDirect_commandAutoCalibration(swigCPtr, this);
  }

  public void commandUserCalibration() {
    AriaJavaJNI.ArTCMCompassDirect_commandUserCalibration(swigCPtr, this);
  }

  public void commandStopCalibration() {
    AriaJavaJNI.ArTCMCompassDirect_commandStopCalibration(swigCPtr, this);
  }

  public void commandContinuousPackets() {
    AriaJavaJNI.ArTCMCompassDirect_commandContinuousPackets(swigCPtr, this);
  }

  public void commandOnePacket() {
    AriaJavaJNI.ArTCMCompassDirect_commandOnePacket(swigCPtr, this);
  }

  public void commandOff() {
    AriaJavaJNI.ArTCMCompassDirect_commandOff(swigCPtr, this);
  }

  public void commandSoftReset() {
    AriaJavaJNI.ArTCMCompassDirect_commandSoftReset(swigCPtr, this);
  }

  public void commandJustCompass() {
    AriaJavaJNI.ArTCMCompassDirect_commandJustCompass(swigCPtr, this);
  }

  public int read(long msWait) {
    return AriaJavaJNI.ArTCMCompassDirect_read__SWIG_0(swigCPtr, this, msWait);
  }

  public int read() {
    return AriaJavaJNI.ArTCMCompassDirect_read__SWIG_1(swigCPtr, this);
  }

  public void setDeviceConnection(ArDeviceConnection devCon) {
    AriaJavaJNI.ArTCMCompassDirect_setDeviceConnection(swigCPtr, this, ArDeviceConnection.getCPtr(devCon), devCon);
  }

  public ArDeviceConnection getDeviceConnetion() {
    long cPtr = AriaJavaJNI.ArTCMCompassDirect_getDeviceConnetion(swigCPtr, this);
    return (cPtr == 0) ? null : new ArDeviceConnection(cPtr, false);
  }

}
