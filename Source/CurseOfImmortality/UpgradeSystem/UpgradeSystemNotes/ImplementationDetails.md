# Implementation Details

---

## Terminology

- **BaseAbility** &rarr; A unique Ability the PlayerCharacter can have, that is either a 
*Melee Ability*, a *Ranged Ability* or a *Special Ability*
- **UpgradeAbility** &rarr; Something that can be applied to Base Abilities in order to change their
behaviour. UpgradeAbilities can apply to either one of the three BaseAbility-Types or to all of them.
- **PassiveBoon** 
- **Upgrade** &rarr; Any of the three above

## Base Ability

### Order of Execution
- ``BeginPlay()`` gets called first, whenever an Ability-Actor is spawned.
- ``InitializeAbility()`` gets called directly after the Ability is spawned. Here, 
important changes to the Ability can be made, such as changing its parent (for Special Abilities) or setting parameters
- ``OnAbilityCreation()`` gets called only when the Ability is spawned the first time and not
when Upgrades spawn Instances of it (e.g., Seal of Congruence)
- ``AfterInitialization()`` gets called after all the Upgrades get added to the Ability.
It is here, that ``OnAbilityStart()`` gets called on all the Upgrades and that important changes 
to the Ability are made (e.g. scale it up, based on the ``RelativeSize`` Attribute)



- ``OnAbilityCreation()``

## Base Upgrade

The Base Upgrade has multiple functions on it that get called at multiple stages in the
Ability Lifetime. 
- ``OnAbilityStart()`` gets called, when the Ability is fully initialized (``AfterInitialization()``)
- ``OnEnemyHit()`` gets called, whenever the Ability hits someone
- ``OnAbilityEnd()`` gets called, before the Ability is destroyed

Specific Upgrades, that inherit from ``BaseUpgrade`` can override these functions to inject their own behaviour
in the Ability.

## AttackManager

The Attack Manager has multiple responsibilities (might be better to split it into multiple
classes in the future)
- Spawning Abilities
- Managing the BaseAbilties and UpgradeAbilities that are currently active on the PlayerCharacter
- Managing the Pool, from which one of three random Upgrades can be picked at the end of each round

Buffs can either be temporary or permanent.

