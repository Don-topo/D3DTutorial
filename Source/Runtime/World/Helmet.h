#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/World/GameObject.h>

class Helmet : public GameObject
{
public:
	Helmet();
	Helmet(const Helmet&) = delete;
	Helmet& operator=(const Helmet&) = delete;
	~Helmet() = default;

	void Update() override;

private:

};