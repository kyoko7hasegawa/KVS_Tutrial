#include <kvs/PolygonObject>
#include <kvs/Application>
#include <kvs/Screen>

int main( int argc, char** argv )
{
  // 頂点座標
  kvs::Real32 vertex[] = {
    -1.0, -1.0, -1.0,
    1.0, -1.0, -1.0,
    -1.0, 1.0, -1.0,
    1.0, 1.0, -1.0,
    -1.0, -1.0, 1.0,
    1.0, -1.0, 1.0,
    -1.0, 1.0, 1.0,
    1.0, 1.0, 1.0
  };
  // 頂点色
  kvs::UInt8 vertCol[] = {
      0,   0,   0,
    255,   0,   0,
    255, 255,   0,
    255,   0, 255,
      0, 255,   0,
      0, 255, 255,
      0,   0, 255,
    128, 128, 128
  };
  // 頂点法線
  kvs::Real32 norm[] = {
    -0.577, -0.577, -0.577,
    0.577, -0.577, -0.577,
    -0.577, 0.577, -0.577,
    0.577, 0.577, -0.577,
    -0.577, -0.577, 0.577,
    0.577, -0.577, 0.577,
    -0.577, 0.577, 0.577,
    0.577, 0.577, 0.577,
  };

  // 接続情報
  kvs::UInt32 tri[] = {
    2, 1, 0,
    1, 2, 3,
    4, 2, 0,
    2, 4, 6,
    1, 4, 0,
    4, 1, 5,
    6, 5, 7,
    5, 6, 4,
    3, 6, 7,
    6, 3, 2,
    5, 3, 7,
    3, 5, 1
  };

  kvs::Vector3f p0( 1, 1, 1 );
  p0.normalize( );
  std::cout << p0 << std::endl;
  
  // Vectorコンテナに格納
  std::vector<kvs::Real32>coords( vertex, vertex + 24 );
  std::vector<kvs::UInt32>connects( tri, tri + 36 );
  std::vector<kvs::UInt8>colors( vertCol, vertCol + 24 );
  std::vector<kvs::Real32>normals( norm, norm + 24 );
 
  // ポリゴンオブジェクトの作成
  kvs::PolygonObject* object = new kvs::PolygonObject( );
  object->setCoords( kvs::ValueArray<kvs::Real32>( coords ) );
  object->setConnections( kvs::ValueArray<kvs::UInt32>( connects ) );
  object->setColors( kvs::ValueArray<kvs::UInt8>( colors ) ); 
  object->setOpacity( 255 );
  object->setNormals( kvs::ValueArray<kvs::Real32>( normals ) );
  object->setPolygonType( kvs::PolygonObject::Triangle );            //  PolygonType
  object->setColorType( kvs::PolygonObject::VertexColor );         // ColorType
  object->setNormalType( kvs::PolygonObject::VertexNormal );      // NormalType  
  // 頂点の最大値と最小値を計算
  object->updateMinMaxCoords();

  // windowの初期化
  kvs::Application app( argc, argv );
  // Screenクラスの生成と設定
  kvs::Screen screen( &app );
  screen.registerObject( object );
  screen.setGeometry( 0, 0, 512, 512 );
  screen.setTitle( "Polygon");
  screen.show();
  // イベント待ち
  return( app.run() );   
}

