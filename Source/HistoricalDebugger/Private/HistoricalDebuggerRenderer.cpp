// Copyright Philip Dunstan


#include "HistoricalDebuggerRenderer.h"

#include "HistoricalDebuggerDrawQueue.h"
#include "HistoricalDebuggerManager.h"
#include "GameFramework/HUD.h"


FHistoricalDebuggerRenderer::FHistoricalDebuggerRenderer()
{
}

FHistoricalDebuggerRenderer::~FHistoricalDebuggerRenderer()
{
}

void FHistoricalDebuggerRenderer::Draw(const UWorld* World, const TArray<FHistoricalDebuggerDrawCommand>& DrawCommands, const EHistoricalDebuggerDrawMode DrawMode, const FHistoricalDebuggerDebugFilter& DebugFilter, const bool bShowLabels) const
{
	TRACE_CPUPROFILER_EVENT_SCOPE(TEXT("FHistoricalDebuggerRenderer::Draw"))
	
	// Draw all the captured elements in the viewport
	if ((static_cast<int>(DrawMode) & static_cast<int>(EHistoricalDebuggerDrawMode::Viewport)) != 0)
	{
		for (const FHistoricalDebuggerDrawCommand& Command : DrawCommands)
		{
			constexpr bool bSeeThrough = false;
			constexpr uint8 DepthPriority = bSeeThrough ? Command.DepthPriority: 0;
			
			switch (Command.Type)
			{
			case FHistoricalDebuggerDrawCommand::EDrawType::None:
			{
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Point:
			{
				const FHistoricalDebuggerDrawCommand::FPointData& PointData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FPointData>();
				DrawDebugPoint(World, PointData.Position, Command.Thickness, Command.Color, Command.bPersistentLines, 0.0f, DepthPriority);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Line:
			{
				const FHistoricalDebuggerDrawCommand::FLineData& LineData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FLineData>();
				DrawDebugLine(World, LineData.LineStart, LineData.LineEnd, Command.Color, Command.bPersistentLines, 0.0f, DepthPriority, Command.Thickness);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::DirectionalArrow:
			{
				const FHistoricalDebuggerDrawCommand::FArrowData& ArrowData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FArrowData>();
				DrawDebugDirectionalArrow(World, ArrowData.LineStart, ArrowData.LineEnd, ArrowData.ArrowSize, Command.Color, Command.bPersistentLines, 0.0f, DepthPriority, Command.Thickness);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Sphere:
			{
				const FHistoricalDebuggerDrawCommand::FSphereData& SphereData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FSphereData>();
				DrawDebugSphere(World, SphereData.Center, SphereData.Radius, SphereData.Segments, Command.Color, Command.bPersistentLines, 0.0f, DepthPriority, Command.Thickness);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Box:
			{
				const FHistoricalDebuggerDrawCommand::FBoxData& BoxData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FBoxData>();
				DrawDebugBox(World, BoxData.Center, BoxData.Extent, BoxData.Rotation, Command.Color, Command.bPersistentLines, 0.0f, DepthPriority, Command.Thickness);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::String:
			{
				const FHistoricalDebuggerDrawCommand::FStringData& StringData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FStringData>();
				DrawDebugString(World, StringData.TextLocation, StringData.Text, StringData.TestBaseActor, Command.Color, 0.0f, StringData.bDrawShadow, StringData.FontScale);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Circle:
			{
				const FHistoricalDebuggerDrawCommand::FCircleData& CircleData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FCircleData>();
				FMatrix M = FRotationMatrix::MakeFromYZ(CircleData.YAxis, CircleData.ZAxis);
				M.SetOrigin(CircleData.Center);
				DrawDebugCircle(World, M, CircleData.Radius, CircleData.Segments, Command.Color, Command.bPersistentLines, 0.0f, DepthPriority, Command.Thickness, CircleData.bDrawAxis);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Capsule:
			{
				const FHistoricalDebuggerDrawCommand::FCapsuleData& CapsuleData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FCapsuleData>();
				DrawDebugCapsule(World, CapsuleData.Center, CapsuleData.HalfHeight, CapsuleData.Radius, CapsuleData.Rotation, Command.Color, Command.bPersistentLines, 0.0f, DepthPriority, Command.Thickness);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Cylinder:
			{
				const FHistoricalDebuggerDrawCommand::FCylinderData& CylinderData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FCylinderData>();
				DrawDebugCylinder(World, CylinderData.Start, CylinderData.End, CylinderData.Radius, CylinderData.Segments, Command.Color, Command.bPersistentLines, 0.0f, DepthPriority, Command.Thickness);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Cone:
			{
				const FHistoricalDebuggerDrawCommand::FConeData& ConeData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FConeData>();
				DrawDebugCone(World, ConeData.Origin, ConeData.Direction, ConeData.Length, ConeData.AngleWidth, ConeData.AngleHeight, ConeData.NumSides, Command.Color, Command.bPersistentLines, 0.0f, DepthPriority, Command.Thickness);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Mesh:
			{
				const FHistoricalDebuggerDrawCommand::FMeshData& MeshData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FMeshData>();
				DrawDebugMesh(World, MeshData.Vertices, MeshData.Indices, Command.Color, Command.bPersistentLines, 0.0f, DepthPriority);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::HUDString:
			{
				const FHistoricalDebuggerDrawCommand::FHUDStringData& StringData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FHUDStringData>();
				DrawDebugString(World, FVector(StringData.HUDTextLocation, 0.0f), StringData.Text, nullptr, Command.Color, 0.0f, StringData.bDrawShadow, StringData.FontScale);
				break;
			}
			default:
				break;
			}

			if (bShowLabels)
			{
				DrawDebugString(World, Command.Position, Command.DebugContext.Id, nullptr, Command.Color, 0.0f, false, 1.0f);
			}
		}
	}

	// Draw all the captured elements in the VisLog
	if ((static_cast<int>(DrawMode) & static_cast<int>(EHistoricalDebuggerDrawMode::VisLog)) != 0)
	{
		for (const FHistoricalDebuggerDrawCommand& Command : DrawCommands)
		{
			switch (Command.Type)
			{
			case FHistoricalDebuggerDrawCommand::EDrawType::None:
			{
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Point:
			{
				const FHistoricalDebuggerDrawCommand::FPointData& PointData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FPointData>();
				UE_VLOG_SEGMENT_THICK(Command.DebugContext.Actor, LogHistoricalDebugger, Log, PointData.Position, PointData.Position, Command.Color, Command.Thickness, TEXT_EMPTY);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Line:
			{
				const FHistoricalDebuggerDrawCommand::FLineData& LineData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FLineData>();
				UE_VLOG_SEGMENT(Command.DebugContext.Actor, LogHistoricalDebugger, Log, LineData.LineStart, LineData.LineEnd, Command.Color, TEXT_EMPTY);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::DirectionalArrow:
			{
				const FHistoricalDebuggerDrawCommand::FArrowData& ArrowData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FArrowData>();
				UE_VLOG_SEGMENT(Command.DebugContext.Actor, LogHistoricalDebugger, Log, ArrowData.LineStart, ArrowData.LineEnd, Command.Color, TEXT_EMPTY);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Sphere:
			{
				const FHistoricalDebuggerDrawCommand::FSphereData& SphereData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FSphereData>();
				UE_VLOG_SPHERE(Command.DebugContext.Actor, LogHistoricalDebugger, Log, SphereData.Center, SphereData.Radius, Command.Color, TEXT_EMPTY);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Box:
			{
				const FHistoricalDebuggerDrawCommand::FBoxData& BoxData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FBoxData>();
				UE_VLOG_OBOX(Command.DebugContext.Actor, LogHistoricalDebugger, Log, FBox(-BoxData.Extent, BoxData.Extent), FQuatRotationTranslationMatrix::Make(BoxData.Rotation, BoxData.Center), Command.Color, TEXT_EMPTY);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::String:
			{
				const FHistoricalDebuggerDrawCommand::FStringData& StringData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FStringData>();
				UE_VLOG(StringData.TestBaseActor, LogHistoricalDebugger, Log, TEXT("%s"), *StringData.Text);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Circle:
			{
				const FHistoricalDebuggerDrawCommand::FCircleData& CircleData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FCircleData>();
				const FMatrix M = FRotationMatrix::MakeFromYZ(CircleData.YAxis, CircleData.ZAxis);
				UE_VLOG_CIRCLE(Command.DebugContext.Actor, LogHistoricalDebugger, Log, CircleData.Center, M.GetUnitAxis(EAxis::X), CircleData.Radius, Command.Color, TEXT_EMPTY);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Capsule:
			{
				const FHistoricalDebuggerDrawCommand::FCapsuleData& CapsuleData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FCapsuleData>();
				// VLOG Capsule uses the bottom end as the origin (though the variable is named Center)
				FVector Base = CapsuleData.Center - CapsuleData.HalfHeight * (CapsuleData.Rotation * FVector::UpVector);
				UE_VLOG_CAPSULE(Command.DebugContext.Actor, LogHistoricalDebugger, Log, Base, CapsuleData.HalfHeight, CapsuleData.Radius, CapsuleData.Rotation, Command.Color, TEXT_EMPTY);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Cylinder:
			{
				const FHistoricalDebuggerDrawCommand::FCylinderData& CylinderData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FCylinderData>();
				UE_VLOG_CYLINDER(Command.DebugContext.Actor, LogHistoricalDebugger, Log, CylinderData.Start, CylinderData.End, CylinderData.Radius, Command.Color, TEXT_EMPTY);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Cone:
			{
				const FHistoricalDebuggerDrawCommand::FConeData& ConeData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FConeData>();
				// todo: what about Command.Cone.AngleHeight and Command.Cone.NumSides?
				UE_VLOG_CONE(Command.DebugContext.Actor, LogHistoricalDebugger, Log, ConeData.Origin, ConeData.Direction, ConeData.Length, ConeData.AngleWidth, Command.Color, TEXT_EMPTY);
				break;
			}
			case FHistoricalDebuggerDrawCommand::EDrawType::Mesh:
			{
				const FHistoricalDebuggerDrawCommand::FMeshData& MeshData = Command.Data.Get<FHistoricalDebuggerDrawCommand::FMeshData>();
				UE_VLOG_MESH(Command.DebugContext.Actor, LogHistoricalDebugger, Log, MeshData.Vertices, MeshData.Indices, Command.Color, TEXT_EMPTY);
				break;
			}
			default:
				break;
			}
		}
	}
}


float FHistoricalDebuggerRenderer::CommandLifetime(const FHistoricalDebuggerDrawCommand& Command, const bool bIsPaused) const
{
	// Linebatcher Lifetime < 0: eternal (regardless of bPersistent flag)
	// Linebatcher Lifetime = 0: default lifetime (which is usually 1 second)
	// Linebatcher Lifetime > 0: specified duration
	if (Command.Lifetime == 0)
	{
		return UE_SMALL_NUMBER;
	}
	return Command.Lifetime;
}

