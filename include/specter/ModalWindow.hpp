#pragma once

#include <memory>

#include "specter/View.hpp"

#include <boo/IWindow.hpp>
#include <hecl/UniformBufferPool.hpp>
#include <zeus/CColor.hpp>

namespace specter {
class TextView;
class ViewResources;

class ModalWindow : public View {
public:
  enum class Phase { BuildIn, ResWait, Showing, BuildOut, Done };

private:
  int m_frame = 0;
  int m_contentStartFrame = 0;
  float m_lineTime = 0.0;

  Phase m_phase = Phase::BuildIn;

  int m_width = 0;
  int m_height = 0;
  RectangleConstraint m_constraint;

  zeus::CColor m_windowBg;
  zeus::CColor m_windowBgClear;
  zeus::CColor m_line1;
  zeus::CColor m_line2;
  zeus::CColor m_line2Clear;

  ViewBlock m_viewBlock;
  hecl::UniformBufferPool<ViewBlock>::Token m_viewBlockBuf;
  union {
    struct {
      SolidShaderVert lineVerts[22];
      SolidShaderVert fillVerts[16];
    } m_verts;
    SolidShaderVert _m_verts[38];
  };

  void setLineVerts(int width, int height, float pf, float t);
  void setLineVertsOut(int width, int height, float pf, float t);
  void setLineColors(float t);
  void setLineColorsOut(float t);
  void setFillVerts(int width, int height, float pf);
  void setFillColors(float t);

  VertexBufferBindingSolid m_vertsBinding;
  void _loadVerts() { m_vertsBinding.load<decltype(_m_verts)>(_m_verts); }

  std::unique_ptr<TextView> m_cornersOutline[4];
  std::unique_ptr<TextView> m_cornersFilled[4];

protected:
  virtual void updateContentOpacity(float opacity) {}
  RectangleConstraint& constraint() { return m_constraint; }

public:
  ModalWindow(ViewResources& res, View& parentView, const RectangleConstraint& constraint, const zeus::CColor& bgColor);
  ModalWindow(ViewResources& res, View& parentView, const RectangleConstraint& constraint);
  ~ModalWindow() override;

  void think() override;
  bool skipBuildInAnimation();
  void close(bool skipAnimation = false);
  bool closed() const { return m_phase >= Phase::BuildOut; }
  ModalWindow::Phase phase() const { return m_phase; }

  void resized(const boo::SWindowRect& root, const boo::SWindowRect& sub) override;
  void draw(boo::IGraphicsCommandQueue* gfxQ) override;
};

} // namespace specter
