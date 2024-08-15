// Copyright Philip Dunstan


#include "HistoricalDebuggerSettingsDataAsset.h"

#include "imgui.h"

#include "Serialization/ObjectWriter.h"

UHistoricalDebuggerSettingsDataAsset::UHistoricalDebuggerSettingsDataAsset()
{
}

FString UHistoricalDebuggerSettingsDataAsset::GetDisplayName() const
{
	return TEXT("HistoricalDebuggerSettingsDataAsset");
}

bool UHistoricalDebuggerSettingsDataAsset::SaveDataAsset(const FString& SavePath)
{
    if (SavePath.IsEmpty())
    {
        return false;
    }

    // Get the Asset's Serialized Data
    TArray<uint8> ObjectData;
    FObjectWriter Writer(this, ObjectData);

    // Write Data to File
    FFileHelper::SaveArrayToFile(ObjectData, *SavePath);

    return true;
}


void UHistoricalDebuggerSettingsDataAsset::DrawImGui()
{
#if WITH_EDITOR
	static bool ImGuiWindow = false;
	if (ImGui::Begin(TCHAR_TO_UTF8(*GetClass()->GetName()), &ImGuiWindow, 0))
	{
		FString LastCategory;
		
		ImGui::PushItemWidth(ImGui::GetFontSize() * -20);
		for (TFieldIterator<FProperty> PropIt(GetClass()); PropIt; ++PropIt)
        {
            const FProperty* Property = *PropIt;
			const FString Category = Property->GetMetaData("Category");

			if (Category != LastCategory)
			{
				ImGui::Text(TCHAR_TO_UTF8(*Category));
				LastCategory = Category;
			}
			
			if (Property->IsA(FMapProperty::StaticClass()))
			{
				if (const FMapProperty* const MapProperty = CastField<FMapProperty>(Property))
				{
					// Get a pointer to the map
					void* MapPtr = MapProperty->ContainerPtrToValuePtr<void>(this);
            
					// Cast the pointer to TMap
					TMap<FName, bool>* MyMap = static_cast<TMap<FName, bool>*>(MapPtr);

					// Now you can iterate over the map
					for (auto& Elem : *MyMap)
					{
						ImGui::Checkbox(TCHAR_TO_UTF8(*Elem.Key.ToString()), &Elem.Value);
					}
				}
			}
			else
			{
				DrawPropertyImGui(*Property);
			}
        }

		if (ImGui::Button("Save DataAsset"))
		{
			SaveDataAsset(GetPathName());
		}
	}
	
	ImGui::End();
#endif
}

void UHistoricalDebuggerSettingsDataAsset::DrawPropertyImGui(const FProperty& Property)
{
	const FString PropertyName = Property.GetName();
	if (Property.IsA(FStrProperty::StaticClass()))
	{
		if (FString* PropertyValue = Property.ContainerPtrToValuePtr<FString>(this))
		{
			static char buffer[128];
			strncpy_s(buffer, TCHAR_TO_UTF8(**PropertyValue), FMath::Max(PropertyValue->Len(), 127));
			if (ImGui::InputText(TCHAR_TO_UTF8(*PropertyName), buffer, 64, ImGuiInputTextFlags_AutoSelectAll))
			{
				*PropertyValue = buffer;
			}
		}
	}
	else if (Property.IsA(FFloatProperty::StaticClass()))
	{
		if (float* PropertyValue = Property.ContainerPtrToValuePtr<float>(this))
		{
			ImGui::InputFloat(TCHAR_TO_UTF8(*PropertyName), PropertyValue, 1.0f, 100.0f, "%.4f", ImGuiInputTextFlags_AutoSelectAll);
		}
	}
	else if (Property.IsA(FIntProperty::StaticClass()))
	{
		if (int* PropertyValue = Property.ContainerPtrToValuePtr<int>(this))
		{
			ImGui::InputInt(TCHAR_TO_UTF8(*PropertyName), PropertyValue, 1, 100, ImGuiInputTextFlags_AutoSelectAll);
		}
	}
	else if (Property.IsA(FBoolProperty::StaticClass()))
	{
		if (bool* PropertyValue = Property.ContainerPtrToValuePtr<bool>(this))
		{
			ImGui::Checkbox(TCHAR_TO_UTF8(*PropertyName), PropertyValue);
		}
	}
}