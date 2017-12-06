// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class SpawnGeos_cppBaseEditorTarget : TargetRules
{
	public SpawnGeos_cppBaseEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		ExtraModuleNames.Add("SpawnGeos_cppBase");
	}
}
