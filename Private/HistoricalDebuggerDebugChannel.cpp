// Fill out your copyright notice in the Description page of Project Settings.


#include "HistoricalDebuggerDebugChannel.h"
#include "DrawDebugHelpers.h"
#include "HistoricalDebuggerDrawQueue.h"
#include "HistoricalDebuggerManager.h"
#include "Engine/World.h"
#include "Logging/LogMacros.h"
#include "VisualLogger/VisualLogger.h"


FHistoricalDebuggerDebugChannel::FHistoricalDebuggerDebugChannel(const FName& Name)
	: Name(Name)
	, DebugDrawQueue(new FHistoricalDebuggerDrawQueue)
{
}

FHistoricalDebuggerDebugChannel::~FHistoricalDebuggerDebugChannel()
{
	delete DebugDrawQueue;
}

void FHistoricalDebuggerDebugChannel::DrawNull(const FHistoricalDebuggerDebugContext &DebugContext)
{
	DebugDrawQueue->DrawNull(DebugContext, WorldTimeSeconds, Iteration);
}

void FHistoricalDebuggerDebugChannel::DrawLine(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& LineStart, const FVector& LineEnd, const FColor& Color)
{
	DebugDrawQueue->DrawDebugLine(DebugContext, WorldTimeSeconds, Iteration, LineStart + DrawOffset, LineEnd + DrawOffset, Color, bPersistentLines, Lifetime, DepthPriority, Thickness);
}

void FHistoricalDebuggerDebugChannel::DrawPoint(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Position, float Size, const FColor& PointColor)
{
	DebugDrawQueue->DrawDebugPoint(DebugContext, WorldTimeSeconds, Iteration, Position + DrawOffset, PointColor, bPersistentLines, Lifetime, DepthPriority, Size);
}

void FHistoricalDebuggerDebugChannel::DrawDirectionalArrow(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& LineStart, const FVector& LineEnd, float ArrowSize, const FColor& Color)
{
	DebugDrawQueue->DrawDebugDirectionalArrow(DebugContext, WorldTimeSeconds, Iteration, LineStart + DrawOffset, LineEnd + DrawOffset, ArrowSize, Color, bPersistentLines, Lifetime, DepthPriority, Thickness);
}

void FHistoricalDebuggerDebugChannel::DrawBox(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Center, const FVector& Extent, const FColor& Color)
{
	const FQuat Rotation = FQuat::Identity;
	DebugDrawQueue->DrawDebugBox(DebugContext, WorldTimeSeconds, Iteration, Center + DrawOffset, Extent, Rotation, Color, bPersistentLines, Lifetime, DepthPriority, Thickness);
}

void FHistoricalDebuggerDebugChannel::DrawBox(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Center, const FVector& Extent, const FQuat& Rotation, const FColor& Color)
{
	DebugDrawQueue->DrawDebugBox(DebugContext, WorldTimeSeconds, Iteration, Center + DrawOffset, Extent, Rotation, Color, bPersistentLines, Lifetime, DepthPriority, Thickness);
}

void FHistoricalDebuggerDebugChannel::DrawCoordinateSystem(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& AxisLoc, const FRotator& AxisRot, float Scale)
{
	DebugDrawQueue->DrawDebugCoordinateSystem(DebugContext, WorldTimeSeconds, Iteration, AxisLoc + DrawOffset, AxisRot, Scale, bPersistentLines, Lifetime, DepthPriority, Thickness);
}

void FHistoricalDebuggerDebugChannel::DrawCrosshairs(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& AxisLoc, const FRotator& AxisRot, float Scale, const FColor& Color)
{
}

void FHistoricalDebuggerDebugChannel::DrawCircle(const FHistoricalDebuggerDebugContext& DebugContext, const FMatrix& TransformMatrix, float Radius, int32 Segments, const FColor& Color, bool bDrawAxis)
{
	DebugDrawQueue->DrawDebugCircle(DebugContext, WorldTimeSeconds, Iteration, TransformMatrix.GetOrigin() + DrawOffset, Radius, Segments, Color, bPersistentLines, Lifetime, DepthPriority, Thickness, TransformMatrix.GetColumn(1), TransformMatrix.GetColumn(2), bDrawAxis);
}

