#include "player.h"

Player::Player(Vector3 startPos, const char* modelPath) : Entity(startPos)
{
	model = LoadModel(modelPath);
	maxHp = 100;
	hp = maxHp;
}

Player::~Player()
{
	UnloadModel(model);
}

void Player::Update()
{
	Vector3 forward = {0.0f, 0.0f, 0.0f};
	Vector3 right = {0.0f, 0.0f, 0.0f};

	position.y = 0.5f;

	Move(forward, right);
	SetRotation(forward);
}

void Player::Move(Vector3 forward, Vector3 right)
{
	float dt = GetFrameTime();
	Vector3 moveDir = {0, 0, 0};

	if (IsKeyDown(KEY_W)) moveDir = Vector3Add(moveDir, forward);
    if (IsKeyDown(KEY_S)) moveDir = Vector3Subtract(moveDir, forward);
    if (IsKeyDown(KEY_A)) moveDir = Vector3Subtract(moveDir, right);
    if (IsKeyDown(KEY_D)) moveDir = Vector3Add(moveDir, right);

    if (Vector3Length(moveDir) > 0.0f)
    {
    	moveDir = Vector3Normalize(moveDir);
    	position = Vector3Add(position, Vector3Scale(moveDir, speed * dt));
    }
}

void Player::SetRotation(Vector3 forward)
{
	float angleY = atan2f(forward.x, forward.z);
	rotation.y = angleY * (180.0f / PI);
}

void Player::ClampHP()
{
	if (hp < 0) hp = 0;
	if (hp > maxHp) hp = maxHp;
}

void Player::Draw()
{
	DrawModel(model, position, 1.0f, WHITE);
}