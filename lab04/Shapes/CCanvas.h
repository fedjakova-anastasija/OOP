#pragma once
#include "CPoint.h"
#include "ICanvas.h"

class CCanvas : public ICanvas
{
public:
	CCanvas(sf::RenderWindow& window);
	~CCanvas() = default;
	void DrawLine(const CPoint& start, const CPoint& end, uint32_t lineColor) override;
	void FillPolygon(const std::vector<CPoint>& points, uint32_t fillColor) override;
	void DrawCircle(const CPoint& center, double radius, uint32_t lineColor) override;
	void FillCircle(const CPoint& center, double radius, uint32_t fillColor) override;

private:
	sf::RenderWindow& m_window;
};