void FHistoricalDebuggerDebugChannel::DrawCircle(const FHistoricalDebuggerDebugContext& DebugContext, FVector Center, float Radius, int32 Segments, const FColor& Color, FVector YAxis, FVector ZAxis, bool bDrawAxis)
{
	DebugDrawQueue->DrawDebugCircle(DebugContext, WorldTimeSeconds, Iteration, Center + DrawOffset, Radius, Segments, Color, bPersistentLines, Lifetime, DepthPriority, Thickness, YAxis, ZAxis, bDrawAxis);
}

void FHistoricalDebuggerDebugChannel::DrawCircleArc(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Center, float Radius, const FVector& Direction, float AngleWidth, int32 Segments, const FColor& Color)
{
}

void FHistoricalDebuggerDebugChannel::Draw2DDonut(const FHistoricalDebuggerDebugContext& DebugContext, const FMatrix& TransformMatrix, float InnerRadius, float OuterRadius, int32 Segments, const FColor& Color)
{
}

void FHistoricalDebuggerDebugChannel::DrawSphere(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Center, float Radius, int32 Segments, const FColor& Color)
{
	DebugDrawQueue->DrawDebugSphere(DebugContext, WorldTimeSeconds, Iteration, Center + DrawOffset, Radius, Segments, Color, bPersistentLines, Lifetime, DepthPriority, Thickness);
}

void FHistoricalDebuggerDebugChannel::DrawCylinder(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Start, const FVector& End, float Radius, int32 Segments, const FColor& Color)
{
	DebugDrawQueue->DrawDebugCylinder(DebugContext, WorldTimeSeconds, Iteration, Start + DrawOffset, End + DrawOffset, Radius, Segments, Color, bPersistentLines, Lifetime, DepthPriority, Thickness);
}

void FHistoricalDebuggerDebugChannel::DrawCone(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Origin, const FVector& Direction, float Length, float AngleWidth, float AngleHeight, int32 NumSides, const FColor& Color)
{
	DebugDrawQueue->DrawDebugCone(DebugContext, WorldTimeSeconds, Iteration, Origin + DrawOffset, Direction, Length, AngleWidth, AngleHeight, NumSides, Color, bPersistentLines, Lifetime, DepthPriority, Thickness);
}

void FHistoricalDebuggerDebugChannel::DrawAltCone(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Origin, const FRotator& Rotation, float Length, float AngleWidth, float AngleHeight, const FColor& DrawColor)
{
}

void FHistoricalDebuggerDebugChannel::DrawString(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& TextLocation, const FString& Text, AActor* TestBaseActor, const FColor& TextColor, bool bDrawShadow, float FontScale)
{
	DebugDrawQueue->DrawDebugString(DebugContext, WorldTimeSeconds, Iteration, TextLocation + DrawOffset, Text, TestBaseActor, TextColor, Lifetime, bDrawShadow, FontScale);
}

void FHistoricalDebuggerDebugChannel::DrawFrustum(const FHistoricalDebuggerDebugContext& DebugContext, const FMatrix& FrustumToWorld, const FColor& Color)
{
}

void FHistoricalDebuggerDebugChannel::DrawCircle(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Base, const FVector& X, const FVector& Y, const FColor& Color, float Radius, int32 NumSides)
{
	DebugDrawQueue->DrawDebugCircle(DebugContext, WorldTimeSeconds, Iteration, Base + DrawOffset, Radius, NumSides, Color, bPersistentLines, Lifetime, DepthPriority, Thickness, X, Y, false);
}

void FHistoricalDebuggerDebugChannel::DrawCapsule(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Center, float HalfHeight, float Radius, const FQuat& Rotation, const FColor& Color)
{
	DebugDrawQueue->DrawDebugCapsule(DebugContext, WorldTimeSeconds, Iteration, Center + DrawOffset, HalfHeight, Radius, Rotation, Color, bPersistentLines, Lifetime, DepthPriority, Thickness);
}

void FHistoricalDebuggerDebugChannel::DrawCamera(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Location, const FRotator& Rotation, float FOVDeg, float Scale, const FColor& Color)
{
}

void FHistoricalDebuggerDebugChannel::DrawCentripetalCatmullRomSpline(const FHistoricalDebuggerDebugContext& DebugContext, TConstArrayView<FVector> Points, const FColor& Color, float Alpha, int32 NumSamplesPerSegment)
{
}

void FHistoricalDebuggerDebugChannel::DrawCentripetalCatmullRomSpline(const FHistoricalDebuggerDebugContext& DebugContext, TConstArrayView<FVector> Points, TConstArrayView<FColor> Colors, float Alpha, int32 NumSamplesPerSegment)
{
}

