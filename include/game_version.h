#ifndef GUARD_GAME_VERSION_H
#define GUARD_GAME_VERSION_H

#include "gba/types.h"

#define VERSION_RANDOMIZED 0
#define VERSION_OBFUSCATED 1
#define VERSION_RUDE 2
#define VERSION_HIDDEN_POWER 3

#define RELAY_VERSION_AMOUNT 4

// Give Obfuscated game version higher shiny odds by letting it re-roll non-shinies (they cant tell)
#define OBFUSCATED_SHINY_RETRIES 32 // ~1/200

#define MAX_SPINNER_VISION_RANGE 8 // SPEEDCHOICE PORT: Maximum number of tile vision for agressive spinners
#define RUDE_TRAINER_LEVEL_SCALING 1.2
#define RUDE_STATUS_CHANCE_ON_HEAL 10 // 1/X

extern u16 gGameSubVersion;
extern const u8 sFakeMoveDescription[18];

/*
 * SPEEDCHOICE PORT:
 * In Gen 3, there is an oversight by Game Freak where upon going to a sub menu and returning
 * the spinner timers are reset due to reloading the field. Since spinners dont start trying
 * to spin until later, this oversight can be used to run past spinners safely without
 * encountering them. Because this trivializes Spinner Hell, we fix this when Hell/Why is
 * toggled by backing up the NPC timers and restoring them upon returning to the field. We skip
 * the player object's timer to avoid sprite issues.
 */
struct MapObjectTimerBackup
{
    bool8 backedUp;
    s16 spriteId;
    s16 timer;
};

u16 GameVersionRandom(void);
u16 GameVersionObfuscated(void);
u16 GameVersionRude(void);
u16 GameVersionHiddenPower(void);

u16 GetOpeningSprite(void);

u16 ReplaceWildMonSpecies(u16 oldSpecies, u16 levelID);
u16 ReplaceLevelUpMove(u16 oldMove, u16 species);

const u8* GetNameOfObfuscatedMove(u16 moveID);
bool8 IsMoveSilly(u16 moveID);
u16 ObfuscateMove(u16 moveID);
const u8* ObfuscateMoveName(u16 moveID);
u16 ObfuscateSpecies(u16 species);

u8 GetTrainerPokemonLevel(u8 originalLevel, u8 trainerClass);
u8 ShouldApplyStatusOnHeal(u8 mapID);

u16 SwizzleIV(u8 iv, u8 data_type);

#endif // GUARD_GAME_VERSION_H