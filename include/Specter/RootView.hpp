#ifndef SPECTER_ROOTVIEW_HPP
#define SPECTER_ROOTVIEW_HPP

#include "View.hpp"
#include "FontCache.hpp"
#include <boo/boo.hpp>

namespace Specter
{

class RootView : public View, public boo::IWindowCallback
{
    FontCache& m_fontCache;
    boo::IWindow* m_window = nullptr;
    float m_scale = 1.0;

    void resized(const boo::SWindowRect& rect);
    void mouseDown(const boo::SWindowCoord& coord, boo::EMouseButton button, boo::EModifierKey mods);
    void mouseUp(const boo::SWindowCoord& coord, boo::EMouseButton button, boo::EModifierKey mods);
    void mouseMove(const boo::SWindowCoord& coord);
    void mouseEnter(const boo::SWindowCoord& coord);
    void mouseLeave(const boo::SWindowCoord& coord);
    void scroll(const boo::SWindowCoord& coord, const boo::SScrollDelta& scroll);

    void touchDown(const boo::STouchCoord& coord, uintptr_t tid);
    void touchUp(const boo::STouchCoord& coord, uintptr_t tid);
    void touchMove(const boo::STouchCoord& coord, uintptr_t tid);

    void charKeyDown(unsigned long charCode, boo::EModifierKey mods, bool isRepeat);
    void charKeyUp(unsigned long charCode, boo::EModifierKey mods);
    void specialKeyDown(boo::ESpecialKey key, boo::EModifierKey mods, bool isRepeat);
    void specialKeyUp(boo::ESpecialKey key, boo::EModifierKey mods);
    void modKeyDown(boo::EModifierKey mod, bool isRepeat);
    void modKeyUp(boo::EModifierKey mod);

    void draw(boo::IGraphicsCommandQueue* gfxQ);

public:
    RootView(FontCache& fontCache) : m_fontCache(fontCache) {}
    void setWindow(boo::IWindow* window, float userScale);
};

}

#endif // SPECTER_ROOTVIEW_HPP
