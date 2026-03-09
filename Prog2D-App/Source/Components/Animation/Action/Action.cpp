#include "Action.h"
#include "Render/RenderEngine.h"



CAction::CAction() 
{
	// en algun momento hace cosas
}

CAction::CAction(const pugi::xml_node& oRoot)
{

	GET_VARIABLE_VALUE_WITH_ERROR(string, m_sActionName, sActionName, "", "Action has no ActionName. -_-");
	GET_VARIABLE_VALUE(uint, m_uPriority, uPriority, 0);
	GET_VARIABLE_VALUE(string, m_sNextAction, sNextAction, "");
	GET_VARIABLE_VALUE_WITH_ERROR(string, m_sTexturePath, sTexturePath, "", "Action has no TexturePath. -_-");
	if (pugi::xml_node oNode = oRoot.find_child([](const pugi::xml_node& _oNode) { return strcmp(_oNode.name(), "sTexturePath") == 0; })) {
		if (pugi::xml_attribute oValue = oNode.attribute("value")) {
			m_sTexturePath = oValue.as_string();
		}
		else {
			m_sTexturePath = ""; TraceLog(LOG_ERROR, "Action has no TexturePath. -_-");
		}
	}
	else {
		m_sTexturePath = ""; TraceLog(LOG_ERROR, "Action has no TexturePath. -_-");
	};	GET_VARIABLE_COLLECTION(m_tFrames, tFrames);

	m_fDuration = 0;
	for (SFrame& oFrame : m_tFrames)
	{
		m_fDuration += oFrame.fDuration;
	}

	if (!m_pTexture && !m_sTexturePath.empty())
	{
		m_pTexture = CRenderEngine::GetInstance()->LoadTexture2D(m_sTexturePath.c_str());
	}

}

CAction::~CAction() 	
{
	CRenderEngine::GetInstance()->UnloadTexture2D(m_pTexture);
}

CAction::SFrame::SFrame(const pugi::xml_node& oNode)
{
	GET_ATTRIBUTE(float, fDuration, fDuration, 0.04166666667f);
	GET_ATTRIBUTES_AS_VECTOR4(vUVs, fU1, fV1, fU2, fV2, 0.f, 0.f, 1.f, 1.f);
}

//void CAction::ConfigureAction(const char* _pFilePath)
//{
//	//m_pTexture = CRenderEngine::GetInstance()->LoadTexture2D(m_sTexturePath);
//
//	if (strstr(_pFilePath, ".act"))
//	{
//		pugi::xml_document oActionDoc;
//		pugi::xml_parse_result oResult = oActionDoc.load_file(_pFilePath);
//
//		if (oResult)
//		{
//			START_DESERIALIZATION(oActionDoc)
//			GET_VARIABLE_VALUE_WITH_ERROR(string, m_sActionName, sActionName, "", "ACTION NAME HAS NO VALUE!!!!");
//			GET_VARIABLE_VALUE(uint, m_uPriority, uPriority, 0u);
//			GET_VARIABLE_VALUE(string, m_sNextAction, sNextAction, "");
//			GET_VARIABLE_VALUE_WITH_ERROR(string, m_sTexturePath, sTexturePath, "", "ACTION HAS NO TEXTURE!!!!");
//
//			if (pugi::xml_node oOnActionFinishedNode =  Node.find_child([](const pugi::xml_node& _oNode) { return strcmp(_oNode.name(), "eOnActionFinished") == 0;}))
//			{
//				if (pugi::xml_attribute oOnActionFinishedAtt = oOnActionFinishedNode.attribute("Value"))
//				{
//					const char* sEnumString = oOnActionFinishedAtt.as_string();
//					if (strcmp(sEnumString, "ToDefault") == 0)
//					{
//						m_eOnActionFinished = EOnActionFinished::ToDefault;
//					}
//					else if (strcmp(sEnumString, "ToAction") == 0)
//					{
//						m_eOnActionFinished = EOnActionFinished::ToAction;
//					}
//					else if (strcmp(sEnumString, "Freeze") == 0)
//					{
//						m_eOnActionFinished = EOnActionFinished::Freeze;
//					}
//					else if (strcmp(sEnumString, "Loop") == 0)
//					{
//						m_eOnActionFinished = EOnActionFinished::Loop;
//					}
//					else if (strcmp(sEnumString, "") == 0)
//					{
//						m_eOnActionFinished = EOnActionFinished::ToDefault;
//					}
//					else
//					{
//						TraceLog(LOG_ERROR, "INCORRECT VALUE NAME!!!!");
//					}
//				}
//				else
//				{
//					m_eOnActionFinished = EOnActionFinished::ToDefault;
//				}
//			}
//			else
//			{
//				m_eOnActionFinished = EOnActionFinished::ToDefault;
//			}
//
//			CREATE_COLLECTION(SFrame, m_tFrames, tFrames);
//			END_DESERIALIZATION()
//		}
//		else
//		{
//			TraceLog(LOG_ERROR, oResult.description());
//		}
//	}
//	else
//	{
//		TraceLog(LOG_ERROR, "ACTION FILE PATH HAS INCORRECT FILE TYPE!!!!");
//	}
//}

