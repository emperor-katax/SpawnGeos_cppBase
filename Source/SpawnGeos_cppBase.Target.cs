// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SpawnGeos_cppBaseTarget : TargetRules
{
	public SpawnGeos_cppBaseTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		ExtraModuleNames.Add("SpawnGeos_cppBase");
	}
}
