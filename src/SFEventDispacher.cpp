#include "SFEventDispacher.h"

SFEventDispacher& SFEventDispacher::GetInstance() {
  static SFEventDispacher the_instance;

  return the_instance;
}

void SFEventDispacher::RegisterInterest(const SFAssetId a, const SFEVENT e, sigc::slot<void> f) {
  auto signal_container        = make_shared<SFEventSlots>();
  signal_container->signals[e] = f;
  (*interested_parties)[a]     = signal_container;
}

void SFEventDispacher::DeregisterInterestAll(const SFAssetId a) {
  if((*interested_parties)[a]) {
    (*interested_parties)[a].reset();
  }
}

void SFEventDispacher::RaiseAndDispach(const SFAssetId a, const SFEVENT e) {
  auto sc = (*interested_parties)[a]; 
  auto f = sc->signals[e];
  f();
}
