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

public class ArMath {
  /* (begin code from javabody typemap) */

  private long swigCPtr;
  protected boolean swigCMemOwn;

  /* for internal use by swig only */
  public ArMath(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  /* for internal use by swig only */
  public static long getCPtr(ArMath obj) {
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
        AriaJavaJNI.delete_ArMath(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  public static double epsilon() {
    return AriaJavaJNI.ArMath_epsilon();
  }

  public static double addAngle(double ang1, double ang2) {
    return AriaJavaJNI.ArMath_addAngle(ang1, ang2);
  }

  public static double subAngle(double ang1, double ang2) {
    return AriaJavaJNI.ArMath_subAngle(ang1, ang2);
  }

  public static double fixAngle(double angle) {
    return AriaJavaJNI.ArMath_fixAngle(angle);
  }

  public static double degToRad(double deg) {
    return AriaJavaJNI.ArMath_degToRad(deg);
  }

  public static double radToDeg(double rad) {
    return AriaJavaJNI.ArMath_radToDeg(rad);
  }

  public static double cos(double angle) {
    return AriaJavaJNI.ArMath_cos(angle);
  }

  public static double sin(double angle) {
    return AriaJavaJNI.ArMath_sin(angle);
  }

  public static double tan(double angle) {
    return AriaJavaJNI.ArMath_tan(angle);
  }

  public static double atan2(double y, double x) {
    return AriaJavaJNI.ArMath_atan2(y, x);
  }

  public static boolean angleBetween(double angle, double startAngle, double endAngle) {
    return AriaJavaJNI.ArMath_angleBetween(angle, startAngle, endAngle);
  }

  public static double fabs(double val) {
    return AriaJavaJNI.ArMath_fabs(val);
  }

  public static int roundInt(double val) {
    return AriaJavaJNI.ArMath_roundInt(val);
  }

  public static short roundShort(double val) {
    return AriaJavaJNI.ArMath_roundShort(val);
  }

  public static void pointRotate(double[] x, double[] y, double th) {
    AriaJavaJNI.ArMath_pointRotate(x, y, th);
  }

  public static int random() {
    return AriaJavaJNI.ArMath_random();
  }

  public static int getRandMax() {
    return AriaJavaJNI.ArMath_getRandMax();
  }

  public static int randomInRange(int m, int n) {
    return AriaJavaJNI.ArMath_randomInRange(m, n);
  }

  public static double distanceBetween(double x1, double y1, double x2, double y2) {
    return AriaJavaJNI.ArMath_distanceBetween(x1, y1, x2, y2);
  }

  public static double squaredDistanceBetween(double x1, double y1, double x2, double y2) {
    return AriaJavaJNI.ArMath_squaredDistanceBetween(x1, y1, x2, y2);
  }

  public static double log2(double x) {
    return AriaJavaJNI.ArMath_log2(x);
  }

  public static boolean isNan(double d) {
    return AriaJavaJNI.ArMath_isNan__SWIG_0(d);
  }

  public static boolean isNan(float f) {
    return AriaJavaJNI.ArMath_isNan__SWIG_1(f);
  }

  public static boolean isFinite(float f) {
    return AriaJavaJNI.ArMath_isFinite__SWIG_0(f);
  }

  public static boolean isFinite(double d) {
    return AriaJavaJNI.ArMath_isFinite__SWIG_1(d);
  }

  public static boolean compareFloats(double f1, double f2, double epsilon) {
    return AriaJavaJNI.ArMath_compareFloats__SWIG_0(f1, f2, epsilon);
  }

  public static boolean compareFloats(double f1, double f2) {
    return AriaJavaJNI.ArMath_compareFloats__SWIG_1(f1, f2);
  }

  public ArMath() {
    this(AriaJavaJNI.new_ArMath(), true);
  }

}
