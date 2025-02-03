
# Pokemon 8+1 Emerald  
An 8-in-1 emerald game designed for nuzlocke relays.  
  
If you just want to download, you can do so on the [releases](https://github.com/ordinary-magic/Pokemon-8plus1-Emerald/releases) page.
  
Game Features (Many Spoilers)  
  
## Common Changes  
 - Added Level Caps (gym leaders and e4)  
 - All evolutions are now achievable by level up, item, or leveling up while holding a specific item.  
 - Most evolution items are now purchasable in the lilycove department store.  
 - Pokemon won't faint to out of battle poison.  
 - Your rival is now always at the level cap (except for first battle).  
 - Made boss trainers more difficult (on average one extra pokemon, more interesting mons & moves)  
 - Added "Rare Candies" key item for reusable rare candy  
 - Added "Tent" key item: It's a portable pokemon center!
 - Added "Dad's Cologne" key item as a toggleable infinite repel.  
 - Made Gambling Illegal, Added Cryptocurrency instead.  
   - After Every Battle, you gain/lose a percentage of your "Coin Wallet"
   - You can buy items and nfp's from the game corner using COIN. 
 - Select your Game Version at the title screen (L/R)  
 -  Note: all versions are compatible with each other, and can be swapped by saving and returning to the title scren.  
  
## CHAOS Version:  
 - Wild Pokemon Encounters and Level Up moves are randomized  
   - The randomization seed is your trainer id, thus it should be consistent within a game.  
   - Each Species has a completley different moveset, and each map area's pool is differnent  
   - Pokemon are grouped into pools and randomized within them, so power levels should be constrained.  

## GUILE Version:  
 - Every Single Pokemon in the game is visually replaced with a different one.  
 - Every Single Move in the game is visually replaced with a different one.  
 - The replacements are *very* thorough, and the ui should not leak information out of battle.  
 - These use the same randomization function, and thus power levels of opponents are reasonably intuitive.  
 - The replacements never change, and are 1-1 to create a puzzle of figuring out what everything actually is.  
  
## HELL Version:  
 - Difficulty Hack  
 - Every standard trainer is a very agressive spinner.  
 - Non-Boss enemy trainer pokemon are higher level than normal.  
 - Random chance that standard trainers will jumpscare you (increases with level cap)  
   - Pokemon are always at level cap, first mon only knows self-destruct/explosion  
 - Reusable Healing Methods have a chance to status you when used.  
 - You are not allowed to use the tent.  
  
## UNKNOWN Version:  
 - Every single pokemon level up move is replaced with Hidden Power.  
 - Enemy pokemon will only ever use hidden power.  
 - You can only use hidden power (your pokemon will disobey)  
 - Enemy Trainer Pokemon's Hidden Power bp will scale as the game progresses. (relative to their pkmn iv's)  
 - Standard "Rare Candy" items now maximize your hidden power bp instead of leveling you up.  
  
## SKETCHY Version:    
 - Caught Wild Pokemon will always know exactly Tackle and Sketch.  
 - Every single level-up move is replaced with Sketch.  
 - The Move Relearner will only teach you Sketch.  
 - Enemy Movesets are unaffected.  
 
## REVERSE Version:  
 - Attacking and Defending types are swapped when calculating type effectiveness  
   - eg. Ghost is Super effective against Ghost and Dark types, but fighting type is Immune. 
 - EXP gained from battles is boosted and negative (you lose levels by fighting)  

## IRON Version:  
 - You cannot withdraw pokemon from boxes.  
 - Reusable Healing Methods do not restore PP.  
 - Non-Boss enemy trainer pokemon are higher level than normal.  
 - Wild Pokemon are stronger than normal, and you are not allowed to use the cologne.  

## HEX Version:  
 - Move Damage, Accuracy, Secondary Effects always result in the worst possible outcome for the player.  
 - Critical Hits are impossible (for everybody).  
 - Wild Encounters happen more often.  
 - Wild Pokemon Have 0 IVs.  
 - Reusable Healing Methods have a chance to status you when used.  

## RAINBOW Version:
 - Every Single Mechanic is enabled at once.  
 - This version is very cursed
 - Ambiguity Resolution:
   - Initial moveset is Tackle+Sketch (SKETCHY), Level-up moves are only hidden power (UNKNOWN).
   - Move Relearner will let you learn Sketch (SKETCHY)
   - Every battle is a jumpscare (HELL + HEX)
 - Changes:  
   - Pokemon obey as normal (UNKNOWN)
   - Enemy Pokemon use moves as normal (UNKNOWN)

### Other Info  
To set up the repository, see [INSTALL.md](INSTALL.md).  
Special thanks to the original decomp authors: [pret.github.io](https://pret.github.io/).  
