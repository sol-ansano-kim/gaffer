//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2014, Image Engine Design Inc. All rights reserved.
//
//  Redistribution and use in source and binary forms, with or without
//  modification, are permitted provided that the following conditions are
//  met:
//
//      * Redistributions of source code must retain the above
//        copyright notice, this list of conditions and the following
//        disclaimer.
//
//      * Redistributions in binary form must reproduce the above
//        copyright notice, this list of conditions and the following
//        disclaimer in the documentation and/or other materials provided with
//        the distribution.
//
//      * Neither the name of John Haddon nor the names of
//        any other contributors to this software may be used to endorse or
//        promote products derived from this software without specific prior
//        written permission.
//
//  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
//  IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
//  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
//  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
//  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
//  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
//  PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
//  LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
//  NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
//  SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//////////////////////////////////////////////////////////////////////////

#include "IECore/ExternalProcedural.h"

#include "Gaffer/StringPlug.h"

#include "GafferScene/ExternalProcedural.h"

using namespace Imath;
using namespace Gaffer;
using namespace GafferScene;

IE_CORE_DEFINERUNTIMETYPED( ExternalProcedural );

size_t ExternalProcedural::g_firstPlugIndex = 0;

ExternalProcedural::ExternalProcedural( const std::string &name )
	:	ObjectSource( name, "procedural" )
{
	storeIndexOfNextChild( g_firstPlugIndex );
	addChild( new StringPlug( "fileName" ) );
	addChild( new Box3fPlug( "bound", Plug::In, Box3f( V3f( -0.5 ), V3f( 0.5 ) ) ) );
	addChild( new CompoundDataPlug( "parameters" ) );
}

ExternalProcedural::~ExternalProcedural()
{
}

Gaffer::StringPlug *ExternalProcedural::fileNamePlug()
{
	return getChild<StringPlug>( g_firstPlugIndex );
}

const Gaffer::StringPlug *ExternalProcedural::fileNamePlug() const
{
	return getChild<StringPlug>( g_firstPlugIndex );
}

Gaffer::Box3fPlug *ExternalProcedural::boundPlug()
{
	return getChild<Box3fPlug>( g_firstPlugIndex + 1 );
}

const Gaffer::Box3fPlug *ExternalProcedural::boundPlug() const
{
	return getChild<Box3fPlug>( g_firstPlugIndex + 1 );
}

Gaffer::CompoundDataPlug *ExternalProcedural::parametersPlug()
{
	return getChild<CompoundDataPlug>( g_firstPlugIndex + 2 );
}

const Gaffer::CompoundDataPlug *ExternalProcedural::parametersPlug() const
{
	return getChild<CompoundDataPlug>( g_firstPlugIndex + 2 );
}

void ExternalProcedural::affects( const Gaffer::Plug *input, AffectedPlugsContainer &outputs ) const
{
	ObjectSource::affects( input, outputs );

	if(
		input == fileNamePlug() ||
		boundPlug()->isAncestorOf( input ) ||
		parametersPlug()->isAncestorOf( input )
	)
	{
		outputs.push_back( sourcePlug() );
	}
}

void ExternalProcedural::hashSource( const Gaffer::Context *context, IECore::MurmurHash &h ) const
{
	fileNamePlug()->hash( h );
	boundPlug()->hash( h );
	parametersPlug()->hash( h );
}

IECore::ConstObjectPtr ExternalProcedural::computeSource( const Context *context ) const
{
	IECore::ExternalProceduralPtr result = new IECore::ExternalProcedural( fileNamePlug()->getValue(), boundPlug()->getValue() );
	parametersPlug()->fillCompoundData( result->parameters()->writable() );
	return result;
}
