/*************************************************************************
	> File Name: color.h
	> Author: 
	> Mail: 
	> Created Time: Sat 09 Jan 2021 07:21:55 AM PST
 ************************************************************************/

#ifndef _COLOR_H
#define _COLOR_H

#define COLOR(content, color) "\033[" #color "m" content "\033[0m"
#define COLOR_HL(content, color) "\033[1;" #color "m" content "\033[0m"

#define GREEN(content) COLOR(content, 32)
#define RED(content) COLOR(content, 31)
#define BLUE(content) COLOR(content, 34)
#define YELLOW(content) COLOR(content, 33)

#define GREEN_HL(content) COLOR_HL(content, 32)
#define RED_HL(content) COLOR_HL(content, 31)
#define BLUE_HL(content) COLOR_HL(content, 34)
#define YELLOW_HL(content) COLOR_HL(content, 33)

#endif
