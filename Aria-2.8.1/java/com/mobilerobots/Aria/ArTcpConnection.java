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

public class ArTcpConnection extends ArDeviceConnection {
  /* (begin code from javabody_derived typemap) */

  private long swigCPtr;

  /* for internal use by swig only */
  public ArTcpConnection(long cPtr, boolean cMemoryOwn) {
    super(AriaJavaJNI.SWIGArTcpConnectionUpcast(cPtr), cMemoryOwn);
    swigCPtr = cPtr;
  }

  /* for internal use by swig only */
  public static long getCPtr(ArTcpConnection obj) {
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
        AriaJavaJNI.delete_ArTcpConnection(swigCPtr);
      }
      swigCPtr = 0;
    }
    super.delete();
  }

  public ArTcpConnection() {
    this(AriaJavaJNI.new_ArTcpConnection(), true);
  }

  public int open(String host, int port) {
    return AriaJavaJNI.ArTcpConnection_open__SWIG_0(swigCPtr, this, host, port);
  }

  public int open(String host) {
    return AriaJavaJNI.ArTcpConnection_open__SWIG_1(swigCPtr, this, host);
  }

  public int open() {
    return AriaJavaJNI.ArTcpConnection_open__SWIG_2(swigCPtr, this);
  }

  public void setPort(String host, int port) {
    AriaJavaJNI.ArTcpConnection_setPort__SWIG_0(swigCPtr, this, host, port);
  }

  public void setPort(String host) {
    AriaJavaJNI.ArTcpConnection_setPort__SWIG_1(swigCPtr, this, host);
  }

  public void setPort() {
    AriaJavaJNI.ArTcpConnection_setPort__SWIG_2(swigCPtr, this);
  }

  public boolean openSimple() {
    return AriaJavaJNI.ArTcpConnection_openSimple(swigCPtr, this);
  }

  public int getStatus() {
    return AriaJavaJNI.ArTcpConnection_getStatus(swigCPtr, this);
  }

  public boolean close() {
    return AriaJavaJNI.ArTcpConnection_close(swigCPtr, this);
  }

  public int read(String data, long size, long msWait) {
    return AriaJavaJNI.ArTcpConnection_read__SWIG_0(swigCPtr, this, data, size, msWait);
  }

  public int read(String data, long size) {
    return AriaJavaJNI.ArTcpConnection_read__SWIG_1(swigCPtr, this, data, size);
  }

  public int write(String data, long size) {
    return AriaJavaJNI.ArTcpConnection_write(swigCPtr, this, data, size);
  }

  public String getOpenMessage(int messageNumber) {
    return AriaJavaJNI.ArTcpConnection_getOpenMessage(swigCPtr, this, messageNumber);
  }

  public ArTime getTimeRead(int index) {
    return new ArTime(AriaJavaJNI.ArTcpConnection_getTimeRead(swigCPtr, this, index), true);
  }

  public boolean isTimeStamping() {
    return AriaJavaJNI.ArTcpConnection_isTimeStamping(swigCPtr, this);
  }

  public String getHost() {
    return AriaJavaJNI.ArTcpConnection_getHost(swigCPtr, this);
  }

  public int getPort() {
    return AriaJavaJNI.ArTcpConnection_getPort(swigCPtr, this);
  }

  public int internalOpen() {
    return AriaJavaJNI.ArTcpConnection_internalOpen(swigCPtr, this);
  }

  public void setSocket(ArSocket socket) {
    AriaJavaJNI.ArTcpConnection_setSocket(swigCPtr, this, ArSocket.getCPtr(socket), socket);
  }

  public ArSocket getSocket() {
    long cPtr = AriaJavaJNI.ArTcpConnection_getSocket(swigCPtr, this);
    return (cPtr == 0) ? null : new ArSocket(cPtr, false);
  }

  public void setStatus(int status) {
    AriaJavaJNI.ArTcpConnection_setStatus(swigCPtr, this, status);
  }

  public final static class Open {
    public final static Open OPEN_NET_FAIL = new Open("OPEN_NET_FAIL", AriaJavaJNI.ArTcpConnection_OPEN_NET_FAIL_get());
    public final static Open OPEN_BAD_HOST = new Open("OPEN_BAD_HOST");
    public final static Open OPEN_NO_ROUTE = new Open("OPEN_NO_ROUTE");
    public final static Open OPEN_CON_REFUSED = new Open("OPEN_CON_REFUSED");

    public final int swigValue() {
      return swigValue;
    }

    public String toString() {
      return swigName;
    }

    public static Open swigToEnum(int swigValue) {
      if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
        return swigValues[swigValue];
      for (int i = 0; i < swigValues.length; i++)
        if (swigValues[i].swigValue == swigValue)
          return swigValues[i];
      throw new IllegalArgumentException("No enum " + Open.class + " with value " + swigValue);
    }

    private Open(String swigName) {
      this.swigName = swigName;
      this.swigValue = swigNext++;
    }

    private Open(String swigName, int swigValue) {
      this.swigName = swigName;
      this.swigValue = swigValue;
      swigNext = swigValue+1;
    }

    private Open(String swigName, Open swigEnum) {
      this.swigName = swigName;
      this.swigValue = swigEnum.swigValue;
      swigNext = this.swigValue+1;
    }

    private static Open[] swigValues = { OPEN_NET_FAIL, OPEN_BAD_HOST, OPEN_NO_ROUTE, OPEN_CON_REFUSED };
    private static int swigNext = 0;
    private final int swigValue;
    private final String swigName;
  }

}
