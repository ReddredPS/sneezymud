#include "stdsneezy.h"
#include "pathfinder.h"
#include "obj_portal.h"
#include "obj_base_corpse.h"


// findRoom
findRoom::findRoom(int d)
{
  dest=d;
}

bool findRoom::isTarget(int room) const
{
  return (room==dest);
}
//////////////


// findClutter
findClutter::findClutter(TBeing *tb)
{
  myself=tb;
}

bool findClutter::isTarget(int room) const
{
  if (room == ROOM_DONATION)
    return false;

  TRoom *rp = real_roomp(room);
  if (!rp->inGrimhaven())
    return false;

  TThing *t;
  for (t = rp->getStuff(); t; t = t->nextThing) {
    TObj * obj = dynamic_cast<TObj *>(t);
    if (!obj)
      continue;
    if (!okForJanitor((TMonster *) myself, obj))
      continue;
    return true;
  }
  return false;
}
////////////

// findPolice
findPolice::findPolice(){
}

bool findPolice::isTarget(int room) const
{
  TRoom *rp;
  TThing *t;
  rp = real_roomp(room);

  for (t = rp->getStuff(); t; t = t->nextThing) {
    TBeing *ch = dynamic_cast<TBeing *>(t);
    if (!ch)
      continue;
    if (ch->isPc() && !ch->isImmortal())
      return true;
    if (ch->isPolice())
      return true;
  }
  return false;
}
//////////////

// findOutdoors

findOutdoors::findOutdoors(){
}

bool findOutdoors::isTarget(int room) const
{
  TRoom *rp = real_roomp(room);
  
  if(rp->isRoomFlag(ROOM_INDOORS))
    return FALSE;

  return TRUE;
}


///////////////



// findCorpse
findCorpse::findCorpse(){
}

bool findCorpse::isTarget(int room) const
{
  // don't track corpses in the morgue
  if (room == ROOM_MORGUE)
    return FALSE;
  
  TRoom *rp = real_roomp(room);

  // don't leave gh
  if (!rp->inGrimhaven())
    return FALSE;

  TThing *t;
  for (t = rp->getStuff(); t; t = t->nextThing) {
    if (!dynamic_cast<TBaseCorpse *>(t))
      continue;
    return TRUE;
  }
  return FALSE;
}
///////////////

// findFire
findFire::findFire(){
}

bool findFire::isTarget(int room) const
{
  TRoom *rp = real_roomp(room);
  TObj *o;

  // don't leave gh
  if (!rp->inGrimhaven())
    return FALSE;

  TThing *t;
  for (t = rp->getStuff(); t; t = t->nextThing) {
    if((o=dynamic_cast<TObj *>(t)) && o->isObjStat(ITEM_BURNING))
      return TRUE;
  }
  return FALSE;
}
/////////////

// findBeing

findBeing::findBeing(sstring n){
  name=n;
}

bool findBeing::isTarget(int room) const
{
  return (searchLinkedList(name, real_roomp(room)->getStuff(), TYPEBEING) != NULL);
}


//////////


// findWater

findWater::findWater(){
}


bool findWater::isTarget(int room) const
{
  TRoom *rp;
  TThing *t;
  rp = real_roomp(room);

  if (rp->isRiverSector())
    return TRUE;

  for (t = rp->getStuff(); t; t = t->nextThing) {
    if (t->spec == SPEC_FOUNTAIN)
      return TRUE;
    if (t->waterSource())
      return TRUE;
  }
  return FALSE;
}




///////////


TPathFinder::TPathFinder()
{
  thru_doors=true;
  use_portals=true;
  range=5000;
  stay_zone=false;
  no_mob=true;
  dest=ROOM_NOWHERE;
}

TPathFinder::TPathFinder(int depth)
{
  TPathFinder();
  setRange(depth);
}

void TPathFinder::setRange(int d){ 
  if(d<0){
    // old find_path used negative depth to set certain options
    // this is depreciated, so check for erroneous usage
    vlogf(LOG_BUG, fmt("TPathFinder::setRange called with negative depth (%i)!") % d);
    d=-d;
  }
  
  range=d; 
}


