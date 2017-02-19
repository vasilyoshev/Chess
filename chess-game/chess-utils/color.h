#ifndef COLOR_H
#define COLOR_H

/**
 * @brief The Color enum contains the possible piece/player colors
 */
enum Color {
    cBlack,
    cWhite
};

/**
 * @brief The ColorUtils class contains helper functions for dealing with colors
 */
class ColorUtils {
public:

    /**
     * @brief getOppositeColor
     *
     * Returns the opposite color to the provided one.
     *
     * @param color the provided color
     * @return the oposite of the provided color
     */
    static Color getOppositeColor(Color color) {
        if(color == cBlack) {
            return cWhite;
        } else {
            return cBlack;
        }
    }
};

#endif // COLOR_H
