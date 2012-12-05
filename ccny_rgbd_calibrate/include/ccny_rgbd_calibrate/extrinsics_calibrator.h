#ifndef CCNY_RGBD_CALIBRATE_EXTRINSICS_CALIBRATOR_H
#define CCNY_RGBD_CALIBRATE_EXTRINSICS_CALIBRATOR_H

#include <ros/ros.h>
#include <tf/transform_listener.h>
#include <boost/filesystem.hpp>
#include <sensor_msgs/Image.h>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/io/pcd_io.h>

#include "ccny_rgbd_calibrate/calib_util.h"

namespace ccny_rgbd
{

class ExtrinsicsCalibrator
{
  public:

    ExtrinsicsCalibrator(ros::NodeHandle nh, ros::NodeHandle nh_private);
    virtual ~ExtrinsicsCalibrator();

  private:

    ros::NodeHandle nh_;
    ros::NodeHandle nh_private_;

    // parameters
    double square_size_;
    int n_cols_;
    int n_rows_;
       
    // directories & filenames
    std::string path_;
    std::string train_path_;
    std::string test_path_;

    std::string calib_rgb_filename_;
    std::string calib_ir_filename_;
    std::string calib_extr_filename_;

    std::string rgb_test_filename_;
    std::string depth_test_filename_;   
    std::string cloud_filename_;
    
    // calibration variables    
    cv::Size patternsize_;
    
    std::vector<cv::Point3f> corners_3d_;
    
    cv::Mat intr_rgb_, intr_ir_;
    cv::Mat dist_rgb_, dist_ir_;
       
    cv::Mat intr_rect_rgb_, intr_rect_ir_;
    
    cv::Mat map_rgb_1_, map_rgb_2_;
    cv::Mat map_ir_1_,  map_ir_2_;
    
    cv::Mat ir2rgb_;
    
    void calibrate();
    void build3dCornerVector();
    void buildRectMaps();
    bool loadCameraParams();
 
    void testExtrinsicCalibration();
    
    bool loadCalibrationImagePair(
      int idx,
      cv::Mat& rgb_img,
      cv::Mat& ir_img);
};

} //namespace ccny_rgbd

#endif // CCNY_RGBD_CALIBRATE_EXTRINSICS_CALIBRATOR_H
