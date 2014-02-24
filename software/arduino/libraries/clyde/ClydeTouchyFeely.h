/*
  Copyright (c) 2013-2014, Fabule Fabrications Inc, All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, version 3.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General
  Public License along with this library.
*/

#ifndef __CLYDETOUCHYFEELY_H
#define __CLYDETOUCHYFEELY_H

#include "ClydeModule.h"
#include "Clyde.h"
#include "MPR121.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

/**
 * The Touchy Feely personality module.
 */
class CClydeTouchyFeely : public CClydeModule {
  static const uint8_t DEVICE_ADDR = 0x5A;        /**< i2c address of mpr121 */
  static const uint16_t ID_LOW = 1001;            /**< low limit of read identification value */
  static const uint16_t ID_HIGH = 1007;           /**< high limit of read identification value */

  static const uint32_t TICKLE_INTERVAL = 2500;    /**< max time in millis between touch events to trigger laugh */
  static const uint8_t TICKLE_REPEAT = 4;         /**< number of consecutive touch events to trigger laugh */
  
  static const RGB SELECT_COLORS[];           /**< colors of the color select cycle */
  static const uint16_t SELECT_INTERVALS[];       /**< intervals of the color select cycle */
  static const uint8_t SELECT_STEPS = 8;          /**< steps in the color select cycle */
  
  MPR121 m_mpr121;          /**< interface to the mpr121 */
  uint8_t m_tickleCount;    /**< number of detected tickle touch events */
  uint32_t m_firstTickle;   /**< time in millis we detected the first tickle tap */
  uint8_t m_lastStopStep;   /**< step index when the color select cycle was stopped. */
  
  RGB m_laughColors[CClyde::CAmbientCycle::MAX_CYCLE_LENGTH];           /**< colors of the laugh cycle */   //this could be in the main class
  uint16_t m_laughIntervals[CClyde::CAmbientCycle::MAX_CYCLE_LENGTH];   /**< intervals of the laugh cycle */
  
public:  
  /** Constructor. */
  CClydeTouchyFeely();
  
  /**
   * Initialize the module with specified analog and digital pins.
   */  
  bool init(uint8_t apin, uint8_t dpin);

  /**
   * Update the module using the specified analog and digital pins.
   */  
  void update(uint8_t apin, uint8_t dpin);
  
private:
  /** Check if the detected touch is tickling. */
  void tickleCheck();
  
  /** Start laugh cycle. */
  //TODO this should be in the main class
  void laugh();
  
  /** Start the color select cycle. */
  void startColorSelect();
  
  /** Stop the color select cycle. */
  void stopColorSelect();
  
  /** Debug autoconfig values. */
  void debugAutoConfig();
};

//TODO
//using this as a singleton means that it would get
//confused if we're using two identical modules
extern CClydeTouchyFeely TouchyFeely;

#endif