void FHistoricalDebuggerDebugChannel::DrawSolidBox(const FHistoricalDebuggerDebugContext& DebugContext, const FBox& Box, const FColor& Color, const FTransform& Transform)
{
	DebugDrawQueue->DrawDebugBox(DebugContext, WorldTimeSeconds, Iteration, Box.GetCenter() + DrawOffset, Box.GetExtent(), FQuat::Identity, Color, false, Lifetime, DepthPriority, 0.0f);
}

void FHistoricalDebuggerDebugChannel::DrawSolidBox(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Center, const FVector& Extent, const FColor& Color)
{
	DebugDrawQueue->DrawDebugBox(DebugContext, WorldTimeSeconds, Iteration, Center + DrawOffset, Extent, FQuat::Identity, Color, false, Lifetime, DepthPriority, 0.0f);
}

void FHistoricalDebuggerDebugChannel::DrawSolidBox(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Center, const FVector& Extent, const FQuat& Rotation, const FColor& Color)
{
	DebugDrawQueue->DrawDebugBox(DebugContext, WorldTimeSeconds, Iteration, Center + DrawOffset, Extent, Rotation, Color, false, Lifetime, DepthPriority, 0.0f);
}

void FHistoricalDebuggerDebugChannel::DrawMesh(const FHistoricalDebuggerDebugContext& DebugContext, const TArray<FVector>& Verts, const TArray<int32>& Indices, const FColor& Color)
{
	DebugDrawQueue->DrawDebugMesh(DebugContext, WorldTimeSeconds, Iteration, Verts, Indices, Color, false, Lifetime, DepthPriority, 0.0f);
}

void FHistoricalDebuggerDebugChannel::DrawSolidPlane(const FHistoricalDebuggerDebugContext& DebugContext, const FPlane& P, const FVector& Loc, float Size, const FColor& Color)
{
}

void FHistoricalDebuggerDebugChannel::DrawSolidPlane(const FHistoricalDebuggerDebugContext& DebugContext, const FPlane& P, const FVector& Loc, const FVector2D& Extents, const FColor& Color)
{
}

void FHistoricalDebuggerDebugChannel::DrawHitResult(const FHistoricalDebuggerDebugContext &DebugContext, const FHitResult &HitResult)
{
	if (HitResult.IsValidBlockingHit())
	{
		DrawLine(DebugContext, HitResult.TraceStart, HitResult.ImpactPoint, FColor::Red);
		DrawLine(DebugContext, HitResult.ImpactPoint, HitResult.TraceEnd, FColor::Red);
	}
	else
	{
		DrawLine(DebugContext, HitResult.TraceStart, HitResult.TraceEnd, FColor::Green);
	}
}

