#pragma once

#include <iv_components.hpp>
#include <ivorium.hpp>
#include "Defs.hpp"

class MyGame : public iv::Game
{
public:
iv::Instance inst;
iv::ClientMarker cm;
	
	iv::SourceInputNode input_source;
	iv::FixedOrder_Camera camera;
	iv::Heap heap;
	
	iv::GameIdentity identity() const
	{
		iv::GameIdentity id;
		id.configuration_tag = "ivorium_default_project";
		return id;
	}
	
	iv::Instance * instance()
	{
		return &this->inst;
	}
	
	MyGame( iv::Window * window ) :
		iv::Game( window, this->identity() ),
		inst( this->system_container() ),
		cm( &this->inst, this, "MyGame" ),
		input_source( &this->inst ),
		camera( &this->inst, this->geometry() ),
		heap( &this->inst, &this->cm )
	{
		this->cm.owns( this->camera.cm );
		this->inst.instance_finalize( "MyGame", &this->cm );
		
		//--------------- setup ------------------------------------------
		this->input_source.Add_InputNode( &this->camera );
		
		// diagnostics
		auto * diagnostics = this->heap.createInstance< iv::SimpleDiagnostics >( "diagnostics" );
		this->input_source.Add_InputNode( diagnostics );
		
		// style
		//iv::DefaultLumaStyles( this->instance() ).Green( Defs::Style::Primary );
		//iv::DefaultLumaStyles( this->instance() ).Dark( Defs::Style::Primary, Defs::Style::Secondary );
		iv::DefaultLumaStyles( this->instance() ).Light( Defs::Style::Primary, Defs::Style::Secondary );
		iv::LumaStyler( this->instance() ).current_style( Defs::Style::Primary );
				
		//--------------- view -----------------------------------------------------
		/*
		// background
		this->camera.createChild< iv::Image >()
			->filename( "/ivorium_graphics/generic/white.png" )
			->colorTransform( iv::ColorTransform::Scale( iv::float3( 0.184f, 0.184f, 0.184f ) ) );
		
		// example button
		auto attrib = this->heap.create< iv::Lambda_ActivationAttribute >(
			[]()
			{
				iv::TextOutput << "MyGame.hpp: Button activated." << std::endl;
			}
		);
		
		auto button = this->camera.createChild< iv::Border >()
			->createChild< iv::Rectangle_LumaButton >( iv::ResourcePath( "/ivorium_UI/icons/ok.png" ), "HELLO" );
		
		button->input.field_release.Assign_Attribute_RW( attrib );
		
		// splash overlay 
		this->camera.createChild< iv::SimpleSplash >();
		*/
		
		this->camera.createChild< iv::Image >()
			->filename( "/spectrum.png" )
			->colorTransform( iv::ColorTransform::Change( iv::float4( 1, 0, 0, 1 ), iv::float4( 0, 0, 1, 1 ) ) );
	}
	
	virtual bool game_input( iv::Input const * input ) override
	{
		return this->input_source.input( input );
	}
	
	virtual void game_geometryChanged( iv::RenderTarget::Geometry geometry ) override
	{
		this->camera.geometry( geometry );
	}
	
	virtual void game_draw() override
	{
		this->camera.render_scene();
	}
	
	virtual void game_focusLost() override
	{
	}
};
