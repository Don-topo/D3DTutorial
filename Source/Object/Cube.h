#pragma once

#include <Object/Object.h>

class Cube : public Object
{
public:
	Cube();
	~Cube() = default;

	void Update() override;

private:

};