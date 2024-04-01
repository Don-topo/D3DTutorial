#pragma once

#include <Runtime/Core/Core.h>
#include <Runtime/Graphics/Pipeline/InputLayout/SemanticName.h>
#include <Runtime/Graphics/Pipeline/InputLayout/SlotClass.h>
#include <Runtime/Graphics/Pipeline/InputLayout/PrimitiveMode.h>

#include <Runtime/Graphics/Texture/TextureFormat.h>

#include <vector>

struct InputLayoutDesc
{
	std::vector<SemanticName> SemanticNames;
	std::vector<TextureFormat> InputFormats;
	std::vector<uint32> SemanticIndices;
	std::vector<uint32> InputSlotIndices;
	std::vector<uint32> AlignedByteOffsets;
	std::vector<SlotClass> SlotClasses;
	std::vector<uint32> InstanceDataSteps;
	PrimitiveMode PrimitiveMode;
};