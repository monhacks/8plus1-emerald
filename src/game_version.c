#include "game_version.h"
#include "global.h"
#include "random.h"
#include "event_data.h"
#include "constants/battle.h"
#include "constants/moves.h"
#include "constants/region_map_sections.h"
#include "constants/species.h"
#include "constants/trainers.h"

// Declare the relay version global flag
EWRAM_DATA u16 gGameSubVersion = 0;

// References to tables defined elsewhere
extern const struct Evolution gEvolutionTable[NUM_SPECIES][EVOS_PER_MON];
extern const u8 gMoveNames[MOVES_COUNT][MOVE_NAME_LENGTH + 1];

// Special Randomizer Groups
# define NUM_BABIES 9
static const u16 babyPokemon[] =
{
    SPECIES_PICHU,
    SPECIES_CLEFFA,
    SPECIES_IGGLYBUFF,
    SPECIES_TYROGUE,
    SPECIES_SMOOCHUM,
    SPECIES_ELEKID,
    SPECIES_MAGBY,
    SPECIES_AZURILL,
    SPECIES_WYNAUT
};

# define NUM_LEGENDARIES 21
static const u16 legendaryPokemon[] = {
    SPECIES_ARTICUNO,
    SPECIES_ZAPDOS,
    SPECIES_MOLTRES,
    SPECIES_MEWTWO,
    SPECIES_MEW,
    SPECIES_RAIKOU,
    SPECIES_ENTEI,
    SPECIES_SUICUNE,
    SPECIES_LUGIA,
    SPECIES_HO_OH,
    SPECIES_CELEBI,
    SPECIES_REGIROCK,
    SPECIES_REGICE,
    SPECIES_REGISTEEL,
    SPECIES_KYOGRE,
    SPECIES_GROUDON,
    SPECIES_RAYQUAZA,
    SPECIES_LATIOS,
    SPECIES_LATIAS,
    SPECIES_JIRACHI,
    SPECIES_DEOXYS
};

// Create two sets of pokemon: evolved and unevolved
#define FULL_EVO_PKMN 193
#define ONE_EVO_PKMN 125
#define TWO_EVO_PKMN 38
EWRAM_DATA u16 fullEvoPokemon[FULL_EVO_PKMN] = {0};
EWRAM_DATA u16 singleEvoPokemon[ONE_EVO_PKMN] = {0};
EWRAM_DATA u16 doubleEvoPokemon[TWO_EVO_PKMN] = {0};

// hidden power bits of interest: (hp, att, def, spe, spa, spd)
static const u8 HIDDEN_POWER_POWER_BITS[] = {
    0x00, // 30bp (00-06)
    0x04, // 40bp (07-13)
    0x02, // 50bp (14-20)
    0x06, // 60bp (21-27)
    0x3F, // 70bp (28-31)
};

// Silly Alternate Move Names for Obfuscated Version (Collect them all!)
#define NUM_FAKE_MOVES 16
static const u8 FAKE_MOVE_NAMES[NUM_FAKE_MOVES][MOVE_NAME_LENGTH + 1] = {
    _("BEAM"),
    _("INSULT"),
    _("PUNCH"),
    _("KICK"),
    _("FINGER GUNS"),
    _("A RUDE WORD"),
    _("REAL TEARS"),
    _("WATCH TV"),
    _("SOMETHING?"),
    _("CURE WOUNDS"),
    _("FIREBALL"),
    _("AN ATTACK"),
    _("GUN"),
    _("FLIP OFF"),
    _("CAT JAM"),
    _("MEGA BITE"),
};
const u8 sFakeMoveDescription[18] = _("It's a Good Move");

// SPEEDCHOIE PORT: Spinner timer used in rude mode.
EWRAM_DATA struct MapObjectTimerBackup gMapObjectTimerBackup[MAX_SPRITES] = {0};

// Jumpscare stuff
EWRAM_DATA bool8 gIsJumpscareBattle = FALSE;

