#include <iostream>
#include <itkImage.h>
#include <itkImageFileWriter.h>
#include <itkImageRegionIterator.h>
#include <itkRGBPixel.h>

int main( int argc, char * argv[] )
{
  //Define the ring
  typedef itk::RGBPixel<unsigned char> RGBPixelType;
  typedef itk::Image<RGBPixelType, 2> ImageType;
  ImageType::Pointer oneRing = ImageType::New();
  ImageType::IndexType oneRingStart = {0, 0};
  ImageType::SizeType oneRingSize = {500, 500};
  ImageType::RegionType oneRingRegion;
  oneRingRegion.SetIndex(oneRingStart);
  oneRingRegion.SetSize(oneRingSize);
  oneRing->SetRegions(oneRingRegion);
  
  //Not illustrated
  //ImageType::PointType oneRingOrigin;
  //oneRingOrigin[0] = 0.0;
  //oneRingOrigin[1] = 0.0;
  //oneRing->SetOrigin(oneRingOrigin);
  //ImageType::SpacingType oneRingSpacing;
  //oneRingSpacing[0] = 1.0;
  //oneRingSpacing[1] = 1.0;
  //oneRing->SetSpacing(oneRingSpacing);
  
  oneRing->Allocate();
   
  
  //Forge the ring
  int externalOneRingRadius = 200;
  int internalOneRingRadius = 150;
  ImageType::IndexType oneRingCenter = {250, 250};
  
  typedef itk::ImageRegionIterator<ImageType> IteratorType;
  IteratorType it(oneRing, oneRing->GetLargestPossibleRegion());
  for (it.GoToBegin(); !it.IsAtEnd(); ++it)
    {
    ImageType::IndexType currentIndex = it.GetIndex();
    
    int xDist = currentIndex[0] - oneRingCenter[0];
    int yDist = currentIndex[1] - oneRingCenter[1];
    
    if (xDist*xDist + yDist*yDist > internalOneRingRadius*internalOneRingRadius
        && xDist*xDist + yDist*yDist < externalOneRingRadius*externalOneRingRadius)
      {
      RGBPixelType goldColor;
      goldColor[0] = 255;
      goldColor[1] = 235;
      goldColor[2] = 0;

      it.Set(goldColor);
      }
    }
    
  //Take it out
  typedef itk::ImageFileWriter<ImageType> WriterType;
  WriterType::Pointer mountDoom = WriterType::New();
  mountDoom->SetInput(oneRing);
  mountDoom->SetFileName("./OneRing.png");
  mountDoom->Update();
  
  return EXIT_SUCCESS;
}