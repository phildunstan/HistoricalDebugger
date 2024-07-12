// Copyright Philip Dunstan


#include "HistoricalDebuggerDrawQueue.h"

#include "HistoricalDebuggerManager.h"

FHistoricalDebuggerDrawCommand::FHistoricalDebuggerDrawCommand() noexcept
{
}

FHistoricalDebuggerDrawCommand::FHistoricalDebuggerDrawCommand(const FHistoricalDebuggerDrawCommand& Other) noexcept
	: DebugContext(Other.DebugContext)
	, WorldTimeSeconds(Other.WorldTimeSeconds)
	, Iteration(Other.Iteration)
	, Position(Other.Position)
	, Color(Other.Color)
	, bPersistentLines(Other.bPersistentLines)
	, Lifetime(Other.Lifetime)
	, DepthPriority(Other.DepthPriority)
	, Thickness(Other.Thickness)
	, Type(Other.Type)
	, Data(Other.Data)
{
}

FHistoricalDebuggerDrawCommand::FHistoricalDebuggerDrawCommand(FHistoricalDebuggerDrawCommand&& Other) noexcept
	: DebugContext(std::move(Other.DebugContext))
	, WorldTimeSeconds(std::move(Other.WorldTimeSeconds))
	, Iteration(std::move(Other.Iteration))
	, Position(std::move(Other.Position))
	, Color(std::move(Other.Color))
	, bPersistentLines(std::move(Other.bPersistentLines))
	, Lifetime(std::move(Other.Lifetime))
	, DepthPriority(std::move(Other.DepthPriority))
	, Thickness(std::move(Other.Thickness))
	, Type(std::move(Other.Type))
	, Data(std::move(Other.Data))
{
}

FHistoricalDebuggerDrawCommand::~FHistoricalDebuggerDrawCommand()
{
}

FHistoricalDebuggerDrawCommand FHistoricalDebuggerDrawCommand::DrawNull(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration)
{
	FHistoricalDebuggerDrawCommand Command;
	Command.Type = EDrawType::None;
	Command.DebugContext = DebugContext;
	Command.WorldTimeSeconds = WorldTimeSeconds;
	Command.Iteration = Iteration;
	return Command;
}

FHistoricalDebuggerDrawCommand FHistoricalDebuggerDrawCommand::DrawPoint(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Position, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FHistoricalDebuggerDrawCommand Command;
	Command.Type = EDrawType::Point;
	Command.DebugContext = DebugContext;
	Command.WorldTimeSeconds = WorldTimeSeconds;
	Command.Iteration = Iteration;
	Command.Position = Position;
	Command.Color = Color;
	Command.bPersistentLines = bPersistentLines;
	Command.Lifetime = Lifetime;
	Command.DepthPriority = DepthPriority;
	Command.Thickness = Thickness;
	Command.Data.Emplace<FPointData>(Position);
	return Command;
}

FHistoricalDebuggerDrawCommand FHistoricalDebuggerDrawCommand::DrawLine(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& LineStart, const FVector& LineEnd, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FHistoricalDebuggerDrawCommand Command;
	Command.Type = EDrawType::Line;
	Command.DebugContext = DebugContext;
	Command.WorldTimeSeconds = WorldTimeSeconds;
	Command.Iteration = Iteration;
	Command.Position = 0.5f * (LineStart + LineEnd);
	Command.Color = Color;
	Command.bPersistentLines = bPersistentLines;
	Command.DepthPriority = DepthPriority;
	Command.Thickness = Thickness;
	Command.Lifetime = Lifetime;
	Command.Data.Emplace<FLineData>(LineStart, LineEnd);
	return Command;
}

FHistoricalDebuggerDrawCommand FHistoricalDebuggerDrawCommand::DrawDirectionalArrow(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& LineStart, const FVector& LineEnd, float ArrowSize, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FHistoricalDebuggerDrawCommand Command;
	Command.Type = EDrawType::DirectionalArrow;
	Command.DebugContext = DebugContext;
	Command.WorldTimeSeconds = WorldTimeSeconds;
	Command.Iteration = Iteration;
	Command.Position = 0.5f * (LineStart + LineEnd);
	Command.Color = Color;
	Command.bPersistentLines = bPersistentLines;
	Command.Lifetime = Lifetime;
	Command.DepthPriority = DepthPriority;
	Command.Thickness = Thickness;
	Command.Data.Emplace<FArrowData>(LineStart, LineEnd, ArrowSize);
	return Command;
}

