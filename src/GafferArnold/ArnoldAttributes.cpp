//////////////////////////////////////////////////////////////////////////
//
//  Copyright (c) 2012, John Haddon. All rights reserved.
//  Copyright (c) 2013, Image Engine Design Inc. All rights reserved.
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

#include "Gaffer/StringPlug.h"

#include "GafferArnold/ArnoldAttributes.h"

using namespace Imath;
using namespace Gaffer;
using namespace GafferArnold;

IE_CORE_DEFINERUNTIMETYPED( ArnoldAttributes );

ArnoldAttributes::ArnoldAttributes( const std::string &name )
	:	GafferScene::Attributes( name )
{
	Gaffer::CompoundDataPlug *attributes = attributesPlug();

	// Visibility parameters

	attributes->addOptionalMember( "ai:visibility:camera", new IECore::BoolData( true ), "cameraVisibility", Gaffer::Plug::Default, false );
	attributes->addOptionalMember( "ai:visibility:shadow", new IECore::BoolData( true ), "shadowVisibility", Gaffer::Plug::Default, false );
	attributes->addOptionalMember( "ai:visibility:reflected", new IECore::BoolData( true ), "reflectedVisibility", Gaffer::Plug::Default, false );
	attributes->addOptionalMember( "ai:visibility:refracted", new IECore::BoolData( true ), "refractedVisibility", Gaffer::Plug::Default, false );
	attributes->addOptionalMember( "ai:visibility:diffuse", new IECore::BoolData( true ), "diffuseVisibility", Gaffer::Plug::Default, false );
	attributes->addOptionalMember( "ai:visibility:glossy", new IECore::BoolData( true ), "glossyVisibility", Gaffer::Plug::Default, false );

	// Shading parameters

	attributes->addOptionalMember( "ai:matte", new IECore::BoolData( false ), "matte", Gaffer::Plug::Default, false );
	attributes->addOptionalMember( "ai:opaque", new IECore::BoolData( true ), "opaque", Gaffer::Plug::Default, false );
	attributes->addOptionalMember( "ai:receive_shadows", new IECore::BoolData( true ), "receiveShadows", Gaffer::Plug::Default, false );
	attributes->addOptionalMember( "ai:self_shadows", new IECore::BoolData( true ), "selfShadows", Gaffer::Plug::Default, false );

	// Subdivision parameters

	attributes->addOptionalMember( "ai:polymesh:subdiv_type", new StringPlug( "value", Plug::In, "none" ), "subdivType", false );
	attributes->addOptionalMember( "ai:polymesh:subdiv_iterations", new IntPlug( "value", Plug::In, 1, 1 ), "subdivIterations", false );
	attributes->addOptionalMember( "ai:polymesh:subdiv_adaptive_error", new FloatPlug( "value", Plug::In, 0.0f, 0.0f ), "subdivAdaptiveError", false );
	attributes->addOptionalMember( "ai:polymesh:subdiv_adaptive_metric", new StringPlug( "value", Plug::In, "auto" ), "subdivAdaptiveMetric", false );
	attributes->addOptionalMember( "ai:polymesh:subdiv_adaptive_space", new StringPlug( "value", Plug::In, "raster" ), "subdivAdaptiveSpace", false );
	attributes->addOptionalMember( "ai:polymesh:subdiv_uv_smoothing", new StringPlug( "value", Plug::In, "pin_corners" ), "subdivUVSmoothing", false );
	attributes->addOptionalMember( "ai:polymesh:smoothing", new IECore::BoolData( false ), "smoothing", Gaffer::Plug::Default, false );

	// Curves parameters

	attributes->addOptionalMember( "ai:curves:mode", new StringPlug( "value", Plug::In, "ribbon" ), "curvesMode", false );
	attributes->addOptionalMember( "ai:curves:min_pixel_width", new FloatPlug( "value", Plug::In, 0.0f, 0.0f ), "curvesMinPixelWidth", false );

	// Volume parameters

	attributes->addOptionalMember( "ai:shape:step_size", new FloatPlug( "value", Plug::In, 0.0f, 0.0f ), "volumeStepSize", false );

}

ArnoldAttributes::~ArnoldAttributes()
{
}
