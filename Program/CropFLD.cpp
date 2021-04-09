#include <cstdlib>
#include <kvs/MersenneTwister>
#include <kvs/TrilinearInterpolator>
#include <kvs/IgnoreUnusedVariable>
#include <kvs/AnyValueArray>
// For compiled version 1.0 & 2.0
#include <kvs/Version>

#include "CropFLD.h"

CropFLD::CropFLD(
		 const kvs::VolumeObjectBase* ORGvolume,
		 const kvs::Vector3ui grid_min,
		 const kvs::Vector3ui grid_max ):
  m_grid_min( grid_min ),
  m_grid_max( grid_max )
{

  this->cropVolume( ORGvolume );
}

void CropFLD::cropVolume(const kvs::VolumeObjectBase* ORGvolume) 
{
  
  if ( ORGvolume->volumeType() == kvs::VolumeObjectBase::Structured )
    {
      // Down Cast Pointer from SuperClass
      const kvs::StructuredVolumeObject* structured_volume =
	kvs::StructuredVolumeObject::DownCast( ORGvolume );
            
      const std::type_info& type = structured_volume->values().typeInfo()->type();
      if (      type == typeid( kvs::Int8   ) ) 
	this->extract<kvs::Int8>( structured_volume );
      else if ( type == typeid( kvs::Int16  ) ) 
	this->extract<kvs::Int16>( structured_volume );
      else if ( type == typeid( kvs::Int32  ) ) 
	this->extract<kvs::Int32>( structured_volume );
      else if ( type == typeid( kvs::Int64  ) ) 
	this->extract<kvs::Int64>( structured_volume );
      else if ( type == typeid( kvs::UInt8  ) ) 
	this->extract<kvs::UInt8>( structured_volume );
      else if ( type == typeid( kvs::UInt16 ) ) 
	this->extract<kvs::UInt16>( structured_volume );
      else if ( type == typeid( kvs::UInt32 ) ) 
	this->extract<kvs::UInt32>( structured_volume );
      else if ( type == typeid( kvs::UInt64 ) ) 
	this->extract<kvs::UInt64>( structured_volume );
      else if ( type == typeid( kvs::Real32 ) ) 
	this->extract<kvs::Real32>( structured_volume );
      else if ( type == typeid( kvs::Real64 ) ) 
	this->extract<kvs::Real64>( structured_volume );
      else
        {
	  kvsMessageError("Unsupported data type '%s'.", structured_volume->values().typeInfo()->typeName() );
        }
    }
  else // volume->volumeType() == kvs::VolumeObjectBase::Unstructured
    {
        kvsMessageError("Input volume is unStructured");
	return;
    }  

}

//-----------------------------------------------------------------------
// 
//-----------------------------------------------------------------------
template <typename T>
void CropFLD::extract(const kvs::StructuredVolumeObject* ORGvolume)
{
  SuperClass::setGridType( ORGvolume->gridType() );
  SuperClass::setVeclen( ORGvolume->veclen() );

  /*  Resolution of Original Volume Data */
  const kvs::Vector3ui ORGncells(ORGvolume->resolution());  
  const kvs::UInt64 ORGdim1 = static_cast<kvs::UInt64>( ORGncells.x() );
  const kvs::UInt64 ORGdim2 = static_cast<kvs::UInt64>( ORGncells.y() );
  const kvs::UInt64 ORGdim3 = static_cast<kvs::UInt64>( ORGncells.z() );

  kvs::Vector3ui resol;
  kvs::UInt64 nx, ny, nz;
  
  //----- New Grid Size 
  nx = m_grid_max.x() - m_grid_min.x() ;
  ny = m_grid_max.y() - m_grid_min.y() ;
  nz = m_grid_max.z() - m_grid_min.z() ;
  resol.set( nx, ny, nz);
  SuperClass::setResolution( resol );
  
  // const T* const ORGdata = reinterpret_cast<const T*>( ORGvolume->values().pointer() );
  const T* const ORGdata = reinterpret_cast<const T*>( ORGvolume->values().data() );

  //  kvs::UInt64 line_size  = static_cast<kvs::UInt64>(ORGvolume->nnodesPerLine());
  //  kvs::UInt64 slice_size = static_cast<kvs::UInt64>(ORGvolume->nnodesPerSlice());  
  kvs::UInt64 line_size  = static_cast<kvs::UInt64>(ORGvolume->numberOfNodesPerLine());
  kvs::UInt64 slice_size = static_cast<kvs::UInt64>(ORGvolume->numberOfNodesPerSlice());  
  
  kvs::UInt32 ORGindex;

  //----- Memory Allocation 
  /*  if ( !data.allocate<T>( ORGdim1 * ORGdim2 * ORGdim3 ) ) {
    kvsMessageError("Cannot allocate memory for the data.");
    exit(1);
    }*/
  kvs::ValueArray<T> data( ORGdim1 * ORGdim2 * ORGdim3 );
  //----- Pointer Setting to data
  //T* pdata = data.pointer<T>();    
  T* pdata = data.data();    
  //---- Setting Data to New FLD Data from Original Data
  kvs::UInt64 index = 0;
  for(kvs::UInt64 k = m_grid_min.z(); k < m_grid_max.z(); k++) {
    for(kvs::UInt64 j = m_grid_min.y(); j < m_grid_max.y(); j++) {
      for(kvs::UInt64 i = m_grid_min.x(); i < m_grid_max.x(); i++ ) {
	ORGindex = (i + j * line_size + k * slice_size); // Index Number of Original Volume Data
	pdata[ index++ ] = ORGdata[ORGindex];		      // Add to Data for New FLD-Data
      }
    }  
  }
  SuperClass::setValues( kvs::AnyValueArray( data ) );  
  SuperClass::updateMinMaxCoords();

}

CropFLD::~CropFLD( void )
{
}

CropFLD::CropFLD( void )
{
}
