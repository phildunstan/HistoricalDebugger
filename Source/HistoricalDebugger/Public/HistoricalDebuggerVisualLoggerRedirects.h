// Copyright Philip Dunstan

#pragma once

#include "HistoricalDebuggerDebugChannel.h"
#include "HistoricalDebuggerSubsystem.h"

#define ENABLE_HISTORICAL_DEBUGGER_VISUAL_LOGGER_REDIRECTS 1

#ifdef ENABLE_HISTORICAL_DEBUGGER_VISUAL_LOGGER_REDIRECTS

#define REDIRECT_TO_VLOG(Dest)
#define REDIRECT_OBJECT_TO_VLOG(Src, Dest)

#define CONNECT_WITH_VLOG(Dest)
#define CONNECT_OBJECT_WITH_VLOG(Src, Dest)

// Text, regular log
#define UE_VLOG(LogOwner, CategoryName, Verbosity, Format, ...)
// #define UE_VLOG(LogOwner, CategoryName, Verbosity, Format, ...)  if (FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) { DebugChannel->DrawLine({ TEXT("AI Sight Segment"), LogOwner }, SegmentStart, SegmentEnd, Color); }
// #define UE_VLOG(LogOwner, CategoryName, Verbosity, Format, ...) if (FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::CategorizedLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Format, ##__VA_ARGS__)
#define UE_CVLOG(Condition, LogOwner, CategoryName, Verbosity, Format, ...)  if (UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG(LogOwner, CategoryName, Verbosity, Format, ##__VA_ARGS__);} 
// Text, log with output to regular unreal logs too.  NOTE: UE_VLOG_UELOG will not UELOG if the Visual Logger is disabled (i.e. ENABLE_VISUAL_LOG is 0).  For the more common case where you want to always log, use UE_VLOG_ALWAYS_UELOG
#define UE_VLOG_UELOG(LogOwner, CategoryName, Verbosity, Format, ...) { UE_LOG(CategoryName, Verbosity, Format, ##__VA_ARGS__); }
// #define UE_VLOG_UELOG(LogOwner, CategoryName, Verbosity, Format, ...) { if (FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::CategorizedLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Format, ##__VA_ARGS__); UE_LOG(CategoryName, Verbosity, Format, ##__VA_ARGS__); }
#define UE_CVLOG_UELOG(Condition, LogOwner, CategoryName, Verbosity, Format, ...)  if(Condition) { UE_VLOG_UELOG(LogOwner, CategoryName, Verbosity, Format, ##__VA_ARGS__); } 
// Text, log with output to regular unreal logs too.  Regular log will always happen even if the Visual Logger is disabled by via compiler switch.  See also UE_CVLOG_ALWAYS_UELOG below
#define UE_VLOG_ALWAYS_UELOG(LogOwner, CategoryName, Verbosity, Format, ...) { UE_VLOG_UELOG(LogOwner, CategoryName, Verbosity, Format, ##__VA_ARGS__); }
// Segment shape
#define UE_VLOG_SEGMENT(LogOwner, CategoryName, Verbosity, SegmentStart, SegmentEnd, Color, Format, ...) if (FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) { DebugChannel->DrawLine({ TEXT("VLOG"), LogOwner }, SegmentStart, SegmentEnd, Color); }
#define UE_CVLOG_SEGMENT(Condition, LogOwner, CategoryName, Verbosity, SegmentStart, SegmentEnd, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_SEGMENT(LogOwner, CategoryName, Verbosity, SegmentStart, SegmentEnd, Color, Format, ##__VA_ARGS__);}
// Segment shape
#define UE_VLOG_SEGMENT_THICK(LogOwner, CategoryName, Verbosity, SegmentStart, SegmentEnd, Color, Thickness, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) { DebugChannel->DrawLine({ TEXT("VLOG"), LogOwner }, SegmentStart, SegmentEnd, Color); }
#define UE_CVLOG_SEGMENT_THICK(Condition, LogOwner, CategoryName, Verbosity, SegmentStart, SegmentEnd, Color, Thickness, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_SEGMENT_THICK(LogOwner, CategoryName, Verbosity, SegmentStart, SegmentEnd, Color, Thickness, Format, ##__VA_ARGS__);} 
// Localization as sphere shape
#define UE_VLOG_LOCATION(LogOwner, CategoryName, Verbosity, Location, Thickness, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) { DebugChannel->DrawSphere({ TEXT("VLOG"), LogOwner }, Location, Thickness, Color); }
#define UE_CVLOG_LOCATION(Condition, LogOwner, CategoryName, Verbosity, Location, Thickness, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_LOCATION(LogOwner, CategoryName, Verbosity, Location, Thickness, Color, Format, ##__VA_ARGS__);} 
// Sphere shape
#define UE_VLOG_SPHERE(LogOwner, CategoryName, Verbosity, Location, Radius, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) { DebugChannel->DrawSphere({ TEXT("VLOG"), LogOwner }, Location, Radius, Color); }
#define UE_CVLOG_SPHERE(Condition, LogOwner, CategoryName, Verbosity, Location, Radius, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_SPHERE(LogOwner, CategoryName, Verbosity, Location, Radius, Color, Format, ##__VA_ARGS__);} 
// Wire sphere shape
#define UE_VLOG_WIRESPHERE(LogOwner, CategoryName, Verbosity, Location, Radius, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)){ DebugChannel->DrawSphere({ TEXT("VLOG"), LogOwner }, Location, Radius, Color); } 
#define UE_CVLOG_WIRESPHERE(Condition, LogOwner, CategoryName, Verbosity, Location, Radius, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_WIRESPHERE(LogOwner, CategoryName, Verbosity, Location, Radius, Color, Format, ##__VA_ARGS__);} 
// Box shape
#define UE_VLOG_BOX(LogOwner, CategoryName, Verbosity, Box, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::BoxLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Box, FMatrix::Identity, Color, /*bWireframe = */false, Format, ##__VA_ARGS__)
#define UE_CVLOG_BOX(Condition, LogOwner, CategoryName, Verbosity, Box, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_BOX(LogOwner, CategoryName, Verbosity, Box, Color, Format, ##__VA_ARGS__);} 
// Wire box shape
#define UE_VLOG_WIREBOX(LogOwner, CategoryName, Verbosity, Box, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::BoxLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Box, FMatrix::Identity, Color, /*bWireframe = */true, Format, ##__VA_ARGS__)
#define UE_CVLOG_WIREBOX(Condition, LogOwner, CategoryName, Verbosity, Box, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_BOX(LogOwner, CategoryName, Verbosity, Box, Color, Format, ##__VA_ARGS__);} 
// Oriented box shape
#define UE_VLOG_OBOX(LogOwner, CategoryName, Verbosity, Box, Matrix, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::BoxLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Box, Matrix, Color, /*bWireframe = */false, Format, ##__VA_ARGS__)
#define UE_CVLOG_OBOX(Condition, LogOwner, CategoryName, Verbosity, Box, Matrix, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_OBOX(LogOwner, CategoryName, Verbosity, Box, Matrix, Color, Format, ##__VA_ARGS__);} 
// Wire oriented box shape
#define UE_VLOG_WIREOBOX(LogOwner, CategoryName, Verbosity, Box, Matrix, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::BoxLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Box, Matrix, Color, /*bWireframe = */true, Format, ##__VA_ARGS__)
#define UE_CVLOG_WIREOBOX(Condition, LogOwner, CategoryName, Verbosity, Box, Matrix, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_OBOX(LogOwner, CategoryName, Verbosity, Box, Matrix, Color, Format, ##__VA_ARGS__);} 
// Cone shape
#define UE_VLOG_CONE(LogOwner, CategoryName, Verbosity, Origin, Direction, Length, Angle, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::ConeLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Origin, Direction, Length, Angle, Color, /*bWireframe = */false, Format, ##__VA_ARGS__)
#define UE_CVLOG_CONE(Condition, LogOwner, CategoryName, Verbosity, Origin, Direction, Length, Angle, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_CONE(LogOwner, CategoryName, Verbosity, Origin, Direction, Length, Angle, Color, Format, ##__VA_ARGS__);} 
// Wire cone shape
#define UE_VLOG_WIRECONE(LogOwner, CategoryName, Verbosity, Origin, Direction, Length, Angle, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::ConeLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Origin, Direction, Length, Angle, Color, /*bWireframe = */true, Format, ##__VA_ARGS__)
#define UE_CVLOG_WIRECONE(Condition, LogOwner, CategoryName, Verbosity, Origin, Direction, Length, Angle, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_CONE(LogOwner, CategoryName, Verbosity, Origin, Direction, Length, Angle, Color, Format, ##__VA_ARGS__);} 
// Cylinder shape
#define UE_VLOG_CYLINDER(LogOwner, CategoryName, Verbosity, Start, End, Radius, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::CylinderLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Start, End, Radius, Color, /*bWireframe = */false, Format, ##__VA_ARGS__)
#define UE_CVLOG_CYLINDER(Condition, LogOwner, CategoryName, Verbosity, Start, End, Radius, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_CYLINDER(LogOwner, CategoryName, Verbosity, Start, End, Radius, Color, Format, ##__VA_ARGS__);} 
// Wire cylinder shape
#define UE_VLOG_WIRECYLINDER(LogOwner, CategoryName, Verbosity, Start, End, Radius, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::CylinderLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Start, End, Radius, Color, /*bWireframe = */true, Format, ##__VA_ARGS__)
#define UE_CVLOG_WIRECYLINDER(Condition, LogOwner, CategoryName, Verbosity, Start, End, Radius, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_CYLINDER(LogOwner, CategoryName, Verbosity, Start, End, Radius, Color, Format, ##__VA_ARGS__);} 
// Capsule shape
#define UE_VLOG_CAPSULE(LogOwner, CategoryName, Verbosity, Base, HalfHeight, Radius, Rotation, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::CapsuleLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Base, HalfHeight, Radius, Rotation, Color, /*bWireframe = */false, Format, ##__VA_ARGS__)
#define UE_CVLOG_CAPSULE(Condition, LogOwner, CategoryName, Verbosity, Base, HalfHeight, Radius, Rotation, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_CAPSULE(LogOwner, CategoryName, Verbosity, Base, HalfHeight, Radius, Rotation, Color, Format, ##__VA_ARGS__);} 
// Wire capsule shape
#define UE_VLOG_WIRECAPSULE(LogOwner, CategoryName, Verbosity, Base, HalfHeight, Radius, Rotation, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::CapsuleLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Base, HalfHeight, Radius, Rotation, Color, /*bWireframe = */true, Format, ##__VA_ARGS__)
#define UE_CVLOG_WIRECAPSULE(Condition, LogOwner, CategoryName, Verbosity, Base, HalfHeight, Radius, Rotation, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_CAPSULE(LogOwner, CategoryName, Verbosity, Base, HalfHeight, Radius, Rotation, Color, Format, ##__VA_ARGS__);} 
// Histogram data for 2d graphs 
#define UE_VLOG_HISTOGRAM(LogOwner, CategoryName, Verbosity, GraphName, DataName, Data) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::HistogramDataLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, GraphName, DataName, Data, FColor::White, TEXT(""))
#define UE_CVLOG_HISTOGRAM(Condition, LogOwner, CategoryName, Verbosity, GraphName, DataName, Data) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_HISTOGRAM(LogOwner, CategoryName, Verbosity, GraphName, DataName, Data);} 
// NavArea or vertically pulled convex shape
#define UE_VLOG_PULLEDCONVEX(LogOwner, CategoryName, Verbosity, ConvexPoints, MinZ, MaxZ, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::PulledConvexLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, ConvexPoints, MinZ, MaxZ, Color, Format, ##__VA_ARGS__)
#define UE_CVLOG_PULLEDCONVEX(Condition, LogOwner, CategoryName, Verbosity, ConvexPoints, MinZ, MaxZ, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_PULLEDCONVEX(LogOwner, CategoryName, Verbosity, ConvexPoints, MinZ, MaxZ, Color, Format, ##__VA_ARGS__);}
// regular 3d mesh shape to log
#define UE_VLOG_MESH(LogOwner, CategoryName, Verbosity, Vertices, Indices, Color, Format, ...) if (FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::MeshLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Vertices, Indices, Color, Format, ##__VA_ARGS__)
#define UE_CVLOG_MESH(Condition, LogOwner, CategoryName, Verbosity, Vertices, Indices, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_MESH(LogOwner, CategoryName, Verbosity, Vertices, Indices, Color, Format, ##__VA_ARGS__);}
// 2d convex poly shape
#define UE_VLOG_CONVEXPOLY(LogOwner, CategoryName, Verbosity, Points, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::ConvexLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Points, Color, Format, ##__VA_ARGS__)
#define UE_CVLOG_CONVEXPOLY(Condition, LogOwner, CategoryName, Verbosity, Points, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_CONVEXPOLY(LogOwner, CategoryName, Verbosity, Points, Color, Format, ##__VA_ARGS__);}
// Segment with an arrowhead
#define UE_VLOG_ARROW(LogOwner, CategoryName, Verbosity, SegmentStart, SegmentEnd, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::ArrowLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, SegmentStart, SegmentEnd, Color, Format, ##__VA_ARGS__)
#define UE_CVLOG_ARROW(Condition, LogOwner, CategoryName, Verbosity, SegmentStart, SegmentEnd, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_ARROW(LogOwner, CategoryName, Verbosity, SegmentStart, SegmentEnd, Color, Format, ##__VA_ARGS__);} 
// Circle shape
#define UE_VLOG_CIRCLE(LogOwner, CategoryName, Verbosity, Center, UpAxis, Radius, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::CircleLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Center, UpAxis, Radius, Color, 0, Format, ##__VA_ARGS__)
#define UE_CVLOG_CIRCLE(Condition, LogOwner, CategoryName, Verbosity, Center, UpAxis, Radius, Color, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_CIRCLE(LogOwner, CategoryName, Verbosity, Center, UpAxis, Radius, Color, 0, Format, ##__VA_ARGS__);} 
// Circle shape
#define UE_VLOG_CIRCLE_THICK(LogOwner, CategoryName, Verbosity, Center, UpAxis, Radius, Color, Thickness, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::CircleLogf(LogOwner, CategoryName, ELogVerbosity::Verbosity, Center, UpAxis, Radius, Color, Thickness, Format, ##__VA_ARGS__)
#define UE_CVLOG_CIRCLE_THICK(Condition, LogOwner, CategoryName, Verbosity, Center, UpAxis, Radius, Color, Thickness, Format, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_CIRCLE(LogOwner, CategoryName, Verbosity, Center, UpAxis, Radius, Color, Thickness, Format, ##__VA_ARGS__);} 

