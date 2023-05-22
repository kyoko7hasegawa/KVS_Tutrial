/*
 KVS Tutrial サンプルプログラム
 行列クラス

 */

#include <kvs/Matrix33>
#include <kvs/Vector3>

int main ()
{
  // 値を指定しない（初期値には０がはいる）
  kvs::Matrix33f A;  
  std::cout << "Matix A \n" << A << std::endl;
  A[0][0] = 1.0;   A[0][1] = 1.0;   A[0][2] = 3.0;
  A[1][0] = 4.0;   A[1][1] = 1.0;   A[1][2] = 0.0;
  A[2][0] = 2.0;   A[2][1] = 0.0;   A[2][2] = 2.0;

  // 成分を１つ１つ記述する
  kvs::Matrix33f B( 1.0, 2.0, 0.0, 
		    2.0, 2.0, 1.0,
		    0.0, 1.0, 3.0 );
  std::cout << "Matrix B \n" << B << std::endl;
  
  // 3次元ベクトルを３つ並べる
  kvs::Vector3f v0( 1.0, 1.0, 1.0 );
  kvs::Vector3f v1( 2.0, 2.0, 1.0 );
  kvs::Vector3f v2( 1.0, 2.0, 4.0 );
  kvs::Matrix33f C( v0, v1, v2 );
  std::cout << "Matrix C \n" << C << std::endl;

  // 配列を代入する
  float elem[9] = { 1.0, 2.0, 3.0,
                    4.0, 5.0, 6.0,
                    7.0, 8.0, 9.0 };
  kvs::Matrix33f D( elem );
  std::cout << "Matrix D \n" << D << std::endl;
  
  // 値を代入する
  A.set( 1.0, 2.0, 2.0,
 	 2.0, 2.0, 1.0,
	 0.0, 1.0, 3.0 );
  std::cout << "A set 1 \n" << A << std::endl;
  A.set( v0, v1, v2 );
  std::cout << "A set 2 \n" << A << std::endl;
  A.set( elem );
  std::cout << "A set 3 \n" << A << std::endl;

  //値を取得する
  std::cout << "get element : " << A[0][0] << " " << A[0][1] << " " << A[0][2] << std::endl;
  float a11 = A[1][1];
  std::cout << "A11 : " << a11 << std::endl; 

  // 全要素のクリア
  std::cout << "------ Setting All Elements -----" << std::endl;
  B.setZero();   // 全要素を 0 にする
  std::cout << B << std::endl;
  std::cout << "------" << std::endl;
  B.setOnes();   // 全要素を 1 にする
  std::cout << B << std::endl;
  std::cout << "------" << std::endl;
  B.setIdentity();  // 単位行列にする
  std::cout << B << std::endl;
  std::cout << "------" << std::endl;
  B.setConstant( 5.0 );  // 全要素を 5.0 にする
  std::cout << B << std::endl;
  std::cout << "------" << std::endl;
  B.setDiagonal( 2.0 );   // 全対角要素が 2 となる
  std::cout << B << std::endl;
  std::cout << "------" << std::endl;
  kvs::Vector3f diag( 1.0, 2.0, 3.0 );
  B.setDiagonal( diag );   // 対角要素に diag の成分が設定される
  std::cout << B << std::endl;
  std::cout << "------" << std::endl;
  B.setRandom();   // 全要素に乱数が設定される．

  // 静的メンバ関数
  std::cout << "==== Static member ========" << std::endl;
  std::cout << kvs::Matrix33f::Zero() << std::endl;
  C = kvs::Matrix33f::Ones();
  std::cout << C<< std::endl;
  C = kvs::Matrix33f::RotationX( 90 );
  std::cout << C << std::endl;
  std::cout << "------" << std::endl;
  std::cout << kvs::Matrix33f::RotationX( 90 ) << std::endl;
  
  // 転置行列
  std::cout << "----- transposed -----" << std::endl; 
  // 自身に上書き
  A.transpose();
  std::cout << "Transposed A \n" << A << std::endl;
  // 転置行列を返す（自身に上書きしない）
  std::cout << "Matrix B \n" << B << std::endl;
  // For version 1.0 --> 2.0
  //  const kvs::Matrix33f E = static_cast<const kvs::Matrix33f>( B ).transpose();
  kvs::Matrix33f E = B.transposed();
  std::cout << "Matrix B \n" << B << std::endl;
  std::cout << "Transposed B \n" << E << std::endl;

  // 逆行列
  std::cout << "----- inverse -----" << std::endl; 
  // 自身に上書き
  // For version 1.0 --> 2.0  
  //  C.inverse();
  C.invert();
  std::cout << "Inverse C \n" << C << std::endl;
  // 逆行列を返す（自身に上書きしない）
  std::cout << "Matrix B \n" << B << std::endl;
  kvs::Matrix33f F = B.inverted();
  std::cout << "Matrix B \n" << B << std::endl;
  std::cout << "Inverse B \n" << F << std::endl;

  // trace, determinant
  std::cout << "A \n" << A << std::endl;  
  std::cout << "Trace : " << A.trace() << std::endl;
  std::cout << "Determinant : " << A.determinant() << std::endl;

  //---- 行列の性質を確認する
  // 対称行列かどうか？
  if( A.isSymmetric() ) {
    std::cout << "この行列は対角行列です" << std::endl;
  }
  // 対角行列かどうか
  if( !A.isDiagonal() ) {
    std::cout << "この行列は対角行列ではありません" << std::endl;
  }
  
  // 四則演算
  std::cout << "----- Operator + -----" << std::endl; 
  std::cout << "Matrix A \n" << A << std::endl;
  std::cout << "Matrix B \n" << B << std::endl;
  C = A+B;
  std::cout << "A+B \n" << C << std::endl;
  A+=C;
  std::cout << "A+=C \n" << A << std::endl;  

  std::cout << "----- Operator - -----" << std::endl; 
  A -=  B;
  std::cout << "A-= B \n" << A << std::endl;
  std::cout << "-A \n" << -A << std::endl;  

  std::cout << "----- Operator * -----" << std::endl; 
  int i = 10;
  std::cout << "i : " << i << std::endl;
  A*=B;
  std::cout << "A*=B : \n" <<  A << std::endl;
  C = i*B;
  std::cout << "i*B : \n" << C << std::endl;;
  C = B*i;
  std::cout << "C = B*i : \n" << C << std::endl;;
  C*=i;
  i*=C;  // <-- Error
  std::cout << "C*=i : \n" << C << std::endl;;
  // 行列とベクトルのかけ算
  A.set( 1, 1, 1,  1, 1, 1,  2, 2, 2);
  v0.set( 1, 1, 1);
  kvs::Vector3f x = v0*A;
  std::cout << "v0*A : \n" << x << std::endl;;
  x = A*v0;
  std::cout << "A*v0 : \n" << x << std::endl;;

  std::cout << "----- Operator / -----" << std::endl; 
  D = C/i; 
  std::cout << "D = C/i : " << D << std::endl;;
  C /= i;
  std::cout << "C/=i : " << C << std::endl;;
  D = i/C;    // <--Error
  i/=C;       // <--Error


  // 値が等しいかどうか
  if( A == B ) {
    std::cout << "A == B"  << std::endl; }
  else if( A != B ) {
    std::cout << "A != B"  << std::endl; } 

  return 0;  
}
