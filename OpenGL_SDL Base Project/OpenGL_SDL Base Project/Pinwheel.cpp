#include "Pinwheel.h"

Pinwheel::Pinwheel()
{
	mBase = new Object("base.obj");
	mBase->AddComponent(MODEL_RENDERER);
	mStand = new Object("pole.obj");
	mStand->AddComponent(MODEL_RENDERER);
	mPinwheel = new Object("pinwheel.obj");
	mPinwheel->AddComponent(MODEL_RENDERER);

	mCurrentStandRot = 0.0f;
	mCurrentWheelRot = 0.0f;

	mFanRotate = false;
	mStandRotate = false;

	mCanAddFan = true;
	mCanAddStand = false;
}

Pinwheel::~Pinwheel()
{
	delete mBase;
	delete mStand;
	delete mPinwheel;
}

void Pinwheel::Update(float deltaTime)
{
	if (mFanRotate && mCanAddFan)
	{
		mCurrentWheelRot += fWheelRotSpeed;
	}
	else if (mFanRotate && !mCanAddFan)
	{
		mCurrentWheelRot -= fWheelRotSpeed;
	}

	if (mStandRotate)
	{
		if (mCanAddStand)
		{
			mCurrentStandRot += fStandRotSpeed;

			if (mCurrentStandRot >= 60.0f)
			{
				mCanAddStand = false;
			}
		}
		else
		{
			mCurrentStandRot -= fStandRotSpeed;

			if (mCurrentStandRot <= -60.0f)
			{
				mCanAddStand = true;
			}
		}
	}
}

void Pinwheel::Render()
{	
	glRotatef(90, 0, 1, 0);
	mBase->Render();
	
	glPushMatrix();
		glRotatef(mCurrentStandRot, 0, 1, 0);
		mStand->Render();
	
		glPushMatrix();	
			glTranslatef(1.9f, 26.4f, 0.0f);
			glRotatef(mCurrentWheelRot, 1, 0, 0);
			mPinwheel->Render();
		glPopMatrix();
	glPopMatrix();
}