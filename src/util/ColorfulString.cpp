/**
 *  @author <a href="mailto:harvey.blocks@outlook.com">Harvey Blocks</a>
 *  @date 2024/6/28
 *
 */
#include "ColorfulString.h"

const String ColorfulString::COLOR_POST("\033[0m");
const String ColorfulString::COLOR_PRE("\033[");

String ColorfulString::colorPre(util::Color color, util::Color background) {
    StringBuilder result(COLOR_PRE);
    if (background != util::Color::DEFAULT) {
        // 一般不加
        result.append(String::valueOf(background + 40)).append(String(";"));
    }
    if (color == util::Color::DEFAULT) {
        // 一般要加
        color = util::Color::BLACK;
    }
    return result.append(String::valueOf(color + 30)).append(String("m")).toString();
}

String ColorfulString::painting(const String &str, util::Color color, util::Color background) {
    return StringBuilder()
            .append(colorPre(color, background))
            .append(str)
            .append(COLOR_POST)
            .toString();
}
