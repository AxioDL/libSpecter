#pragma once

#include <functional>
#include <memory>
#include <string>

#include "specter/Button.hpp"
#include "specter/ModalWindow.hpp"

namespace specter {
class MultiLineTextView;

class MessageWindow : public ModalWindow {
public:
  enum class Type { InfoOk, ErrorOk, ConfirmOkCancel };

private:
  Type m_type;
  std::function<void(bool ok)> m_func;

  std::unique_ptr<MultiLineTextView> m_text;

  struct OKBinding : IButtonBinding {
    MessageWindow& m_mw;
    std::string m_name;
    OKBinding(MessageWindow& mw, std::string_view name) : m_mw(mw), m_name(name) {}
    std::string_view name(const Control* control) const override { return m_name; }
    void activated(const Button* button, const boo::SWindowCoord& coord) override { m_mw.m_func(true); }
  } m_okBind;
  ViewChild<std::unique_ptr<Button>> m_ok;

  struct CancelBinding : IButtonBinding {
    MessageWindow& m_mw;
    std::string m_name;
    CancelBinding(MessageWindow& mw, std::string_view name) : m_mw(mw), m_name(name) {}
    std::string_view name(const Control* control) const override { return m_name; }
    void activated(const Button* button, const boo::SWindowCoord& coord) override { m_mw.m_func(false); }
  } m_cancelBind;
  ViewChild<std::unique_ptr<Button>> m_cancel;

public:
  MessageWindow(ViewResources& res, View& parentView, Type type, std::string_view message,
                std::function<void(bool ok)> func);
  ~MessageWindow() override;

  void updateContentOpacity(float opacity) override;

  void mouseDown(const boo::SWindowCoord&, boo::EMouseButton, boo::EModifierKey) override;
  void mouseUp(const boo::SWindowCoord&, boo::EMouseButton, boo::EModifierKey) override;
  void mouseMove(const boo::SWindowCoord&) override;
  void mouseEnter(const boo::SWindowCoord&) override;
  void mouseLeave(const boo::SWindowCoord&) override;

  void resized(const boo::SWindowRect& root, const boo::SWindowRect& sub) override;
  void draw(boo::IGraphicsCommandQueue* gfxQ) override;
};

} // namespace specter
