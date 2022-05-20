#pragma once

UENUM()
enum EStats
{
	Health,
	PhysicalDamage,
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
	SoulFlayer
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
	Deprived,
	Stormcaller,
	MawOfSothros
};