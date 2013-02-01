#ifndef SFASSET_H
#define SFASSET_H

#include <string>
#include <memory>
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <sigc++/sigc++.h>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFEventDispacher.h"
#include "SFBoundingBox.h"

/**
 * We could create SFPlayer, SFProjectile and SFAsset which are subclasses
 * of SFAsset.  However, I've made an implementation decision to use this
 * enum to mark the type of the SFAsset.  If we add more asset types then
 * the subclassing strategy becomes a better option.
 */
enum SFASSETTYPE {SFASSET_DEAD, SFASSET_PLAYER, SFASSET_PROJECTILE, SFASSET_ALIEN};

class SFAsset {
public:
  SFAsset(const SFASSETTYPE);
  SFAsset(const SFAsset&);
  virtual ~SFAsset();

  virtual void      SetPosition(Point2 &);
  virtual Point2    GetPosition();
  virtual SFAssetId GetId();
  virtual void      OnRender(SDL_Surface *);
  virtual void      GoEast();
  virtual void      GoWest();
  virtual void      GoNorth();
  virtual void      SetNotAlive();
  virtual bool      IsAlive();

  virtual bool                      CollidesWith(shared_ptr<SFAsset>);
  virtual shared_ptr<SFBoundingBox> GetBoundingBox();
private:
  // it would be nice if we could make this into a smart pointer,
  // but, because we need to call SDL_FreeSurface on it, we can't.
  // (or we could use a std::shared_ptr with a custom Deleter, but
  // that's a little too much right now)
  SDL_Surface               * sprite;
  shared_ptr<SFBoundingBox>   bbox;
  SFASSETTYPE                 type;
  SFAssetId                   id;

  static int SFASSETID;
};

#endif
