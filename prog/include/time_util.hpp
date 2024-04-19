#pragma once

class Time_util
{
    public:
        const float& get_delta_time() const;
        
        void update_delta_time();

    private:
        float delta_time = 0.0f;
        float current_time = 0.0f;
        float last_time = 0.0f;
};
extern Time_util time_util;
