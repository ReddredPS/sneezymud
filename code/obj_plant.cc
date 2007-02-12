//////////////////////////////////////////////////////////////////////////
//
// SneezyMUD - All rights reserved, SneezyMUD Coding Team
//
//////////////////////////////////////////////////////////////////////////

#include "stdsneezy.h"
#include "obj_plant.h"

TPlant::TPlant() :
  TExpandableContainer()
{
  setType(0);
  setAge(0);
  setYield(0);
  setCarryWeightLimit(100.0);
  setCarryVolumeLimit(10000);
}

TPlant::TPlant(const TPlant &a) :
  TExpandableContainer(a)
{
}

void TPlant::assignFourValues(int x1, int x2, int x3, int)
{
  setType(x1);
  setAge(x2);
  setYield(x3);
}

void TPlant::getFourValues(int *x1, int *x2, int *x3, int *x4) const
{
  *x1 = getType();
  *x2 = getAge();
  *x3 = getYield();
  *x4 = 0;
}

TPlant & TPlant::operator=(const TPlant &a)
{
  if (this == &a) return *this;
  TObj::operator=(a);
  return *this;
}

TPlant::~TPlant()
{
  vlogf(LOG_MISC, fmt("%s is dying: lifetime yield of %i.") % this->getName() % this->getYield());
}

int TPlant::putSomethingInto(TBeing *ch, TThing *)
{
  // technically, would be OK since is a container, but prevent them anyhow
  act("Unfortunately, you can't put things into $p.", 
             FALSE, ch, this, 0, TO_CHAR);
  return 2;
}


sstring TPlant::statObjInfo() const
{
  char buf[256];
  sprintf(buf, "Type: %i Age: %i Total Yield: %i", getType(), getAge(), getYield());
  sstring a(buf);
  return a;
}


// the case numbers are the vnum of the seed tool object
// the return value is the plant type index
int seed_to_plant(int vnum)
{
  switch(vnum){
    case 13880:
      return 0;
    case 13881:
      return 1;
    case 13882:
      return 2;
    case 13883:
      return 3;
    case 13884:
      return 4;
    case 13885:
      return 5;
    case 13886:
      return 6;
    case 34213:
      return 7;
    case 33526:
      return 8;
    case 35485:
      return 9;
    case 35499:
      return 10;
    case 33600:
      return 11;
    case 34738:
      return 12;
    case 29410:  // candy heart seed
      return 13; // candy heart tree
    case 34216:  // grape seeds
      return 14; // gray grapes
  }
  
  return 0;
}





void TPlant::updateDesc()
{
  int plantindex=min(3, (getAge()/10));
  char buf[256];

  const char *plantkeywords [] =
  {
    "mound dirt",
    "sprout tiny",
    "plant small %s",
    "plant %s",
    "plant withered %s"
  };
  
  const char *plantname [] =
  {
    "a small mound of <o>dirt<1>", 
    "a tiny sprout", 
    "a small %s", 
    "a %s",
    "an old, withered %s"
  };
  
  const char *plantdesc [] =
  {
    "A small mound of <o>dirt<1> is here.",
    "A tiny sprout is growing here.",
    "A small %s is here.",
    "A %s is here.",
    "An old, withered %s is here."
  };

  const char *planttypes [] =
  {
    "<r>tomato<1> <g>plant<1>",
    "<r>red<1> rose bush",
    "<r>apple<1> tree",
    "<W>white<1> rose bush",
    "<Y>yellow<1> rose bush",
    "<o>orange<1> tree",
    "<g>money<1> tree",
    "<w>pipe<g>weed<1><o> bush<1>",
    "<o>pumpkin<1> vine",
    "<g>turnip<1> plant",
    "<G>lettuce<1> plant",
    "<g>marijuana<1> plant",
    "<p>catnip<1> <g>plant<1>",
    "<P>candy heart<1> tree",
    "vine of <k>gray grapes<1>"
  };
  const char *planttypeskeywords [] =
  {
    "tomato",
    "red rose bush",
    "apple tree",
    "white rose bush",
    "yellow rose bush",
    "orange tree",
    "money tree",
    "pipeweed bush",
    "pumpkin vine",
    "turnip plant",
    "lettuce plant",
    "marijuana plant",
    "catnip plant",
    "candy heart tree",
    "gray grape vine"
  };
  int plantfruits [] =
  {
    14348,
    28917,
    8936,
    28918,
    28919,
    432,
    13,
    34212,
    33507,
    33508,
    33525,
    33601,
    34737,
    29405,
    34215
  };

  // considering a plant ages an average of 2 'age' points each mud hour, 
  // a plant will age to 17520 in a mud year
  int plantlifeexpectancy [] =
  {
    175200, // 10 years
    262800, // 15 years 
    219000,  // 12.5 years
    262800,  // 15 years
    262800,  // 15 years
    219000,  // 12.5 years
    35040,  // 2 years
    17520,  // 1 year
    8760, // 1/2 year
    8760, // 1/2 year
    8760, // bah
    17520, // 1 year
    17520, // 1 year
    3456, // 3 real days
    262800 // 15 years 
  };
  
  // really old plants should wither and die
  if(getAge() > plantlifeexpectancy[getType()]){
    plantindex=4;
    if(obj_flags.decay_time <= -1)
      obj_flags.decay_time=300;
  }

  if (isObjStat(ITEM_STRUNG)) {
    delete [] shortDescr;
    delete [] descr;

    extraDescription *exd;
    while ((exd = ex_description)) {
      ex_description = exd->next;
      delete exd;
    }
    ex_description = NULL;
    delete [] action_description;
    action_description = NULL;
  } else {
    addObjStat(ITEM_STRUNG);
    name = mud_str_dup(obj_index[getItemIndex()].name);
    ex_description = NULL;
    action_description = NULL;
  }

  if(plantindex>=2){
    sprintf(buf, plantkeywords[plantindex], planttypeskeywords[getType()]);
    delete [] name;
    name = mud_str_dup(buf);

    sprintf(buf, plantname[plantindex], planttypes[getType()]);
    shortDescr = mud_str_dup(buf);
    
    sprintf(buf, plantdesc[plantindex], planttypes[getType()]);
    setDescr(mud_str_dup(buf));
  } else {
    sprintf(buf, plantkeywords[plantindex]);
    delete [] name;
    name = mud_str_dup(buf);

    sprintf(buf, plantname[plantindex]);
    shortDescr = mud_str_dup(buf);
    
    sprintf(buf, plantdesc[plantindex]);
    setDescr(mud_str_dup(buf));
  }

  if(plantindex == 3 && !::number(0,3)){
    TThing *t;
    int count=0;

    for(t=getStuff();t;t=t->nextThing){
      ++count;
    }
    
    if(count<=4){
      t=read_object(plantfruits[getType()], VIRTUAL);
      *this += *t;
      setYield(getYield() + 1);
    }
  }

  if(plantindex == 4 && !::number(0,11)){
    TThing *t;
    int count=0;

    for(t=getStuff();t;t=t->nextThing){
      ++count;
    }
    
    if(count<=2){
      t=read_object(plantfruits[getType()], VIRTUAL);
      *this += *t;
      setYield(getYield() + 1);
    }
  }
}


void TPlant::updateAge(){
  setAge(getAge()+::number(1,3));
  updateDesc();
  if(roomp)
    roomp->saveItems("");
}