FHistoricalDebuggerDrawCommand FHistoricalDebuggerDrawCommand::DrawDebugSphere(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, FVector::FReal Radius, int32 Segments, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FHistoricalDebuggerDrawCommand Command;
	Command.Type = EDrawType::Sphere;
	Command.DebugContext = DebugContext;
	Command.WorldTimeSeconds = WorldTimeSeconds;
	Command.Iteration = Iteration;
	Command.Position = Center;
	Command.Color = Color;
	Command.bPersistentLines = bPersistentLines;
	Command.Lifetime = Lifetime;
	Command.DepthPriority = DepthPriority;
	Command.Thickness = Thickness;
	Command.Data.Emplace<FSphereData>(Center, Radius, Segments);
	return Command;
}

FHistoricalDebuggerDrawCommand FHistoricalDebuggerDrawCommand::DrawDebugBox(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, const FVector& Extent, const FQuat& Rotation, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FHistoricalDebuggerDrawCommand Command;
	Command.Type = EDrawType::Box;
	Command.DebugContext = DebugContext;
	Command.WorldTimeSeconds = WorldTimeSeconds;
	Command.Iteration = Iteration;
	Command.Position = Center;
	Command.Color = Color;
	Command.bPersistentLines = bPersistentLines;
	Command.Lifetime = Lifetime;
	Command.DepthPriority = DepthPriority;
	Command.Thickness = Thickness;
	Command.Data.Emplace<FBoxData>(Center, Extent, Rotation);
	return Command;
}

FHistoricalDebuggerDrawCommand FHistoricalDebuggerDrawCommand::DrawDebugString(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& TextLocation, const FString& Text, AActor* TestBaseActor, const FColor& Color, float Lifetime, bool bDrawShadow, float FontScale)
{
	FHistoricalDebuggerDrawCommand Command;
	Command.Type = EDrawType::String;
	Command.DebugContext = DebugContext;
	Command.WorldTimeSeconds = WorldTimeSeconds;
	Command.Iteration = Iteration;
	Command.Color = Color;
	
	Command.Position = TextLocation;
	Command.Lifetime = Lifetime;
	
	Command.Data.Emplace<FStringData>(TextLocation, Text, TestBaseActor, bDrawShadow, FontScale);
	return Command;
}

FHistoricalDebuggerDrawCommand FHistoricalDebuggerDrawCommand::DrawDebugCircle(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, FVector::FReal Radius, int32 Segments, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness, const FVector& YAxis, const FVector& ZAxis, bool bDrawAxis)
{
	FHistoricalDebuggerDrawCommand Command;
	Command.Type = EDrawType::Circle;
	Command.DebugContext = DebugContext;
	Command.WorldTimeSeconds = WorldTimeSeconds;
	Command.Iteration = Iteration;
	Command.Position = Center;
	Command.Color = Color;
	Command.bPersistentLines = bPersistentLines;
	Command.Lifetime = Lifetime;
	Command.DepthPriority = DepthPriority;
	Command.Thickness = Thickness;
	Command.Data.Emplace<FCircleData>(Center, Radius, Segments, YAxis, ZAxis, bDrawAxis);
	return Command;
}

FHistoricalDebuggerDrawCommand FHistoricalDebuggerDrawCommand::DrawDebugCapsule(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, FVector::FReal HalfHeight, FVector::FReal Radius, const FQuat& Rotation, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FHistoricalDebuggerDrawCommand Command;
	Command.Type = EDrawType::Capsule;
	Command.DebugContext = DebugContext;
	Command.WorldTimeSeconds = WorldTimeSeconds;
	Command.Iteration = Iteration;
	Command.Position = Center;
	Command.Color = Color;
	Command.bPersistentLines = bPersistentLines;
	Command.Lifetime = Lifetime;
	Command.DepthPriority = DepthPriority;
	Command.Thickness = Thickness;
	Command.Data.Emplace<FCapsuleData>(Center, HalfHeight, Radius, Rotation);
	return Command;
}

