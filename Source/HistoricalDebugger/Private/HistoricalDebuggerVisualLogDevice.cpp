#include "HistoricalDebuggerVisualLogDevice.h"

#include "HistoricalDebuggerDebugChannel.h"
#include "HistoricalDebuggerSubsystem.h"

#if ENABLE_VISUAL_LOG

FHistoricalDebuggerVisualLogDevice::~FHistoricalDebuggerVisualLogDevice()
{
}

void FHistoricalDebuggerVisualLogDevice::Serialize(const UObject* LogOwner, FName OwnerName, FName InOwnerClassName, const FVisualLogEntry& LogEntry)
{
	// for (const FVisualLogLine& Line : LogEntry.LogLines)
	for (const FVisualLogShapeElement& ShapeElement : LogEntry.ElementsToDraw)
	{
		if (FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(LogOwner->GetWorld(), ShapeElement.Category))
		{
			const FHistoricalDebuggerDebugContext DebugContext { ShapeElement.Category.ToString(), Cast<AActor>(LogOwner) };
			switch (ShapeElement.Type)
			{
			case EVisualLoggerShapeElement::Invalid:
				break;
			case EVisualLoggerShapeElement::SinglePoint:
				DebugChannel->DrawSphere(DebugContext, ShapeElement.Points[0], 4, 4, ShapeElement.GetFColor());
				break;
			case EVisualLoggerShapeElement::Sphere:
				DebugChannel->DrawSphere(DebugContext, ShapeElement.Points[0], ShapeElement.Radius, 8, ShapeElement.GetFColor());
				break;
			case EVisualLoggerShapeElement::WireSphere:
				break;
			case EVisualLoggerShapeElement::Segment:
				DebugChannel->DrawLine(DebugContext, ShapeElement.Points[0], ShapeElement.Points[1], ShapeElement.GetFColor());
				break;
			case EVisualLoggerShapeElement::Path:
				break;
			case EVisualLoggerShapeElement::Box:
				DebugChannel->DrawSolidBox(DebugContext, FBox { ShapeElement.Points[0], ShapeElement.Points[1] }, ShapeElement.GetFColor(), FTransform(ShapeElement.TransformationMatrix));
				break;
			case EVisualLoggerShapeElement::WireBox:
				DebugChannel->DrawBox(DebugContext, 0.5f * (ShapeElement.Points[0] + ShapeElement.Points[1]), (ShapeElement.Points[1] - ShapeElement.Points[0]), ShapeElement.GetFColor());
				break;
			case EVisualLoggerShapeElement::Cone:
				break;
			case EVisualLoggerShapeElement::WireCone:
				break;
			case EVisualLoggerShapeElement::Cylinder:
				break;
			case EVisualLoggerShapeElement::WireCylinder:
				break;
			case EVisualLoggerShapeElement::Capsule:
				break;
			case EVisualLoggerShapeElement::WireCapsule:
				break;
			case EVisualLoggerShapeElement::Polygon:
				break;
			case EVisualLoggerShapeElement::Mesh:
				break;
			case EVisualLoggerShapeElement::NavAreaMesh:
				break;
			case EVisualLoggerShapeElement::Arrow:
				DebugChannel->DrawDirectionalArrow(DebugContext, ShapeElement.Points[0], ShapeElement.Points[1], 10.0f, ShapeElement.GetFColor());
				break;
			case EVisualLoggerShapeElement::Circle:
				DebugChannel->DrawCircle(DebugContext, ShapeElement.Points[0], ShapeElement.Points[2].X, 8, ShapeElement.GetFColor());
				break;
			}
		}
	}
}

void FHistoricalDebuggerVisualLogDevice::Cleanup(bool bReleaseMemory)
{
	if (GEngine)
	{
		for (const FWorldContext& WorldContext : GEngine->GetWorldContexts())
		{
			if (UWorld* World = WorldContext.World())
			{
				if (FHistoricalDebuggerManager* HistoricalDebuggerManager = UHistoricalDebuggerSubsystem::GetHistoricalDebuggerManager(World))
				{
					HistoricalDebuggerManager->Reset();
				}
			}
		}
	}
}

void FHistoricalDebuggerVisualLogDevice::StartRecordingToFile(double TimeStamp)
{
}

void FHistoricalDebuggerVisualLogDevice::StopRecordingToFile(double TimeStamp)
{
}

void FHistoricalDebuggerVisualLogDevice::DiscardRecordingToFile()
{
}

void FHistoricalDebuggerVisualLogDevice::SetFileName(const FString &InFileName)
{
}

void FHistoricalDebuggerVisualLogDevice::GetRecordedLogs(TArray<FVisualLogDevice::FVisualLogEntryItem> &OutLogs) const
{
}

bool FHistoricalDebuggerVisualLogDevice::HasFlags(int32 InFlags) const
{
	return false;
}

#endif