// Special Region IDS and the status to apply
#define NUM_OVERWORLD_HEALS 7
const u8 NON_POKECENTER_HEALS[NUM_OVERWORLD_HEALS] = {
    MAPSEC_NONE, // Used to indicate PC retrieval
    MAPSEC_ROUTE_101, // birch heal at start of game (no status applied)
    MAPSEC_LITTLEROOT_TOWN, // mom heal
    MAPSEC_ROUTE_111, // Old lady pit stop
    MAPSEC_LAVARIDGE_TOWN, // Hot spring (also the pokemon center)
    MAPSEC_ROUTE_119, // Weather institute bed
    MAPSEC_DYNAMIC, // SS_Tidal Bed
};
const u8 NON_POKECENTER_STATUS[NUM_OVERWORLD_HEALS] = {
    STATUS1_FREEZE, // Used for PC retrieval
    STATUS1_NONE, // birch heal at start of game (no status applied)
    STATUS1_PARALYSIS, // Old lady pit stop
    STATUS1_PARALYSIS, // mom heal
    STATUS1_BURN, // Hot spring (also the pokemon center)
    STATUS1_SLEEP, // Weather institute bed
    STATUS1_SLEEP, // SS_Tidal Bed
};

// Return True/False if the game version is "Randomized"
u16 GameVersionRandom(void) {
    return gGameSubVersion == VERSION_RANDOMIZED || GameVersionRainbow();
}

// Return True/False if the game version is "Obfuscated"
u16 GameVersionObfuscated(void) {
    return gGameSubVersion == VERSION_OBFUSCATED || GameVersionRainbow();
}

// Return True/False if the game version is "Rude Trainers"
u16 GameVersionRude(void) {
    return gGameSubVersion == VERSION_RUDE || GameVersionRainbow();
}

// Return True/False if the game version is "Hidden Power"
u16 GameVersionHiddenPower(void) {
    return gGameSubVersion == VERSION_HIDDEN_POWER || GameVersionRainbow();
}

// Return True/False if the game version is "Sketchy"
u16 GameVersionSketchy(void) {
    return gGameSubVersion == VERSION_SKETCHY || GameVersionRainbow();
}

// Return True/False if the game version is "Reverse"
u16 GameVersionReverse(void) {
    return gGameSubVersion == VERSION_REVERSE || GameVersionRainbow();
}

// Return True/False if the game version is "Marathon"
u16 GameVersionMarathon(void) {
    return gGameSubVersion == VERSION_MARATHON || GameVersionRainbow();
}

// Return True/False if the game version is "Unlucky"
u16 GameVersionUnlucky(void) {
    return gGameSubVersion == VERSION_UNLUCKY || GameVersionRainbow();
}

// Return True/False if the game version is "Rainbow"
u16 GameVersionRainbow(void) {
    return gGameSubVersion == VERSION_RAINBOW;
}

// Get the pokemon that pops out of birch's pokeball, based on the game
u16 GetOpeningSprite(void) {
    switch (gGameSubVersion){
        case VERSION_RANDOMIZED:
            return SPECIES_DITTO;
        case VERSION_RUDE:
            return SPECIES_HOUNDOOM;
        case VERSION_HIDDEN_POWER:
            return SPECIES_UNOWN;
        case VERSION_SKETCHY:
            return SPECIES_SMEARGLE;
        case VERSION_REVERSE:
            return SPECIES_PORYGON;
        case VERSION_MARATHON:
            return SPECIES_DODUO;
        case VERSION_UNLUCKY:
            return SPECIES_MURKROW;
        
        // Obfuscated mode just obfuscates the lotad
        default:
            return SPECIES_LOTAD;
    }
}

// How many times can a pokemon evolve, by any method.
u8 CanEvolve(u16 species) {
    // Can Evolve
    if (EVO_FRIENDSHIP <= gEvolutionTable[species][0].method && gEvolutionTable[species][0].method <= EVO_BEAUTY) {
        u16 target = gEvolutionTable[species][0].targetSpecies;
        if (EVO_FRIENDSHIP <= gEvolutionTable[target][0].method && gEvolutionTable[target][0].method <= EVO_BEAUTY)
            return 2;   // can evolve twice
        else // Note that, in this gen, divergent evolutions always happen in the last evo step
            return 1;   // can evolve once
    } else
        return 0;   // cant evolve
}

// Check if a pokemon is in a special group
u16 IsInGroup(u16 id, const u16* group, u16 groupSize) {
    u16 i;
    for (i = 0; i < groupSize; ++i)
        if (group[i] == id)
            return 1;
    return 0;
}

