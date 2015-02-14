/**
 ******************************************************************************
 * @addtogroup OpenPilotModules OpenPilot Modules
 * @{
 * @addtogroup PathFollower CONTROL interface class
 * @brief CONTROL interface class for pathfollower goal fsm implementations
 * @{
 *
 * @file       PIDControlNE.h
 * @author     The OpenPilot Team, http://www.openpilot.org Copyright (C) 2015.
 * @brief      Executes CONTROL for landing sequence
 *
 * @see        The GNU Public License (GPL) Version 3
 *
 *****************************************************************************/
/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
 * for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#ifndef PIDCONTROLNE_H
#define PIDCONTROLNE_H
extern "C" {
#include <pid.h>
}
#include "PathFollowerFSM.h"

class PIDControlNE {
public:
    PIDControlNE();
    ~PIDControlNE();
    void Initialize(PathFollowerFSM *fsm);
    void Deactivate();
    void Activate();
    void UpdateParameters(float kp, float ki, float kd, __attribute__((unused)) float ilimit, float dT, float velocityMax);
    void UpdatePositionalParameters(float kp);
    void UpdateVelocitySetpoint(float setpointNorth, float setpointEast);
    void UpdatePositionSetpoint(float setpointNorth, float setpointEast);
    // void RateLimit(float *spDesired, float *spCurrent, float rateLimit);
    void UpdateVelocityState(float pvNorth, float pvEast);
    void UpdatePositionState(float pvNorth, float pvEast);
    void UpdateCommandParameters(float minCommand, float maxCommand, float velocityFeedforward);
    void ControlPosition();
    void GetNECommand(float *northCommand, float *eastCommand);
    void GetVelocityDesired(float *north, float *east);

private:
    struct pid2 PIDvel[2]; // North, East
    struct pid PIDposH[2];
    float mVelocitySetpointTarget[2];
    float mPositionSetpointTarget[2];
    float mVelocityState[2];
    float mPositionState[2];


    float deltaTime;
    float mVelocitySetpointCurrent[2];
    float mNECommand;
    PathFollowerFSM *mFSM;
    float mNeutral;
    float mVelocityMax;
    float mMinCommand;
    float mMaxCommand;
    float mVelocityFeedforward;
    uint8_t mActive;
};

#endif // PIDCONTROLNE_H
