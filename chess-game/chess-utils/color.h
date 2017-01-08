#ifndef COLOR_H
#define COLOR_H

enum Color {
    cBlack,
    cWhite
};

class ColorUtils {
public:
    static Color getOppositeColor(Color color) {
        if(color == cBlack) {
            return cWhite;
        } else {
            return cBlack;
        }
    }
};


#endif // COLOR_H
