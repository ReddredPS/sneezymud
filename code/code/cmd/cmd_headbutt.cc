//////////////////////////////////////////////////////////////////////////
//
// SneezyMUD - All rights reserved, SneezyMUD Coding Team
//
// cmd_headbutt.cc : The headbutt command
//
//////////////////////////////////////////////////////////////////////////


#include "handler.h"
#include "extern.h"
#include "room.h"
#include "being.h"
#include "combat.h"
#include "enum.h"

bool TBeing::canHeadbutt(TBeing *victim, silentTypeT silent)
{
  if (checkBusy()) {
    return FALSE;
  }
  if (!doesKnowSkill(SKILL_HEADBUTT)) {
    if (!silent)
      sendTo("You know nothing about headbutting.\n\r");
    return FALSE;
  }
  switch (race->getBodyType()) {
    case BODY_HUMANOID:
    case BODY_OWLBEAR:
    case BODY_MINOTAUR:
    case BODY_ORB:
      break;
    case BODY_KUOTOA:  // thick necks
    case BODY_OTYUGH:  // no real head
    default:
      if (!silent)
        sendTo("You lack the proper body form to headbutt.\n\r");
      return FALSE;
  }
  if (checkPeaceful("You feel too peaceful to contemplate violence.\n\r"))
    return FALSE;

  if (victim->riding && !dynamic_cast<TBeing *> (victim->riding)) {
    act("You can't headbutt $N while $E is on $p!", TRUE, this, victim->riding, victim, TO_CHAR);
    return FALSE;
  }

  if (victim == this) {
    if (!silent)
      sendTo("Aren't we funny today...\n\r");
    return FALSE;
  }
  if (riding) {
    if (!silent)
      sendTo("You can't butt heads while mounted!\n\r");
    return FALSE;
  }
  if (noHarmCheck(victim))
    return FALSE;

  if (victim->isImmortal() || IS_SET(victim->specials.act, ACT_IMMORTAL)) {
    if (!silent)
      sendTo("You can't successfully butt an immortal.\n\r");
    return FALSE;
  }

  if ((int) (getPosHeight() * 0.9) > victim->getPosHeight()) {
    if (victim->getPosition() < POSITION_STANDING) {
      if (!silent)

        sendTo(format("That might work, but your victim seems to be on the %s.\n\r") % roomp->describeGround());
    } else {
      if (!silent)
        sendTo("Your head is much higher than theirs.\n\r");
    }
    return FALSE;
  }
  if (victim->isFlying()) {
    if (!silent)
      sendTo("You can't headbutt something that is flying.\n\r");
    return FALSE;
  }
  if (getPosition() == POSITION_CRAWLING) {
    if (!silent)
      sendTo("You can't headbutt while crawling.\n\r");
    return FALSE;
  }

  return true;
}

int TBeing::headbuttMiss(TBeing *v)
{
  int rc;

  if (v->doesKnowSkill(SKILL_COUNTER_MOVE)) {
    // I don't understand this logic
    act("$N deftly avoids $n's headbutt.", FALSE, this, 0, v, TO_NOTVICT); 
    act("$N deftly avoids your headbutt.", FALSE, this, 0, v, TO_CHAR);
    act("You deftly avoid $n's headbutt.", FALSE, this, 0, v, TO_VICT);
  } else {
    act("$N avoids $n's headbutt.", FALSE, this, 0, v, TO_NOTVICT);
    act("$N moves $S head, and you fall down as you miss your headbutt.", FALSE, this, 0, v, TO_CHAR);
    act("$n tries to headbutt you, but you dodge it.", FALSE, this, 0, v, TO_VICT);
   
    rc = crashLanding(POSITION_SITTING);
    if (IS_SET_DELETE(rc, DELETE_THIS))
      return DELETE_THIS;

    rc = trySpringleap(v);
    if (IS_SET_DELETE(rc, DELETE_THIS) || IS_SET_DELETE(rc, DELETE_VICT))
      return rc;
  }
  reconcileDamage(v, 0,SKILL_HEADBUTT);

  return TRUE;
}

