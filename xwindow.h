#ifndef __XWINDOW_H__
#define __XWINDOW_H__

#include <X11/Xlib.h>
#include <string>

const int NUM_COLOURS = 10;

class XWindow {
private:
    Display *d;
    Window w;
    int s;
    GC gc;
    unsigned long colours[NUM_COLOURS];
    int width, height;

public:
    enum Color { White = 0, Black, Red, Green, Blue, Cyan, Magenta, Yellow, Orange, Brown };
    
    // Constructor and Destructor
    XWindow(int width = 800, int height = 500);
    ~XWindow();

    // Public methods to interact with the window
    int getWidth() const;
    int getHeight() const;

    void fillRectangle(int x, int y, int width, int height, int colour = Black);
    void drawString(int x, int y, std::string msg, int colour = White, const char* fontName = "-*-fixed-medium-r-normal--20-*-*-*-*-*-*-*");
    void drawLine(int x1, int y1, int x2, int y2, int colour = Black);
};

#endif // __XWINDOW_H_