FHistoricalDebuggerDrawCommand FHistoricalDebuggerDrawCommand::DrawDebugCylinder(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Start, const FVector& End, float Radius, int32 Segments, const  FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FHistoricalDebuggerDrawCommand Command;
	Command.Type = EDrawType::Cylinder;
	Command.DebugContext = DebugContext;
	Command.WorldTimeSeconds = WorldTimeSeconds;
	Command.Iteration = Iteration;
	Command.Position = 0.5f * (Start + End);
	Command.Color = Color;
	Command.bPersistentLines = bPersistentLines;
	Command.Lifetime = Lifetime;
	Command.DepthPriority = DepthPriority;
	Command.Thickness = Thickness;
	Command.Data.Emplace<FCylinderData>(Start, End, Radius, Segments);
	return Command;
}

FHistoricalDebuggerDrawCommand FHistoricalDebuggerDrawCommand::DrawDebugCone(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Origin, const FVector& Direction, float Length, float AngleWidth, float AngleHeight, int32 NumSides, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FHistoricalDebuggerDrawCommand Command;
	Command.Type = EDrawType::Cone;
	Command.DebugContext = DebugContext;
	Command.WorldTimeSeconds = WorldTimeSeconds;
	Command.Iteration = Iteration;
	Command.Position = Origin;
	Command.Color = Color;
	Command.bPersistentLines = bPersistentLines;
	Command.Lifetime = Lifetime;
	Command.DepthPriority = DepthPriority;
	Command.Thickness = Thickness;
	Command.Data.Emplace<FConeData>(Origin, Direction, Length, AngleWidth, AngleHeight, NumSides);
	return Command;
}

FHistoricalDebuggerDrawCommand FHistoricalDebuggerDrawCommand::DrawDebugMesh(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const TArray<FVector>& Vertices, const TArray<int32>& Indices, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FHistoricalDebuggerDrawCommand Command;
	Command.Type = EDrawType::Mesh;
	Command.DebugContext = DebugContext;
	Command.WorldTimeSeconds = WorldTimeSeconds;
	Command.Iteration = Iteration;
	Command.Position = Vertices.Num() > 0 ? Vertices[0] : FVector::ZeroVector;
	Command.Color = Color;
	Command.bPersistentLines = bPersistentLines;
	Command.Lifetime = Lifetime;
	Command.DepthPriority = DepthPriority;
	Command.Thickness = Thickness;
	Command.Data.Emplace<FMeshData>(Vertices, Indices);
	return Command;
}


FHistoricalDebuggerDrawQueue::FHistoricalDebuggerDrawQueue()
	: CenterOfInterest(FVector::ZeroVector)
	, RadiusOfInterest(0)
{
}

FHistoricalDebuggerDrawQueue::~FHistoricalDebuggerDrawQueue()
{
}

void FHistoricalDebuggerDrawQueue::Clear()
{
	FScopeLock Lock(&CommandQueueCS);
	CommandQueue.Reset();
	CommandQueueTimesSeconds.Reset();
}

void FHistoricalDebuggerDrawQueue::ExtractAllElements(TArray<FHistoricalDebuggerDrawCommand>& OutDrawCommands)
{
	FScopeLock Lock(&CommandQueueCS);
	OutDrawCommands = CommandQueue;
}

