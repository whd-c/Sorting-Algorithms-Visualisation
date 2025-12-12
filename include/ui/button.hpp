#pragma once
#include <raylib.h>
#include "common.hpp"

class Button
{
public:
    Button(Rectangle _rect, const char *_text, uint8_t _fontSize) : rect(_rect), text(_text), fontSize(_fontSize) {};

    void update();
    bool getBtnPressed() const { return btnPressed; }
    void setText(const char *_text) { text = _text; }

private:
    Rectangle rect;
    bool btnPressed = false;
    const char *text = "PLACEHOLDER";
    uint8_t fontSize;
    uint8_t btnState = 0; // 0 - normal, 1 - hovered, 2 - pressed

    Color cNormal = Color{220, 220, 220, 255};
    Color cHover = Color{245, 245, 245, 255};
    Color cPress = Color{180, 180, 180, 255};
};