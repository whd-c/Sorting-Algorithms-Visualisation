#pragma once
#include <raylib.h>
#include "common.hpp"
#include <unordered_map>

class Button
{
public:
    Button(Rectangle _rect, const char *_text, uint8_t _fontSize) : rect(_rect), text(_text), fontSize(_fontSize) {};

    void update();
    bool getBtnPressed() const { return btnPressed; }
    void setText(const char *_text) { text = _text; }
    void setSelected(bool sel = true) { selected = sel; }

private:
    Rectangle rect;
    bool btnPressed = false;
    const char *text = "PLACEHOLDER";
    bool selected = false;
    uint8_t fontSize;
    enum State
    {
        NORMAL,
        HOVERED,
        PRESSED,
        SELECTED,
        SELECTED_HOVER,
        SELECTED_PRESS,
    };
    State btnState = NORMAL;

    Color cNormal = Color{220, 220, 220, 255};
    Color cHover = Color{235, 240, 245, 255};
    Color cPress = Color{180, 180, 180, 255};
    Color cSelected = Color{0, 120, 215, 255};
    Color cSelectedHover = Color{40, 150, 235, 255};
    Color cSelectedPress = Color{0, 70, 150, 255};
};