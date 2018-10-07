#include "zoom.hpp"

ZoomList::ZoomList(int width, int height){
	/* Takes the current width and height of the image to be 
	 * zoomed into. They are to be used for calculations later.
	*/
	m_width = width;
	m_height = height;
}

void ZoomList::add(const zoom &z){
	/* So what we want to do is zoom to a particular pixel.
	 * This is done by shifting our centre of the image w.r.t to
	 * the image's (width/2, height/2). Then we recompute the fractal
	 * for that pixel w.r.t the centre we have zoomed into.
	*/
	m_xCentre += (z.x - m_width/2)*m_scale;
	m_yCentre += (z.y - m_height/2)*m_scale;
	m_scale *= z.scale;

	zooms.push_back(z);
}

std::pair<double, double> ZoomList::doZoom(int x, int y){
	/* Returns the (xFractal, yFractal) co-ordinates to be used further
	 * by the fractal function to recalculate the fractal for the zoomed 
	 * image (w.r.t to the zoomed centre).
	*/
	double xFractal = (x - m_width/2)*m_scale + m_xCentre;
	double yFractal = (y - m_height/2)*m_scale + m_yCentre;

	return std::pair<double, double> (xFractal, yFractal);
}