#include "parameters.h"
#include "hip.h"
#include "knee.h"
#include "spline.h"
#include <cstdio>
#include <cstdlib>
#include <vector>

class TrajectoryGenerator{
private:
    float t, walking_angle, sample_time, halfTotalTime;
    int rightStarted, doneKnee, doneHip, stopTriggered;
    StepHipTraj hip_trajectory_generator_l, hip_trajectory_generator_r;
    StepKneeTraj knee_trajectory_generator_l, knee_trajectory_generator_r;
    float hip_angle, knee_angle;

public:
     TrajectoryGenerator(float t = 0, float walking_angle = _walking_angle_, float sample_time = 0.001, float halfTotalTime = 1): // FIXME: the step time is set to be very small because plot is too slow
        t(t),
        walking_angle(walking_angle),
        sample_time(sample_time), // in seconds
        rightStarted(0), // the right leg has not yet started!
        halfTotalTime(halfTotalTime)
        {
        // left Hip
        hip_trajectory_generator_l = StepHipTraj();  // new object

        hip_trajectory_generator_l.reset();
        hip_trajectory_generator_l.set_max_hip_flexion( _max_hip_flexion_ ); // degrees, default 36
        hip_trajectory_generator_l.set_second_hip_flexion( _second_hip_flexion_ ); // degrees, default 36
        hip_trajectory_generator_l.set_max_hip_flexion_time( _max_hip_flexion_time_portion_ * halfTotalTime / sample_time);       // in ms
        hip_trajectory_generator_l.set_step_time( halfTotalTime / sample_time ); // in ms, integer. 5000 here.
        hip_trajectory_generator_l.set_walking_angle( walking_angle ); // offset, can vary
        hip_trajectory_generator_l.set_swing_start( _hip_swing_start_ ); // default -6.934
        hip_trajectory_generator_l.set_step_range( _step_range_ ); // step length in meter. example: 0.78m legLen 1.1m -> theta 41.8
        hip_trajectory_generator_l.set_leg_length( _leg_length_ );

        // left Knee
        knee_trajectory_generator_l = StepKneeTraj();  // new object

        knee_trajectory_generator_l.reset();
        knee_trajectory_generator_l.set_max_hip_flexion_time( _max_hip_flexion_time_portion_*halfTotalTime/sample_time );       // in ms
        knee_trajectory_generator_l.set_step_time( halfTotalTime / sample_time ); // in ms, integer. 5000 here.
        knee_trajectory_generator_l.set_max_knee_flexion( _max_knee_flexion_ ); // in degrees
        knee_trajectory_generator_l.set_second_knee_flexion( _second_knee_flexion_ );
        knee_trajectory_generator_l.set_min_knee_flexion( _min_knee_flexion_ );
        knee_trajectory_generator_l.set_walking_angle( walking_angle );

        hip_trajectory_generator_l.init(); // set coordinates for interpolation
        knee_trajectory_generator_l.init();

        doneHip = 0;
        doneKnee = 0;
        stopTriggered = 0;
        hip_angle = 0;  // will be altering with time
        knee_angle = 0; //
    }

    inline void stopTrigger(){ // reserved interface for outside triggering!
        stopTriggered = 1;
    }

    inline void resumeTrigger(){
        stopTriggered = 0;
    }

    void carryOut(){ // carry out calculation
        doneHip = hip_trajectory_generator_l.Increment(&hip_angle);
        doneKnee = knee_trajectory_generator_l.Increment(&knee_angle); // generate traj in next time step
    }

    float generateTrajectory(){
        if (stopTriggered)
            if (doneHip == 0)
                carryOut();
            else;
        else // stop signal not triggered
            carryOut();

        return hip_angle; // only return hip! When is knee needed?
    }

    inline float getTime() {return hip_trajectory_generator_l.get_time();}
};