dirTypeT TPathFinder::findPath(int here, const TPathTarget &pt)
{
  // just to be dumb, check my own room first
  if(pt.isTarget(here)){
    dest = here;
    return DIR_NONE;
  }

  // create this room as a starting point
  pathData *pd = new pathData();
  pd->direct = DIR_NONE;
  pd->source = -1;
  pd->checked = false;

  map<int, pathData *>path_map;
  path_map[here] = pd;
  bool found=true;
    map<int, pathData *>::const_iterator CI;

  for(int distance=0;found;++distance){
    found=false;

    if (path_map.size() > (unsigned int) range) {
      dest = path_map.size();

      // clean up allocated memory
      for (CI = path_map.begin(); CI != path_map.end(); ++CI) {
        pd = CI->second;
        delete pd;
      }
      return DIR_NONE;
    }

    for (CI = path_map.begin(); CI != path_map.end(); ++CI) {
      // no need to do things twice
      pd = CI->second;
      if (pd->checked)
        continue;

      if(pd->distance > distance)
	continue;

      dirTypeT dir;
      TRoom *rp = real_roomp(CI->first);
      if (!rp) {
        vlogf(LOG_BUG, "Problem iterating path map.");
        continue;
      }

      for (dir = MIN_DIR; dir < MAX_DIR; dir++) {
	roomDirData *exitp = rp->dir_option[dir];
	TRoom *hp = NULL;
	if (exitp && 
	    (hp = real_roomp(exitp->to_room)) &&
	    (!no_mob || !(hp->isRoomFlag(ROOM_NO_MOB))) &&
	    (thru_doors ? go_ok_smarter(exitp) : go_ok(exitp))) {
	  // check stay_zone criteria
	  if (stay_zone && (hp->getZoneNum() != rp->getZoneNum())) {
	    continue;
	  }
	  
	  // do we have this room already?
	  map<int, pathData *>::const_iterator CT;
	  CT = path_map.find(exitp->to_room);
	  if (CT != path_map.end())
	    continue;
	  
	  // is this our target?
	  if(pt.isTarget(exitp->to_room)){
	    // found our target, walk our list backwards
	    dest = exitp->to_room;
	    
	    pd = CI->second;
	    for (;;) {
	      if (pd->source == -1) {
		// clean up allocated memory
		for (CI = path_map.begin(); CI != path_map.end(); ++CI) {
		  pathData *tpd = CI->second;
		  delete tpd;
		}
		
		return dir;
	      }
	      dir = pd->direct;
	      pd = path_map[pd->source];
	    }
	  }
	  // it's not our target, and we don't have this room yet
	  pd = new pathData();
	  pd->source = CI->first; 
	  pd->direct = dir; 
	  pd->checked = false; 
	  pd->distance=distance+1;
	  path_map[exitp->to_room] = pd;
	  found=true;
	}
      }

      // check for portals that might lead to target
      // return 10 if its the 1st portal in the room, 11 for 2nd, etc
      // 0-9 are obviously real exits (see above)
      if (use_portals) {
        dir = dirTypeT(MAX_DIR-1);
        TThing *t;
        for (t = rp->getStuff(); t; t = t->nextThing) {
          TPortal *tp = dynamic_cast<TPortal *>(t);
          if (!tp) 
            continue;
          dir++;   // increment portal
          if (tp->isPortalFlag(EX_LOCKED | EX_CLOSED))
            continue;
          int tmp_room = tp->getTarget();   // next room
          TRoom *hp = real_roomp(tmp_room);
          if (!hp) {
            continue;
          }

          // check stay_zone criteria
          if (stay_zone && (hp->getZoneNum() != rp->getZoneNum())) {
            continue;
          }

          // do we have this room already?
          map<int, pathData *>::const_iterator CT;
          CT = path_map.find(tmp_room);
          if (CT != path_map.end())
            continue;

          // is this our target?
	  if(pt.isTarget(tmp_room)){
            // found our target, walk our list backwards
	    dest = tmp_room;

            pd = CI->second;
            for (;;) {
              if (pd->source == -1) {
                // clean up allocated memory
                for (CI = path_map.begin(); CI != path_map.end(); ++CI)
                  delete CI->second;

                return dir;
              }
              dir = pd->direct;
              pd = path_map[pd->source];
            }
          }
          // it's not our target, and we don't have this room yet
          pd = new pathData();
          pd->source = CI->first; 
          pd->direct = dir; 
          pd->checked = false; 
	  pd->distance=distance+1;
          path_map[tmp_room] = pd;
	  found=true;
        }  // stuff in room
      }
      // end portal check

      // we've checked all dirs for this room, so mark it checked
      pd = CI->second;
      pd->checked = true;
    }
  }

  
  // if we failed to find any new rooms, abort, or be in an endless loop
  dest=ROOM_NOWHERE;
  
  // clean up allocated memory
  for (CI = path_map.begin(); CI != path_map.end(); ++CI)
    delete CI->second;
  
  return DIR_NONE;
}

