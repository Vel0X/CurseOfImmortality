# Implementation Details

---

## Terminology

- **BaseAbility** or **Ability** &rarr; A unique Ability the PlayerCharacter can have, that is either a 
*Melee Ability*, a *Ranged Ability* or a *Special Ability*
- **UpgradeAbility** &rarr; Something that can be applied to Base Abilities in order to change their
behaviour. UpgradeAbilities can apply to either one of the three BaseAbility-Types or to all of them.
- **PassiveBoon** &rarr; A Buff, that sits on the PlayerCharacter.
- **Upgrade** &rarr; Any of the three above

## Base Ability

### Order of Execution
- ``BeginPlay()`` gets called first, whenever an Ability-Actor is spawned.
- ``InitializeAbility()`` gets called directly after the Ability is spawned. Here, 
important changes to the Ability can be made, such as changing its parent (for Special Abilities) or setting parameters
- ``OnAbilityCreation()`` gets called only when the Ability is spawned the first time and not
when UpgradeAbilities spawn Instances of it (e.g., Seal of Congruence)
- ``AfterInitialization()`` gets called after all the UpgradeAbilities get added to the Ability.
It is here, that ``OnAbilityStart()`` gets called on all the UpgradeAbilities and that important changes 
to the Ability are made (e.g. scale it up, based on the ``RelativeSize`` Attribute)



- ``OnAbilityCreation()``

## Base Upgrade

the Base Class for all UpgradeAbilities. The Base Upgrade has multiple functions on it that get called at multiple stages in the
Ability Lifetime. 
- ``OnAbilityStart()`` gets called, when the Ability is fully initialized (``AfterInitialization()``)
- ``OnEnemyHit()`` gets called, whenever the Ability hits someone
- ``OnAbilityEnd()`` gets called, before the Ability is destroyed

Specific UpgradeAbilities, that inherit from ``BaseUpgrade`` can override these functions to inject their own behaviour
in the Ability.

## Base Buff

Every Character in the game has a Buff-Stack on him. The Base Buff has multiple functions on it that get called at multiple stages in the
Character Lifetime.
- ``Tick()`` gets called on every Buff on the Stack in the ``Tick()`` of the Character
- ``OnBuffStart()`` gets called, when the Buff is put on the Stack
- ``OnBuffEnd()`` gets called, when the Buff is removed from the Stack
- ``OnDamageTaken()`` gets called, when the Actor takes Damage

Additionally, there are a number of flags, that can define the basic behaviour of the buff-
- ``CustomBuffEnd`` &rarr; When this flag is enabled, the buff duration will be ignored and the the buff will instead be removed at a
custom point later, defined by the buff.
- ``Stackable`` &rarr; When this flag is enabled, a buff can be applied multiple times in succession, its effects stacking.
The behaviour of this stacking can be defined within the concrete buff.
- ``StatModifier`` &rarr; When this flag is enabled all the stats will be recalculated, when the Buff does something (e.g. Gets applied or removed from the stack).

The order in which the Upgrades 

## Stat Modification

This small class holds a map of Stat Modifications, with the key being the Stat-Name to modify and the Value being a 
``Tuple<float, bool>`` with the float indicating an amount and the bool if the modification is *percentage* or *flat*. 

## AttackManager

The Attack Manager has multiple responsibilities (might be better to split it into multiple
classes in the future)
- Spawning Abilities
- Managing the BaseAbilties and UpgradeAbilities that are currently active on the PlayerCharacter
- Managing the Pool, from which one of three random Upgrades can be picked at the end of each round

