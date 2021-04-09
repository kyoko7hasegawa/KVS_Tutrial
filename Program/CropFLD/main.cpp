//-----------------------------------------------------------------------
// Cropping Volume Data
//-----------------------------------------------------------------------

#include <iostream>
#include <cstdlib>
#include <kvs/AVSField>
#include <kvs/StructuredVolumeImporter>
#include <kvs/StructuredVolumeExporter>
#include <kvs/StructuredVolumeObject>

// Rendering
#include <kvs/RayCastingRenderer>
#include <kvs/glut/Application>
#include <kvs/glut/Screen>

#include "CropFLD.h"

int main( int argc, char** argv )
{
 if( !(argc == 3) ) {
   std::cerr << "USAGE: "<< argv[0] << " input.fld output.fld" ;
      std::cerr << std::endl;
    exit(1) ;
  }
 // Read an AVS FLD file
 kvs::AVSField* field = new kvs::AVSField(argv[1]);
 
 // Import Volume Data
 kvs::StructuredVolumeObject *volume = 
   new kvs::StructuredVolumeImporter( field );
 if ( volume->veclen() != 1 ) {
   std::cout << " Parameter veclen != 1 " << std::endl;
   delete volume;
   exit(1);
 }

 // Gropping Size
 const kvs::Vector3ui ncells( volume->resolution());
 kvs::Vector3ui grid_min, grid_max;
 // kvs::UInt64 i0, i1, i2;
 int i0, i1, i2;
 std::cout << "Grid Size : " << ncells.x() << ", " << ncells.y() << ", " << ncells.z() << std::endl;
 std::cout << "Input Minimun Cropping Position [xmin, ymin, zmin] :" ;
 std::cin  >> i0 >> i1 >> i2;
 if( i0 < 0 ) i0 = 0; if( i1 < 0 ) i1 = 0; if( i2 < 0 ) i2 = 0;
 grid_min.set(i0, i1, i2);

 std::cout << "Input Maximum Cropping Position [xmax, ymax, zmax] :" ;
 std::cin  >> i0 >> i1 >> i2;
 if( i0 > ncells.x() ) i0 = ncells.x(); 
 if( i1 > ncells.y() ) i1 = ncells.y(); 
 if( i2 > ncells.z() ) i2 = ncells.z();
 grid_max.set(i0, i1, i2);

  kvs::StructuredVolumeObject *volume2 = 
      new CropFLD(volume, grid_min, grid_max);
    
  //Export Volume Data 
  kvs::AVSField* field2 = 
    new kvs::StructuredVolumeExporter<kvs::AVSField>( volume2 );
 
  if( !field2 ) {
    kvsMessageError( "Cannot export Resized volume data." );
    delete volume2;
    return (false);
  } 
  if ( !field2->write( argv[2] ) ) {
    kvsMessageError( "Cannot write to the file as AVS field format." );
    delete volume2;
    return( false );
  }
  
  std::cout << "Output >> " << argv[2] << std::endl;


  kvs::RayCastingRenderer* renderer = new kvs::RayCastingRenderer();
  if ( !renderer ) {
    kvsMessageError( "Cannot create a ray casting renderer." );
    delete volume2;
    return( false );
  }
  
  kvs::glut::Application app( argc, argv );
  kvs::glut::Screen screen( &app );
  screen.registerObject( volume2 );
  screen.setGeometry( 0, 0, 512, 512 );
  screen.setTitle( "RayCastingRenderer" );
  screen.show();


  return( app.run() ); 
}