#define DECLARE_VLOG_EVENT(EventName) extern FVisualLogEventBase EventName;
#define DEFINE_VLOG_EVENT(EventName, Verbosity, UserFriendlyDesc) FVisualLogEventBase EventName(TEXT(#EventName), TEXT(UserFriendlyDesc), ELogVerbosity::Verbosity); 

#define UE_VLOG_EVENTS(LogOwner, TagNameToLog, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::EventLog(LogOwner, TagNameToLog, ##__VA_ARGS__)
#define UE_CVLOG_EVENTS(Condition, LogOwner, TagNameToLog, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_EVENTS(LogOwner, TagNameToLog, ##__VA_ARGS__);}
#define UE_VLOG_EVENT_WITH_DATA(LogOwner, LogEvent, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName)) FVisualLogger::EventLog(LogOwner, LogEvent, ##__VA_ARGS__)
#define UE_CVLOG_EVENT_WITH_DATA(Condition, LogOwner, LogEvent, ...) if(FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) && Condition) {UE_VLOG_EVENT_WITH_DATA(LogOwner, LogEvent, ##__VA_ARGS__);}

#define UE_IFVLOG(__code_block__) if( FHistoricalDebuggerDebugChannel* DebugChannel = UHistoricalDebuggerSubsystem::GetDebugChannel(GetWorld(), CategoryName) ) { __code_block__; }

#endif // ENABLE_HISTORICAL_DEBUGGER_VISUAL_LOGGER_REDIRECTS
