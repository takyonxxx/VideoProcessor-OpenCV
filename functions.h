#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdlib.h>

class RGB
{
public:
    int R;
    int G;
    int B;

    RGB(int r, int g, int b)
    {
        R = r;
        G = g;
        B = b;
    }

    bool Equals(RGB rgb)
    {
        return (R == rgb.R) && (G == rgb.G) && (B == rgb.B);
    }
};

class HSV
{
public:
    float H;
    float S;
    float V;

    HSV(float h, float s, float v)
    {
        H = h;
        S = s;
        V = v;
    }

    bool Equals(HSV hsv)
    {
        return (H == hsv.H) && (S == hsv.S) && (V == hsv.V);
    }
};

static double Min(double a, double b) {
    return a <= b ? a : b;
}

static double Max(double a, double b) {
    return a >= b ? a : b;
}

static HSV RGBToHSV(RGB rgb) {
    double delta, min;
    double h = 0, s, v;

    min = Min(Min(rgb.R, rgb.G), rgb.B);
    v = Max(Max(rgb.R, rgb.G), rgb.B);
    delta = v - min;

    if (v == 0.0)
        s = 0;
    else
        s = delta / v;

    if (s == 0)
        h = 0.0;

    else
    {
        if (rgb.R == v)
            h = (rgb.G - rgb.B) / delta;
        else if (rgb.G == v)
            h = 2 + (rgb.B - rgb.R) / delta;
        else if (rgb.B == v)
            h = 4 + (rgb.R - rgb.G) / delta;

        h *= 60;

        if (h < 0.0)
            h = h + 360;
    }

    return HSV(h, s, (v / 255));
}
#endif // FUNCTIONS_H
