#pragma once
#include "CShape.h"
#include "ISolidShape.h"

class CSolidShape : public ISolidShape
	, public CShape
{
public:
	CSolidShape() = default;
	virtual ~CSolidShape() = default;
	std::string GetOutlineColor() const override;
	std::string GetFillColor() const override;
	void SetFillColor(const std::string& fillColor);

private:
	std::string m_fillColor;
};
