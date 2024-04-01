#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/Pipeline/Blend/RenderTargetBlendDesc.h>

struct BlenderStateDesc
{
	bool AlphaToCoverageEnable;
	bool IndependentBlendEnable;
	RenderTargetBlendDesc RenderTargetBlendDescs;
};