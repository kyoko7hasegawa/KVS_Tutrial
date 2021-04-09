#include <kvs/Vector3>
#include <kvs/AVSField>
#include <kvs/StructuredVolumeObject>
#include <kvs/StructuredVolumeExporter>  

inline float func( float x, float y, float z) {
  return ( 3.0 - x*x - y*y - 4.0*z*z );
}

int main( int argc, char** argv )
{
  // グリッドサイズ
  kvs::UInt32 gridNum = 64;
  std::cin >> gridNum; 
  const kvs::Vector3ui resol(gridNum, gridNum, gridNum);
  // ボリュームデータの値を格納するためのメモリの割り当て
  kvs::ValueArray<float> data( gridNum * gridNum * gridNum );

  // dataにを操作するためのポインタ変数
  float* pdata = data.data();  

  float min = -2.0, max = 2.0;
  float dt = (float)(max - min)/(float)(gridNum-1);

  kvs::UInt64 index = 0;
  for(int k=0; k< gridNum; k++) {
    for(int j = 0; j<gridNum; j++) {
      for(int i=0; i<gridNum; i++) {
	float x = (float)min + (float)i*dt; 	
	float y = (float)min + (float)j*dt; 
	float z = (float)min + (float)k*dt; 
	// 関数値を評価してdataへ格納
	pdata[ index++ ] =  func(x, y, z) ;
      }
    }
  }

  size_t vecren = 1;		// 各要素のデータ数の設定
  // 構造型ボリュームデータの生成
  kvs::StructuredVolumeObject *volume = 
    new kvs::StructuredVolumeObject ( );
  volume->setGridType( kvs::StructuredVolumeObject::Uniform );
  volume->setResolution( resol );
  volume->setVeclen( vecren );
  volume->setValues( data );    
  
  // データをAVSFieldにExport
  kvs::AVSField* field2 =
    new kvs::StructuredVolumeExporter<kvs::AVSField>( volume );
  if( !field2 ) {
    kvsMessageError( "Cannot export Resized volume data." );
    delete volume;
    return (false);
  }
  // ファイルへ出力
  if ( !field2->write( "test.fld" ) ) {
    kvsMessageError( "Cannot write to the file as AVS field format." );
    delete volume;
    return( false );
  }    

  return ( 0 );

 }
