

#ifndef __DISC_SHAMAN_SKUNK_H
#define __DISC_SHAMAN_SKUNK_H


class CDShamanSkunk : public CDiscipline
{
public:
    CSkill skTurnSkill;
    CSkill skDeathMist;
    CSkill skLichTouch;

    CDShamanSkunk()
      : CDiscipline(),
      skTurnSkill(),
      skDeathMist(),
      skLichTouch() {
    }
    CDShamanSkunk(const CDShamanSkunk &a)
      : CDiscipline(a),
      skTurnSkill(a.skTurnSkill),
      skDeathMist(a.skDeathMist),
      skLichTouch(a.skLichTouch) {
    }
    CDShamanSkunk & operator=(const CDShamanSkunk &a) {
      if (this == &a) return *this;
      CDiscipline::operator=(a);
      skTurnSkill = a.skTurnSkill;
      skDeathMist = a.skDeathMist;
      skLichTouch = a.skLichTouch;
      return *this;
    }
    virtual ~CDShamanSkunk() {}
    virtual CDShamanSkunk * cloneMe() { return new CDShamanSkunk(*this); }

private:
};
int deathMist(TBeing * caster, int level, byte bKnown, int adv_learn);
int deathMist(TBeing * caster);
int castDeathMist(TBeing * caster);

int lichTouch(TBeing *, TBeing *);
int castLichTouch(TBeing *, TBeing *);
int lichTouch(TBeing *, TBeing *, int, byte, int);
int lichTouch(TBeing *, TBeing *, TMagicItem *);

#endif



