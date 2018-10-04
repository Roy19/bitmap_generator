#include <iostream>
#include "zoom.hpp"

ZoomList::ZoomList(int width, int height){
	m_width = width;
	m_height = height;
}

void ZoomList::add(const zoom &z){
	m_xCentre += (z.x - m_width/2)*m_scale;
	m_yCentre += (z.y - m_height/2)*m_scale;
	m_scale *= z.scale;

	zooms.push_back(z);
}

std::pair<double, double> ZoomList::doZoom(int x, int y){
	double xFractal = (x - m_width/2)*m_scale + m_xCentre;
	double yFractal = (y - m_height/2)*m_scale + m_yCentre;

	return std::pair<double, double> (xFractal, yFractal);
}