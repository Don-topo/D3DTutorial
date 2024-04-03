#include <Runtime/Graphics/Sampler/Sampler.h>
#include <Runtime/Graphics/Pipeline/Pipeline.h>
#include <Runtime/Graphics/Buffer/GraphicsBuffer.h>
#include <Runtime/Graphics/Command/CommandList.h>
#include <Runtime/Resources/ResourceImporter.h>
#include <Runtime/Resources/Mesh/Mesh.h>
#include <Runtime/Resources/Texture/TextureResource.h>
#include <Runtime/Graphics/GraphicsManager.h>
#include <Runtime/Window/WindowManager.h>
#include <Runtime/Application/ApplicationManager.h>
#include <Runtime/World/ObjectPipeline.h>


struct CBData
{
	XMMATRIX World;
	XMMATRIX View;
	XMMATRIX Projection;
};

int main()
{	
	auto app = ApplicationManager::GetInstance().GetApplication();

	auto objectPipeline = std::make_shared<ObjectPipeline>();

	auto testMesh = std::make_shared<Mesh>();
	auto testColor = std::make_shared<TextureResource>();
	auto testEmmisive = std::make_shared<TextureResource>();
	auto testNormal = std::make_shared<TextureResource>();
	ResourceImporter::ReadStaticMeshFile(R"(C:\Users\ruben\Documents\UOC\TFM\Directx12Course\glTF-Sample-Models\2.0\DamagedHelmet\glTF\DamagedHelmet.gltf)", testMesh);
	ResourceImporter::ReadTextureFile(R"(C:\Users\ruben\Documents\UOC\TFM\Directx12Course\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_albedo.jpg)", testColor);
	ResourceImporter::ReadTextureFile(R"(C:\Users\ruben\Documents\UOC\TFM\Directx12Course\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_emissive.jpg)", testEmmisive);
	ResourceImporter::ReadTextureFile(R"(C:\Users\ruben\Documents\UOC\TFM\Directx12Course\glTF-Sample-Models\2.0\DamagedHelmet\glTF\Default_normal.jpg)", testNormal);

	CBData modelMatrix = {
		.World = XMMatrixIdentity(),
		.View = XMMatrixIdentity(),
		.Projection = XMMatrixIdentity()
	};
	GraphicsBufferDesc cbDesc = {};
	cbDesc.ResourceUsage = ResourceUsage::DYNAMIC;
	cbDesc.CPUAccess = BufferCPUAccess::WRITE;
	cbDesc.Usage = BufferUsage::CONSTANT_BUFFER;
	cbDesc.SizeInBytes = sizeof(CBData);
	cbDesc.StructureByteStride = sizeof(XMMATRIX);
	cbDesc.MiscFlags = 0;
	cbDesc.InitialData = &modelMatrix;

	auto cb = GraphicsManager::GetInstance().GetMainDevice()->CreateGraphicsBuffer(cbDesc);

	XMFLOAT3 pos = { 0.0f, 0.0f, 0.0f };
	XMFLOAT3 rot = { 90.0f, 0.0f, 0.0f };
	XMFLOAT3 scale = { 1.0f,1.0f, 1.0 };

	while (app->IsRunning())
	{
		app->Run();

		rot.y += 0.5f;

		modelMatrix.World = XMMatrixTranspose(XMMatrixScaling(scale.x, scale.y, scale.z) * 
			XMMatrixRotationRollPitchYaw(XMConvertToRadians(rot.x), XMConvertToRadians(rot.y), XMConvertToRadians(rot.z)) * XMMatrixTranslation(pos.x, pos.y, pos.z));
		modelMatrix.View = XMMatrixTranspose(XMMatrixLookAtLH({ 0.0f, 0.0f, -3.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 1.0f, 0.0f }));
		modelMatrix.Projection = XMMatrixTranspose(XMMatrixPerspectiveFovLH(XMConvertToRadians(74.0f), 
			(float)WindowManager::GetInstance().GetWindow()->GetWindowSize().x / (float)WindowManager::GetInstance().GetWindow()->GetWindowSize().y, 0.1f, 100.0f));
		
		app->GetCommandList()->BindPipeline(objectPipeline->GetPipeline());
		app->GetCommandList()->BindVertexBuffer({ testMesh->GetPositionBuffer(), testMesh->GetTexCoordBuffer(), testMesh->GetNormalBuffer()});
		app->GetCommandList()->BindIndexBuffer({ testMesh->GetIndexBuffer()});
		app->GetCommandList()->BindViewPort(WindowManager::GetInstance().GetWindow()->GetWindowSize());

		app->GetCommandList()->UpdateDynamicBuffer(cb, &modelMatrix, sizeof(CBData));
		app->GetCommandList()->BindResources({ testColor->GetTextureView(), testEmmisive->GetTextureView(), testNormal->GetTextureView()}, { objectPipeline->GetSampler()}, {}, ShaderStage::PixelShader);
		app->GetCommandList()->BindResources({}, {}, { cb }, ShaderStage::VertexShader);

		app->GetCommandList()->DrawIndexed(testMesh->GetIndices().size(), 0, 0);

		GraphicsManager::GetInstance().GetMainDevice()->ExecuteCommandLists({ app->GetCommandList() });
		GraphicsManager::GetInstance().GetMainDevice()->Present();

	}

	return 0;
}