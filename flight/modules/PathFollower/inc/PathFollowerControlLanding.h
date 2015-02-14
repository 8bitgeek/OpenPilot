/**
 ******************************************************************************
 * @addtogroup OpenPilotModules OpenPilot Modules
 * @{
 * @addtogroup PathFollower CONTROL interface class
 * @brief CONTROL interface class for pathfollower goal fsm implementations
 * @{
 *
 * @file       PathFollowerCONTROL.h
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
#ifndef PATHFOLLOWERCONTROLLANDING_H
#define PATHFOLLOWERCONTROLLANDING_H
#include "PathFollowerControl.h"
#include "PIDControlThrust.h"
#include "PIDControlNE.h"
// forward decl
class PathFollowerFSM;
class PathFollowerControlLanding : PathFollowerControl {
private:
    static PathFollowerControlLanding *p_inst;
    PathFollowerControlLanding();


public:
    static PathFollowerControlLanding *instance()
    {
        if (!p_inst) {
            p_inst = new PathFollowerControlLanding();
        }
        return p_inst;
    }

    int32_t Initialize(PathFollowerFSM *fsm_ptr,
                       VtolPathFollowerSettingsData *vtolPathFollowerSettings,
                       PathDesiredData *pathDesired,
                       FlightStatusData *flightStatus,
                       PathStatusData *pathStatus);


    void Activate(void);
    void Deactivate(void);
    void SettingsUpdated(void);
    void UpdateAutoPilot(void);
    void ObjectiveUpdated(void);
    uint8_t IsActive(void);

private:
    void UpdateVelocityDesired(void);
    int8_t UpdateStabilizationDesired(bool yaw_attitude, float yaw_direction);
    void setArmedIfChanged(uint8_t val);

    PathFollowerFSM *fsm;
    VtolPathFollowerSettingsData *vtolPathFollowerSettings;
    PathDesiredData *pathDesired;
    FlightStatusData *flightStatus;
    PathStatusData *pathStatus;
    PIDControlThrust controlThrust;
    PIDControlNE controlNE;
    uint8_t mActive;
};

#endif // PATHFOLLOWERCONTROLLANDING_H
