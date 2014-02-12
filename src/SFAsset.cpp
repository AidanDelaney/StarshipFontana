#include "SFAsset.h"

int SFAsset::SFASSETID=0;

SFAsset::SFAsset(SFASSETTYPE type) {
  this->type = type;
  this->id   = ++SFASSETID;
  SDL_Surface * tmp_surf;

  switch (type) {
  case SFASSET_PLAYER:
    tmp_surf = IMG_Load("assets/player.png");
    break;
  case SFASSET_PROJECTILE:
    tmp_surf = IMG_Load("assets/projectile.png");
    break;
  case SFASSET_ALIEN:
    tmp_surf = IMG_Load("assets/alien.png");
    break;
  case SFASSET_COIN:
    tmp_surf = IMG_Load("assets/coin.png");
    break;
  }

  if(!tmp_surf) {
    cerr << "Could not load asset of type " << type << endl;
    throw SF_ERROR_LOAD_ASSET;
  }

  sprite = SDL_DisplayFormatAlpha(tmp_surf);
  SDL_FreeSurface(tmp_surf);

  // Initialise bounding box
  bbox = make_shared<SFBoundingBox>(SFBoundingBox(Vector2(0.0f, 0.0f), sprite->w, sprite->h));
}

SFAsset::SFAsset(const SFAsset& a) {
  sprite = a.sprite;
  bbox   = a.bbox;
  type   = a.type;
}

SFAsset::~SFAsset() {
  bbox.reset();
  if(sprite) {
    SDL_FreeSurface(sprite);
    sprite = NULL;
  }
}

/**
 * The logical coordinates in the game assume that the screen
 * is indexed from 0,0 in the bottom left corner.  The blittable
 * coordinates of the screen map 0,0 to the top left corner. We
 * need to convert between the two coordinate spaces.  We assume
 * that there is a 1-to-1 quantisation.
 */
Vector2 GameSpaceToScreenSpace(Vector2 &r) {
  return Vector2 (
		  r.getX(),
		  (SDL_GetVideoSurface()->h - r.getY())
		  );
}

void SFAsset::SetPosition(Point2 & point) {
  Vector2 v(point.getX(), point.getY());
  bbox->SetCentre(v);
}

Point2 SFAsset::GetPosition() {
  return Point2(bbox->centre->getX(), bbox->centre->getY());
}

SFAssetId SFAsset::GetId() {
  return id;
}

void SFAsset::OnRender(SDL_Surface * level) {
  // 1. Get the SDL_Rect from SFBoundingBox
  SDL_Rect rect;

  Vector2 gs = (*(bbox->centre) + (*(bbox->extent_x) * -1)) + (*(bbox->extent_y) * -1);
  Vector2 ss = GameSpaceToScreenSpace(gs);
  rect.x = ss.getX();
  rect.y = ss.getY();
  rect.w = bbox->extent_x->getX() * 2;
  rect.h = bbox->extent_y->getY() * 2;

  // 2. Blit the sprite onto the level
  SDL_BlitSurface(sprite, NULL, level, &rect);
}

void SFAsset::GoWest() {
  Vector2 c = *(bbox->centre) + Vector2(-5.0f, 0.0f);
  if(!(c.getX() < 0)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
  }
}

void SFAsset::GoEast() {
  Vector2 c = *(bbox->centre) + Vector2(5.0f, 0.0f);
  if(!(c.getX() > SDL_GetVideoSurface()->w)) {
    bbox->centre.reset();
    bbox->centre = make_shared<Vector2>(c);
  }
}

void SFAsset::GoNorth() {
  Vector2 c = *(bbox->centre) + Vector2(0.0f, 1.0f);
  bbox->centre.reset();
  bbox->centre = make_shared<Vector2>(c);
}

bool SFAsset::CollidesWith(shared_ptr<SFAsset> other) {
  return bbox->CollidesWith(other->bbox);
}

shared_ptr<SFBoundingBox> SFAsset::GetBoundingBox() {
  return bbox;
}

void SFAsset::SetNotAlive() {
  type = SFASSET_DEAD;
}

bool SFAsset::IsAlive() {
  return (SFASSET_DEAD != type);
}

void SFAsset::HandleCollision() {
  if(SFASSET_PROJECTILE == type || SFASSET_ALIEN == type) {
    SetNotAlive();
  }
}
