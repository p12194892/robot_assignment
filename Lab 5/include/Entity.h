#pragma once

class Entity
{

	protected:
	
		//Make this be inhertited by everything and get working :)
	public:
	//	virtual void init() = 0;
		virtual void update(float t) = 0;
	//	virtual void draw() = 0;
};