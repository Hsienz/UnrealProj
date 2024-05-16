// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboSequence.h"

#include "Combo.h"


TSharedPtr<FCombo> FComboSequence::operator[](int32 Index)
{
	if( Index < 0 || Index > Combos.Num() ) return nullptr; 
	return MakeShared<FCombo>( Combos[Index] );
}
