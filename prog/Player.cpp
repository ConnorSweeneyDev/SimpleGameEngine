#include "Player.hpp"

PlayerPtrList players;

Player::Player(std::string name) { this->name = name; }

const std::string& Player::getName() const { return name; }

void Player::MoveUp() { translationY += speed * time_util.getDeltaTime(); }
void Player::MoveDown() { translationY -= speed * time_util.getDeltaTime(); }
void Player::MoveLeft() { translationX -= speed * time_util.getDeltaTime(); }
void Player::MoveRight() { translationX += speed * time_util.getDeltaTime(); }
void Player::MoveForward() { translationZ -= speed * time_util.getDeltaTime(); }
void Player::MoveBackward() { translationZ += speed * time_util.getDeltaTime(); }

void Player::RotateXPos(float speed) { rotationX += speed * time_util.getDeltaTime(); }
void Player::RotateXNeg(float speed) { rotationX -= speed * time_util.getDeltaTime(); }
void Player::RotateYPos(float speed) { rotationY += speed * time_util.getDeltaTime(); }
void Player::RotateYNeg(float speed) { rotationY -= speed * time_util.getDeltaTime(); }
void Player::RotateZPos(float speed) { rotationZ += speed * time_util.getDeltaTime(); }
void Player::RotateZNeg(float speed) { rotationZ -= speed * time_util.getDeltaTime(); }

void Player::ScaleXPos(float speed) { scaleX += speed * time_util.getDeltaTime(); }
void Player::ScaleXNeg(float speed) { scaleX -= speed * time_util.getDeltaTime(); }
void Player::ScaleYPos(float speed) { scaleY += speed * time_util.getDeltaTime(); }
void Player::ScaleYNeg(float speed) { scaleY -= speed * time_util.getDeltaTime(); }
void Player::ScaleZPos(float speed) { scaleZ += speed * time_util.getDeltaTime(); }
void Player::ScaleZNeg(float speed) { scaleZ -= speed * time_util.getDeltaTime(); }

void Player::ResetStats()
{
    health = initialStats[0];
    speed = initialStats[1];
}
void Player::ResetPosition()
{
    translationX = initialPosition[0];
    translationY = initialPosition[1];
    translationZ = initialPosition[2];
    rotationX = initialPosition[3];
    rotationY = initialPosition[4];
    rotationZ = initialPosition[5];
    scaleX = initialPosition[6];
    scaleY = initialPosition[7];
    scaleZ = initialPosition[8];
}

void Player::init(
                  float health, float speed,
                  std::vector<float> defaultPosition
                 )
{
    initialStats.push_back(this->health = health);
    initialStats.push_back(this->speed = speed);

    initialPosition.push_back(this->translationX = defaultPosition[0]);
    initialPosition.push_back(this->translationY = defaultPosition[1]);
    initialPosition.push_back(this->translationZ = defaultPosition[2]);
    initialPosition.push_back(this->rotationX = defaultPosition[3]);
    initialPosition.push_back(this->rotationY = defaultPosition[4]);
    initialPosition.push_back(this->rotationZ = defaultPosition[5]);
    initialPosition.push_back(this->scaleX = defaultPosition[6]);
    initialPosition.push_back(this->scaleY = defaultPosition[7]);
    initialPosition.push_back(this->scaleZ = defaultPosition[8]);
}
