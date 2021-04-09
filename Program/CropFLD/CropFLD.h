#ifndef _CropFLD_H_
#define _CropFLD_H_

#include <kvs/VolumeObjectBase>
#include <kvs/StructuredVolumeObject>
#include <kvs/AnyValueArray>
#include <kvs/Vector3>


class CropFLD : public kvs::StructuredVolumeObject
{
  kvs::Vector3ui m_grid_min;
  kvs::Vector3ui m_grid_max;
  
   typedef kvs::StructuredVolumeObject SuperClass;
   //   kvs::AnyValueArray data;

 public:
   CropFLD( const kvs::VolumeObjectBase* volume,
	    const kvs::Vector3ui grid_min,
	    const kvs::Vector3ui grid_max );

   virtual ~CropFLD( void );

 private:
   void cropVolume( const kvs::VolumeObjectBase* volume );

   template <typename T>
   void  extract(
		 const kvs::StructuredVolumeObject* volume );

 private:
   CropFLD( void );
      
};

#endif

