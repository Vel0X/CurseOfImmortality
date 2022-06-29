#pragma once

UENUM()
enum EStats
{
	Health,
	PhysicalDamage,
	AttackSpeed,
	Arcane,
	Faith,
	Astrality,
	Soul,
	Ruin,
	Gravity,
	Movespeed
};

UENUM()
enum EBuff
{
	Bleed,
	IncreaseHealth,
	CursedBlade,
	Rejuvenation,
	SoulFlayer,
	AdrenalineRush
};

UENUM()
enum EAttachmentPoint
{
	UpperPoint,
	CenterPoint,
	LowerPoint
};

UENUM()
enum ETrapTypes
{
	Spikes,
	Saws,
	Turrets,
	Arrows,
	All
};

UENUM()
enum EFaction
{
	Friendly,
	Enemy
};

UENUM()
enum EEnemy
{
	Base,
	WeakDeprived,
	Deprived,
	Stormcaller,
	MawOfSothros,
	Inu,
	Moloch
};

UENUM()
enum EMawAttacks
{
	VomitState,
	TailSweepState,
	GroundSlamState,
	ChargeAttackState,
	LaserState
};

UENUM()
enum EUpgradeName
{
	SwordSlash,
	Fireball,
	ArcaneWhisper,
	KarysAnimus,
	Whirlwind,
	ArcaneReplicatorTurret,
	KarysAnimusProjectile,
	SpellbladeProjectile,
	Behemoth,
	Hemorrhage,
	CursemarkOfDoom,
	//does this need to be on an ability
	SharpendReflexes,
	Spellblade,
	BattleFrenzy,
	FierceDetermination,
	SealOfCongruence,
	Pierce,
	ShatteredImpact,
	SustainedFocus,
	Revelation,
	ArcaneReplicator,
	DolomarsWrath,
	SeaOfDarkness,
	MawSlam,
	LavaCrack,
	TailSweep,
	TrailExplosion,
	TrapProjectile,
	InuProjectile
};

UENUM()
enum EUpgradeOrder
{
	AttributeSetter,
	AttributeReader
};

UENUM()
enum EAssortment
{
	StormcallerCircle,
	DeprivedMob
};

UENUM()
enum ELog
{
	Round,
	PlayerStateMachine,
	MawStateMachine,
	DeprivedStateMachine,
	StormCallerStateMachine,
	MolochStateMachine,
	InuStateMachine,
	DamageComponent,
	Buff
};

UENUM()
enum EControlFlag
{
	AutomaticRoundIncrement,
	SFX,
	Music
};

UENUM()
enum EAbilityType
{
	None,
	Melee,
	Ranged,
	Special
};