// Check if Dynamic Pokemon Evolution Groups have been made yet
void InitializeEvolutionGroups() {
    if (!doubleEvoPokemon[0]) {
        // Perform the great sort
        u16 id, i, swap;
        u8 oneevo = 0;
        u8 twoevo = 0;
        u8 evolved = 0;
        for (id = 0; id < NUM_SPECIES; id++) {
            
            // ignore the "none" species and the old alternate unknown forms
            if (id == SPECIES_NONE || (SPECIES_OLD_UNOWN_B <= id && id <= SPECIES_OLD_UNOWN_Z))
                continue;

            // Ignore Babies and Legendaries
            if (IsInGroup(id, babyPokemon, NUM_BABIES) || IsInGroup(id, legendaryPokemon, NUM_LEGENDARIES))
                continue;

            switch (CanEvolve(id)) {
                case 0:
                    fullEvoPokemon[evolved++] = id;
                    break;
                case 1:
                    singleEvoPokemon[oneevo++] = id;
                    break;
                case 2:
                    doubleEvoPokemon[twoevo++] = id;
                    break;
            }
        }

        // Perform in place array shuffling of the unevolved pokemon
        for (i = 0; i < ONE_EVO_PKMN - 1; ++i) {
            swap = i + (gSaveBlock2Ptr->playerTrainerId[1] % (ONE_EVO_PKMN - i));
            id = singleEvoPokemon[i];
            singleEvoPokemon[i] = singleEvoPokemon[swap];
            singleEvoPokemon[swap] = id;
        }
        
        // Perform in place array shuffling of the evolved pokemon
        for (i = 0; i < TWO_EVO_PKMN - 1; ++i) {
            swap = i + (gSaveBlock2Ptr->playerTrainerId[2] % (TWO_EVO_PKMN - i));
            id = doubleEvoPokemon[i];
            doubleEvoPokemon[i] = doubleEvoPokemon[swap];
            doubleEvoPokemon[swap] = id;
        }
        
        // Perform in place array shuffling of the evolved pokemon
        for (i = 0; i < FULL_EVO_PKMN - 1; ++i) {
            swap = i + (gSaveBlock2Ptr->playerTrainerId[3] % (FULL_EVO_PKMN - i));
            id = fullEvoPokemon[i];
            fullEvoPokemon[i] = fullEvoPokemon[swap];
            fullEvoPokemon[swap] = id;
        }
    }
}

// Internal Function to replace a pokemon's species.
u16 ReplaceMonSpecies(u16 species, u16 dynamicSeed) {
    u16 i;

    if (species == SPECIES_EGG || species == SPECIES_NONE)
        return species; // Ignore special handling flags

    // Check for and randomize babies within themselves (ignore dynamicSeed)
    for (i = 0; i < NUM_BABIES; ++i)
        if (babyPokemon[i] == species)
            return babyPokemon[(gSaveBlock2Ptr->playerTrainerId[0] + i) % NUM_BABIES];

            
    // Check for and randomize legendaries within themselves (ignore dynamicSeed)
    for (i = 0; i < NUM_LEGENDARIES; ++i)
        if (legendaryPokemon[i] == species)
            return legendaryPokemon[(gSaveBlock2Ptr->playerTrainerId[0] + i) % NUM_LEGENDARIES];

    // Check if the original pokemon can still evolve
    InitializeEvolutionGroups();
    switch (CanEvolve(species)) {
        case 0:
            return fullEvoPokemon[(dynamicSeed + species) % FULL_EVO_PKMN];
        case 1:
            return singleEvoPokemon[(dynamicSeed + species) % ONE_EVO_PKMN];
        case 2:
            return doubleEvoPokemon[(dynamicSeed + species) % TWO_EVO_PKMN];
    }
}

// If Randomized mode is not active, this will just return oldSpecies.
// If randomized mode is active, it will swap the species for a differnet one
// Randomization will always be consistent within a location & game.
// Note: Will randomize pokemon within one of four distinct groups:
//       babies, legendaries, not fully evolved, and fully evolved
u16 ReplaceWildMonSpecies(u16 oldSpecies, u16 levelID) {
    if (GameVersionRandom()) {
        return ReplaceMonSpecies(oldSpecies, (levelID * 7));
    }

    return oldSpecies;
}

// Randomize a the given move for a pokemon species.
// Note that, randomization will always be the same for each species.
u16 RandomizeMove(u16 oldMove, u16 species) {
    // MOVES_COUNT includes invalid moves MOVE_NONE (0) and STRUGGLE (165)
    u16 move = 1 + (oldMove + (gSaveBlock2Ptr->playerTrainerId[0] * species)) % (MOVES_COUNT - 2);
            
    // Struggle is in the middle of the list, so we just shorten the range and pick the last move instead
    if (move == MOVE_STRUGGLE)
        move = MOVES_COUNT - 1;

    return move;
}

