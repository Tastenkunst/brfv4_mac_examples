#ifndef __brf__CameraUtils_hpp
#define __brf__CameraUtils_hpp

namespace brf {

class CameraUtils {

	public: unsigned int cameraWidth;
	public: unsigned int cameraHeight;

	public: bool doMirror;

	public: cv::VideoCapture camera;
	public: cv::Mat cameraData;

	public: CameraUtils(
			unsigned int cameraWidth,
			unsigned int cameraHeight,
			bool doMirror = true) :

		cameraWidth(cameraWidth),
		cameraHeight(cameraHeight),
		doMirror(doMirror),

		camera(), // cv::CAP_ANY -> default device
		cameraData(cameraHeight, cameraWidth, CV_8UC3)
	{
	}

	public: virtual ~CameraUtils() {
		dispose();
	}

	public: bool init() {

        camera.open(1);

		if(!camera.isOpened()) {	// check if we succeeded
			return false;
		} else {
			camera.set(cv::CAP_PROP_FRAME_WIDTH,  (double)(cameraWidth));
			camera.set(cv::CAP_PROP_FRAME_HEIGHT, (double)(cameraHeight));
			camera.set(cv::CAP_PROP_FPS, 30.0);
			return true;
		}
	}

	public: bool update() {
		if(camera.read(cameraData)) {
			if(doMirror) { cv::flip(cameraData, cameraData, 1); }
			return true;
		} else {
			return false;
		}
	}

	public: void dispose() {
		if(camera.isOpened()) {
			camera.release();
		}
	}
};

}

#endif // __brf__CameraUtils_hpp
