#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H
class GameManager {
public:
	GameManager() {}
	virtual ~GameManager() {}

	virtual bool OnCreate() = 0;
	virtual void Update(const float deltaTime_) = 0;
	virtual void Render() = 0;
};
#endif

