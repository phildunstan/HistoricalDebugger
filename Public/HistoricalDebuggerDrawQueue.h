// Copyright Philip Dunstan

#pragma once

#include "CoreMinimal.h"
#include "HistoricalDebuggerDebugContext.h"

class FHistoricalDebuggerDebugFilter;

class HISTORICALDEBUGGER_API FHistoricalDebuggerDrawCommand
{
public:
	FHistoricalDebuggerDrawCommand() noexcept;
	FHistoricalDebuggerDrawCommand(const FHistoricalDebuggerDrawCommand& Other) noexcept;
	FHistoricalDebuggerDrawCommand(FHistoricalDebuggerDrawCommand&& Other) noexcept;
	FHistoricalDebuggerDrawCommand& operator=(const FHistoricalDebuggerDrawCommand& Other) = delete;
	
	~FHistoricalDebuggerDrawCommand();
	
	static FHistoricalDebuggerDrawCommand DrawNull(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration);
	static FHistoricalDebuggerDrawCommand DrawPoint(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Position, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);
	static FHistoricalDebuggerDrawCommand DrawLine(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& LineStart, const FVector& LineEnd, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);
	static FHistoricalDebuggerDrawCommand DrawDirectionalArrow(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& LineStart, const FVector& LineEnd, float ArrowSize, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);
	static FHistoricalDebuggerDrawCommand DrawDebugSphere(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, FVector::FReal Radius, int32 Segments, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);
	static FHistoricalDebuggerDrawCommand DrawDebugBox(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, const FVector& Extent, const FQuat& Rotation, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);
	static FHistoricalDebuggerDrawCommand DrawDebugString(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& TextLocation, const FString& Text, AActor* TestBaseActor, const FColor& Color, float Lifetime, bool bDrawShadow, float FontScale);
	static FHistoricalDebuggerDrawCommand DrawDebugCircle(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, FVector::FReal Radius, int32 Segments, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness, const FVector& YAxis, const FVector& ZAxis, bool bDrawAxis);
	static FHistoricalDebuggerDrawCommand DrawDebugCapsule(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, FVector::FReal HalfHeight, FVector::FReal Radius, const FQuat& Rotation, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);
	static FHistoricalDebuggerDrawCommand DrawDebugCylinder(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Start, const FVector& End, float Radius, int32 Segments, const  FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);
	static FHistoricalDebuggerDrawCommand DrawDebugCone(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Origin, const FVector& Direction, float Length, float AngleWidth, float AngleHeight, int32 NumSides, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);
	static FHistoricalDebuggerDrawCommand DrawDebugMesh(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const TArray<FVector>& Vertices, const TArray<int32>& Indices, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);

	FHistoricalDebuggerDebugContext DebugContext;
	float WorldTimeSeconds = 0.0f;
	int Iteration = 0;
	FVector Position = FVector::ZeroVector;
	FColor Color = FColor::White;
	bool bPersistentLines = false;
	float Lifetime = 0.0f;
	uint8 DepthPriority = 0;
	float Thickness = 0.0f;

	enum class EDrawType
	{
		None,
		Point,
		Line,
		DirectionalArrow,
		Sphere,
		Box,
		String,
		Circle,
		Capsule,
		Cylinder,
		Cone,
		Mesh,
	};
	EDrawType Type = EDrawType::None;

