#pragma once
#include "Core/GlobalDefines.h"
#include "Prog2D-Raylib/raylib.h"
#include "Prog2D-Raylib/raymath.h"
#include <vector>
#include <string>
#include "Core/pugixml.hpp"


enum EOnActionFinished
{
	ToDefault = 0u,
	ToAction,
	Freeze,
	Loop,	
};



class CAction
{
public:

	struct SFrame
	{
		SFrame() : fDuration(0.001f), vUVs(Vector4(0.f, 0.f, 1.f, 1.f)) {};
		SFrame(float _fDuration, const Vector4& _vUVs) : fDuration(_fDuration), vUVs(_vUVs) {};
		SFrame(const SFrame& _other) : fDuration(_other.fDuration), vUVs(_other.vUVs) {}; 
		SFrame(SFrame&& _other) noexcept: fDuration(_other.fDuration), vUVs(_other.vUVs) {};
		SFrame( const pugi::xml_node& _rNode);

		~SFrame() {};

		float fDuration = 0.001f;
		Vector4 vUVs = Vector4(0.f, 0.f, 1.f, 1.f);
		
	};

	struct SUpdateResult
	{
		SUpdateResult() : fExtraTime(0.0f), bIsFinished(false) {};
		SUpdateResult(float _fExtraTime, bool _bIsFinished) : fExtraTime(_fExtraTime), bIsFinished(_bIsFinished) {};
		SUpdateResult(const SUpdateResult& _other) : fExtraTime(_other.fExtraTime), bIsFinished(_other.bIsFinished) {};
		SUpdateResult(SUpdateResult&& _other) noexcept : fExtraTime(_other.fExtraTime), bIsFinished(_other.bIsFinished) {};
		~SUpdateResult() {};

		float fExtraTime{ 0.f };
		bool bIsFinished{false};

	};


	CAction();
	CAction(const pugi::xml_node& oRoot);
	virtual ~CAction();

	void ConfigureAction(const char* _pFilePath);
	void Start(float _fStartTime);
	SUpdateResult Update(float _fTimeStep);

	float GetFrameToTime(float _fframe);
	float GetTimeToFrame(float _fTime);

	const std::string& GetActionName() const { return m_sActionName; }

	// m_tFrames
	const std::vector<SFrame>& GetFrames() const { return m_tFrames; }
	unsigned int GetNumFrames() const { return static_cast<unsigned int>(m_tFrames.size()); }
	// m_uPriority
	unsigned int GetPriority() const { return m_uPriority; }
	// m_eOnActionFinished
	EOnActionFinished GetOnActionFinished() const { return m_eOnActionFinished; }
	// m_sNextAction
	const std::string& GetNextAction() const { return m_sNextAction; }
	// m_sTexturePath
	std::string GetTexturePath() const { return m_sTexturePath; }
	// m_pTexture
	Texture* GetTexture() const { return m_pTexture; }
	// m_fDuration
	float GetDuration() const { return m_fDuration; }
	// m_fCurrentTime
	float GetCurrentTime() const { return m_fCurrentTime; }
	void SetCurrentTime(float fTime);
	// m_fCurrentFrame
	float GetCurrentFrame() const { return m_fCurrentFrame; }
	void SetCurrentFrame(float fFrame);

	const SFrame& GetCurrentFrameInfo() const;

private:

	void SetCurrentTimeClean(float _fTime);
	void SetCurrentFrameClean(float _fFrame);

private:

	std::string m_sActionName{};
	std::vector<SFrame> m_tFrames{};
	unsigned int m_uPriority{ 0 };
	EOnActionFinished m_eOnActionFinished;
	std::string m_sNextAction{};
	std::string m_sTexturePath{};
	Texture* m_pTexture{};

	float m_fDuration = 0.f;
	float m_fCurrentTime = 0.f;
	float m_fCurrentFrame = 0.f;

	bool m_bIsDirty = false;
	

};