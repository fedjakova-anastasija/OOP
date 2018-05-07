#pragma once
#include "CPoint.h"
#include "CSolidShape.h"

class CCircle : public CSolidShape
{
public:
	CCircle(const CPoint& center, const double radius,
		const std::string& outlineColor,
		const std::string& fillColor);
	~CCircle() = default;
	double GetArea() const override;
	double GetPerimeter() const override;
	std::string ToString() const override;
	CPoint GetCenter() const;
	double GetRadius() const;
	void Draw(ICanvas& canvas) const;

private:
	double m_radius;
	CPoint m_center;
};
