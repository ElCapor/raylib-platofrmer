#ifndef GUIELEMENT_H
#define GUIELEMENT_H
#include <raylib.h>
#include <functional>
#include <string>
#include "TextureAtlas.h"

static int GetMaxFontSize(const std::string& text, const Vector2& buttonSize, const Font& font, float spacing = 0, Vector2 padding = { 0, 0 })
{
    int fontSize = GetFontDefault().baseSize; // Start with an initial font size

    // Measure the text's size with the current font size, including padding
    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, spacing);

    // Calculate the maximum allowed width and height for the text
    float maxWidth = buttonSize.x - (2 * padding.x);
    float maxHeight = buttonSize.y - (2 * padding.y);

    // Keep reducing the font size until it fits within the button's dimensions
    while (textSize.x < maxWidth && textSize.y < maxHeight)
    {
        fontSize++;

        // Re-measure the text's size with the updated font size, including padding
        textSize = MeasureTextEx(font, text.c_str(), fontSize, spacing);
    }

    return fontSize;
}

class GUIElement {
public:
    virtual void Init() = 0;
    virtual void Draw() = 0;
    virtual void Update() = 0;
    // Add other common methods and properties here
};


class GUIButton : public GUIElement {
public:
    GUIButton(Vector2 position, Vector2 size, const std::string& text = "", Color color = BLUE,
        std::function<void()> onClickCallback = 0, Vector2 padding = { 5,5 })
    {
        this->position = position;
        this->size = size;
        this->text = text;
        this->onClick = onClickCallback;
        this->color = color;
        this->padding = padding;
        this->idleTexture = TextureAtlasManager::GetInstance()->GetTexureAtlas("blueSheet").Rect2Texture("blue_button00.png");
        // default behaviour , hover & click are the same
        this->hoverTexture = this->clickTexture = TextureAtlasManager::GetInstance()->GetTexureAtlas("blueSheet").Rect2Texture("blue_button01.png");
        total_bb = { position.x, position.y, size.x, size.y };
    }

    // Methods for initializing, updating, and drawing the button
    void Init() {
        
    }
    void Update() override
    {
        if (IsMouseButtonPressed(0) && CheckCollisionPointRec(GetMousePosition(), total_bb))
        {
            TraceLog(LOG_INFO, "Button clicked !");
            this->padding = { padding.x + 5, padding.y + 5 };
        }

    }
    void Draw() override
    {
        // Draw the button background
        //DrawRectangle(position.x, position.y, size.x, size.y, color);
        DrawTexturePro(this->idleTexture, { 0,0, (float)idleTexture.width, (float)idleTexture.height }, { 0, 0, size.x, size.y }, { position.x, position.y }, 0, WHITE);
        
        float spacing = 5; // font spacing

        // Calculate the maximum font size that fits within the button
        int fontSize = GetMaxFontSize(text, size, GetFontDefault(), 5, padding);

        // Calculate the position to center the text, considering spacing and equal left/right padding
        float textX = position.x - size.x / 2 + MeasureTextEx(GetFontDefault(), text.c_str(), fontSize, spacing).x / 2 + padding.x*2;
        float textY = position.y + size.y / 2 - fontSize / 2;


        // Draw the centered text with the calculated font size
        DrawTextEx(GetFontDefault(), text.c_str(), { textX, textY }, fontSize, spacing, WHITE);
    }

private:
    Vector2 position;  // Position of the button
    Vector2 size;      // Size of the button
    Vector2 padding;   // Padding for text
    Color color;       // Color of button
    std::string text;  // Text or label displayed on the button
    bool isHovered;    // Flag to track if the mouse is hovering over the button
    std::function<void()> onClick;  // Callback function to be called on button click
    Texture2D idleTexture;
    Texture2D hoverTexture;
    Texture2D clickTexture;
    Rectangle total_bb;
};





#endif // !GUIELEMENT_H