int TBeing::headbuttHit(TBeing *victim)
{
  int rc;
  int h_dam = 1, spikeddam=0;
  int hgt;
  spellNumT dam_type = SKILL_HEADBUTT;
  wearSlotT pos;

  int dam = getSkillDam(victim, SKILL_HEADBUTT, getSkillLevel(SKILL_HEADBUTT), getAdvLearning(SKILL_HEADBUTT));

  hgt = getHeight();

  if (hgt < victim->getPartMinHeight(ITEM_WEAR_FEET)) {
    dam_type = DAMAGE_HEADBUTT_FOOT;
    act("You try to headbutt $N's foot, but $E is just too high up right now.", FALSE, this, 0, victim, TO_CHAR);
    act("$n tries to headbutt your foot, but fails.", FALSE, this, 0, victim, TO_VICT);
    act("$n tries to headbutt $N's foot, but fails.", FALSE, this, 0, victim, TO_NOTVICT);

    if ((rc = reconcileDamage(victim, 0,dam_type)) == -1)
      return DELETE_VICT;

    return TRUE;
  } else if (hgt < victim->getPartMinHeight(ITEM_WEAR_LEGS)) {
    pos = (::number(0,1) ? WEAR_FOOT_L : WEAR_FOOT_R);
    dam_type = DAMAGE_HEADBUTT_FOOT;
    act("$n headbutts $N, slamming $s head into $N's foot.", FALSE, this, 0, victim, TO_NOTVICT);
    act("You headbutt $N, slamming your head into $S foot.", FALSE, this, 0, victim, TO_CHAR);
    act("$n headbutts you, slamming $s head into your foot.", FALSE, this, 0, victim, TO_VICT);
  } else if (hgt < victim->getPartMinHeight(ITEM_WEAR_WAIST)) {
    pos = (::number(0,1) ? WEAR_LEG_L : WEAR_LEG_R);
    dam_type = DAMAGE_HEADBUTT_LEG;
    act("$n headbutts $N, slamming $s head into $N's leg.", FALSE, this, 0, victim, TO_NOTVICT);
    act("You headbutt $N, slamming your head into $S leg.", FALSE, this, 0, victim, TO_CHAR);
    act("$n headbutts you, slamming $s head into your leg.", FALSE, this, 0, victim, TO_VICT);
  } else if (hgt < victim->getPartMinHeight(ITEM_WEAR_BODY)) {
    pos = WEAR_WAIST;
    dam_type = DAMAGE_HEADBUTT_CROTCH;
    act("$n headbutts $N, slamming $s head into $N's crotch.", FALSE, this, 0, victim, TO_NOTVICT);
    act("You headbutt $N, slamming your head into $S crotch.", FALSE, this, 0, victim, TO_CHAR);
    act("$n headbutts you, slamming $s head into your crotch.", FALSE, this, 0, victim, TO_VICT);
    victim->addToWait(combatRound(0.25));
  } else if (hgt < victim->getPartMinHeight(ITEM_WEAR_ARMS)) {
    pos = WEAR_BODY;
    dam_type = DAMAGE_HEADBUTT_BODY;
    act("$n headbutts $N, slamming $s head into $N's solar plexus.", FALSE, this, 0, victim, TO_NOTVICT);
    act("You headbutt $N, slamming your head into $S solar plexus.", FALSE, this, 0, victim, TO_CHAR);
    act("$n headbutts you, slamming $s head into your solar plexus.", FALSE, this, 0, victim, TO_VICT);
    victim->addToWait(combatRound(0.25));
  } else if (hgt < victim->getPartMinHeight(ITEM_WEAR_NECK)) {
    pos = WEAR_NECK;
    dam_type = DAMAGE_HEADBUTT_THROAT;
    act("$n headbutts $N, slamming $s head into $N's throat.", FALSE, this, 0, victim, TO_NOTVICT);
    act("You headbutt $N, slamming your head into $S throat.", FALSE, this, 0, victim, TO_CHAR);
    act("$n headbutts you, slamming $s head into your throat.", FALSE, this, 0, victim, TO_VICT);
    victim->addToWait(combatRound(0.25));
  } else if (hgt < victim->getPartMinHeight(ITEM_WEAR_HEAD)) {
    pos = WEAR_HEAD;
    dam_type = DAMAGE_HEADBUTT_JAW;
    act("$n headbutts $N, slamming $s head into $N's jaw.", FALSE, this, 0, victim, TO_NOTVICT);
    act("You headbutt $N, slamming your head into $S jaw.", FALSE, this, 0, victim, TO_CHAR);
    act("$n headbutts you, slamming $s head into your jaw.", FALSE, this, 0, victim, TO_VICT);
    victim->addToWait(combatRound(0.25));
  } else {
    pos = WEAR_HEAD;
    dam_type = DAMAGE_HEADBUTT_SKULL;
    act("$n headbutts $N, slamming $s head into $N's skull.", FALSE, this, 0, victim, TO_NOTVICT);
    act("You headbutt $N, slamming your head into $S skull.", FALSE, this, 0, victim, TO_CHAR);
    act("$n headbutts you, slamming $s head into your skull.", FALSE, this, 0, victim, TO_VICT);
    victim->addToWait(combatRound(0.25));
  }

  TObj *item = dynamic_cast<TObj *>(victim->equipment[pos]);
  if (!item) {
    rc = damageLimb(victim, pos, 0, &h_dam);
    if (IS_SET_DELETE(rc, DELETE_VICT))
      return DELETE_VICT;
  } else if (dentItem(victim, item, 1, WEAR_HEAD) == DELETE_ITEM) {
    delete item;
    item = NULL;
  }

  item = dynamic_cast<TObj *>(equipment[WEAR_HEAD]);
  if (!item) {
    rc = damageLimb(this, WEAR_HEAD, 0, &h_dam);
    if (IS_SET_DELETE(rc, DELETE_VICT))
      return DELETE_THIS;
  } else {
    if (item->isSpiked() || item->isObjStat(ITEM_SPIKED))
      spikeddam=(int) (dam*0.15);
    if (dentItem(victim, item, 1, WEAR_HEAD) == DELETE_ITEM) {
      delete item;
      item = NULL;
    }
  }

  if(spikeddam) {
    act("The spikes on your $o sink into $N.", FALSE, this, item, victim, TO_CHAR);
    act("The spikes on $n's $o sink into $N.", FALSE, this, item, victim, TO_NOTVICT);
    act("The spikes on $n's $o sink into you.", FALSE, this, item, victim, TO_VICT);
    if ((rc = reconcileDamage(victim, spikeddam,TYPE_STAB)) == -1)
      return DELETE_VICT;
  }
  if ((rc = reconcileDamage(victim, dam,dam_type)) == -1)
    return DELETE_VICT;

  return TRUE;
}