void FHistoricalDebuggerDrawQueue::ExtractElements(TArray<FHistoricalDebuggerDrawCommand> &OutDrawCommands, const FHistoricalDebuggerDebugFilter& DebugFilter)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("FHistoricalDebuggerDrawQueue::ExtractElements"))
	FScopeLock Lock(&CommandQueueCS);

	// ideally we would replace lower bound with binary search, but the data is sorted by WorldTimeSeconds and we care about Command.WorldTimeSeconds + Command.Lifetime
	// const int LowerBound = Algo::LowerBoundBy(CommandQueue, DebugFilter.DrawTimeSeconds, [](const FHistoricalDebuggerDrawCommand& Command) { return Command.WorldTimeSeconds + Command.Lifetime; });
	const int LowerBound = 0;
	// const int UpperBound = CommandQueue.Num() - 1;
	const int UpperBound = Algo::UpperBoundBy(CommandQueue, DebugFilter.DrawTimeSeconds, [](const FHistoricalDebuggerDrawCommand& Command) { return Command.WorldTimeSeconds; }) - 1;
	
	TMap<FString, float> LastUniqueCommandTimes;
	for (int Index = UpperBound; Index >= LowerBound; --Index)
	{
		const FHistoricalDebuggerDrawCommand& Command = CommandQueue[Index];
		if (Command.WorldTimeSeconds + Command.Lifetime < DebugFilter.DrawTimeSeconds)
			continue;
		if (Command.WorldTimeSeconds > DebugFilter.DrawTimeSeconds)
			continue;
		if (DebugFilter.Actor && (Command.DebugContext.Actor != DebugFilter.Actor))
			continue;
		if (!DebugFilter.IdFilterInclude.IsEmpty() && !Command.DebugContext.Id.Contains(DebugFilter.IdFilterInclude))
			continue;
		if (!DebugFilter.IdFilterExclude.IsEmpty() && Command.DebugContext.Id.Contains(DebugFilter.IdFilterExclude))
			continue;
		if ((DebugFilter.DrawSubIteration >= 0) && (Command.DebugContext.SubIteration >= 0) && (Command.DebugContext.SubIteration != DebugFilter.DrawSubIteration))
			continue;
		if (Command.DebugContext.FramePersistence == EHistoricalDebuggerDebugFramePersistence::Unique)
		{
			if (const float* LastUniqueFrameTime = LastUniqueCommandTimes.Find(Command.DebugContext.Id))
			{
				if (Command.WorldTimeSeconds != *LastUniqueFrameTime)
					continue;
			}
			LastUniqueCommandTimes.Add(Command.DebugContext.Id, Command.WorldTimeSeconds);
		}
		OutDrawCommands.Add(Command);
	}
}

void FHistoricalDebuggerDrawQueue::ExtractCommandTimes(TArray<float> &Times) const
{
	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("FHistoricalDebuggerDrawQueue::ExtractCommandTimes"))
	FScopeLock Lock(&CommandQueueCS);
	Times = CommandQueueTimesSeconds;
}

void FHistoricalDebuggerDrawQueue::RemoveOldElements(float WorldTimeSeconds, float DebugHistoryWindowSeconds)
{
	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("FHistoricalDebuggerDrawQueue::RemoveOldElements"))
	const int LowerBound = Algo::LowerBoundBy(CommandQueue, WorldTimeSeconds - DebugHistoryWindowSeconds, [](const FHistoricalDebuggerDrawCommand& Command) { return Command.WorldTimeSeconds; });
	if (LowerBound < CommandQueue.Num())
		CommandQueue.RemoveAt(0, LowerBound, EAllowShrinking::No);
	// const int TimesLowerBound = CommandQueueTimesSeconds.FindByPredicate([WorldTimeSeconds, DebugHistoryWindowSeconds](float Time) { return Time >= WorldTimeSeconds - DebugHistoryWindowSeconds; }) - CommandQueueTimesSeconds.GetData();
	// const int TimesLowerBound = Algo::LowerBound(CommandQueueTimesSeconds, WorldTimeSeconds - DebugHistoryWindowSeconds);
	// if (LowerBound < CommandQueueTimesSeconds.Num())
	//	CommandQueueTimesSeconds.RemoveAt(0, TimesLowerBound);
}

void FHistoricalDebuggerDrawQueue::DrawNull(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration)
{
	FScopeLock Lock(&CommandQueueCS);
	CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawNull(DebugContext, WorldTimeSeconds, Iteration));
	AddTimeToCommandQueueTimes(WorldTimeSeconds);
}

void FHistoricalDebuggerDrawQueue::DrawDebugPoint(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Position, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FScopeLock Lock(&CommandQueueCS);
	if (AcceptCommand(Position))
	{
		CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawPoint(DebugContext, WorldTimeSeconds, Iteration, Position, Color, bPersistentLines, Lifetime, DepthPriority, Thickness));
		AddTimeToCommandQueueTimes(WorldTimeSeconds);
	}
}

void FHistoricalDebuggerDrawQueue::DrawDebugLine(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& LineStart, const FVector& LineEnd, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FScopeLock Lock(&CommandQueueCS);
	if (AcceptCommand(LineStart))
	{
		CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawLine(DebugContext, WorldTimeSeconds, Iteration, LineStart, LineEnd, Color, bPersistentLines, Lifetime, DepthPriority, Thickness));
		AddTimeToCommandQueueTimes(WorldTimeSeconds);
	}
}