	struct FPointData
	{
		FVector Position;
	};
	struct FLineData
	{
		FVector LineStart;
		FVector LineEnd;
	};
	struct FArrowData
	{
		FVector LineStart;
		FVector LineEnd;
		float ArrowSize;
	};
	struct FSphereData
	{
		FVector Center;
		FVector::FReal Radius;
		int32 Segments;
	};
	struct FBoxData
	{
		FVector Center;
		FVector Extent;
		FQuat Rotation;
	};
	struct FStringData
	{
		FVector TextLocation;
		FString Text;
		AActor* TestBaseActor;
		bool bDrawShadow;
		float FontScale;
	};
	struct FCircleData
	{
		FVector Center;
		FVector::FReal Radius;
		int32 Segments;
		FVector YAxis;
		FVector ZAxis;
		bool bDrawAxis;
	};
	struct FCapsuleData
	{
		FVector Center;
		FVector::FReal HalfHeight;
		FVector::FReal Radius;
		FQuat Rotation;
	};
	struct FCylinderData
	{
		FVector Start;
		FVector End;
		FVector::FReal Radius;
		int32 Segments;
	};
	struct FConeData
	{
		FVector Origin;
		FVector Direction;
		float Length;
		float AngleWidth;
		float AngleHeight;
		int32 NumSides;
	};
	struct FMeshData
	{
		TArray<FVector> Vertices;
		TArray<int32> Indices;
	};
	TVariant<FPointData, FLineData, FArrowData, FSphereData, FBoxData, FStringData, FCircleData, FCapsuleData, FCylinderData, FConeData, FMeshData> Data;
};

class HISTORICALDEBUGGER_API FHistoricalDebuggerDrawQueue
{
public:
	FHistoricalDebuggerDrawQueue();
	~FHistoricalDebuggerDrawQueue();

	void Clear();
	void ExtractAllElements(TArray<FHistoricalDebuggerDrawCommand>& OutDrawCommands);
	void ExtractElements(TArray<FHistoricalDebuggerDrawCommand>& OutDrawCommands, const FHistoricalDebuggerDebugFilter& DebugFilter);
	void ExtractCommandTimes(TArray<float>& Times) const;
	void RemoveOldElements(float WorldTimeSeconds, float DebugHistoryWindowSeconds);

	void DrawNull(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration);
	void DrawDebugPoint(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Position, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);
	void DrawDebugLine(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& LineStart, const FVector& LineEnd, const FColor& Color, bool bPersistentLines = false, float Lifetime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);
	void DrawDebugDirectionalArrow(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& LineStart, const FVector& LineEnd, float ArrowSize, const FColor& Color, bool bPersistentLines = false, float Lifetime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);
	void DrawDebugCoordinateSystem(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Position, const FRotator& AxisRot, FVector::FReal Scale, bool bPersistentLines = false, float Lifetime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);
	void DrawDebugSphere(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, FVector::FReal Radius, int32 Segments, const FColor& Color, bool bPersistentLines = false, float Lifetime = -1.f, uint8 DepthPriority = 0, float Thickness = 0.f);
	void DrawDebugBox(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, const FVector& Extent, const FQuat& Rotation, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);
	void DrawDebugString(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& TextLocation, const FString& Text, AActor* TestBaseActor, const FColor& Color, float Lifetime, bool bDrawShadow, float FontScale);
	void DrawDebugCircle(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, FVector::FReal Radius, int32 Segments, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness, const FVector& YAxis, const FVector& ZAxis, bool bDrawAxis);
	void DrawDebugCapsule(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, FVector::FReal HalfHeight, FVector::FReal Radius, const FQuat& Rotation, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);
	void DrawDebugCylinder(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Start, const FVector& End, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);
	void DrawDebugCone(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Origin, const FVector& Direction, float Length, float AngleWidth, float AngleHeight, int32 NumSides, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);
	void DrawDebugMesh(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const TArray<FVector>& Vertices, const TArray<int32>& Indices, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness);
	
	void SetRegionOfInterest(const FVector& Position, float InRadius);
	const FVector& GetCenterOfInterest() const;
	FVector::FReal GetRadiusOfInterest() const;
	bool IsInRegionOfInterest(const FVector& Position) const;
	bool IsInRegionOfInterest(const FVector& Position, FVector::FReal Radius) const;
	//bool IsInRegionOfInterest(FAABB3 Bounds) const;

	static bool IsDebugDrawingEnabled() { return true; }

	bool AcceptCommand(const FVector& Position) const;

	void AddTimeToCommandQueueTimes(float WorldTimeSeconds);
	
private:
	mutable FCriticalSection CommandQueueCS;
	TArray<FHistoricalDebuggerDrawCommand> CommandQueue;
	TArray<float> CommandQueueTimesSeconds;

	FVector CenterOfInterest;
	FVector::FReal RadiusOfInterest;
};
