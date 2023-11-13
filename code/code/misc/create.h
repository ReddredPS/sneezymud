//////////////////////////////////////////////////////////////////////////
//
// SneezyMUD - All rights reserved, SneezyMUD Coding Team
//
//////////////////////////////////////////////////////////////////////////

#pragma once

class TArrow;
class TPortal;
class TOpenContainer;
class TEgg;

enum editorEnterTypeT {
  ENTER_REENTRANT,
  ENTER_CHECK
};

extern void change_obj_values(TBeing*, TObj*, const char*, editorEnterTypeT);
extern void change_arrow_value3(TBeing*, TArrow*, const char*,
  editorEnterTypeT);
extern void change_arrow_value4(TBeing*, TArrow*, const char*,
  editorEnterTypeT);
extern void change_component_value4(TBeing*, TObj*, const char*,
  editorEnterTypeT);
extern void change_portal_value1(TBeing*, TPortal*, const char*,
  editorEnterTypeT);
extern void change_portal_value3(TBeing*, TPortal*, const char*,
  editorEnterTypeT);
extern void change_portal_value4(TBeing*, TPortal*, const char*,
  editorEnterTypeT);
extern void change_chest_value2(TBeing*, TOpenContainer*, const char*,
  editorEnterTypeT);
extern void change_magicitem_value1(TBeing*, TObj*, const char*,
  editorEnterTypeT);
extern void change_bed_value1(TBeing*, TObj*, const char*, editorEnterTypeT);
extern void change_trap_value2(TBeing*, TObj*, const char*, editorEnterTypeT);
extern void change_trap_value3(TBeing*, TObj*, const char*, editorEnterTypeT);
extern void change_weapon_value1(TBeing*, TObj*, const char*, editorEnterTypeT);
extern void change_weapon_value2(TBeing*, TObj*, const char*, editorEnterTypeT);
extern void change_weapon_value3(TBeing*, TObj*, const char*, editorEnterTypeT);
extern void change_egg_value1(TBeing*, TEgg*, const char*, editorEnterTypeT);

enum editorChangeTypeT {
  MAIN_MENU,
  CHANGE_NAME,
  CHANGE_SHORT_DESC,
  CHANGE_LONG_DESC,
  CHANGE_DESC,

