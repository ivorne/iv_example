#include <ivorium.hpp>
#include "MyGame.hpp"

//========================================================================
#if IV_GLPLATFORM_GLFW

int main( int argc, char ** argv )
{
	iv::ivorium_init();
    {
        iv::GlfwWindow window( "Example application" );
        MyGame game( &window );
        window.loop();
    }
    iv::ivorium_destroy();
}

#elif IV_GLPLATFORM_GLFM

#include <glfm.h>
void glfmMain( GLFMDisplay * display )
{
	iv::ivorium_init();
	iv::GlfmWindow * window = new iv::GlfmWindow( display );
	auto game = new MyGame( window );
}

#else
#error "Unimplemented OpenGL platform."
#endif