void CAction::Start(float _fStartTime)
{
	SetCurrentTime(_fStartTime);
}

CAction::SUpdateResult CAction::Update(float _fTimeStep)
{
	SUpdateResult oUpdateResult;
	float fNewTime = m_fCurrentTime + _fTimeStep;
	
	if (fNewTime >= m_fDuration - EPS_3)
	{
		oUpdateResult.bIsFinished = true;
		float fExtraTime = fNewTime - m_fDuration;

		switch (m_eOnActionFinished)
		{
		case Freeze:
		{
			oUpdateResult.fExtraTime = 0.f;
			oUpdateResult.bIsFinished = m_fCurrentTime < m_fDuration - EPS_3 || m_bIsDirty ;
			SetCurrentTimeClean(m_fDuration);
		}
		break;
		case Loop:
		{
			oUpdateResult.bIsFinished = false;
			SetCurrentTimeClean(oUpdateResult.fExtraTime);
			oUpdateResult.fExtraTime = 0.f;
		}
		case ToDefault:
		case ToAction:
		default:
		{
			SetCurrentTimeClean(m_fDuration);
		}
		break;
		}
	}
	else
	{
		SetCurrentTimeClean(fNewTime);
	}

	m_bIsDirty = false;
	return oUpdateResult;
}

float CAction::GetFrameToTime(float _fframe)
{
	unsigned int uFrame = static_cast<unsigned int>(_fframe);
	
	float fReturn = 0.f;
	if (uFrame < m_tFrames.size())
	{
		unsigned int i = 0;

		while (i < uFrame)
		{
			fReturn += m_tFrames[i].fDuration;
			++i;
		}

		float fAux = static_cast<float>(i);
		fAux = _fframe - fAux;

		fReturn += m_tFrames[i].fDuration * fAux;
	}
	else
	{
		fReturn = m_fDuration;
	}

	return fReturn;
}

float CAction::GetTimeToFrame(float _fTime)
{
	float fReturn = 0.f;
	if (_fTime < m_fDuration)
	{
		unsigned int i = 0u;
		while (m_tFrames[i].fDuration <= _fTime)
		{
			_fTime -= m_tFrames[i].fDuration;
			++i;
		}

		float fFramePercentage = _fTime / m_tFrames[i].fDuration;
		fReturn = static_cast<float>(i) + fFramePercentage;
	}
	else
	{
		fReturn = static_cast<float>(m_tFrames.size());
	}
	return fReturn;
}

void CAction::SetCurrentTime(float fTime)
{
	m_fCurrentTime = std::max(0.f, std::min(fTime, m_fDuration));
	m_fCurrentFrame = GetTimeToFrame(m_fCurrentTime);
	m_bIsDirty = true;
}

void CAction::SetCurrentFrame(float fFrame)
{
	m_fCurrentFrame = std::max(0.f, std::min(fFrame, static_cast<float>(GetNumFrames())));
	m_fCurrentFrame = GetFrameToTime(m_fCurrentFrame);
	m_bIsDirty = true;

}

const CAction::SFrame& CAction::GetCurrentFrameInfo() const
{
	return m_tFrames[static_cast<unsigned int>(m_fCurrentFrame)];
}

void CAction::SetCurrentTimeClean(float _fTime)
{
	m_fCurrentTime = std::max(0.f, std::min(_fTime, m_fDuration));
	m_fCurrentFrame = GetTimeToFrame(m_fCurrentTime);
	
}

void CAction::SetCurrentFrameClean(float _fFrame)
{
	m_fCurrentFrame = std::max(0.f, std::min(_fFrame, static_cast<float>(GetNumFrames())));
	m_fCurrentFrame = GetFrameToTime(m_fCurrentFrame);

}


