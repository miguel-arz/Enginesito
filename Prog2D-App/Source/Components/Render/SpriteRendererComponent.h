#pragma once
#include "Prog2D-Raylib/raylib.h"
#include "Prog2D-Raylib/raymath.h"
#include <vector>
#include "Core/GlobalDefines.h"
#include "Render/RenderItem.h"


#include "Core/Component.h"


class CSpriteRendererComponent : public CComponent, public IRenderItem
{
	DERIVED_CLASS(CSpriteRendererComponent, CComponent);

public:

	CSpriteRendererComponent();

	virtual ~CSpriteRendererComponent() {};
	

	virtual void Initialize() override;
	//virtual void Configure(pugi::xml_node& _rNode) override;
	CSpriteRendererComponent(const pugi::xml_node& oRoot);

	virtual void Configure() override;
	virtual void Awake() override;
	virtual void BeginPlay() override;
		
	virtual void EndPlay() override;
	virtual void Delete() override;

	void Draw() override;
	

	const Color& GetColor() const { return m_vColor; }
	void SetColor(const Color& _vColor) { m_vColor = _vColor; }

	BlendMode GetBlendMode() const { return m_eBlendMode; }
	void SetBlendMode(BlendMode _eBlendMode) { m_eBlendMode = _eBlendMode; }

	Texture2D* GetTexture() const { return m_pTexture; }
	void SetTexture(Texture2D* _pTexture) { m_pTexture = _pTexture; }

	const Vector4& GetUVs() const { return m_vUVs; }
	void SetUVs(const Vector4& _vUVs) { m_vUVs = _vUVs; }

	const Vector2& GetSize() const { return m_vSize; }
	void SetSize(const Vector2& _vSize) { m_vSize = _vSize; }

	const Vector2& GetPivot() const { return m_vPivot; }
	void SetPivot(const Vector2& _vPivot) { m_vPivot = _vPivot; }

	unsigned int GetLayer() const override { return m_uLayer; }
	void SetLayer(unsigned int _uLayer);// { m_uLayer = _uLayer; }

	//const char*?
	std::string GetPath() const { return m_sPath; }
	void SetPath(const char* _sPath) { m_sPath = _sPath; }


protected:
private:
	Color m_vColor;
	BlendMode m_eBlendMode;
	Texture2D* m_pTexture;
	Vector4 m_vUVs;
	Vector2 m_vSize;
	Vector2 m_vPivot;
	unsigned int m_uLayer;
	std::string m_sPath;

};