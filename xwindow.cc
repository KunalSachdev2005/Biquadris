#include "window.h"
#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <iostream>
#include <cstdlib>
#include <unistd.h>

Xwindow::Xwindow(int width, int height) : width(width), height(height) {
    d = XOpenDisplay(NULL);
    if (d == NULL) {
        cerr << "Cannot open display" <<endl;
        exit(1);
    }
    s = DefaultScreen(d);
    w = XCreateSimpleWindow(d, RootWindow(d, s), 10, 10, width, height, 1,
                            BlackPixel(d, s), WhitePixel(d, s));
    XSelectInput(d, w, ExposureMask | KeyPressMask);
    XMapRaised(d, w);
    
    gc = XCreateGC(d, w, 0, NULL);

    // Set up colours
    Colormap cmap = DefaultColormap(d, DefaultScreen(d));
    const char* color_names[] = {"white", "black", "red", "green", "blue", 
                                 "cyan", "magenta", "yellow", "orange", "brown"};
    
    for (int i = 0; i < 10; ++i) {
        XColor color;
        XParseColor(d, cmap, color_names[i], &color);
        XAllocColor(d, cmap, &color);
        colours[i] = color.pixel;
    }

    XSetForeground(d, gc, colours[Black]);

    // Make window non-resizable
    XSizeHints hints;
    hints.flags = USPosition | PSize | PMinSize | PMaxSize;
    hints.height = hints.base_height = hints.min_height = hints.max_height = height;
    hints.width = hints.base_width = hints.min_width = hints.max_width = width;
    XSetNormalHints(d, w, &hints);

    XSynchronize(d, True);
    usleep(1000);
}

Xwindow::~Xwindow() {
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

int Xwindow::getWidth() const { return width; }
int Xwindow::getHeight() const { return height; }

void Xwindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XSetForeground(d, gc, colours[Black]);
}

void Xwindow::drawString(int x, int y, std::string msg) {
    XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
}

void Xwindow::drawLine(int x1, int y1, int x2, int y2) {
    XDrawLine(d, w, gc, x1, y1, x2, y2);
}
