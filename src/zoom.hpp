#ifndef __zoom_h__
#define __zoom_h__

#include <vector>
#include <utility>

typedef struct _zoom{
	int x{0};
	int y{0};
	double scale{0.0};

	_zoom(int x,int y,double scale):x(x),y(y),scale(scale){}
}zoom;

class ZoomList{
	double m_xCentre{0.0};
	double m_yCentre{0.0};
	double m_scale{1.0};

	int m_width{0};
	int m_height{0};
	std::vector<zoom> zooms;

public:
	ZoomList(int width, int height);
	void add(const zoom &z);
	std::pair<double, double> doZoom(int x, int y);
};

#endif