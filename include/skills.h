/* NetHack 3.6	skills.h	$NHDT-Date: 1547255911 2019/01/12 01:18:31 $  $NHDT-Branch: NetHack-3.6.2-beta01 $:$NHDT-Revision: 1.15 $ */
/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985-1999. */
/*-Copyright (c) Pasi Kallinen, 2017. */
/* NetHack may be freely redistributed.  See license for details. */

#ifndef SKILLS_H
#define SKILLS_H

/* Much of this code was taken from you.h.  It is now
 * in a separate file so it can be included in objects.c.
 */

enum p_skills {
    /* Code to denote that no skill is applicable */
    P_NONE = 0,

/* Weapon Skills -- Stephen White
 * Order matters and are used in macros.
 * Positive values denote hand-to-hand weapons or launchers.
 * Negative values denote ammunition or missiles.
 * Update weapon.c if you amend any skills.
 * Also used for oc_subtyp.
 */
    P_DAGGER             =  1,
    P_KNIFE              =  2,
    P_AXE                =  3,
    P_PICK_AXE           =  4,
    P_SHORT_SWORD        =  5,
    P_BROAD_SWORD        =  6,
    P_LONG_SWORD         =  7,
    P_TWO_HANDED_SWORD   =  8,
    P_SABER              =  9,
    P_CLUB               = 10, /* Heavy-shafted bludgeon */
    P_MACE               = 11,
    P_MORNING_STAR       = 12, /* Spiked bludgeon */
    P_FLAIL              = 13, /* Two pieces hinged or chained together */
    P_HAMMER             = 14, /* Heavy head on the end */
    P_QUARTERSTAFF       = 15, /* Long-shafted bludgeon */
    P_POLEARMS           = 16, /* attack two or three steps away */
    P_SPEAR              = 17, /* includes javelin */
    P_TRIDENT            = 18,
    P_LIGHTSABER         = 19,
    P_LANCE              = 20,
    P_BOW                = 21, /* launchers */
    P_SLING              = 22,
    P_FIREARM            = 23, /* KMH */
    P_CROSSBOW           = 24,
    P_DART               = 25, /* hand-thrown missiles */
    P_SHURIKEN           = 26,
    P_BOOMERANG          = 27,
    P_WHIP               = 28, /* flexible, one-handed */
    P_UNICORN_HORN       = 29, /* last weapon */

    /* Spell Skills added by Larry Stewart-Zerba */
    P_ATTACK_SPELL       = 30,
    P_HEALING_SPELL      = 31,
    P_DIVINATION_SPELL   = 32,
    P_ENCHANTMENT_SPELL  = 33,
    P_NECROMANCY_SPELL   = 34,
    P_ESCAPE_SPELL       = 35,
    P_MATTER_SPELL       = 36,

    /* Other types of combat */
    P_BARE_HANDED_COMBAT = 37, /* actually weaponless; gloves are ok */
    P_TWO_WEAPON_COMBAT  = 38, /* pair of weapons, one in each hand */
    P_SHIELD             = 39, /* How well you use a shield */
    P_RIDING             = 40, /* How well you control your steed */

    P_NUM_SKILLS         = 41
};

#define P_MARTIAL_ARTS P_BARE_HANDED_COMBAT /* Role distinguishes */
#define P_THIEVERY P_BARE_HANDED_COMBAT

#define P_FIRST_WEAPON P_DAGGER
#define P_LAST_WEAPON P_UNICORN_HORN

#define P_FIRST_SPELL P_ATTACK_SPELL
#define P_LAST_SPELL P_MATTER_SPELL

#define P_LAST_H_TO_H P_RIDING
#define P_FIRST_H_TO_H P_BARE_HANDED_COMBAT

/* These roles qualify for a martial arts bonus */
#define martial_bonus() (Role_if(PM_SAMURAI) \
                         || Role_if(PM_MONK) \
                         || Role_if(PM_JEDI) \
                         || Role_if(PM_UNDEAD_SLAYER) \
                         || (uarm && uarm->oartifact == ART_GRANDMASTER_S_ROBE))

/*
 * These are the standard weapon skill levels.  It is important that
 * the lowest "valid" skill be be 1.  The code calculates the
 * previous amount to practice by calling  practice_needed_to_advance()
 * with the current skill-1.  To work out for the UNSKILLED case,
 * a value of 0 needed.
 */
enum skill_levels {
    P_ISRESTRICTED = 0, /* unskilled and can't be advanced */
    P_UNSKILLED    = 1, /* unskilled so far but can be advanced */
    /* Skill levels Basic/Advanced/Expert had long been used by
       Heroes of Might and Magic (tm) and its sequels... */
    P_BASIC        = 2,
    P_SKILLED      = 3,
    P_EXPERT       = 4,
    /* when the skill system was adopted into nethack, levels beyond expert
       were unnamed and just used numbers.  Devteam coined them Master and
       Grand Master.  Sometime after that, Heroes of Might and Magic IV (tm)
       was released and had two more levels which use these same names. */
    P_MASTER       = 5, /* Unarmed combat/martial arts/thievery/shield only */
    P_GRAND_MASTER = 6  /* ditto */
};

#define practice_needed_to_advance(level) ((level) * (level) *20)

/* The hero's skill in various weapons. */
struct skills {
    xchar skill;
    xchar max_skill;
    unsigned short advance;
};

#define P_SKILL(type) (u.weapon_skills[type].skill)
#define P_MAX_SKILL(type) (u.weapon_skills[type].max_skill)
#define P_ADVANCE(type) (u.weapon_skills[type].advance)
#define P_RESTRICTED(type) (u.weapon_skills[type].skill == P_ISRESTRICTED)
#define P_UN_SKILL(type) (u.weapon_skills[type].skill == P_UNSKILLED)
#define P_BA_SKILL(type) (u.weapon_skills[type].skill == P_BASIC)
#define P_SK_SKILL(type) (u.weapon_skills[type].skill == P_SKILLED)
#define P_EX_SKILL(type) (u.weapon_skills[type].skill == P_EXPERT)

#define P_SKILL_LIMIT 60 /* Max number of skill advancements */

/* Initial skill matrix structure; used in u_init.c and weapon.c */
struct def_skill {
    xchar skill;
    xchar skmax;
};

#endif /* SKILLS_H */
