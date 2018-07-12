#include "brfv4/BRFManager.hpp"
#include "brfv4/image/BRFBitmapData.hpp"

#include "opencv2/opencv.hpp"

#include "brfv4/opencv3/CameraUtils.hpp"
#include "brfv4/opencv3/DrawingUtils.hpp"
#include "brfv4/opencv3/Stats.hpp"

#include "brfv4/utils/BRFv4PointUtils.hpp"
#include "brfv4/utils/BRFv4ExtendedFace.hpp"

#include "brfv4/examples/Basic_Example.hpp"

// +++ basic face detection

//#include "brfv4/examples/face_detection/detect_in_whole_image.hpp"
//#include "brfv4/examples/face_detection/detect_in_center.hpp"
//#include "brfv4/examples/face_detection/detect_smaller_faces.hpp"
//#include "brfv4/examples/face_detection/detect_larger_faces.hpp"

// +++ basic - face tracking +++

#include "brfv4/examples/face_tracking/track_single_face.hpp"
//#include "brfv4/examples/face_tracking/track_multiple_faces.hpp"
//#include "brfv4/examples/face_tracking/candide_overlay.hpp"

// +++ basic - point tracking +++

//#include "brfv4/examples/point_tracking/track_multiple_points.hpp"
//#include "brfv4/examples/point_tracking/track_points_and_face.hpp"

// +++ intermediate - face tracking +++

//#include "brfv4/examples/face_tracking/restrict_to_center.hpp"
//#include "brfv4/examples/face_tracking/extended_face_shape.hpp"
//#include "brfv4/examples/face_tracking/smile_detection.hpp"
//#include "brfv4/examples/face_tracking/yawn_detection.hpp"
//#include "brfv4/examples/face_tracking/png_mask_overlay.hpp"			// not implemented
//#include "brfv4/examples/face_tracking/color_libs.hpp"

// +++ advanced - face tracking +++

//#include "brfv4/examples/face_tracking/blink_detection.hpp"
//#include "brfv4/examples/face_tracking/ThreeJS_example.hpp"			// not implemented
//#include "brfv4/examples/face_tracking/face_texture_overlay.hpp"		// not implemented
//#include "brfv4/examples/face_tracking/face_swap_two_faces.hpp"		// not implemented

static int _imageDataWidth  = 640;	// default: landscape camera 640x480
static int _imageDataHeight = 480;

int main() {
    
    brf::trace("init app ...");
    
    brf::CameraUtils camUtils(_imageDataWidth, _imageDataHeight, true);
    
    if(!camUtils.init()) {
        brf::trace("No Camera found ...");
        return -1;
    }
    
    cv::namedWindow("main", cv::WINDOW_OPENGL);
    
    brf::Stats _stats;
    brf::BRFCppExample example;
    
    example.init(camUtils.cameraWidth, camUtils.cameraHeight, brf::ImageDataType::U8_BGR);
    
    cv::Mat& draw = example._drawing.graphics;
    cv::resizeWindow("main", draw.cols, draw.rows);
    
    brf::trace("execute app ...");
    
    
    while (true) {
        
        if(camUtils.update()) {
            camUtils.cameraData.copyTo(draw);
            example.update(camUtils.cameraData.data);
        }
        
        _stats.update();
        _stats.render(draw);
        
        cv::imshow("main", draw);
        
        int key = cv::waitKey(1);
        
        if (key == 27) { // 27 == ESC
            break;
        } else if(key == 114) { // 114 == R
            example.reset();
        } else if(key != -1) {
            //			brf::trace("key: " + brf::to_string(key));
        }
    }
    
    brf::trace("dispose app ...");
    
    example.dispose();
    
    brf::trace("close app ...");
    
    return 0;
}
