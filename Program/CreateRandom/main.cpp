#include <iostream>
#include <kvs/MersenneTwister>
#include <kvs/BoxMuller>

int main( void )
{
  kvs::MersenneTwister uniRand;	// 一様乱数
  kvs::BoxMuller normRand;	// 正規乱数

  std::cout << "[0, 1] : 一様乱数 " << uniRand() << std::endl;
  std::cout << "N(0, 1) : 正規乱数 " << normRand() << std::endl;

  // 種をセットする
  kvs::MersenneTwister uniRand2( 261422 ); // 一様乱数
  kvs::BoxMuller normRand2( 261422 );      // 正規乱数
  std::cout << "[0, 1] : 一様乱数 " << uniRand2() << std::endl;
  std::cout << "N(0, 1) : 正規乱数 " << normRand2() << std::endl;

  // 乱数の分布を変更する
  std::cout << "[0, 100] : 一様乱数 " << uniRand.rand( 100 ) << std::endl;
  std::cout << "N(2, 10) : 正規乱数 " << normRand.rand(2, 10) << std::endl;


  // 乱数の試行回数
  const int trialNum = 1000;
  
  // 円内に発生した点の数を数える
  int num = 0;

  // 平均と標準偏差を求めるための初期値
  double uniAve = 0.0, uniDp = 0.0;
   
  for( int i=0; i<trialNum; i++ ) {

    // [0, 1] 内で乱数を生成
    double x = uniRand();
    double y = uniRand();

    // x*x + y*y < 1 内に生成された点の数を数える
    if( ( x*x + y*y ) < 1.0 ) 
      num++;
    
    // 和と2乗和を計算
    uniAve += x;
    uniDp += ( x * x );
  }

  // 円周率を求める
  double pi = (double)num/(double)trialNum * 4.0;
  std::cout << num << " " << trialNum << std::endl;
  std::cout << "円周率 : " << pi << std::endl;

  //  平均と標準偏差をもとめる
  uniAve /= (double)trialNum;
  uniDp = uniDp/(double)trialNum - uniAve*uniAve;

  std::cout << "-- 一様乱数 -- " << std::endl;;
  std::cout << "平均 : " << uniAve << "  標準偏差 : " << uniDp << std::endl;

  return ( 0 );
}
