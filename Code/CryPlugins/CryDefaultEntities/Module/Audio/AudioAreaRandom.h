// Copyright 2001-2016 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "AudioEntitiesUtils.h"
#include "Helpers/DesignerEntityComponent.h"
#include <CrySerialization/Decorators/ResourcesAudio.h>

class CAudioAreaRandom final
	: public CDesignerEntityComponent<>
	  , public IEntityPropertyGroup
{
	CRY_ENTITY_COMPONENT_INTERFACE_AND_CLASS(CAudioAreaRandom, "AudioAreaRandom", 0x8952D4D63E2347D5, 0x86EC4724BF34789F);

public:
	CAudioAreaRandom() = default;
	virtual ~CAudioAreaRandom() {}

	// CNativeEntityBase
	virtual uint64                GetEventMask() const override { return CDesignerEntityComponent::GetEventMask() | BIT64(ENTITY_EVENT_ENTERNEARAREA) | BIT64(ENTITY_EVENT_MOVENEARAREA) | BIT64(ENTITY_EVENT_ENTERAREA) | BIT64(ENTITY_EVENT_MOVEINSIDEAREA) | BIT64(ENTITY_EVENT_LEAVEAREA) | BIT64(ENTITY_EVENT_LEAVENEARAREA); }
	virtual void                  ProcessEvent(SEntityEvent& event) override;

	virtual IEntityPropertyGroup* GetPropertyGroup() final { return this; }

	virtual void                  OnResetState() override;
	// ~CNativeEntityBase

	// IEntityPropertyGroup
	virtual const char* GetLabel() const override { return "AudioAreaAmbience Properties"; }

	virtual void        SerializeProperties(Serialization::IArchive& archive) override;
	// ~IEntityPropertyGroup

private:
	void       Play();
	void       Stop();
	Vec3       GenerateOffset();
	void       UpdateFadeValue(float distance);
	void       UpdateRtpc();
	const bool IsPlaying() const { return m_currentlyPlayingTriggerId != CryAudio::InvalidControlId; }

	CryAudio::ControlId      m_playTriggerId = CryAudio::InvalidControlId;
	CryAudio::ControlId      m_stopTriggerId = CryAudio::InvalidControlId;
	CryAudio::ControlId      m_parameterId = CryAudio::InvalidControlId;

	CryAudio::ControlId      m_currentlyPlayingTriggerId = CryAudio::InvalidControlId;

	string                   m_playTriggerName;
	string                   m_stopTriggerName;

	string                   m_parameterName;

	CryAudio::EOcclusionType m_occlusionType = CryAudio::EOcclusionType::Ignore;

	bool                     m_bTriggerAreasOnMove = false;
	bool                     m_bMoveWithEntity = false;

	float                    m_minDelay = 0.0f;
	float                    m_maxDelay = 1000.0f;
	float                    m_radius = 10.0f;
	float                    m_fadeValue = 0.0;
	bool                     m_bEnabled = true;
	EAreaState               m_areaState = EAreaState::Outside;
	float                    m_parameterDistance = 5.0f;

	bool                     m_bPlaying = false;
	int                      m_timerId = 0;
};
