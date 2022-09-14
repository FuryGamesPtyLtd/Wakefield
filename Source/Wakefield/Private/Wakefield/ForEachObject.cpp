// Copyright Fury Games Pty Ltd. All rights reserved.

#include "Wakefield/ForEachObject.h"

#include "UObject/GarbageCollection.h"
#include "UObject/Object.h"
#include "UObject/UObjectArray.h"
#include "UObject/UObjectBase.h"

void ForEachObject(const FObjectVisitor& ObjectVisitor)
{
	FGCScopeGuard Guard;
	for (FUObjectArray::TIterator Iterator(GUObjectArray);
		 Iterator != FUObjectArray::TIterator(FUObjectArray::TIterator::EndTag, Iterator);
		 ++Iterator)
	{
		FUObjectItem* ObjectItem = GUObjectArray.IndexToObject(Iterator.GetIndex());
		check(ObjectItem);
		UObjectBase* ObjectBase = ObjectItem->Object;
		check(ObjectBase);
		static_assert(sizeof(UObject) == sizeof(UObjectBase));
		UObject* Object = static_cast<UObject*>(ObjectBase);
		check(IsValid(Object));
		ObjectVisitor(Object);
	}
}