void FHistoricalDebuggerDebugChannel::DrawSkeleton(const FHistoricalDebuggerDebugContext &DebugContext, const USkeleton* const Skeleton, const FTransform& LocalToWorldTransform, const TArray<FTransform>& ComponentSpaceTransforms, const FColor& Color)
{
	const FReferenceSkeleton& ReferenceSkeleton = Skeleton->GetReferenceSkeleton();

	// UE_LOG(LogHistoricalDebugger, Log, TEXT("DrawSkeleton: %s"), *Skeleton->GetName());
	
	int32 BonesToDraw[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 20, 56, 57, 58, 66, 106, 107, 108, 131, 130, 129 };
	for (const int32 Index : BonesToDraw)
	// for (int32 Index = 0; Index < ComponentSpaceTransforms.Num(); ++Index)
	{
		if (Index >= ComponentSpaceTransforms.Num())
			continue;
		
		const FTransform Transform = ComponentSpaceTransforms[Index] * LocalToWorldTransform;
		const int32 ParentIndex = ReferenceSkeleton.GetParentIndex(Index);
		// UE_LOG(LogHistoricalDebugger, Log, TEXT("Bone %50s (% 3d) -> %50s (% 3d)"), *ReferenceSkeleton.GetBoneName(Index).ToString(), Index, ((ParentIndex != INDEX_NONE) ? *ReferenceSkeleton.GetBoneName(ParentIndex).ToString() : TEXT("None")), ParentIndex);
		
		FVector Start;
		FVector End;
		if (ParentIndex >= 0)
		{
			Start = (ComponentSpaceTransforms[ParentIndex] * LocalToWorldTransform).GetLocation();
			End = Transform.GetLocation();
		}
		else
		{
			Start = LocalToWorldTransform.GetLocation();
			End = Transform.GetLocation();
		}

		DebugDrawQueue->DrawDebugLine(DebugContext, WorldTimeSeconds, Iteration, Start, End, Color, bPersistentLines, Lifetime, DepthPriority, Thickness);
	}

	/*
	// UE_LOG(LogHistoricalDebugger, Log, TEXT("DrawSkeleton: %s"), *Skeleton->GetName());
	for (const FMeshBoneInfo& RawRefBoneInfo : ReferenceSkeleton.GetRawRefBoneInfo())
	{
		const int32 Index = ReferenceSkeleton.FindBoneIndex(RawRefBoneInfo.Name);
		// UE_LOG(LogHistoricalDebugger, Log, TEXT("Bone %50s (% 3d) -> %50s (% 3d)"), *RawRefBoneInfo.Name.ToString(), Index, ((RawRefBoneInfo.ParentIndex != INDEX_NONE) ? *ReferenceSkeleton.GetBoneName(RawRefBoneInfo.ParentIndex).ToString() : TEXT("None")), RawRefBoneInfo.ParentIndex);
		if (Index == INDEX_NONE)
			continue;
		if (Index >= ComponentSpaceTransforms.Num())
			continue;
		const FTransform Transform = ComponentSpaceTransforms[Index] * LocalToWorldTransform;

		const int32 ParentRawIndex = RawRefBoneInfo.ParentIndex;

		FVector LineStart;
		FVector LineEnd;
		if (ParentRawIndex >= 0)
		{
			const int32 ParentIndex = ReferenceSkeleton.FindBoneIndex(ReferenceSkeleton.GetRawRefBoneInfo()[ParentRawIndex].Name);
			if (ParentIndex == INDEX_NONE)
				continue;
			const FTransform ParentTransform = ComponentSpaceTransforms[ParentIndex] * LocalToWorldTransform;
			LineStart = ParentTransform.GetLocation();
			LineEnd = Transform.GetLocation();
		}
		else
		{
			LineStart = LocalToWorldTransform.GetLocation();
			LineEnd = Transform.GetLocation();
		}

		DebugDrawQueue->DrawDebugLine(DebugContext, WorldTimeSeconds, Iteration, LineStart, LineEnd, Color, bPersistentLines, Lifetime, DepthPriority, Thickness);
	}
	*/
}

void FHistoricalDebuggerDebugChannel::SetWorldTime(const float NewTimeSeconds)
{
	WorldTimeSeconds = NewTimeSeconds;
}

void FHistoricalDebuggerDebugChannel::SetIteration(const int NewIteration)
{
	Iteration = NewIteration;
}

void FHistoricalDebuggerDebugChannel::SetPersistentLines(const bool bNewPersistentLines)
{
	bPersistentLines = bNewPersistentLines;
}

void FHistoricalDebuggerDebugChannel::SetThickness(const float NewThickness)
{
	Thickness = NewThickness;
}

void FHistoricalDebuggerDebugChannel::SetLifetime(const float NewLifetime)
{
	Lifetime = NewLifetime;
}

void FHistoricalDebuggerDebugChannel::SetDepthPriority(const int8 NewDepthPriority)
{
	DepthPriority = NewDepthPriority;
}

void FHistoricalDebuggerDebugChannel::SetDrawOffset(const FVector &NewDrawOffset)
{
	DrawOffset = NewDrawOffset;
}

void FHistoricalDebuggerDebugChannel::ExtractDrawCommands(TArray<FHistoricalDebuggerDrawCommand>& DrawCommands, const FHistoricalDebuggerDebugFilter& DebugFilter) const
{
	DebugDrawQueue->ExtractElements(DrawCommands, DebugFilter);
}

void FHistoricalDebuggerDebugChannel::ExtractDataTimes(TArray<float> &Times) const
{
	DebugDrawQueue->ExtractCommandTimes(Times);
}

void FHistoricalDebuggerDebugChannel::Clear()
{
	DebugDrawQueue->Clear();
}

void FHistoricalDebuggerDebugChannel::RemoveExpiredDrawCommands(float CurrentWorldTimeSeconds, float DebugHistoryWindowSeconds)
{
	DebugDrawQueue->RemoveOldElements(CurrentWorldTimeSeconds, DebugHistoryWindowSeconds);
}
