// Oscar Saharoy 2019

#include <iostream>
#include <complex>
#include <cmath>
#include "CImg.h"

using namespace cimg_library;


int iterate(const std::complex<double>& c) {

	int i = 0;
	std::complex<double> z = 0;

	while (i < 90) {
		
		i++;
		z = std::pow(z, 2) + c;

		if (std::abs(z) > 2) {
			return i;
		}

	}

	return i;
}


void render(double& cx, double& cy, double& h, CImg<unsigned char>& out_img) {

	std::complex<double> c;

	for (int y=0; y<1500; y++) {
		for (int x=0; x<1500; x++) {

			c.real(x * (h/1500.0) - h/2 + cx);
			c.imag(y * (h/1500.0) - h/2 + cy);

			double l  = (90 - iterate(c)) / 90.0;

			unsigned char colour[3];

			colour[0] = 255 - 1000*std::pow((l-0.5), 2);
			colour[1] = -1000*std::pow(l,4) + 1240*std::pow(l,3);
			colour[2] = 255*l;

			out_img.draw_point(x, y, colour);

		}
	}
}


int main() {

	CImg<unsigned char> out_img(1500,1500,1,3,0);

	double cx = -0.5;
	double cy = 0;
	double h  = 3;

	CImgDisplay window(out_img, "mandelbrot set");

	render(cx, cy, h, out_img);
	out_img.display(window);

	while (!window.is_closed()) {

		window.wait();

		if (window.wheel() != 0 && window.mouse_x() >= 0 && window.mouse_y() >= 0) {

			int mx   = window.mouse_x();
			int my   = window.mouse_y();
			int zoom = window.wheel();

			window.set_wheel();

			h  = h  * (1 + zoom/10.0);
			cx = mx * (h/1500.0) - h/2 + cx;
			cy = my * (h/1500.0) - h/2 + cy;

			render(cx, cy, h, out_img);
			out_img.display(window);

		}
	
	}

}
