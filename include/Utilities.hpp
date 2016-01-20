/*
Copyright 2014 Alberto Crivellaro, Ecole Polytechnique Federale de Lausanne (EPFL), Switzerland.
alberto.crivellaro@epfl.ch

terms of the GNU General Public License as published by the Free Software
Foundation; either version 2 of the License, or (at your option) any later
version.

This program is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
this program; if not, write to the Free Software Foundation, Inc., 51 Franklin
Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef UTLITIES_HPP_
#define UTLITIES_HPP_

#include <vector>
#include <string>

#include "Typedefs.hpp"
#include <fstream>
#include <iostream>
#include "Homography.hpp"
#include <sstream>
#include <vector>

using namespace cv;
using namespace std;

//dense descriptors utilities
void ComputeGradientBasedDescriptorFields(Mat &grayscaleImage, vector<Mat> &outDescriptorFields);
void ComputeGradientMagnitudeDescriptorFields(Mat &grayscaleImage, vector<Mat> &outDescriptorFields);
void ComputeImageIntensityDescriptorFields(Mat &grayscaleImage, vector<Mat> &outDescriptorFields);
vector<Mat> SmoothDescriptorFields(const float sigma,const vector<Mat> & descriptorFields);


// control points grids utilities 
StructOfArray2di CreateGridOfControlPoints(Mat & image,uint nPoints, float widthBorderThickness, float heightBorderThickness);
StructOfArray2di CreateAnisotropicGridOfControlPoints(Mat & image, uint nPoints, float widthBorderThickness = 0., float heightBorderThickness = 0.);
StructOfArray2di CreateDenseGridOfControlPoints(uint width, uint height);
StructOfArray2di GetRectangleCornersForAugmentation(OptimizationParameters* optimizationParameters, int width, int height);

void WarpGridOfControlPoints(const StructOfArray2di & pixelsOnTemplate, StructOfArray2di & pixelsOnTemplateWarped, const vector<float> & parameters, const int width, const int height);
inline cv::Matx33f GetScalingMatrix()
{
	float scalex = (MAX_SCALING - MIN_SCALING)/(PICTURE_WIDTH);
	float scaley = (MAX_SCALING - MIN_SCALING)/(PICTURE_HEIGHT);
	return cv::Matx33f(scalex, 0, MIN_SCALING, 0, scaley, MIN_SCALING, 0, 0, 1);
}


//image acquisition and filtering utilities
void AcquireVGAGrayscaleImage(VideoCapture &capture, Mat &outGrayImage, Mat &outRGBImage);
void AcquireVGAGrayscaleImage(VideoCapture &capture, Mat &outGrayImage);
void ConvertImageToFloat(Mat & image);
Mat SmoothImage(const float sigma, const Mat & im);
void ComputeImageDerivatives(const Mat & image, Mat & imageDx, Mat &imageDy);
void NormalizeImage(Mat &image);


//IO files utilities
vector<Point2f> ReadArrayOf2dPoints(const char* fileName);
vector<float> ReadArrayOfFloats(const char* fileName);
vector<vector<float> > ReadMatrixOfFloats(const char* fileName);
Mat ReadGrayscaleImageFile(const char* fileName, uint nRows, uint nCols);
void LoadImage(const char* fileName, Mat &image);
OptimizationParameters ReadOptimizationParametersFromXML(const char* fileName);
void WritePixelsOnTxtFile(const StructOfArray2di & pixels, const char* fileName);


//Visualization utilities
void ShowConvergenceResults(Mat & templ, Mat &image,  vector<vector<float> > &intermediateGuess);
void ShowDetailedOptimizationResults(const AlignmentResults & results, vector<float> parametersBaseline);
void ShowConvergenceResults(Mat & templ, Mat &image, vector<vector<float> > &intermediateGuess, StructOfArray2di panelCorners);
void AugmentFrameWithQuadrilater(string windowName, const StructOfArray2di & panelCorners, Mat& frame);
void AugmentFrameWithQuadrilater(const StructOfArray2di & warpedPixels, Mat& frame);
void WriteResultsOnImage(Mat & image, const AlignmentResults & results, int pixelsNumber, OptimizationType optimizationType);
void operator<<( std::ostream& os, const OptimizationType& optimizationType );
void CheckMatrixForNans(Eigen::MatrixXf & aMatrix);

#endif /* UTLITIES_HPP_*/
