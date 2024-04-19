#pragma once

#include <vector>
#include <memory>

#include <glad/glad.h>

class Player
{
    friend class Render; friend class Shader; friend class Texture;

    public:
        Player(std::string name);
        
        const std::string& get_name() const;

        void move_right();
        void move_left();
        void move_up();
        void move_down();
        void move_forward();
        void move_backward();

        void reset_stats();
        void reset_position();

        void init(float health, float speed,
                  std::vector<float> defaultGeometry);

    private:
        std::string name;

        float health;
        float speed;
        std::vector<float> initialStats;

        GLuint vertexArrayObject;
        GLuint vertexBufferObject;
        GLuint indexBufferObject;
        GLuint shaderProgram;
        GLuint textureObject;
        std::string texturePath;
        int textureWidth;
        int textureHeight;
        int textureChannels;

        float translationX;
        float translationY;
        float translationZ;
        float rotationX;
        float rotationY;
        float rotationZ;
        float scaleX;
        float scaleY;
        float scaleZ;
        std::vector<float> initialGeometry;
};
using PlayerPtr = std::shared_ptr<Player>;
using PlayerPtrList = std::vector<PlayerPtr>;
extern PlayerPtrList players;