// Replace a pokemon's level up move with one, per the current game version's settings. In order:
// If Sketchy is active, it will return Sketch
// If Hidden Power is active, it will return hidden power
// If randomized mode is active, it will return a randomized level up move.
// If none of the above are active this will just return oldMove.
u16 ReplaceLevelUpMove(u16 oldMove, u16 species) {
    if (GameVersionSketchy())
        return MOVE_SKETCH;

    else if (GameVersionHiddenPower())
        return MOVE_HIDDEN_POWER;

    else if (GameVersionRandom())
        return RandomizeMove(oldMove, species);

    return oldMove;
}

// Replace a pokemon's inital moveset move with a new one, per the current version's settings. In order:
// If randomized mode is active, it will return a randomized level up move.
// If Hidden Power is active, it will return hidden power
// If none of the above are active this will just return oldMove.
// Note that sketchy is ignored here, as that replacement only happens after a pokemon is caught.
u16 ReplaceInitialMove(u16 oldMove, u16 species) {
    if (GameVersionRandom())
        return RandomizeMove(oldMove, species);
    
    else if (GameVersionHiddenPower())
        return MOVE_HIDDEN_POWER;

    return oldMove;
}

// If obfuscate mode is not active, this will return the name of the move.
// Otherwise, it will sometimes return a silly name instead.
// moveID - the id of the move who's name we wish to retrieve/obfuscate.
const u8* GetNameOfObfuscatedMove(u16 moveID) {
    if (GameVersionObfuscated() && IsMoveSilly(moveID)) {
        // The start of the "fake moves" replacement range
        u16 sillyMoves = 1 + (gSaveBlock2Ptr->playerTrainerId[1] % (MOVES_COUNT - NUM_FAKE_MOVES - 1));
        return FAKE_MOVE_NAMES[moveID - sillyMoves];
    }
    return gMoveNames[moveID];
}

// If obfuscate mode is not active, this will return false.
// Otherwise, it will return true if the input move is replaced with a "silly" move.
bool8 IsMoveSilly(u16 moveID) {
    if (GameVersionObfuscated()) {
        // The start of the "fake moves" replacement range
        u16 sillyMoves = 1 + (gSaveBlock2Ptr->playerTrainerId[1] % (MOVES_COUNT - NUM_FAKE_MOVES - 1));

        // Check if we are in the "silly move" replacement block
        if (sillyMoves <= moveID && moveID < (sillyMoves + NUM_FAKE_MOVES))
            return TRUE;
    }
    return FALSE;
}

// If obfuscate mode is not active, this will return the input moveID.
// Otherwise, it will obfuscate the move, replacing it with a different one.
// Note: Within a save, every move replacement will be deterministic.
// moveID - the id of the move who's name we wish to obfuscate.
u16 ObfuscateMove(u16 moveID) {
    if (moveID != MOVE_NONE)
        if (GameVersionObfuscated()) {
            // Dont include MOVE_NONE, but do include STRUGGLE
            u16 newMove = 1 + ((moveID + gSaveBlock2Ptr->playerTrainerId[0]) % (MOVES_COUNT - 1));

            // Because its a shift cipher, we can acidentally end up with a case where everyting is the same.
            // Manually prevent this by just picking a preset number and shifting the list by that amount.
            if (newMove == moveID)
                newMove += 31;
            return newMove;
        }
    return moveID;
}

// If obfuscate mode is not active, this will return the name of the move.
// Otherwise, it will obfuscate the move and return the obfuscated move's name.
// Sometimes, when obfuscated, will return a silly name instead of a real one.
// moveID - the id of the move who's name we wish to retrieve/obfuscate.
const u8* ObfuscateMoveName(u16 moveID) {
    if (GameVersionObfuscated())
        return GetNameOfObfuscatedMove(ObfuscateMove(moveID));

    return gMoveNames[moveID];
}

// If obfuscate mode is not active, this will return the input species id.
// Otherwise, it will obfuscate the species and return that id instead.
// species - the id of the species who's name we wish to potentially obfuscate.
u16 ObfuscateSpecies(u16 species) {
    if (GameVersionObfuscated()) {
        return ReplaceMonSpecies(species, gSaveBlock2Ptr->playerTrainerId[0]);
    }
    return species;
}