  CHANGE_ROOM_FLAGS,
  CHANGE_ROOM_TYPE,
  CHANGE_ROOM_TYPE2,
  CHANGE_ROOM_TYPE3,
  CHANGE_ROOM_EXTRA,
  CHANGE_ROOM_EXIT,
  CHANGE_ROOM_EXIT_NORTH,
  CHANGE_ROOM_EXIT_EAST,
  CHANGE_ROOM_EXIT_SOUTH,
  CHANGE_ROOM_EXIT_WEST,
  CHANGE_ROOM_EXIT_UP,
  CHANGE_ROOM_EXIT_DOWN,
  CHANGE_ROOM_EXIT_DELETE,
  CHANGE_ROOM_EXIT_NE,
  CHANGE_ROOM_EXIT_NW,
  CHANGE_ROOM_EXIT_SE,
  CHANGE_ROOM_EXIT_SW,
  CHANGE_ROOM_CONDITION_NORTH,
  CHANGE_ROOM_CONDITION_EAST,
  CHANGE_ROOM_CONDITION_SOUTH,
  CHANGE_ROOM_CONDITION_WEST,
  CHANGE_ROOM_CONDITION_UP,
  CHANGE_ROOM_CONDITION_DOWN,
  CHANGE_ROOM_CONDITION_NE,
  CHANGE_ROOM_CONDITION_NW,
  CHANGE_ROOM_CONDITION_SE,
  CHANGE_ROOM_CONDITION_SW,
  CHANGE_ROOM_KEY_NORTH,
  CHANGE_ROOM_KEY_EAST,
  CHANGE_ROOM_KEY_SOUTH,
  CHANGE_ROOM_KEY_WEST,
  CHANGE_ROOM_KEY_UP,
  CHANGE_ROOM_KEY_DOWN,
  CHANGE_ROOM_KEY_NE,
  CHANGE_ROOM_KEY_NW,
  CHANGE_ROOM_KEY_SE,
  CHANGE_ROOM_KEY_SW,
  CHANGE_ROOM_ROOM_EXDESC,
  CHANGE_ROOM_KEYWORD_NORTH,
  CHANGE_ROOM_KEYWORD_SOUTH,
  CHANGE_ROOM_KEYWORD_WEST,
  CHANGE_ROOM_KEYWORD_EAST,
  CHANGE_ROOM_KEYWORD_UP,
  CHANGE_ROOM_KEYWORD_DOWN,
  CHANGE_ROOM_KEYWORD_NE,
  CHANGE_ROOM_KEYWORD_NW,
  CHANGE_ROOM_KEYWORD_SE,
  CHANGE_ROOM_KEYWORD_SW,
  CHANGE_ROOM_TUNNEL,
  DELETE_ROOM_EXITS,
  CHANGE_ROOM_ROOM_HEIGHT,
  CHANGE_ROOM_TYPE_NORTH,
  CHANGE_ROOM_TYPE_EAST,
  CHANGE_ROOM_TYPE_SOUTH,
  CHANGE_ROOM_TYPE_WEST,
  CHANGE_ROOM_TYPE_UP,
  CHANGE_ROOM_TYPE_DOWN,
  CHANGE_ROOM_TYPE_NE,
  CHANGE_ROOM_TYPE_NW,
  CHANGE_ROOM_TYPE_SE,
  CHANGE_ROOM_TYPE_SW,
  CHANGE_ROOM_WEIGHT_NORTH,
  CHANGE_ROOM_WEIGHT_EAST,
  CHANGE_ROOM_WEIGHT_SOUTH,
  CHANGE_ROOM_WEIGHT_WEST,
  CHANGE_ROOM_WEIGHT_UP,
  CHANGE_ROOM_WEIGHT_DOWN,
  CHANGE_ROOM_WEIGHT_NE,
  CHANGE_ROOM_WEIGHT_NW,
  CHANGE_ROOM_WEIGHT_SE,
  CHANGE_ROOM_WEIGHT_SW,
  CHANGE_ROOM_LOCK_NORTH,
  CHANGE_ROOM_LOCK_EAST,
  CHANGE_ROOM_LOCK_SOUTH,
  CHANGE_ROOM_LOCK_WEST,
  CHANGE_ROOM_LOCK_UP,
  CHANGE_ROOM_LOCK_DOWN,
  CHANGE_ROOM_LOCK_NE,
  CHANGE_ROOM_LOCK_NW,
  CHANGE_ROOM_LOCK_SE,
  CHANGE_ROOM_LOCK_SW,
  CHANGE_ROOM_DIR_SLOPED_NORTH,
  CHANGE_ROOM_DIR_SLOPED_EAST,
  CHANGE_ROOM_DIR_SLOPED_SOUTH,
  CHANGE_ROOM_DIR_SLOPED_WEST,
  CHANGE_ROOM_DIR_SLOPED_UP,
  CHANGE_ROOM_DIR_SLOPED_DOWN,
  CHANGE_ROOM_DIR_SLOPED_NE,
  CHANGE_ROOM_DIR_SLOPED_NW,
  CHANGE_ROOM_DIR_SLOPED_SE,
  CHANGE_ROOM_DIR_SLOPED_SW,
  CHANGE_OBJ_TYPE,
  CHANGE_OBJ_WEIGHT,
  CHANGE_OBJ_VOLUME,
  CHANGE_OBJ_EXTRA_FLAGS,
  CHANGE_OBJ_WEAR_FLAGS,
  CHANGE_OBJ_COST_PER,
  CHANGE_OBJ_COST,
  CHANGE_OBJ_VALUES,
  CHANGE_OBJ_DECAY,
  CHANGE_OBJ_MAX_STRUCTS,
  CHANGE_OBJ_STRUCT_POINTS,
  CHANGE_OBJ_EXTRA,
  CHANGE_OBJ_MATERIAL_TYPE,
  CHANGE_OBJ_APPLYS,
  CHANGE_OBJ_VALUE1,
  CHANGE_OBJ_VALUE2,
  CHANGE_OBJ_VALUE3,
  CHANGE_OBJ_VALUE4,
  CHANGE_OBJ_EXDESC,
  CHANGE_OBJ_MAT_TYPE,
  CHANGE_OBJ_MAT_TYPE1,
  CHANGE_OBJ_MAT_TYPE2,
  CHANGE_OBJ_MAT_TYPE3,
  CHANGE_OBJ_MAT_TYPE4,
  CHANGE_OBJ_CAN_BE_SEEN,
  CHANGE_CHEST_TRAP_TYPE,
  CHANGE_CHEST_TRAP_DAM,
  CHANGE_CHEST_CONT_FLAGS,
  CHANGE_CHEST_VALUE2,
  CHANGE_PORTAL_VALUE1,
  CHANGE_PORTAL_VALUE2,
  CHANGE_PORTAL_VALUE3,
  CHANGE_PORTAL_VALUE4,
  CHANGE_PORTAL_VNUM,
  CHANGE_PORTAL_MAX,
  CHANGE_PORTAL_TYPE,
  CHANGE_PORTAL_TRAP_TYPE,
  CHANGE_PORTAL_TRAP_DAM,
  CHANGE_PORTAL_KEY,
  CHANGE_PORTAL_DOOR_FLAGS,
  CHANGE_WEAPON_VALUE1,
  CHANGE_WEAPON_MAX_SHARP,
  CHANGE_WEAPON_SHARP,
  CHANGE_WEAPON_VALUE2,
  CHANGE_WEAPON_DAMAGE_LEV,
  CHANGE_WEAPON_TYPE,
  CHANGE_WEAPON_VALUE3,
  CHANGE_WEAPON_DAMAGE_PREC,
  CHANGE_WEAPON_QUALITY,
  CHANGE_OBJ_SPEC,
  CHANGE_OBJ_MAX_EXIST,
  CHANGE_MAGICITEM_VALUE1,
  CHANGE_MAGICITEM_LEARNEDNESS,
  CHANGE_MAGICITEM_LEVEL,
  CHANGE_COMPONENT_VALUE4,
  CHANGE_TRAP_VALUE2,
  CHANGE_TRAP_VALUE3,
  CHANGE_BED_VALUE1,
  CHANGE_BED_MAXUSERS,
  CHANGE_BED_MINPOS,
  CHANGE_ARROW_VALUE3,
  CHANGE_ARROW_VALUE4,
  CHANGE_ARROW_TRAPTYPE,
  CHANGE_ARROW_TRAPLVL,
  CHANGE_ARROW_HEAD,
  CHANGE_ARROW_TYPE,
  CHANCE_ARROW_TRAP,
  CHANGE_MOB_ACT_FLAGS,
  CHANGE_MOB_AFF_FLAGS,
  CHANGE_MOB_FACTION,
  CHANGE_MOB_MULT_ATT,
  CHANGE_MOB_LEVEL,
  CHANGE_MOB_THACO,
  CHANGE_MOB_ARMOR,
  CHANGE_MOB_HIT_BONUS,
  CHANGE_MOB_DAMAGE,
  CHANGE_MOB_GOLD,
  CHANGE_MOB_RACE,
  CHANGE_MOB_POSITION,
  CHANGE_MOB_DEF_POS,
  CHANGE_MOB_SEX,
  CHANGE_MOB_IMMUNE,
  CHANGE_MOB_MAX_EXIST,
  CHANGE_MOB_CLASS,
  CHANGE_MOB_STATS,
  CHANGE_MOB_HEIGHT,
  CHANGE_MOB_WEIGHT,
  CHANGE_MOB_SKIN,
  CHANGE_MOB_SKIN1,
  CHANGE_MOB_SKIN2,
  CHANGE_MOB_SKIN3,
  CHANGE_MOB_SKIN4,
  CHANGE_SPEC_PROC,
  CHANGE_MOB_VISION,
  CHANGE_MOB_CBS,
  CHANGE_MOB_SOUND,
  CHANGE_SOUND_ROOM,
  CHANGE_SOUND_DIST,
  CHANGE_MOB_FACTION2,
  CHANGE_MOB_STR,
  CHANGE_MOB_DEX,
  CHANGE_MOB_CON,
  CHANGE_MOB_BRA,
  CHANGE_MOB_AGI,
  CHANGE_MOB_INT,
  CHANGE_MOB_FOC,
  CHANGE_MOB_WIS,
  CHANGE_MOB_SPE,
  CHANGE_MOB_PER,
  CHANGE_MOB_KAR,
  CHANGE_MOB_CHA,
  CHANGE_MOB_LUC,
  CHANGE_MOB_EXT,
  CHANGE_MOB_ADD,
  CHANGE_MOB_STRINGS,
  CHANGE_MOB_STRINGS__BAMFIN,
  CHANGE_MOB_STRINGS__BAMFOUT,
  CHANGE_MOB_STRINGS__DEATHCRY,
  CHANGE_MOB_STRINGS__REPOP,
  CHANGE_MOB_STRINGS__MOVEIN,
  CHANGE_MOB_STRINGS__MOVEOUT,
  SEDIT_ADD,
  SEDIT_DELETE,
  SEDIT_MODIFY,
  SEDIT_DISPLAY,
  CHANGE_EGG_VALUE1,
  CHANGE_EGG_TOUCHED,
  CHANGE_EGG_FILL,
  CHANGE_VEHICLE_VALUE3,
};
