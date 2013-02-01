#ifndef SFEVENTDISPACHER_H
#define SFEVENTDISPACHER_H

#include <memory>
#include <algorithm>
#include <list>
#include <map>

#include <sigc++/sigc++.h>

using namespace std;

#include "SFCommon.h"
#include "SFEvent.h"
#include "SFAsset.h"

class SFEventSlots {
public:
sigc::slot<void> signals[SFEVENT_LAST];
};

typedef map<SFAssetId, shared_ptr<SFEventSlots> >  SFEventMap;

/**
 * A Singleton class that dispaches all SFEvents to the interested
 * parties.
 */
class SFEventDispacher {
public:
  static SFEventDispacher& GetInstance();
  void                     RegisterInterest      (const SFAssetId, const SFEVENT, sigc::slot<void>);
  void                     DeregisterInterestAll (const SFAssetId);
  void                     RaiseAndDispach       (const SFAssetId, const SFEVENT);

private:
  SFEventDispacher() {interested_parties = make_shared<SFEventMap>();};
  SFEventDispacher(SFEventDispacher const&);
  void operator=(SFEventDispacher const&);

  shared_ptr<SFEventMap> interested_parties;
};

#endif
