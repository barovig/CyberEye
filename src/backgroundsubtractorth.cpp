#include "backgroundsubtractorth.h"

void BackgroundSubtractorTH::setHighThreshold(float scale)
{
	IhiF = IavgF + (IdiffF * scale);
	cv::split( IhiF, Ihi );	
}

void BackgroundSubtractorTH::setLowThreshold(float scale)
{
	IlowF = IavgF - (IdiffF * scale);
	cv::split( IlowF, Ilow );	
}

void BackgroundSubtractorTH::AllocateImages(const cv::Mat &I)
{
	cv::Size sz = I.size();
	
	IavgF = cv::Mat::zeros( sz, CV_32FC3 );

	IdiffF = cv::Mat::zeros( sz, CV_32FC3 );
	IprevF = cv::Mat::zeros( sz, CV_32FC3 );
	IhiF = cv::Mat::zeros( sz, CV_32FC3 );
	IlowF = cv::Mat::zeros( sz, CV_32FC3 );
	Icount = 0.00001;
	
	tmp = cv::Mat::zeros( sz, CV_32FC3 );
	tmp2 = cv::Mat::zeros( sz, CV_32FC3 );
	Imaskt = cv::Mat::zeros( sz, CV_32FC3 );	
}

void BackgroundSubtractorTH::accumulateBackground(cv::Mat &I)
{
	static int first = 1;
	I.convertTo( tmp, CV_32F );
	if( !first ){
		IavgF += tmp;
		cv::absdiff( tmp, IprevF, tmp2 );
		IdiffF += tmp2;
		Icount += 1.0;
	}
	first = 0;
	IprevF = tmp;	
}

void BackgroundSubtractorTH::createModelsfromStats()
{
	IavgF *= (1.0/Icount);
	IdiffF *= (1.0/Icount);
	// Make sure diff is always something
	//
	IdiffF += cv::Scalar( 1.0, 1.0, 1.0 );
	setHighThreshold( 7.0 );
	setLowThreshold( 6.0 );	
}

void BackgroundSubtractorTH::backgroundDiff(cv::Mat &I, cv::Mat &Imask)
{
	I.convertTo( tmp, CV_32FC1 );
	// To float
	cv::split( tmp, Igray );
	// Channel 1
	//
	cv::inRange( Igray[0], Ilow[0], Ihi[0], Imask );
	// Channel 2
	//
	cv::inRange( Igray[1], Ilow[1], Ihi[1], Imaskt );
	Imask = cv::min( Imask, Imaskt );
	// Channel 3
	//
	cv::inRange( Igray[2], Ilow[2], Ihi[2], Imaskt );
	Imask = cv::min( Imask, Imaskt );
	// Finally, invert the results
	//
	Imask = 255 - Imask;
}

BackgroundSubtractorTH::BackgroundSubtractorTH()
{
	
}

void BackgroundSubtractorTH::apply(cv::InputArray image, cv::OutputArray fgmask, double learningRate)
{
	cv::Mat im = image.getMat();
	cv::Mat fgm = fgmask.getMat();
	backgroundDiff(im, fgm);
}

void BackgroundSubtractorTH::getBackgroundImage(cv::OutputArray backgroundImage) const
{
	
}
