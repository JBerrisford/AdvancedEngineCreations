#ifndef _PINWHEEL_H
#define _PINWHEEL_H

#include "Object.h"

class Pinwheel
{
public:
	Pinwheel();
	~Pinwheel();

	void Render();
	void Update(float deltaTime);

	void SetFanRotate(bool newRotate) { mFanRotate = newRotate; };
	bool GetFanRotate() { return mFanRotate; };

	void SetStandRotate(bool newRotate) { mStandRotate = newRotate; };
	bool GetPoleRotate() { return mStandRotate; };

	void SetCanAddStand(bool canAdd) { mCanAddStand = canAdd; };
	void SetCanAddFan(bool canAdd) { mCanAddFan = canAdd; };


private:
	Object* mBase;
	Object* mStand;
	Object* mPinwheel;

	float mCurrentWheelRot;
	float mCurrentStandRot;
	const float fWheelRotSpeed = 5.0f;
	const float fStandRotSpeed = 2.0f;
		
	bool mCanAddStand;
	bool mCanAddFan;

	bool mFanRotate;
	bool mStandRotate;
};

#endif //_PINWHEEL_H

