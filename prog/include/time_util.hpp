#pragma once

class TimeUtil
{
    public:
        const float& get_delta_time() const;
        
        void update_delta_time();

    private:
        float deltaTime = 0.0f;
        float currentTime = 0.0f;
        float lastTime = 0.0f;
};
extern TimeUtil time_util;
