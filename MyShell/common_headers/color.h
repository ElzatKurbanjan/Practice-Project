#ifndef _COLOR_H
#define _COLOR_H

#define COLOR(content, color) "\033[" #color "m" content "\033[0m"
#define COLOR_HL(content, color) "\033[1;" #color "m" content "\033[0m"

#define BLUE(content) COLOR(content, 34)
#define BLUE_HL(content) COLOR_HL(content, 34)
#define GREEN(content) COLOR(content, 32)
#define GREEN_HL(content) COLOR_HL(content, 32)
#define YELLO(content) COLOR(content, 33)
#define YELLO_HL(content) COLOR_HL(content, 33)
#define RED(content) COLOR(content, 31)
#define RED_HL(content) COLOR_HL(content, 31)
#define CYAN(content) COLOR(content, 36)
#define CYAN_HL(content) COLOR_HL(content, 36)

#endif