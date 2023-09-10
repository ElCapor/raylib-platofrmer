#ifndef LAYOUTMANAGER_H
#define LAYOUTMANAGER_H
#include "GUIElement.h"
#include "TextureAtlas.h"
#include <vector>

class LayoutManager {
public:
    LayoutManager() {}
    ~LayoutManager() {}

    void Init()
    {
        // idk i just put this in case i want to setup something
        TraceLog(LOG_INFO, __FUNCTION__);
        TextureAtlasManager::GetInstance()->LoadAtlasTexture("blueSheet", "assets/blueSheet.xml");

    }
    // Add a GUIElement to the layout
    void AddElement(GUIElement* element) {
        elements.emplace_back(element);
    }

    // Remove a GUIElement from the layout
    void RemoveElement(GUIElement* element) {
        auto it = std::remove(elements.begin(), elements.end(), element);
        if (it != elements.end()) {
            elements.erase(it);
            delete element; // Don't forget to delete the element to avoid memory leaks
        }
    }

    // Update all GUI elements in the layout
    void Update() {
        for (auto& element : elements) {
            element->Update();
        }
    }

    // Draw all GUI elements in the layout
    void Draw() {
        for (auto& element : elements) {
            element->Draw();
        }
    }

    // Remove all elements
    void Clear()
    {
        for (auto& element : elements)
        {
            RemoveElement(element);
        }
    }

    static LayoutManager* GetInstance()
    {
        if (!instance)
            instance = new LayoutManager();
        return instance;
    }
    // Add other layout management methods as needed
    static LayoutManager* instance;
private:
    std::vector<GUIElement*> elements;
};



#endif // !LAYOUTMANAGER_H
