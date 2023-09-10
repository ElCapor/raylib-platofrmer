#ifndef GUIELEMENT_H
#define GUIELEMENT_H
#include <raylib.h>
#include <functional>
#include <string>
#include "TextureAtlas.h"

// helper function to auto size font for buttons
static int GetMaxFontSize(const std::string& text, const Vector2& buttonSize, const Font& font, float spacing = 0, Vector2 padding = { 0, 0 })
{
    int fontSize = GetFontDefault().baseSize;
    Vector2 textSize = MeasureTextEx(font, text.c_str(), fontSize, spacing);

    float maxWidth = buttonSize.x - (2 * padding.x); // cuz padding is left & right
    float maxHeight = buttonSize.y - (2 * padding.y);

    
    while (textSize.x < maxWidth && textSize.y < maxHeight)
    {
        fontSize++;
        textSize = MeasureTextEx(font, text.c_str(), fontSize, spacing);
    }

    return fontSize;
}

// abstract gui element class
class GUIElement {
public:
    virtual void Init() = 0;
    virtual void Draw() = 0;
    virtual void Update() = 0;
};


// default button with blue texture
// todo : refactor this ugly mess
class GUIButton : public GUIElement {
public:
    GUIButton()
    {

    }
    GUIButton(Vector2 position, Vector2 size, const std::string& text = "", Color color = BLUE,
        std::function<void(GUIButton* self)> onClickCallback = 0, Vector2 padding = { 5,5 })
    {
        this->position = position;
        this->size = size;
        this->text = text;
        this->onClick = onClickCallback;
        this->color = color;
        this->padding = padding;
        this->idleTexture = TextureAtlasManager::GetInstance()->GetTexureAtlas("blueSheet").Rect2Texture("blue_button00.png");
        // default behaviour , hover & click are the same
        this->hoverTexture = TextureAtlasManager::GetInstance()->GetTexureAtlas("blueSheet").Rect2Texture("blue_button13.png");
        this->clickTexture = TextureAtlasManager::GetInstance()->GetTexureAtlas("blueSheet").Rect2Texture("blue_button01.png");
        total_bb = { position.x, position.y, size.x, size.y };
    }

    
    void Init() {
        // shouldnt i be setting & loading everything here ?
        // because atlas manager might not be init when we call the constructor
        // while in this function we are sure a 1000% that it is
    }
    void Update() override
    {
        if (CheckCollisionPointRec(GetMousePosition(), total_bb))
        {
            if (IsMouseButtonPressed(0))
            {
                isClicked = true;
                onClick(this);
            }
            else {
                isClicked = false;
            }
            isHovered = true;
        }
        else {
            isClicked = false;
            isHovered = false;
        }
        
    }
    void Draw() override
    {
        // texture test
        // DrawRectangle(position.x, position.y, size.x, size.y, color);
        Texture2D currentTexture = isHovered ? hoverTexture : idleTexture;
        if (isClicked)
        {
            // click is more important than behaviour
            currentTexture = clickTexture;
        }

        // we have to do this to resize the texture on the fly
        DrawTexturePro(currentTexture, { 0,0, (float)currentTexture.width, (float)currentTexture.height }, { position.x, position.y, size.x, size.y }, { 0, 0 }, 0, WHITE);
        
        float spacing = 5; // font spacing
        int fontSize = GetMaxFontSize(text, size, GetFontDefault(), 5, padding);

        //todo : fix and adapt this pasta code
        float textX = position.x - size.x / 2 + MeasureTextEx(GetFontDefault(), text.c_str(), fontSize, spacing).x / 2 + padding.x*2;
        float textY = position.y + size.y / 2 - fontSize / 2;

        Color textColor = isHovered ? BLACK : WHITE; // because the hover texture is white

        // draw the text in the middle
        DrawTextEx(GetFontDefault(), text.c_str(), { textX, textY }, fontSize, spacing, textColor);
    }

private:
    Vector2 position;  // Position of the button
    Vector2 size;      // Size of the button
    Vector2 padding;   // Padding for text
    Color color;       // Color of button
    std::string text;  // Text or label displayed on the button
    bool isHovered;    // Flag to track if the mouse is hovering over the button
    bool isClicked;    // Flag to track if the mouse is clicking the button
    std::function<void(GUIButton* self)> onClick;  // Callback function to be called on button click
    Texture2D idleTexture; // fix this ugly mess probably
    Texture2D hoverTexture; //
    Texture2D clickTexture; //
    Rectangle total_bb; //
};





#endif // !GUIELEMENT_H
