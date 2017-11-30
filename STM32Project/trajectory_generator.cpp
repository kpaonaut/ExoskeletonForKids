#include "parameters.h"
#include "hip.h"
#include "knee.h"
#include "spline.h"
#include <iostream> // debug
#include <cstdio>
#include <cstdlib>
#include <vector>

class TrajectoryGenerator{
private:
    float t, walking_angle, sample_time, halfTotalTime;
    int rightStarted, doneKnee, doneHip;
    StepHipTraj hip_trajectory_generator_l, hip_trajectory_generator_r;
    StepKneeTraj knee_trajectory_generator_l, knee_trajectory_generator_r;
public:
     TrajectoryGenerator( t = 0, walking_angle = par::_walking_angle_, sample_time = 0.001, halfTotalTime = 1) // FIXME: the step time is set to be very small because plot is too slow
        t(t),
        walking_angle(walking_angle),
        sample_time(sample_time), // in seconds
        rightStarted(0), // the right leg has not yet started!
        halfTotalTime(halfTotalTime)
        {
        // left Hip
        hip_trajectory_generator_l = StepHipTraj();  // new object

        hip_trajectory_generator_l.reset();
        hip_trajectory_generator_l.set_max_hip_flexion( par::_max_hip_flexion_ ); // degrees, default 36
        hip_trajectory_generator_l.set_max_hip_flexion_time( par::_max_hip_flexion_time_portion_ * halfTotalTime / sample_time);       // in ms
        hip_trajectory_generator_l.set_step_time( halfTotalTime / sample_time ); // in ms, integer. 5000 here.
        hip_trajectory_generator_l.set_walking_angle( walking_angle ); // offset, can vary
        hip_trajectory_generator_l.set_swing_start( par::_hip_swing_start_ ); // default -6.934
        hip_trajectory_generator_l.set_step_range( par::_step_range_ ); // step length in meter. example: 0.78m legLen 1.1m -> theta 41.8
        hip_trajectory_generator_l.set_leg_length( par::_leg_length_ );

        // left Knee
        knee_trajectory_generator_l = StepKneeTraj();  // new object

        knee_trajectory_generator_l.reset();
        knee_trajectory_generator_l.set_max_hip_flexion_time( par::_max_hip_flexion_time_portion_*halfTotalTime/sample_time );       // in ms
        knee_trajectory_generator_l.set_step_time( halfTotalTime / sample_time ); // in ms, integer. 5000 here.
        knee_trajectory_generator_l.set_max_knee_flexion( par::_max_knee_flexion_ ); // in degrees
        knee_trajectory_generator_l.set_second_knee_flexion( par::_second_knee_flexion_ );
        knee_trajectory_generator_l.set_min_knee_flexion( par::_min_knee_flexion_ );
        knee_trajectory_generator_l.set_walking_angle( walking_angle ); 

        hip_trajectory_generator_l.init(); // set coordinates for interpolation
        knee_trajectory_generator_l.init();
/*
        // right Hip
        hip_trajectory_generator_r = StepHipTraj();  // right leg

        hip_trajectory_generator_r.reset();
        hip_trajectory_generator_r.set_max_hip_flexion( par::_max_hip_flexion_ ); // degrees, default 36
        hip_trajectory_generator_r.set_max_hip_flexion_time( par::_max_hip_flexion_time_portion_ * halfTotalTime/sample_time);       // in ms
        hip_trajectory_generator_r.set_step_time( halfTotalTime / sample_time ); // in ms, integer. 5000 here.
        hip_trajectory_generator_r.set_walking_angle( walking_angle );                 // offset, can vary
        hip_trajectory_generator_r.set_swing_start( par::_hip_swing_start_ ); // default -6.934
        hip_trajectory_generator_r.set_step_range( par::_step_range_ ); // step length in meter. example: 0.78m legLen 1.1m -> theta 41.8
        hip_trajectory_generator_r.set_leg_length( par::_leg_length_ );

        // right Knee
        knee_trajectory_generator_r = StepKneeTraj();  // new object

        knee_trajectory_generator_r.reset();
        knee_trajectory_generator_r.set_max_hip_flexion_time( par::_max_hip_flexion_time_portion_*halfTotalTime/sample_time );       // in ms
        knee_trajectory_generator_r.set_step_time( halfTotalTime/sample_time ); // in ms, integer. 5000 here.
        knee_trajectory_generator_r.set_max_knee_flexion( par::_max_knee_flexion_ ); // in degrees
        knee_trajectory_generator_r.set_second_knee_flexion( par::_second_knee_flexion_ );
        knee_trajectory_generator_r.set_min_knee_flexion( par::_min_knee_flexion_ );
        knee_trajectory_generator_r.set_walking_angle( walking_angle );

        hip_trajectory_generator_r.init() // set coordinates for interpolation
        knee_trajectory_generator_r.init()
*/
        doneHip = 0;
        doneKnee = 0;
        stopTriggered = 0;
    }

    inline void stopTrigger(){ // reserved interface for outside triggering!
        stopTriggered = 1;
    }

    inline void resumeTrigger(){
        stopTriggered = 0;
    }

    void carryOut(){ // carry out calculation
        float hip_value_l = hip_trajectory_generator_l.Increment();
        float knee_value_l = knee_trajectory_generator_l.Increment(); // generate traj in next time step
        // two knees are stoped together, as their derivative happen to be 0 at the same time, one at minima, one at maxima
        // two hips are stopeed the same way.
        if ((rightStarted == 1) || (hip_trajectory_generator_l.get_time() > halfTotalTime))
        {
            hip_value_r = hip_trajectory_generator_r.Increment();
            knee_value_r = knee_trajectory_generator_r.Increment(); // generate traj in next time step
            rightStarted = 1;
        }
        else
        {
            hip_value_r = hip_trajectory_generator_r.get_initial_pos();
            knee_value_r = knee_trajectory_generator_r.get_initial_pos();
        }
        
        doneHip = doneHipl | doneHipr;
        doneKnee = doneKneel | doneKneer;
    }

    float generateTrajectory(){
        if (stopTriggered)
            if (doneHip == 0)
                carryOut();

        else // stop signal not triggered
            carryOut();
        
        angles = [walking_angle, hip_value_l - walking_angle, knee_value_l,
                           hip_value_r - walking_angle, knee_value_r];
        // print hip_trajectory_generator_l.get_time(), hip_trajectory_generator_r.get_time()
        return hip_value_l;
    }

    inline float getTime() return hip_trajectory_generator_l.get_time();
};