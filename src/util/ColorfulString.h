/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/28
 *
 */
#ifndef ALGORITHM_COLORFUL_STRING_H
#define ALGORITHM_COLORFUL_STRING_H

#include "Color.h"

class ColorfulString {
private:
    static String colorPre(util::Color color, util::Color background = util::Color::GRAY);

    static const String COLOR_POST;
    static const String COLOR_PRE;

    ColorfulString() = default;

public:
    static String painting(const String &str,
                           util::Color color = util::Color::DEFAULT,
                           util::Color background = util::Color::DEFAULT);
};


#endif //ALGORITHM_COLORFUL_STRING_H
