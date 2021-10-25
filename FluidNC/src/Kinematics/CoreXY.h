// Copyright (c) 2021 -	Bart Dring
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#pragma once

/*
	CoreXY.h

	This implements CoreXY Kinematics

    Ref: https://corexy.com/

*/

#include "Kinematics.h"

namespace Kinematics {
    class CoreXY : public KinematicSystem {
    public:
        CoreXY() = default;

        CoreXY(const CoreXY&) = delete;
        CoreXY(CoreXY&&)      = delete;
        CoreXY& operator=(const CoreXY&) = delete;
        CoreXY& operator=(CoreXY&&) = delete;

        // Kinematic Interface

        void init() override;
        bool kinematics_homing(AxisMask cycle_mask) override;
        void kinematics_post_homing() override;
        bool cartesian_to_motors(float* target, plan_line_data_t* pl_data, float* position) override;
        void motors_to_cartesian(float* cartesian, float* motors, int n_axis) override;
        bool limitsCheckTravel(float* target) override;

        // Configuration handlers:
        void validate() const override {}
        void group(Configuration::HandlerBase& handler) override;
        void afterParse() override {}

        // Name of the configurable. Must match the name registered in the cpp file.
        const char* name() const override { return "CoreXY"; }

        ~CoreXY() {}

    private:
        void lengths_to_xy(float left_length, float right_length, float& x, float& y);
        void xy_to_lengths(float x, float y, float& left_length, float& right_length);

        void plan_homing_move(AxisMask axisMask, bool approach, bool seek);

        void  transform_cartesian_to_motors(float* motors, float* cartesian);
        float three_axis_dist(float* point1, float* point2);

        float _x_scaler       = 1;
        float _y_scaler       = 1;
        float _segment_length = 10;
    };
}  //  namespace Kinematics