// Apply any potential level scaling to a trainer's pokemon.
// If the game mode is not Rude/Marathon, this will always return the original level.
// Otherwise, it will scale the level based on the trainer and battle type
// level - the original level of the pokemon
// class - the trainer's class type
u8 GetTrainerPokemonLevel(u8 level, u8 class) {    
    u8 cap = GetLevelCap();

    // Scale the level if game version supports it
    if (GameVersionMarathon()) {
        level = (level * 1.1) + 2;
        cap += ((GetNumBadges() + 1) / 2);
    }

    // Scale more agressivley in hell mode
    else if (GameVersionRude()) {
        level = (level * 1.2) + 3;
        cap += GetNumBadges() + 1;
    }

    // Rival is always at the level cap (after first battle)
    if (class == TRAINER_CLASS_RIVAL && level > 8)
        return cap;

    // Jumpscare trainers are always at least the level cap
    if (IsJumpscareBattle() && level < cap)
        level = cap; 

    // Make sure boss trainers dont break the level cap
    if ((level > cap) &&
        (class == TRAINER_CLASS_ELITE_FOUR || class == TRAINER_CLASS_LEADER ||
         class == TRAINER_CLASS_AQUA_ADMIN || class == TRAINER_CLASS_AQUA_LEADER ||
         class == TRAINER_CLASS_MAGMA_ADMIN || class == TRAINER_CLASS_MAGMA_LEADER))
            level = cap; // Cap gym leaders / e4 at the level caps

    // Make sure we dont break the game's hard level cap
    level = (level > MAX_LEVEL)? MAX_LEVEL: level;

    return level;
}

// Apply any potential level scaling to a trainer's pokemon.
// If the game mode is not Rude, this will always return the original level.
// level - the original level of the pokemon
u8 GetWildPokemonLevel(u8 level) {
    if (GameVersionMarathon())
        return (level * 1.25) + 5;
    return level;
}

// If rude version is not active, will always return Status None.
// Otherwise, will return a status appropriate to where the player is being healed.
// mapID - the region map section id where the player got healed, or none if its a box retrieval. 
u8 ShouldApplyStatusOnHeal(u8 mapID) {
    if (GameVersionRude()) {
        u8 i;
        for (i = 0; i < NUM_OVERWORLD_HEALS; ++i)
            if (NON_POKECENTER_HEALS[i] == mapID)
                return NON_POKECENTER_STATUS[i];
        return STATUS1_POISON; // any other heal is a pokemon center and will just poison u
    }
    return STATUS1_NONE;
}

// If rude version is not active, will always return FALSE
// Otherwise, it will roll a % chance (level cap / 255) to determine
//   if the current battle should be a jumpscare.
u8 ShouldJumpscare() {
    if (GameVersionRude())
        // In Rainbow Mode, every battle is a jumpscare
        gIsJumpscareBattle = (RandomOr(0) & 0xFF) < GetLevelCap();
    return IsJumpscareBattle();
}

// Check if the current battle is a jumpscare battle
u8 IsJumpscareBattle() {
    return gIsJumpscareBattle;
}

// Reset the jumpscare flag
void ClearJumpscare() {
    gIsJumpscareBattle = FALSE;
}

// If HiddenPower mode is not active, will simply return the input fixediv value.
// If hidden power mode is active, this will prodce an iv value with relevant properties:
//    the last bit will be randomized to select a random type, and the second last bit will be
//    set to produce a hidden power move power that scales with the iv value.
// iv - the iv to swizzle
// data_type - the MON_DATA_TYPE field to identify which iv we are affecting. 
u16 SwizzleIV(u8 iv, u8 data_type) {
    // Make sure we are in the correct game mode and the data type is an IV
    if (GameVersionHiddenPower() && MON_DATA_HP_IV <= data_type && data_type <= MON_DATA_SPDEF_IV){
        u8 power_bucket = iv / 7;
        u8 power_bit = (HIDDEN_POWER_POWER_BITS[power_bucket] >> (5 - (data_type - MON_DATA_HP_IV))) & 1;
        u8 type_bit = Random() % 2;
        return (iv & 0xFC) | (power_bit << 1) | type_bit;
    }
    return iv;
}

// If Unlucky mode is not active, will simply return the result of Random().
//  Otherwise, it will return the provided deterministic result instead.
u16 RandomOr(u16 determinsticResult)
{
    if (!GameVersionUnlucky())
        return Random();
    else
        return determinsticResult;
}

// TODO:
// Consider making different player sprites/palettes for different versions

// LOW PRIORITY:
// Pokedex cries are probably double obfuscated
// Kyogre/Groudon cries are obfuscated in intro cutscene if you select guile/rainbow (might affect seeding?)

// NEEDS TEST
// Uncommon unlucky mechanics
// Uncommon obfuscated sprite Locations (contests, eggs, move relearner)