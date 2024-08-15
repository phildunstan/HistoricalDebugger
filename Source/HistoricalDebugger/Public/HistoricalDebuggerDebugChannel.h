// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HistoricalDebuggerDrawQueue.h"
#include "Engine/Blueprint.h"

class AActor;
class UWorld;

class FHistoricalDebuggerDebugContext;
class FHistoricalDebuggerDebugFilter;
class FHistoricalDebuggerDrawQueue;

class HISTORICALDEBUGGER_API FHistoricalDebuggerDebugChannel
{
public:
	FHistoricalDebuggerDebugChannel(const FName& Name);
	~FHistoricalDebuggerDebugChannel();

	FHistoricalDebuggerDebugChannel(const FHistoricalDebuggerDebugChannel&) = delete;
	FHistoricalDebuggerDebugChannel& operator=(const FHistoricalDebuggerDebugChannel&) = delete;
	FHistoricalDebuggerDebugChannel(FHistoricalDebuggerDebugChannel&&) = delete;
	FHistoricalDebuggerDebugChannel& operator=(FHistoricalDebuggerDebugChannel&&) = delete;

	const FName& GetName() const { return Name; }

	void DrawNull(const FHistoricalDebuggerDebugContext& DebugContext);
	void DrawLine(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& LineStart, const FVector& LineEnd, const FColor& Color);
	void DrawPoint(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Position, float Size, const FColor& PointColor);
	void DrawDirectionalArrow(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& LineStart, const FVector& LineEnd, float ArrowSize, const FColor& Color);
	void DrawBox(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Center, const FVector& Extent, const FColor& Color);
	void DrawBox(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Center, const FVector& Extent, const FQuat& Rotation, const FColor& Color);
	void DrawCoordinateSystem(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& AxisLoc, const FRotator& AxisRot, float Scale);
	void DrawCrosshairs(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& AxisLoc, const FRotator& AxisRot, float Scale, const FColor& Color = FColor::White);
	void DrawCircle(const FHistoricalDebuggerDebugContext& DebugContext, const FMatrix& TransformMatrix, float Radius, int32 Segments, const FColor& Color, bool bDrawAxis = true);
	void DrawCircle(const FHistoricalDebuggerDebugContext& DebugContext, FVector Center, float Radius, int32 Segments, const FColor& Color, FVector YAxis = FVector(0.f, 1.f, 0.f), FVector ZAxis = FVector(0.f, 0.f, 1.f), bool bDrawAxis = true);
	void DrawCircleArc(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Center, float Radius, const FVector& Direction, float AngleWidth, int32 Segments, const FColor& Color);
	void Draw2DDonut(const FHistoricalDebuggerDebugContext& DebugContext, const FMatrix& TransformMatrix, float InnerRadius, float OuterRadius, int32 Segments, const FColor& Color);
	void DrawSphere(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Center, float Radius, int32 Segments, const FColor& Color);
	void DrawCylinder(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Start, const FVector& End, float Radius, int32 Segments, const FColor& Color);
	void DrawCone(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Origin, const FVector& Direction, float Length, float AngleWidth, float AngleHeight, int32 NumSides, const FColor& Color);
	void DrawAltCone(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Origin, const FRotator& Rotation, float Length, float AngleWidth, float AngleHeight, const FColor& DrawColor);
	void DrawString(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& TextLocation, const FString& Text, class AActor* TestBaseActor = NULL, const FColor& TextColor = FColor::White, bool bDrawShadow = false, float FontScale = 1.f);
	void DrawFrustum(const FHistoricalDebuggerDebugContext& DebugContext, const FMatrix& FrustumToWorld, const FColor& Color);
	void DrawCircle(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Base, const FVector& X, const FVector& Y, const FColor& Color, float Radius, int32 NumSides);
	void DrawCapsule(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Center, float HalfHeight, float Radius, const FQuat& Rotation, const FColor& Color);
	void DrawCamera(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Location, const FRotator& Rotation, float FOVDeg, float Scale = 1.f, const FColor& Color = FColor::White);
	void DrawCentripetalCatmullRomSpline(const FHistoricalDebuggerDebugContext& DebugContext, TConstArrayView<FVector> Points, const FColor& Color, float Alpha = 0.5f, int32 NumSamplesPerSegment = 8);
	void DrawCentripetalCatmullRomSpline(const FHistoricalDebuggerDebugContext& DebugContext, TConstArrayView<FVector> Points, TConstArrayView<FColor> Colors, float Alpha = 0.5f, int32 NumSamplesPerSegment = 8);
	void DrawSolidBox(const FHistoricalDebuggerDebugContext& DebugContext, const FBox& Box, const FColor& Color, const FTransform& Transform = FTransform::Identity);
	void DrawSolidBox(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Center, const FVector& Extent, const FColor& Color);
	void DrawSolidBox(const FHistoricalDebuggerDebugContext& DebugContext, const FVector& Center, const FVector& Extent, const FQuat& Rotation, const FColor& Color);
	void DrawMesh(const FHistoricalDebuggerDebugContext& DebugContext, const TArray<FVector>& Verts, const TArray<int32>& Indices, const FColor& Color);
	void DrawSolidPlane(const FHistoricalDebuggerDebugContext& DebugContext, const FPlane& P, const FVector& Loc, float Size, const FColor& Color);
	void DrawSolidPlane(const FHistoricalDebuggerDebugContext& DebugContext, const FPlane& P, const FVector& Loc, const FVector2D& Extents, const FColor& Color);
	
	void DrawHitResult(const FHistoricalDebuggerDebugContext& DebugContext, const FHitResult& HitResult);
	void DrawSkeleton(const FHistoricalDebuggerDebugContext& DebugContext, const USkeleton* const Skeleton, const FTransform& LocalToWorldTransform, const TArray<FTransform>& ComponentSpaceTransforms, const FColor& Color);

	void SetWorldTime(const float NewTimeSeconds);
	void SetIteration(const int NewIteration);
	void SetPersistentLines(const bool bNewPersistentLines);
	void SetThickness(const float NewThickness);
	void SetLifetime(const float NewLifetime);
	void SetDepthPriority(const int8 NewDepthPriority);
	void SetDrawOffset(const FVector& NewDrawOffset);

	void ExtractDrawCommands(TArray<FHistoricalDebuggerDrawCommand>& DrawCommands, const FHistoricalDebuggerDebugFilter& DebugFilter) const;
	void ExtractDataTimes(TArray<float>& Times) const;

	void Clear();
	void RemoveExpiredDrawCommands(float WorldTimeSeconds, float DebugHistoryWindowSeconds);
	
private:
	const FName Name;
	FHistoricalDebuggerDrawQueue* DebugDrawQueue = nullptr;
	float WorldTimeSeconds = 0.0f;
	int Iteration = 0;
	bool bPersistentLines = false;
	float Lifetime = 1.0f; // one frame
	uint8 DepthPriority = 0;
	float Thickness = 0.f;
	FVector DrawOffset = FVector::ZeroVector;
};
