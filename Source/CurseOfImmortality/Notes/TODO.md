# Todo

---

# Upgrade System

---

### General:

- (**DONE**) Upgrade Application Order: In which order lie the Upgrades on the Stack
 - (**DONE**) Enum and making Upgrades sortable with Enum
- Weight Behaviour Classes
  - Change Weight based on Number of Rounds
  - Change Weight based on Number of Abilties or Ratio Abilities/Upgrades)
  - Change Weight based on if the Player has some specific other Ability

### Abilities:

- Dealing Damage
- SwordSlash Ability

### Upgrades:

- Fierce Determination
  - static Field in the Upgrade, so it can be checked with each Swordstrike, if the same Enemy was hit
  - maybe this needs to be a List with the enemies that were hit last time
- Battle Frenzy 
  - Requires Buff System
- Spellblade
- Hemorrhage
  - Requires Buff System
- Berserker Fury
  - Requires Buff System
- Sharpend Reflexes
- Expose Weakness
  - Requires Buff System
- Cursemark of Doom
  - Is this even an AbilityUpgrade?

# Buff System

- Player has a Stack of Buffs on him
- The Buffs have a OnBuffApply and OnBuffDestroy
  - Permanent Stat Buffs can just add their Stats at OnBuffApply and remove them at OnBuffDestroy
- The Buffs can subscribe to 
  - OnDamageDealt
  - OnDamageTaken
  - OnAbilityUsed
- Similar to Upgrade System



# Random Stuff 

- Better Sword Model and Texture (With unique Emissive Map, that can be scaled based on Attack Speed)
- Damage Objects for all Abilities!!!