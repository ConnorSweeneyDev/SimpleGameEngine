#include "Player.hpp"

PlayerPtrList players;

Player::Player(std::string name) { this->name = name; }

const std::string& Player::getName() const { return name; }

void Player::MoveRight() { translationX += speed * time_util.getDeltaTime(); }
void Player::MoveLeft() { translationX -= speed * time_util.getDeltaTime(); }
void Player::MoveUp() { translationY += speed * time_util.getDeltaTime(); }
void Player::MoveDown() { translationY -= speed * time_util.getDeltaTime(); }
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
    translationX = initialGeometry[0];
    translationY = initialGeometry[1];
    translationZ = initialGeometry[2];
    rotationX = initialGeometry[3];
    rotationY = initialGeometry[4];
    rotationZ = initialGeometry[5];
    scaleX = initialGeometry[6];
    scaleY = initialGeometry[7];
    scaleZ = initialGeometry[8];
}

void Player::init(float health, float speed,
                  std::vector<float> defaultGeometry)
{
    initialStats.push_back(this->health = health);
    initialStats.push_back(this->speed = speed);

    initialGeometry.push_back(this->translationX = defaultGeometry[0]);
    initialGeometry.push_back(this->translationY = defaultGeometry[1]);
    initialGeometry.push_back(this->translationZ = defaultGeometry[2]);
    initialGeometry.push_back(this->rotationX = defaultGeometry[3]);
    initialGeometry.push_back(this->rotationY = defaultGeometry[4]);
    initialGeometry.push_back(this->rotationZ = defaultGeometry[5]);
    initialGeometry.push_back(this->scaleX = defaultGeometry[6]);
    initialGeometry.push_back(this->scaleY = defaultGeometry[7]);
    initialGeometry.push_back(this->scaleZ = defaultGeometry[8]);
}