void FHistoricalDebuggerDrawQueue::DrawDebugDirectionalArrow(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& LineStart, const FVector& LineEnd, float ArrowSize, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FScopeLock Lock(&CommandQueueCS);
	if (AcceptCommand(LineStart))
	{
		CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawDirectionalArrow(DebugContext, WorldTimeSeconds, Iteration, LineStart, LineEnd, ArrowSize, Color, bPersistentLines, Lifetime, DepthPriority, Thickness));
		AddTimeToCommandQueueTimes(WorldTimeSeconds);
	}
}

void FHistoricalDebuggerDrawQueue::DrawDebugCoordinateSystem(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Position, const FRotator& AxisRot, FVector::FReal Scale, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FScopeLock Lock(&CommandQueueCS);

	FRotationMatrix R(AxisRot);
	const FVector X = R.GetScaledAxis(EAxis::X);
	const FVector Y = R.GetScaledAxis(EAxis::Y);
	const FVector Z = R.GetScaledAxis(EAxis::Z);

	if (AcceptCommand(Position))
	{
		CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawLine(DebugContext, WorldTimeSeconds, Iteration, Position, Position + X * Scale, FColor::Red, bPersistentLines, Lifetime, DepthPriority, Thickness));
		CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawLine(DebugContext, WorldTimeSeconds, Iteration, Position, Position + Y * Scale, FColor::Green, bPersistentLines, Lifetime, DepthPriority, Thickness));
		CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawLine(DebugContext, WorldTimeSeconds, Iteration, Position, Position + Z * Scale, FColor::Blue, bPersistentLines, Lifetime, DepthPriority, Thickness));
		AddTimeToCommandQueueTimes(WorldTimeSeconds);
	}
}


void FHistoricalDebuggerDrawQueue::DrawDebugSphere(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, FVector::FReal Radius, int32 Segments, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FScopeLock Lock(&CommandQueueCS);
	if (AcceptCommand(Center))
	{
		CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawDebugSphere(DebugContext, WorldTimeSeconds, Iteration, Center, Radius, Segments, Color, bPersistentLines, Lifetime, DepthPriority, Thickness));
		AddTimeToCommandQueueTimes(WorldTimeSeconds);
	}
}

void FHistoricalDebuggerDrawQueue::DrawDebugBox(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, const FVector& Extent, const FQuat& Rotation, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FScopeLock Lock(&CommandQueueCS);
	if (AcceptCommand(Center))
	{
		CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawDebugBox(DebugContext, WorldTimeSeconds, Iteration, Center, Extent, Rotation, Color, bPersistentLines, Lifetime, DepthPriority, Thickness));
		AddTimeToCommandQueueTimes(WorldTimeSeconds);
	}
}

void FHistoricalDebuggerDrawQueue::DrawDebugString(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& TextLocation, const FString& Text, AActor* TestBaseActor, const FColor& Color, float Lifetime, bool bDrawShadow, float FontScale)
{
	FScopeLock Lock(&CommandQueueCS);
	if (AcceptCommand(TextLocation))
	{
		CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawDebugString(DebugContext, WorldTimeSeconds, Iteration, TextLocation, Text, TestBaseActor, Color, Lifetime, bDrawShadow, FontScale));
		AddTimeToCommandQueueTimes(WorldTimeSeconds);
	}
}

void FHistoricalDebuggerDrawQueue::DrawDebugCircle(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, FVector::FReal Radius, int32 Segments, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness, const FVector& YAxis, const FVector& ZAxis, bool bDrawAxis)
{
	FScopeLock Lock(&CommandQueueCS);
	if (AcceptCommand(Center))
	{
		CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawDebugCircle(DebugContext, WorldTimeSeconds, Iteration, Center, Radius, Segments, Color, bPersistentLines, Lifetime, DepthPriority, Thickness, YAxis, ZAxis, bDrawAxis));
		AddTimeToCommandQueueTimes(WorldTimeSeconds);
	}
}

