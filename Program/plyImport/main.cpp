#include <kvs/PointObject>
#include <kvs/PointRenderer>
#include <kvs/Screen>
#include <kvs/Application>

#include <kvs/ParticleBasedRenderer>

#include <fstream>

int main( int argc, char** argv )
{
  if( !(argc == 2 ) ) {
    std::cerr << "USAGE (1): ./plyImport ply_data" << std::endl;
    exit(1) ;
  }
  //--- FIle Open
  std::ifstream fin( argv[1] );
  if (!fin) {
    std::cout << "Cannnot Open file." << std::endl;
    exit(1) ;
  }
  const int BUF_SIZE = 512;
  char buf[BUF_SIZE];
  
  //--- Check to ply
  fin.getline( buf, BUF_SIZE, '\n' );
  if( strncmp( buf, "ply", 3 ) ) {
    std::cout << buf << std::endl;
    std::cout << "This file is NOT ply-format." << std::endl;
    exit(1);
  }
  //--- Read header
  char words[ 20 ][BUF_SIZE];
  char *w;
  size_t numToken;
  size_t numVert;
  while( fin.getline( buf, BUF_SIZE, '\n' ) ) {
    numToken = 0;
    w = buf;
    //--- Devide Token
    while( (w=strtok(w, " \t") ) !=NULL ) {
      strcpy( words[numToken], w );
      numToken++;
      w = NULL;
    }
    //--- Number of vertex
    if( !strncmp( words[0], "element", 7 ) &&
        !strncmp( words[1], "vertex", 6 ) )  {
      errno = 0;
      char *endp;
      numVert = std::strtol( words[2], &endp, 10);
      if (errno != 0 ) {
        std::cout << words[2] << std::endl;
        std::cerr << "strtol error: over flow" << std::endl;
        exit(1);
      }
      std::cout << "Number of vertices: " << numVert << std::endl;
    }
    if( !strncmp( words[0], "end_header", 10 ) ) break;
  }
  //--- Read Data
  std::vector<kvs::Real32> coords;
  std::vector<kvs::Real32> normals;
  std::vector<kvs::UInt8>  colors;
  float p[3];
  float np[3];
  unsigned char c[4];
  for(size_t i=0; i<numVert; i++ ) {
    //---- Vertex
    fin.read( (char*) p, sizeof(float)*3 );
    coords.push_back( p[0] );
    coords.push_back( p[1] );
    coords.push_back( p[2] );

    //---- Normal
    fin.read( (char*)np, sizeof(float)*3 );
    normals.push_back( np[0] );
    normals.push_back( np[1] );
    normals.push_back( np[2] );

    //---- Color
    fin.read( (char*)c, sizeof(unsigned char)*3 );
    colors.push_back( c[0] );
    colors.push_back( c[1] );
    colors.push_back( c[2] );
  }

  //---- Generate instance at PointObject
  kvs::PointObject *point = new kvs::PointObject();
  point->setCoords( kvs::ValueArray<kvs::Real32>( coords ));
  point->setNormals( kvs::ValueArray<kvs::Real32>(normals ) );
  point->setColors( kvs::ValueArray<kvs::UInt8>( colors ) );
  point->updateMinMaxCoords();

  //--- Standard output about Pointbject
  point->print( std::cout );

  //  kvs::glsl::PointRenderer *renderer = new kvs::glsl::PointRenderer();
  auto* renderer =
    new kvs::glsl::ParticleBasedRenderer();
  renderer->setRepetitionLevel ( 1 );
  renderer->disableZooming();
  
  kvs::Application app( argc, argv );
  kvs::Screen screen( &app );
  screen.setGeometry( 0, 0, 512, 512 );
  screen.setTitle( "Point Renderer");
  screen.registerObject( point, renderer );
  screen.show();
  
  return( app.run() );
    
}
