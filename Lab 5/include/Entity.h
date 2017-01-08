#pragma once

class Entity
{
	public:
		virtual void init() {}
		virtual void update(float t) {}
		virtual void update() {} //Overload of the update function

		//virtual void render(CameraComponent camera);
};