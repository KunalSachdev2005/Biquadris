#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <cstdlib>
#include <unistd.h>
#include <iostream>

#include "xwindow.h"

XWindow::XWindow(int width, int height) : width(width), height(height) {
    d = XOpenDisplay(NULL);
    if (d == NULL) {
        std::cerr << "Cannot open display" << std::endl;
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
    sleep(1);
}

// Destructor
XWindow::~XWindow() {
    XFreeGC(d, gc);
    XCloseDisplay(d);
}

// Getter methods
int XWindow::getWidth() const { return width; }
int XWindow::getHeight() const { return height; }

// Drawing methods
void XWindow::fillRectangle(int x, int y, int width, int height, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XFillRectangle(d, w, gc, x, y, width, height);
    XFlush(d);  // Ensure immediate rendering
}

void XWindow::drawString(int x, int y, std::string msg, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XDrawString(d, w, gc, x, y, msg.c_str(), msg.length());
    XFlush(d);  // Ensure immediate rendering
}

void XWindow::drawLine(int x1, int y1, int x2, int y2, int colour) {
    XSetForeground(d, gc, colours[colour]);
    XDrawLine(d, w, gc, x1, y1, x2, y2);
    XFlush(d);  // Ensure immediate rendering
}
