#include <kvs/MersenneTwister> 
#include <kvs/PointObject>
#include <kvs/ParticleBasedRenderer>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>

#include <cstdlib>

int main( int argc, char** argv )
{
  //--- Fixed parameter
  const double ALPHA = 0.2;
  const int REPEAT_LEVEL = 50;
  const int IMAGE_RESOLUTION = 512;

  const unsigned char  POINT_COLOR[3] = { 0, 255, 255 }; 
  const double RAD = 1.0;

  //---- Calculate pixcel Width
  double diameter = 2.0*RAD;
  double pixel_width = diameter/(double)IMAGE_RESOLUTION;
  std::cout << "pixel width:" << pixel_width << std::endl;

  double pixel_area = pixel_width*pixel_width;
  double area = 4.0*M_PI*RAD*RAD;

  //---- Calculate number of vertices
  double nall = ( log(1.0 - ALPHA) / log(1.0 - pixel_area/area) * (double)REPEAT_LEVEL ); 
  size_t numVert = (size_t)nall;

  std::cout << "Number of Vertecies : " << numVert << ", " <<  std::endl;
  std::vector <kvs::Real32> coords;
  std::vector <kvs::Real32> normals;
  std::vector <kvs::UInt8>  colors;

  kvs::MersenneTwister uniRand;
  
  for( size_t i=0; i<numVert; i++ ) {
    //--- Generate a uniform point cloud on sphere
    double z = RAD*(-2.0 * uniRand() + 1.0);  // uniRand() => s
    double sinTheta = sqrt(1.0 - z * z);
    double phi = 2.0 * M_PI * uniRand();      // uniRand() => t
    double x = RAD*sinTheta * cos(phi);
    double y = RAD*sinTheta * sin(phi);

    coords.push_back( (float)x );
    coords.push_back( (float)y );
    coords.push_back( (float)z );

    kvs::Vector3f norm( (float)x, (float)y, (float)z );
    norm.normalize( );
    normals.push_back( norm.x() );
    normals.push_back( norm.y() );
    normals.push_back( norm.z() );

    colors.push_back( POINT_COLOR[0] );
    colors.push_back( POINT_COLOR[1] );
    colors.push_back( POINT_COLOR[2] );
      
  }

  // Generate PointObject
  kvs::PointObject *point = new kvs::PointObject();
  point->setCoords( kvs::ValueArray<kvs::Real32>( coords ));
  point->setNormals( kvs::ValueArray<kvs::Real32>(normals ) );
  point->setColors( kvs::ValueArray<kvs::UInt8>( colors ) );
  point->updateMinMaxCoords();

  point->print( std::cout );
  
  // auto* renderer =
  kvs::glsl::ParticleBasedRenderer* renderer =
    new kvs::glsl::ParticleBasedRenderer();
  renderer->setRepetitionLevel ( REPEAT_LEVEL );
  renderer->disableZooming();    // Particle zooming off

  kvs::glut::Application app( argc, argv );
  kvs::glut::Screen screen( &app );
  screen.setGeometry( 0, 0, IMAGE_RESOLUTION, IMAGE_RESOLUTION );
  
  screen.setBackgroundColor( kvs::RGBColor ( 0, 0, 0 ) );
  screen.setTitle( "SPBR" );
  screen.registerObject( point, renderer );
  screen.show();
 
  return( app.run() );

}
