#ifndef __ALADDIN_2D_SPRITE_H__
#define __ALADDIN_2D_SPRITE_H__

/*
 * Created by phuctm97 on Sep 30th 2017
 */

#include "2dInclude.h"
#include "Size2.h"

NAMESPACE_ALA
{
ALA_CLASS_HEADER_1(Sprite, ala::GameResource)
  // ======================================
  // Basic
  // ======================================
private:
  std::string _sourceFile;
  ala::Size2 _contentSize;
  ala::Color _transColor;

public:
  Sprite( const std::string& name, const std::string& sourceFile, const ala::Color& transColor = ala::Color( 255, 0, 255 ), Scene* scope = NULL );

  const std::string& getSourceFile() const;

  const ala::Color& getTransColor() const;

  const ala::Size2& getContentSize() const;

  void setContentSize( const ala::Size2& size );

protected:
  bool onLoad() override;

  void onRelease() override;

  // ======================================
  // Platform specific
  // ======================================
private:
  LPDIRECT3DTEXTURE9 _directXTexture;

public:
  void setDirectXTexture( LPDIRECT3DTEXTURE9 directXTexture );

  LPDIRECT3DTEXTURE9 getDirectXTexture();
};
}

#endif //!__ALADDIN_2D_SPRITE_H__
