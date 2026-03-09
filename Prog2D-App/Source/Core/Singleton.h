#pragma once

template<class T>
class ISingleton
{
public:

	static T* Initialize()
	{
		if (!m_pInstance)
		{
			m_pInstance = new T();

		}
		return m_pInstance;
	}

	static T* GetInstance()
	{
		return m_pInstance;
	}

	static void Delete()
	{
		if (m_pInstance)
		{
			delete m_pInstance;
			m_pInstance = nullptr;	

		}
	}
private:
	static T* m_pInstance;
};

template<class T>
T* ISingleton<T>::m_pInstance = nullptr;