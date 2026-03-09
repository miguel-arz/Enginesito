#pragma once

class IRenderItem
{
public:

	virtual void Draw() = 0;
	virtual unsigned int GetLayer() const = 0;
	virtual ~IRenderItem() = default;

};