int TBeing::headbutt(TBeing *victim)
{
  int rc;
  const int HEADBUTT_MOVE   = 6;

  if (!canHeadbutt(victim, SILENT_NO))
    return FALSE;

  if (getMove() < HEADBUTT_MOVE) {
    sendTo("You lack the vitality.\n\r");
    return FALSE;
  }
  addToMove(-HEADBUTT_MOVE);

  int bKnown = getSkillValue(SKILL_HEADBUTT);
  int successfulHit = specialAttack(victim, SKILL_HEADBUTT);
  int successfulSkill = bSuccess(bKnown, SKILL_HEADBUTT);

  // keep bSucc at end so counters are OK
  if (!victim->awake() ||
      (successfulSkill && successfulHit && successfulHit != GUARANTEED_FAILURE &&
      !victim->canCounterMove(bKnown*2/5) &&
      !victim->canFocusedAvoidance(bKnown*2/5))) {
    return (headbuttHit(victim));
  } else {
    rc = headbuttMiss(victim);
    if (IS_SET_DELETE(rc, DELETE_THIS) || IS_SET_DELETE(rc, DELETE_VICT))
      return rc;
  }
  return TRUE;
}

int TBeing::doHeadbutt(const char *argument, TBeing *vict)
{
  int rc;
  TBeing *v;
  char name_buf[256];
  
  strcpy(name_buf, argument);
  
  if (!(v = vict)) {
    if (!(v = get_char_room_vis(this, name_buf))) {
      if (!(v = fight())) {
        sendTo("Butt whose head?\n\r");
        return FALSE;
      }
    }
  }
  if (!sameRoom(*v)) {
    sendTo("That person isn't around.\n\r");
    return FALSE;
  }
  rc = headbutt(v);
  if (rc)
    addSkillLag(SKILL_HEADBUTT, rc);

  if (IS_SET_ONLY(rc, DELETE_VICT)) {
    if (vict)
      return rc;
    delete v;
    v = NULL;
    REM_DELETE(rc, DELETE_VICT);
  }
  return rc;
}

