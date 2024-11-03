#pragma once
#include <mez/merize/merize.h>
#include <mez/merize/entity/BaseEntity.h>
#include <mez/merize/entity/Entity3D.h>
#include <mez/merize/ren/camera.h>

//Todo: make this a base class of sorts, and move it to MERIZE
class TstEntityCameraController : public MezEntity3DTransform
{
public:
	DECLARE_ENTITY(TstEntityCameraController);
	virtual void Initialize();
	virtual void Update();
	~TstEntityCameraController();
	MezCamera m_Camera;

	EHandle m_Target;
};