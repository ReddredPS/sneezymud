#pragma once

#include "discipline.h"
#include "skills.h"

class CDOffense : public CDiscipline {
  public:
    CSkill skAdvancedOffense;
    CSkill skInevitability;

    CDOffense();
    CDOffense(const CDOffense& a);
    CDOffense& operator=(const CDOffense& a);
    virtual ~CDOffense();
    virtual CDOffense* cloneMe() { return new CDOffense(*this); }

    bool isFast() { return true; }
};
