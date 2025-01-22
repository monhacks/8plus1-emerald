
# Pokemon 4x Emerald  
A 4-in-1 emerald game designed for nuzlocke relays.  
  
If you just want to download, you can do so on the [releases](https://github.com/ordinary-magic/Pokemon-4x-Emerald/releases) page.
  
Game Features (Many Spoilers)  
  
## Common Changes  
 - Added Level Caps (gym leaders and e4)  
 - Added "Rare Candies" key item for reusable rare candy  
 - Added "Tent" key item: It's a portable pokemon center!
 - All evolutions are now achievable by level up, item, or leveling up while holding a specific item.  
 - Pokemon won't faint to out of battle poison.  
 - Made boss trainers more difficult (on average one extra pokemon, more interesting mons & moves)  
 - Select your Game Version at the title screen (L/R)  
 -  Note: all versions are compatible with each other, and can be swapped freely within a run.  
  
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
 - Difficulty Hack (Its Very Mean)  
 - Every standard trainer is a very agressive spinner.  
 - Non-Boss enemy trainer pokemon are higher level than normal.    
 - Pokemon Centers and similar will not heal your hp, and have a chance to status you when used.  
 - Withdrawing a pokemon from a box will leave it at 1 hp and possibly frozen.  
  
## UNKNOWN Version:  
 - Every single pokemon level up move is replaced with Hidden Power.  
 - Enemy pokemon will only ever use hidden power.  
 - You can only use hidden power (your pokemon will disobey)  
 - Enemy Trainer Pokemon's Hidden Power bp will scale as the game progresses. (relative to their pkmn iv's)  
 - Standard "Rare Candy" items now maximize your hidden power bp instead of leveling you up.  
  
### Other Info  
To set up the repository, see [INSTALL.md](INSTALL.md).  
Special thanks to the original decomp authors: [pret.github.io](https://pret.github.io/).  