void FHistoricalDebuggerDrawQueue::DrawDebugCapsule(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Center, FVector::FReal HalfHeight, FVector::FReal Radius, const FQuat& Rotation, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FScopeLock Lock(&CommandQueueCS);
	if (AcceptCommand(Center))
	{
		CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawDebugCapsule(DebugContext, WorldTimeSeconds, Iteration, Center, HalfHeight, Radius, Rotation, Color, bPersistentLines, Lifetime, DepthPriority, Thickness));
		AddTimeToCommandQueueTimes(WorldTimeSeconds);
	}
}

void FHistoricalDebuggerDrawQueue::DrawDebugCylinder(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Start, const FVector& End, float Radius, int32 Segments, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FScopeLock Lock(&CommandQueueCS);
	if (AcceptCommand(Start))
	{
		CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawDebugCylinder(DebugContext, WorldTimeSeconds, Iteration, Start, End, Radius, Segments, Color, bPersistentLines, Lifetime, DepthPriority, Thickness));
		AddTimeToCommandQueueTimes(WorldTimeSeconds);
	}
}

void FHistoricalDebuggerDrawQueue::DrawDebugCone(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const FVector& Origin, const FVector& Direction, float Length, float AngleWidth, float AngleHeight, int32 NumSides, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	FScopeLock Lock(&CommandQueueCS);
	if (AcceptCommand(Origin))
	{
		CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawDebugCone(DebugContext, WorldTimeSeconds, Iteration, Origin, Direction, Length, AngleWidth, AngleHeight, NumSides, Color, bPersistentLines, Lifetime, DepthPriority, Thickness));
		AddTimeToCommandQueueTimes(WorldTimeSeconds);
	}
}

void FHistoricalDebuggerDrawQueue::DrawDebugMesh(const FHistoricalDebuggerDebugContext& DebugContext, float WorldTimeSeconds, int Iteration, const TArray<FVector>& Vertices, const TArray<int32>& Indices, const FColor& Color, bool bPersistentLines, float Lifetime, uint8 DepthPriority, float Thickness)
{
	if (Vertices.IsEmpty())
		return;
	FScopeLock Lock(&CommandQueueCS);
	if (AcceptCommand(Vertices[0]))
	{
		CommandQueue.Emplace(FHistoricalDebuggerDrawCommand::DrawDebugMesh(DebugContext, WorldTimeSeconds, Iteration, Vertices, Indices, Color, bPersistentLines, Lifetime, DepthPriority, Thickness));
		AddTimeToCommandQueueTimes(WorldTimeSeconds);
	}
}

void FHistoricalDebuggerDrawQueue::SetRegionOfInterest(const FVector& Pos, float InRadius)
{
	FScopeLock Lock(&CommandQueueCS);
	CenterOfInterest = Pos;
	RadiusOfInterest = InRadius;
}

const FVector& FHistoricalDebuggerDrawQueue::GetCenterOfInterest() const
{
	return CenterOfInterest;
}

FVector::FReal FHistoricalDebuggerDrawQueue::GetRadiusOfInterest() const
{
	return RadiusOfInterest;
}

bool FHistoricalDebuggerDrawQueue::IsInRegionOfInterest(const FVector& Position) const
{
	return (RadiusOfInterest <= 0.0f) || ((Position - CenterOfInterest).SizeSquared() < RadiusOfInterest * RadiusOfInterest);
}

bool FHistoricalDebuggerDrawQueue::IsInRegionOfInterest(const FVector& Position, const FVector::FReal Radius) const
{
	return (RadiusOfInterest <= 0.0f) || ((Position - CenterOfInterest).SizeSquared() < (RadiusOfInterest + Radius) * (RadiusOfInterest + Radius));
}

//bool FDebugDrawQueue::IsInRegionOfInterest(FAABB3 Bounds) const
//{
//	return Bounds.ThickenSymmetrically(FVector(RadiusOfInterest)).Contains(CenterOfInterest);
//}

bool FHistoricalDebuggerDrawQueue::AcceptCommand(const FVector& Position) const
{
	if (IsInRegionOfInterest(Position))
	{
		return true;
	}
	return false;
}

void FHistoricalDebuggerDrawQueue::AddTimeToCommandQueueTimes(float WorldTimeSeconds)
{
	if (CommandQueueTimesSeconds.IsEmpty() || CommandQueueTimesSeconds.Last() != WorldTimeSeconds)
		CommandQueueTimesSeconds.Add(WorldTimeSeconds);
}

