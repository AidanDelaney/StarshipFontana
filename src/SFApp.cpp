#include "SFApp.h"

SFApp::SFApp() {
  is_running = true;

  surface = SDL_GetVideoSurface();
  app_box = make_shared<SFBoundingBox>(Vector2(surface->w/2, surface->h/2), surface->w/2, surface->h/2);
  player  = make_shared<SFAsset>(SFASSET_PLAYER);
  auto player_pos = Point2(surface->w/2, 88.0f);
  player->SetPosition(player_pos);

  const int number_of_aliens = 10;
  for(int i=0; i<number_of_aliens; i++) {
    // place an alien at width/number_of_aliens * i
    auto alien = make_shared<SFAsset>(SFASSET_ALIEN);
    auto pos   = Point2((surface->w/number_of_aliens) * i, 200.0f);
    alien->SetPosition(pos);
    aliens.push_back(alien);
  }
}

SFApp::~SFApp() {
}

/**
 * Handle all events that come from SDL.
 * These are timer or keyboard events.
 */
void SFApp::OnEvent(SFEvent& event) {
  SFEVENT the_event = event.GetCode();
  switch (the_event) {
  case SFEVENT_QUIT:
    is_running = false;
    break;
  case SFEVENT_UPDATE:
    OnUpdateWorld();
    OnRender();
    break;
  case SFEVENT_PLAYER_LEFT:
    player->GoWest();
    break;
  case SFEVENT_PLAYER_RIGHT:
    player->GoEast();
    break;
  case SFEVENT_FIRE:
    FireProjectile();
    break;
  }
}

int SFApp::OnExecute() {
  // Execute the app
  SDL_Event event;
  while (SDL_WaitEvent(&event) && is_running) {
    // if this is an update event, then handle it in SFApp,
    // otherwise punt it to the SFEventDispacher.
    SFEvent sfevent((const SDL_Event) event);
    OnEvent(sfevent);
  }
}

void SFApp::OnUpdateWorld() {
  // Update projectile positions
  for(auto p: projectiles) {
    p->GoNorth();
  }

  // Update enemy positions
  for(auto a : aliens) {
    // do something here
  }

  // Detect collisions
  for(auto p : projectiles) {
    for(auto a : aliens) {
      if(p->CollidesWith(a)) {
	SFEventDispacher::GetInstance().RaiseAndDispach(p->GetId(), SFEVENT_COLLISION);
	SFEventDispacher::GetInstance().RaiseAndDispach(a->GetId(), SFEVENT_COLLISION);
      }
    }
  }

  // remove dead aliens (the long way)
  list<shared_ptr<SFAsset>> tmp;
  for(auto a : aliens) {
    if(a->IsAlive()) {
      tmp.push_back(a);
    }
  }
  aliens.clear();
  aliens = list<shared_ptr<SFAsset>>(tmp);
}

void SFApp::OnRender() {
  // clear the surface
  SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 8, 54, 129) );

  // draw the player
  player->OnRender(surface);

  for(auto p: projectiles) {
    if(p->IsAlive()) {p->OnRender(surface);}
  }

  for(auto a: aliens) {
    if(a->IsAlive()) {a->OnRender(surface);}
  }

  // Switch the off-screen buffer to be on-screen
  SDL_Flip(surface);
}

void SFApp::FireProjectile() {
  auto pb = make_shared<SFAsset>(SFASSET_PROJECTILE);
  auto v  = player->GetPosition();
  pb->SetPosition(v);
  projectiles.push_back(pb);
}
