#!/usr/bin/env python3
__author__ = 'Bradley Perry'

import numpy as np


class Pilot:
    def __init__(self, height=1.75, mass=80.7):
        self.Calculate(height, mass)

    def Calculate(self, height=None, mass=None):
        if height is not None:
            self.height = height
        if mass is not None:
            self.mass = mass
        self.m_shank = 0.061 * self.mass
        self.m_thigh = 0.1 * self.mass
        self.m_torso = 0.678 * self.mass

        self.l_shank = 0.285 * self.height
        self.l_thigh = 0.2450 * self.height
        self.l_torso = 0.470 * self.height
        self.l_foot = 0.13 * self.height
        self.CalculateCOM()
        self.CalculateMOI()

    def CalculateCOM(self):
        self.d_shank = 0.394 * self.l_shank
        self.d_thigh = 0.567 * self.l_thigh
        self.d_torso = 0.626 * self.l_torso

    def CalculateMOI(self):
        I_shank = self.m_shank * (self.l_shank * 0.416) ** 2
        I_thigh = self.m_thigh * (self.l_thigh * 0.323) ** 2
        I_torso = self.m_torso * (self.l_torso * 0.496) ** 2


class PoseEstimator:
    def __init__(self, pilot=None):
        if pilot is None:
            self.pilot = Pilot()
        else:
            self.pilot = pilot
        # this matrix transforms from relative to absolute angles when multiplied by the relative angle vector
        # relative angles = [torso, stance/rear hip, stance/rear knee, swing/front hip, swing/front knee]
        # absolute angles = [stance/rear shank, stance/rear thigh, torso, swing/front thigh, swing/front knee]
        self.transform_matrix = np.array([[1, -1, 1, 0, 0],
                                          [1, -1, 0, 0, 0],
                                          [1, 0, 0, 0, 0],
                                          [-1, 0, 0, 1, 0],
                                          [-1, 0, 0, 1, -1]])

    def _RelativeToAbsoluteAngle(self, angles):
        return np.dot(self.transform_matrix, angles)

    def _RadToDeg(self, angles):
        return 180.0 / np.pi * angles

    def _DegToRad(self, angles):
        return np.pi / 180.0 * angles

    def CalculatePose(self, exo_angles, pivot=None):
        if pivot is None:
            pivot = np.array([0.0, 0.0])

        angles = self._RelativeToAbsoluteAngle(exo_angles)
        angles = self._DegToRad(angles)
        joint_positions = np.zeros((8, 2))

        x_stance_toe = pivot[0]
        y_stance_toe = pivot[1]

        # x_stance_heel = pivot[0] - self.pilot.l_foot * np.cos(angles[0] - 0.3)
        # y_stance_heel = pivot[1] + self.pilot.l_foot * np.sin(angles[0] - 0.3)

        x_stance_heel = pivot[0] - self.pilot.l_foot * np.cos(angles[0])
        y_stance_heel = pivot[1] + self.pilot.l_foot * np.sin(angles[0])

        x_stance_knee = x_stance_heel + self.pilot.l_shank * np.sin(angles[0])
        y_stance_knee = y_stance_heel + self.pilot.l_shank * np.cos(angles[0])

        x_hip = x_stance_knee + self.pilot.l_thigh * np.sin(angles[1])
        y_hip = y_stance_knee + self.pilot.l_thigh * np.cos(angles[1])

        x_torso = x_hip + self.pilot.l_torso * np.sin(angles[2])
        y_torso = y_hip + self.pilot.l_torso * np.cos(angles[2])

        x_swing_knee = x_hip + self.pilot.l_thigh * np.sin(angles[3])
        y_swing_knee = y_hip - self.pilot.l_thigh * np.cos(angles[3])

        x_swing_heel = x_swing_knee + self.pilot.l_shank * np.sin(angles[4])
        y_swing_heel = y_swing_knee - self.pilot.l_shank * np.cos(angles[4])

        # x_swing_toe = x_swing_heel + self.pilot.l_foot
        # y_swing_toe = y_swing_heel

        x_swing_toe = x_swing_heel + self.pilot.l_foot * np.sin(np.pi / 2 - angles[4])
        y_swing_toe = y_swing_heel - self.pilot.l_foot * np.cos(np.pi / 2 + angles[4])
        if y_swing_toe <= 0:
            y_swing_toe = 0.0
            x_swing_toe = np.sqrt(self.pilot.l_foot ** 2 + y_swing_heel ** 2) + x_swing_heel

        joint_positions[0] = [x_stance_toe, y_stance_toe]
        joint_positions[1] = [x_stance_heel, y_stance_heel]
        joint_positions[2] = [x_stance_knee, y_stance_knee]
        joint_positions[3] = [x_hip, y_hip]
        joint_positions[4] = [x_torso, y_torso]
        joint_positions[5] = [x_swing_knee, y_swing_knee]
        joint_positions[6] = [x_swing_heel, y_swing_heel]
        joint_positions[7] = [x_swing_toe, y_swing_toe]
        return joint_positions


def main():
    exo_angles = np.array([10.0000, -30.8004, 0, 44.1681, 40.1681])
    estimator = PoseEstimator()
    blah = estimator.CalculatePose(exo_angles)
    np.set_printoptions(precision=3, suppress=True)
    print(blah)


if __name__ == "__main__":
    main()
